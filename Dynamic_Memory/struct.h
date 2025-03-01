#ifndef _ABONENT_H_
#define _ABONENT_H_



struct abonent {
    char name[10];
    char second_name[10];
    char tel[10];
    struct abonent* prevP;
    struct abonent* nextP;
};

#endif
