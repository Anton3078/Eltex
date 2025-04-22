#include "../../include/msg_queue.h"

WINDOW *chat_win, *users_win, *input_win;
char active_users[MAX_USR][MAX_USR_NAME];
int user_count = 0;

// Поток для получения сообщений
void* 
receive_messages(void *arg) {
    mqd_t mqdes_msg = *((mqd_t *)arg);

    while (1) {
        struct Message msg;
        if (mq_receive(mqdes_msg, (char *)&msg, sizeof(msg), NULL) == -1) {
            perror("mq_receive");
            continue;
        }

        // Обновление чата
        wprintw(chat_win, "%s: %s\n", msg.user, msg.mtext);
        wrefresh(chat_win);

        // Перерисовка списка пользователей
        if (msg.type == USER_JOIN || msg.type == USER_LEAVE) {

            if (msg.type == USER_JOIN) add_user(msg.user, active_users, &user_count);
            else remove_user(msg.user, active_users, &user_count);

            werase(users_win);
            box(users_win, 0, 0);
            mvwprintw(users_win, 0, 1, " Users ");

            for (int i = 0; i < user_count; ++i) {
                mvwprintw(users_win, i + 1, 1, "%s", active_users[i]);
            }
            wrefresh(users_win);
        }
    }
    return NULL;
}

int 
main() {
    mqd_t mqdes_usr, mqdes_msg;

    // Подключение к очередям
    mqdes_usr = mq_open(PATH_QUEUE_USR, O_RDWR);
    mqdes_msg = mq_open(PATH_QUEUE_MSG, O_RDWR);

    // Инициализация ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE); 

    // Создание окон
    chat_win = newwin(LINES - 3, COLS * 2 / 3, 0, 0);
    users_win = newwin(LINES - 3, COLS / 3, 0, COLS * 2 / 3);
    input_win = newwin(3, COLS, LINES - 2, 0);
    
    // После создания окон
    werase(chat_win);
    werase(users_win);
    werase(input_win);
    
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

    // Поток для приема сообщений
    pthread_t thread;
    pthread_create(&thread, NULL, receive_messages, &mqdes_msg);

    // Ввод имени пользователя
    char user_name[MAX_USR_NAME];
    echo();
    mvwprintw(input_win, 1, 1, "Enter your name: ");
    wgetnstr(input_win, user_name, MAX_USR_NAME);
    noecho();

    // Отправка сообщения о входе
    struct Message join_msg = {.type = USER_JOIN};
    strncpy(join_msg.user, user_name, MAX_USR_NAME);
    strncpy(join_msg.mtext, "User join chat", MAX_MSG_LEN);

    mq_send(mqdes_usr, (char *)&join_msg, sizeof(join_msg), 0);
    //strncpy(active_users[user_count++], join_msg.user, MAX_USR_NAME);

    // Основной цикл
    char input[MAX_MSG_LEN];
    while (1) {
        werase(input_win);
        mvwprintw(input_win, 1, 1, "> ");
        wrefresh(input_win);
        echo();
        wgetnstr(input_win, input, MAX_MSG_LEN);
        noecho();
        struct Message msg;

        if (strcmp(input, "exit") == 0) {
           msg.type = USER_LEAVE;
           strncpy(msg.user, user_name, MAX_USR_NAME);
           strncpy(msg.mtext, "user leave from chat", MAX_MSG_LEN);
           mq_send(mqdes_usr, (char *)&msg, sizeof(msg), 0);
           break;
        }

        msg.type = CHAT_MSG;
        strncpy(msg.user, user_name, MAX_USR_NAME);
        strncpy(msg.mtext, input, MAX_MSG_LEN);
        mq_send(mqdes_usr, (char *)&msg, sizeof(msg), 0);
    }

    // Завершение
    endwin();
    mq_close(mqdes_usr);
    mq_close(mqdes_msg);
    return 0;
}

