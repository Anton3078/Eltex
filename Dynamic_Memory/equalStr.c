#include "equalStr.h"

int equals_str(char *fin_name, char *name) {
  
     int flag = 1;
  
     while(*fin_name) {
  
         if (*fin_name == *name) {
             ++fin_name;
             ++name;
         } else {
             flag = 0;
             break;
         }
     }
  
     if (flag) {
         return 1;
     } else {
         return 0;
     }
 }

