#include "../include/driver.h"

static void
timer_handler(union sigval sv) 
{
    struct driver *drv = (struct driver *)sv.sival_ptr;
    drv->stat = AVAILABLE;
}

void
handle_driver(struct driver *driver) 
{    
    signal(SIGPIPE, SIG_IGN);
    struct driver *drv = driver;

    int epoll_fd;
    struct epoll_event event, events[MAX_EVENTS];     

    struct sigevent sev;
    struct itimerspec ts;
    
    close(drv->pip_cli[PIP_RD]);
    close(drv->pip[PIP_WR]);
    
    if ((epoll_fd = epoll_create1(0)) == -1)
       errExit("epoll_create1");
    

    event.events = EPOLLIN;
    event.data.fd = drv->pip[PIP_RD];
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, drv->pip[PIP_RD], &event) == -1)
       errExit("epoll_ctl");
    
    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = timer_handler;
    sev.sigev_value.sival_ptr = drv;
    sev.sigev_notify_attributes = NULL;
    if (timer_create(CLOCK_REALTIME, &sev, &drv->timer) == -1)
       errExit("timer_create");
    
    while (1) {
        if (epoll_wait(epoll_fd, events, MAX_EVENTS, -1) == -1) {
           if (errno == EINTR) continue;
           errExit("epoll_wait");
        }
       
        struct command cmd;
        char msg[MAX_MSG];
        
        if (read(drv->pip[PIP_RD], &cmd, sizeof(cmd)) == -1) {
           if (errno == EINTR) continue;
           errExit("read");
        }

       if (drv->stat == AVAILABLE) {
          if (cmd.type == SND_TSK) {
              drv->stat = BUSY; 
              ts.it_value.tv_sec = cmd.timer;
              ts.it_value.tv_nsec = 0;
              ts.it_interval.tv_sec = 0;
              ts.it_interval.tv_nsec = 0;

              if (timer_settime(drv->timer, 0, &ts, NULL) == -1)
                 errExit("timer_settime");
              
              snprintf(msg, sizeof(msg), "Driver %d is busy for %d seconds\n", getpid(), cmd.timer);
              write(drv->pip_cli[PIP_WR], msg, strlen(msg));
          }
          
          else if (cmd.type == GET_STAT) {
              sprintf(msg, "Driver %d: Available\n", getpid());
              write(drv->pip_cli[PIP_WR], msg, strlen(msg));
          }

       } else {
           time_t remaining = 0;
           if (timer_gettime(drv->timer, &ts) == 0) {
              remaining = ts.it_value.tv_sec;
           }

           sprintf(msg, "Driver %d: Busy [%ld seconds remaining]\n", getpid(), remaining); 
           write(drv->pip_cli[PIP_WR], msg, strlen(msg));
        }
  }
}
