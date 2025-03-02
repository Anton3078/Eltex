#include <stdlib.h>
#include "midnight_commander.h"

void draw_panel(WINDOW *wnd, struct File_st *files, int count, int pos, int is_act, const char *title) {
    werase(wnd);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    box(wnd, '|', '=');
    wbkgd(wnd, COLOR_PAIR(1));
    mvwprintw(wnd, 0, 2, "%s", title);

    for (int i = 0; i < count; i++) {
        if (i == pos && is_act) {
            wattron(wnd, A_REVERSE | A_BLINK);
        } else if (i == pos) {
            wattron(wnd, A_REVERSE);
        }

        if (files[i].is_dir) {
            mvwprintw(wnd, i + 1, 1, "%s\t%s", files[i].name, "[DIR]");
        }
        else {
            mvwprintw(wnd, i + 1, 1, "%s\t%d", files[i].name, files[i].size);
        }

        if (i == pos && is_act) {
            wattroff(wnd, A_REVERSE | A_BLINK);
        } else if (i == pos) {
            wattroff(wnd, A_REVERSE);
        }
    }
    wrefresh(wnd);

}
