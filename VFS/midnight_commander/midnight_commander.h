#ifndef _MID_NIGTH_CM_
#define _MID_NIGTH_CM_

#include <ncurses.h>

#define MAX_FILES 50
#define MAX_FILENAME 384

struct File_st {
    char name[MAX_FILENAME];
    int is_dir;
    unsigned short size;

};

void read_dir(const char *path, struct File_st *files, int *count);
void draw_panel(WINDOW *wnd, struct File_st *files, int count, int pos, int is_act, const char *title);
#endif
