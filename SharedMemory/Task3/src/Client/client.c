#include "../../include/shMemory.h"

WINDOW *chat_win, *users_win, *input_win;
int semid;
char user_name[MAX_USR_NAME];

void* 
receive_messages(void *arg) 
{
    struct DataChat *chat = (struct DataChat *)arg;

    struct sembuf lock[1] = {{SEM_ACCESS, -1, 0}};
    struct sembuf unlock[1] = {{SEM_ACCESS, 1, 0}};

    while (1) {
        semop(semid, lock, 1);

        werase(chat_win);
        box(chat_win, 0, 0);
        mvwprintw(chat_win, 0, 1, " Chat (%s) ", user_name);
        
        int total_messages = (chat->msg_count > MAX_MSG) ? MAX_MSG : chat->msg_count;
        for (int i = 0; i < total_messages; ++i) {
            int msg_idx = (chat->msg_count - total_messages + i) % MAX_MSG;
            struct Message *msg = &chat->msg_hist[msg_idx];

            switch (msg->type) {
                case CHAT_MSG:
                    mvwprintw(chat_win, i + 1, 1, "%s: %s", msg->sender, msg->mtext);
                    break;
                         
                case USER_JOIN:
                    mvwprintw(chat_win, i + 1, 1, "[+] %s joined", msg->sender);
                    break;
                         
                case USER_LEAVE:
                    mvwprintw(chat_win, i + 1, 1, "[-] %s left", msg->sender);
                    break;

                default:
                    continue;
            }
        }
        werase(users_win);
        box(users_win, 0, 0);
        mvwprintw(users_win, 0, 1, " Users (%d) ", chat->usr_count);
        
        for (int i = 0; i < chat->usr_count; ++i) {
            mvwprintw(users_win, i + 1, 1, "%s", chat->act_usrs[i]);
        }
        
        wrefresh(chat_win);
        wrefresh(users_win);
        
        semop(semid, unlock, 1);
        sleep(1);
    }
}

int 
main() 
{
    char input[MAX_MSG_LEN];
    
    key_t key, keySem;
    struct DataChat *chat;
    int shmid;

    struct sembuf lock[1] = {{SEM_ACCESS, -1, 0}};
    struct sembuf unlock[1] = {{SEM_ACCESS, 1, 0}};
    struct sembuf wait_msg[1] = {{SEM_NOTIFY, 1, 0}};

    /* Initialize ncurses */
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
    ///////////////////////////////////////////////////////////////

    echo();
    mvwprintw(input_win, 1, 1, "Enter your name: ");
    wgetnstr(input_win, user_name, MAX_USR_NAME);
    noecho();

    if ((key = ftok(PATH_KEY_SHM, PROJ_SHM_ID)) == -1)
       errExit("ftok");
    
    if ((keySem = ftok(PATH_KEY_SEM, PROJ_SEM_ID)) == -1)
       errExit("ftok");

    if ((shmid = shmget(key, 0, 0660)) == -1)
       errExit("shmget");

    if ((chat = (struct DataChat *) shmat(shmid, NULL, 0)) == (void *)-1)
       errExit("shmat");
    
    if ((semid = semget(keySem, 0, 0660)) == -1 )
       errExit("semget"); 
    
    pthread_t thread;
    pthread_create(&thread, NULL, receive_messages, chat);

    struct Message join_msg = {.type = USER_JOIN};
    strncpy(join_msg.sender, user_name, MAX_USR_NAME);

    semop(semid, lock, 1);
    if (chat->usr_count < MAX_USR) {
       chat->msg_hist[chat->msg_count++] = join_msg;
       add_user(join_msg.sender, chat);
    } else {
       endwin();
       shmdt(chat);
       printf("Chat room overflow\n");
       semop(semid, unlock, 1);
       semop(semid, wait_msg, 1);
       exit(EXIT_SUCCESS);
    }
    semop(semid, unlock, 1);
    semop(semid, wait_msg, 1);

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
            semop(semid, lock, 1);
            chat->msg_hist[chat->msg_count++] = leave_msg;
            remove_user(leave_msg.sender, chat);
            semop(semid, unlock, 1);
            semop(semid, wait_msg, 1);
            break;
        }

        struct Message msg = {.type = CHAT_MSG};
        strncpy(msg.sender, user_name, MAX_USR_NAME);
        strncpy(msg.mtext, input, MAX_MSG_LEN);
        
        semop(semid, lock, 1);
        if (chat->msg_count < MAX_MSG) {
           chat->msg_hist[chat->msg_count++] = msg;
        } else {
            for (int i = 0; i < MAX_MSG - 1; i++) {
                chat->msg_hist[i] = chat->msg_hist[i + 1];
            }
            chat->msg_hist[MAX_MSG - 1] = msg;
        }
        semop(semid, unlock, 1);
        semop(semid, wait_msg, 1);
    }

    endwin();
    shmdt(chat);
    exit(EXIT_SUCCESS);
}
