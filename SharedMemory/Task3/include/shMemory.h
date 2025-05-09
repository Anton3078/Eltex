#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <pthread.h>
#include <ncurses.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define PATH_KEY_SHM "/dev/shm/my_shm_key"
#define PATH_KEY_SEM "/dev/shm/my_sem_key"
#define KEY_SEM_CLIENT "/dev/shm/client_sem_key"
#define PROJ_SHM_ID 'A'
#define PROJ_SEM_ID 'S'
#define PROJ_SEM_CLID 'D'

#define MAX_MSG_LEN 1024
#define MAX_MSG 24
#define MAX_USR 2
#define MAX_USR_NAME 16

#define SEM_ACCESS 0
#define SEM_NOTIFY 1

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE);} while(0)

enum MsgType 
{ /* Типы сообщений */
    USER_JOIN,    // Новый пользователь
    CHAT_MSG,     // Обычное сообщение
    USER_LEAVE,   // Выход пользователя
};

struct Message 
{ /* Структура сообщений */ 
    enum MsgType type;              // Тип сообщения
    char sender[MAX_USR_NAME];      // Имя отправителя
    char mtext[MAX_MSG_LEN];        // Текст сообщения
};

struct DataChat 
{ /* Состояние чата на сервере */
    char act_usrs[MAX_USR][MAX_USR_NAME]; // Активные пользователи
    int usr_count;                        // Количество пользователей
    struct Message msg_hist[MAX_MSG];     // История сообщений
    int msg_count;                        // Счётчик сообщений
};

/* добавление новых пользователей в структуру чата*/
void add_user(const char *, struct DataChat *);             

/* удаление пользователя из  чата*/
void remove_user(const char *, struct DataChat *);

/* рассылка сообщений в общий чата*/
void broadcast(mqd_t, struct Message *, struct DataChat *);

/* одиночная рассылка (история чата/активные пользователи)*/
void send_init_data(mqd_t, struct DataChat *, const char *);

#endif
