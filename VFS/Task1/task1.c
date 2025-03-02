#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_BUFF 20

int main(void) {

    FILE *fd;
    char *buff = (char *) malloc(50 *  sizeof(char));
    int ch;
    int i = 0;
    char rev_str[50];
    int num_rev_str = 0;
    long int fl_size;

    printf("Enter string: ");
    while ((ch = getchar()) != '\n' && ch != EOF) {
        buff[i++]  = ch;
    }
    
    buff[i] = '\0';
    
    fd = fopen("output.txt", "w+");

    if (fd == NULL) {
       fprintf(stderr, "Error of opening file\n");
       free(buff);
       exit(EXIT_FAILURE);
    }
    
    fprintf(fd, "%s", buff);
    fflush(fd);
    fl_size = ftell(fd);
    

    for (long j = 1; j <= fl_size; j++) {
        fseek(fd, -j, SEEK_END);
        rev_str[num_rev_str++] = fgetc(fd);
    }
    rev_str[num_rev_str] = '\0';

    printf("%s\n", rev_str);


    fclose(fd);
    free(buff);

    exit(EXIT_SUCCESS);
}
