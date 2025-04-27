#include "../../include/msg_queue.h"

WINDOW *chat_win, *users_win, *input_win;

void* 
receive_messages(void *arg) 
{/*поток читающий из личной очереди сообщений*/
    mqd_t mqdes_usr = *((mqd_t *)arg);
    struct DataChat client_data = {0}; 

    while (1) {
        struct Message msg;
        if (mq_receive(mqdes_usr, (char *)&msg, sizeof(msg), NULL) == -1) {
            perror("mq_receive");
            continue;
        }
        
        switch (msg.type) {
            case CHAT_MSG:
                wprintw(chat_win, "%s: %s\n", msg.sender, msg.mtext);
                break;
                
            case USER_JOIN:
                add_user(msg.sender, &client_data);
                wprintw(chat_win, "[+] %s joined\n", msg.sender);
                break;
                
            case USER_LEAVE:
                remove_user(msg.sender, &client_data);
                wprintw(chat_win, "[-] %s left\n", msg.sender);
                break;
                
            case INIT_HISTORY:
                wprintw(chat_win, "[History] %s: %s\n", msg.sender, msg.mtext);
                break;
            
            case INIT_USERS:
                add_user(msg.sender, &client_data);
                break;

            default:
                continue;
        }
        
        werase(users_win);
        box(users_win, 0, 0);
        mvwprintw(users_win, 0, 1, " Users (%d) ", client_data.usr_count);
        
        for (int i = 0; i < client_data.usr_count; ++i) {
            mvwprintw(users_win, i + 1, 1, "%s", client_data.act_usrs[i]);
        }
        
        wrefresh(chat_win);
        wrefresh(users_win);
    }
}

int 
main() 
{
    mqd_t mqdes_usr, mqdes_client;
    char client_queue[32];
   
    char user_name[MAX_USR_NAME];
    char input[MAX_MSG_LEN];

    if ((mqdes_usr = mq_open(PATH_QUEUE_USR, O_RDWR)) == -1) {
        perror("mq_open (server)");
        exit(EXIT_FAILURE);
    }

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE); 

    chat_win = newwin(LINES - 3, COLS * 2 / 3, 0, 0);
    users_win = newwin(LINES - 3, COLS / 3, 0, COLS * 2 / 3);
    input_win = newwin(3, COLS, LINES - 3, 0);
    
    wbkgd(chat_win, COLOR_PAIR(1));
    wbkgd(users_win, COLOR_PAIR(1));
    wbkgd(input_win, COLOR_PAIR(1));
    box(chat_win, 0, 0);
    box(users_win, 0, 0);
    box(input_win, 0, 0);
    mvwprintw(chat_win, 0, 1, " Chat ");
    mvwprintw(users_win, 0, 1, " Users ");
    mvwprintw(input_win, 0, 1, " Input ");
    wrefresh(chat_win);
    wrefresh(users_win);
    wrefresh(input_win);

    echo();
    mvwprintw(input_win, 1, 1, "Enter your name: ");
    wgetnstr(input_win, user_name, MAX_USR_NAME);
    noecho();

    struct Message join_msg = {.type = USER_JOIN};
    strncpy(join_msg.sender, user_name, MAX_USR_NAME);
    mq_send(mqdes_usr, (char *)&join_msg, sizeof(join_msg), 0);

    sleep(1);

    snprintf(client_queue, sizeof(client_queue), "/mq_%s", user_name);
    if ((mqdes_client = mq_open(client_queue, O_RDWR)) == -1) {
        perror("mq_open (client)");
        mq_close(mqdes_usr);
        endwin();
        exit(EXIT_FAILURE);
    }
    
    pthread_t thread;
    pthread_create(&thread, NULL, receive_messages, &mqdes_client);

    while (1) {
        werase(input_win);
        box(input_win, 0, 0);
        mvwprintw(input_win, 1, 1, "> ");
        wrefresh(input_win);
        
        echo();
        wgetnstr(input_win, input, MAX_MSG_LEN);
        noecho();

        if (strcmp(input, "exit") == 0) {
            struct Message leave_msg = {.type = USER_LEAVE};
            strncpy(leave_msg.sender, user_name, MAX_USR_NAME);
            mq_send(mqdes_usr, (char *)&leave_msg, sizeof(leave_msg), 0);
            break;
        }

        struct Message msg = {.type = CHAT_MSG};
        strncpy(msg.sender, user_name, MAX_USR_NAME);
        strncpy(msg.mtext, input, MAX_MSG_LEN);
        if (mq_send(mqdes_usr, (char *)&msg, sizeof(msg), 0) == -1) {
            perror("mq_send");
        }
    }

    endwin();
    mq_close(mqdes_usr);
    mq_close(mqdes_client);
    mq_unlink(client_queue);
    exit(EXIT_SUCCESS);
}
