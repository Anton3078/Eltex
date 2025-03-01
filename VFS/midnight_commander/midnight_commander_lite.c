#include <sys/ioctl.h>
#include <stdlib.h>
#include <ncurses.h>
#include <termios.h>
#include <signal.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "midnight_commander.h"

void sig_winch(int sigon) {
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *)&size);
    resizeterm(size.ws_row, size.ws_col);
}

int main (int argc, char **argv) {

    struct File_st left_panel[MAX_FILES];
    struct File_st right_panel[MAX_FILES];

    int is_left = 1;

    int left_wnd_num, right_wnd_num = 0;
    int left_wnd_pos, right_wnd_pos = 0;

    char path_left_panel[MAX_FILENAME] = {"."};
    char path_right_panel[MAX_FILENAME] = {"."};

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
                        char new_path[MAX_FILENAME];
                        snprintf(new_path, MAX_FILENAME, "%s", new_file->name);

                        char full_path[MAX_FILENAME];

                        if (realpath(new_path, full_path)) {
                            struct stat st;

                            if (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode)) {
                                strncpy(path_left_panel, full_path, MAX_FILENAME);
                                left_wnd_num = 0;
                                read_dir(path_left_panel, left_panel, &left_wnd_num);
                                left_wnd_pos = 0;
                            }
                        }
                    }
                } else {
                    struct File_st *new_file = &right_panel[right_wnd_pos];

                    if (new_file->is_dir) {
                        char new_path[MAX_FILENAME];
                        snprintf(new_path, MAX_FILENAME, "%s", new_file->name);
                        char full_path[MAX_FILENAME];

                        if (realpath(new_path, full_path)) {
                            struct stat st;

                            if (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode)) {
                                strncpy(path_right_panel, full_path, MAX_FILENAME);
                                right_wnd_num = 0;
                                read_dir(path_right_panel, right_panel, &right_wnd_num);
                                right_wnd_pos = 0;
                            }
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
