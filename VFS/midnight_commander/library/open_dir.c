#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "mid_command.h"

void
open_dir (char path_panel[MAX_FILENAME], struct File_st panel[MAX_FILES], struct File_st *new_file, int *wnd_num, int* wnd_pos) {
        /*Открывает директорию*/
        char new_path[MAX_FILENAME];
        snprintf(new_path, MAX_FILENAME * 2, "%s/%s", path_panel, new_file->name);
        char full_path[MAX_FILENAME];

        if (realpath(new_path, full_path)) {
                struct stat st;

                if (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode)) {
                        strncpy(path_panel, full_path, MAX_FILENAME);
                        *wnd_num = 0;
                        read_dir(path_panel, panel, wnd_num);
                        *wnd_pos = 0;
        }
    }
}
