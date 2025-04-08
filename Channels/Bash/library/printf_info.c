#include <stdio.h>
#include <limits.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>

void
printf_info()
{
    char hostname[32];
    char cwd[PATH_MAX];
    char *username;

    struct passwd *pwd = getpwuid(getuid());
    username = pwd->pw_name;
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        perror("gethostname");
        strcpy(hostname, "None");
    }

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        strcpy(cwd, "???");
    }

    printf("%s@%s:%s$ ", username, hostname, cwd);
    fflush(stdout);
}
