#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "mid_command.h"

void
read_dir(const char *path, struct File_st *files, int *count) {
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
        
        char full_path[MAX_FILENAME * 2];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, namelist[n]->d_name);

        strncpy(files[*count].name, namelist[n]->d_name, MAX_FILENAME - 1);
        
        if (stat(full_path, &st) == 0) {
            files[*count].size = S_ISREG(st.st_mode) ? st.st_size : 0;
            files[*count].is_dir = S_ISDIR(st.st_mode);
        } else {
            files[*count].size = 0;
            files[*count].is_dir = 0;
        }
        /*
        if (stat(namelist[n]->d_name, &st) == 0 && S_ISREG(st.st_mode)) {
            files[*count].size = st.st_size;
        }
        files[*count].is_dir = (namelist[n]->d_type == DT_DIR);
        */
        (*count)++;
        free(namelist[n]);
    }
    free(namelist);
}
