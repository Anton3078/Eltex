#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "midnight_commander.h"


void read_dir(const char *path, struct File_st *files, int *count) {
    struct dirent **namelist;
    struct stat st;
    int n = scandir(path, &namelist, NULL, alphasort);

    if (n == -1) {
        *count = 0;
        perror("scandor");
        exit(EXIT_FAILURE);
    }

    *count = 0;
    while (n--) {

        if (*count >= MAX_FILES) {
            free(namelist[n]);
            continue;
        }

        strncpy(files[*count].name, namelist[n]->d_name, MAX_FILENAME - 1);
        if (stat(namelist[n]->d_name, &st) == 0 && S_ISREG(st.st_mode)) {
            files[*count].size = st.st_size;
        }
        files[*count].is_dir = (namelist[n]->d_type == DT_DIR);
        (*count)++;
        free(namelist[n]);
    }
    free(namelist);
}
