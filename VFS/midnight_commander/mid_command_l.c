#include <sys/ioctl.h>
#include <stdlib.h>
#include <termios.h>
#include <signal.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "library/mid_command.h"
#include <unistd.h>
#include <sys/wait.h>

void 
sig_winch(int sigon) {
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *)&size);
    resizeterm(size.ws_row, size.ws_col);
    clear();
    refresh();
}



int 
main (int argc, char **argv) {
    
    pid_t child_pid, stat;

    struct File_st left_panel[MAX_FILES];
    struct File_st right_panel[MAX_FILES];

    int is_left = 1;

    int left_wnd_num, right_wnd_num = 0;
    int left_wnd_pos, right_wnd_pos = 0;

    char path_left_panel[MAX_FILENAME] = {"."};
    char path_right_panel[MAX_FILENAME] = {"."};
    
    if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
       perror("signal");
       exit(EXIT_FAILURE); 
    }

    initscr();
    signal(SIGWINCH, sig_winch);
    curs_set(0);
    cbreak();
    noecho();
    keypad(stdscr, 1);

    refresh();

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    WINDOW *left_wnd = newwin(max_y - 4, max_x / 2 - 1, 1, 1);
    WINDOW *right_wnd = newwin(max_y - 4, max_x / 2 - 1, 1, max_x / 2 + 1);

    read_dir(path_left_panel, left_panel, &left_wnd_num);
    read_dir(path_right_panel, right_panel, &right_wnd_num);

    int ch;
    while ((ch = getch()) != 'q') {
        def_prog_mode();

        switch (ch) {
            case KEY_UP:
                if (is_left) {
                    if (left_wnd_pos > 0) left_wnd_pos--;
                } else {
                    if (right_wnd_pos > 0) right_wnd_pos--;
                }
                break;
            case KEY_DOWN:
                if (is_left) {
                    if (left_wnd_pos < left_wnd_num - 1) left_wnd_pos++;
                } else {
                    if (right_wnd_pos < right_wnd_num - 1) right_wnd_pos++;
                }

                break;
            case '\t':
                if (is_left) {
                    is_left = 0;
                } else {
                    is_left = 1;
                }
                break;

            case '\n':

                if (is_left) {
                    struct File_st *new_file = &left_panel[left_wnd_pos];

                    if (new_file->is_dir) {
                        fexecut(path_left_panel, left_panel, new_file, &left_wnd_num, &left_wnd_pos);
                    } else {
                          child_pid = fork();
                          
                          switch (child_pid) {
                              case -1:
                                  perror("fork");
                                  exit(EXIT_FAILURE);
                            
                              case 0:
                                  char file_path[MAX_FILENAME * 2];
                                  snprintf(file_path, sizeof(file_path), "%s/%s", path_left_panel, new_file->name);
                                  endwin();
                                  execlp("vim", "vim", file_path, (char *) NULL);
                                  exit(EXIT_FAILURE);
                            
                              default:
                                  wait(&stat);
                                  
                                  reset_prog_mode();
                                  refresh();

                                  touchwin(stdscr);
                                  wrefresh(stdscr);
                                  touchwin(left_wnd);
                                  wrefresh(left_wnd);
                                  touchwin(right_wnd);
                                  wrefresh(right_wnd);  
                                  
                                  read_dir(path_left_panel, left_panel, &left_wnd_num);
                                  read_dir(path_right_panel, right_panel, &right_wnd_num);
 
                                  draw_panel(left_wnd, left_panel, left_wnd_num, left_wnd_pos, 1 == is_left, "Left Panel");
                                  draw_panel(right_wnd, right_panel, right_wnd_num, right_wnd_pos, 0 == is_left, "Right Panel");
                        }              
                    } 
                } else {
                    struct File_st *new_file = &right_panel[right_wnd_pos];

                    if (new_file->is_dir) {
                       fexecut(path_right_panel, right_panel, new_file, &right_wnd_num, &right_wnd_pos);
                    } else {
                        child_pid = fork();
                        
                        switch (child_pid) {
                            case -1:
                                perror("fork");
                                exit(EXIT_FAILURE);
                            
                            case 0:
                                char file_path[MAX_FILENAME * 2];
                                snprintf(file_path, sizeof(file_path), "%s/%s", path_right_panel, new_file->name); 
                                endwin();
                                execlp("vim", "vim", file_path, (char *) NULL);
                                exit(EXIT_FAILURE);
                            
                            default:
                                wait(&stat);
                                
                                reset_prog_mode();
                                clearok(stdscr, TRUE);
                                refresh();

                                touchwin(stdscr);
                                wrefresh(stdscr);
                                touchwin(left_wnd);
                                wrefresh(left_wnd);
                                touchwin(right_wnd);
                                wrefresh(right_wnd);
                                
                                read_dir(path_left_panel, left_panel, &left_wnd_num);
                                read_dir(path_right_panel, right_panel, &right_wnd_num);
                                
                                draw_panel(left_wnd, left_panel, left_wnd_num, left_wnd_pos, 1 == is_left, "Left Panel");
                                draw_panel(right_wnd, right_panel, right_wnd_num, right_wnd_pos, 0 == is_left, "Right Panel");
                        }              
                    }
                }

                break;
        }
    
        draw_panel(left_wnd, left_panel, left_wnd_num, left_wnd_pos, 1 == is_left, "Left Panel");
        draw_panel(right_wnd, right_panel, right_wnd_num, right_wnd_pos, 0 == is_left, "Right Panel");
    }

    endwin();
    exit(EXIT_SUCCESS);
}
