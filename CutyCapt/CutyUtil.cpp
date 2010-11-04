// Dave Sinkula

#include "CutyUtil.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

// unlike atoi(), CustomAtoi will tell you if something went wrong during conversion
int CutyUtil::CustomAtoi(char *s, int *value){
   if ( s != NULL && *s != '\0' && value != NULL )
   {
       char *endptr = s;
       *value = (unsigned int)strtol(s, &endptr, 10);
       if ( *endptr == '\0' )
       {
           return 1;
       }
   }
   return 0; /* failed to convert string to integer */
}
