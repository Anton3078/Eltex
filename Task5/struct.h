#define N 100

struct abonent {
    char name[10];
    char second_name[10];
    char tel[10];
};

void Add(struct abonent **, short *);
void Remove(struct abonent **, short *);
void Find(struct abonent [N]);
void GetAll(struct abonent [N]);
