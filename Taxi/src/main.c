#include "../include/cli_utils.h"
#include "../include/driver.h"

int
main(void) 
{
    char *argV[5];
    char command[30] = {0};
    
    struct driver drivers[MAX_DRIVERS];
    int dr_count = 0;
    
    while(1) {
        struct command cmd = {0};
        
        printf("TAXI@Managment:CLI@Tools$ ");
        read_command(command);
        
        if (strncmp(command, "exit", 4) == 0)
            break;
     
        get_tokens(argV, command);

        if (strcmp(argV[0], "create_driver") == 0) { 
            if (dr_count >= MAX_DRIVERS) {
                printf("Maximum number of drivers reached\n");
                continue;
            }
            

            if (pipe(drivers[dr_count].pip) == -1 || pipe(drivers[dr_count].pip_cli) == -1) {
                error("pipe");
                continue;
            }

            if ((drivers[dr_count].pid = fork()) == -1) {
                error("fork");
                continue;
            }

            if (drivers[dr_count].pid == 0) {
                drivers[dr_count].stat = AVAILABLE;
                handle_driver(&drivers[dr_count]);
                exit(EXIT_FAILURE);
            } else {
                close(drivers[dr_count].pip[PIP_RD]);
                close(drivers[dr_count].pip_cli[PIP_WR]);

                printf("Driver created with PID: %d\n", drivers[dr_count].pid);
                dr_count++;
            }
        }
        
        else if (strcmp(argV[0], "send_task") == 0 && argV[1] && argV[2]) {
            if (dr_count == 0) {
               printf("No drivers available\n");
               continue;
            }
            
            pid_t pid_v = atoi(argV[1]);
            int timer_v = atoi(argV[2]);
            
            if (timer_v <= 0) {
                printf("Error: Timer value must be positive\n");
                continue;
            }
            
            int fg = 0;
            for (int i = 0; i < dr_count; i++) {
                if (drivers[i].pid == pid_v) {
                    fg = 1;
                    break;
                }
            }
            
            if (!fg) {
                printf("Error: not found driver with PID - %d\n", pid_v);
                continue;
            }

            cmd.type = SND_TSK;
            cmd.pid = pid_v;
            cmd.timer = timer_v;
            send_command(drivers, &dr_count, &cmd);
            get_response(drivers, &dr_count, &cmd); 
        }
        
        else if (strcmp(argV[0], "get_status") == 0 && argV[1]) {
            pid_t pid_v = atoi(argV[1]);
            int fg = 0;
            
            for (int i = 0; i < dr_count; i++) {
                if (drivers[i].pid == pid_v) {
                    fg = 1;
                    break;
                }
            }
            
            if (!fg) {
                printf("Error: not found driver with PID - %d\n", pid_v);
                continue;
            }
            
            cmd.type = GET_STAT;
            cmd.pid = atoi(argV[1]);
            send_command(drivers, &dr_count, &cmd);
            get_response(drivers, &dr_count, &cmd);
        }

        else if (strcmp(argV[0], "get_drivers") == 0) {
            for (int i = 0; i < dr_count; i++) {
                cmd.type = GET_STAT;
                cmd.pid = drivers[i].pid;
                send_command(drivers, &dr_count, &cmd);
                get_response(drivers, &dr_count, &cmd);
            }
        }

        else {
            printf("Unknown command: %s\n", command);
        }
    }

    for (int i = 0; i < dr_count; i++) {
        kill(drivers[i].pid, SIGTERM);
        close(drivers[i].pip[PIP_WR]);
        close(drivers[i].pip_cli[PIP_RD]);
        waitpid(drivers[i].pid, NULL, 0);
    }

    exit(EXIT_SUCCESS);
}
