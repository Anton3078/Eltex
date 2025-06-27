#include "../include/driver.h"

int
send_command(struct driver *drvs, int *dr_count, struct command *cmd)
{
   int i;
   for (i = 0; i < *dr_count; ++i) {
       if (drvs[i].pid == cmd->pid) {
          write(drvs[i].pip[PIP_WR], cmd, sizeof(*cmd));
          break;          
       }
   }
   return 0; 
}

int
get_response(struct driver *drvs, int *dr_count, struct command *cmd)
{
   int i;
   char msg[MAX_MSG] = {0};
   ssize_t numByte;
   for (i = 0; i < *dr_count; i++) {
       if (drvs[i].pid == cmd->pid) {
          if((numByte = read(drvs[i].pip_cli[PIP_RD], msg, sizeof(msg))) > 0) {
            printf("%s", msg);
          }
          break;          
       }
   }
   return 0; 
}

