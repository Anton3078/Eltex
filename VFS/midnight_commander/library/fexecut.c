#include "mid_command.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void
fexecut (struct File_st *new_file, char path_panel[MAX_FILENAME]) {
    /*Открывает файл в vim*/
    pid_t child_pid, stat;

    if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
       perror("signal");
       exit(EXIT_FAILURE);
    }

    child_pid = fork();

    switch (child_pid) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);

        case 0:
            char file_path[MAX_FILENAME * 2];
            snprintf(file_path, sizeof(file_path), "%s/%s", path_panel, new_file->name);
            endwin();
            execlp("vim", "vim", file_path, (char *) NULL);
            exit(EXIT_FAILURE);

        default:
            wait(&stat);

            reset_prog_mode();
            clearok(stdscr, TRUE);
            refresh();



        }
}
