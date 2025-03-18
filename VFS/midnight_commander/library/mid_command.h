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

void read_dir(const char *, struct File_st *, int *);
void draw_panel(WINDOW *, struct File_st *, int, int, int, const char *);
void fexecut(char [MAX_FILENAME], struct File_st [MAX_FILES], struct File_st *, int*, int*);
#endif
