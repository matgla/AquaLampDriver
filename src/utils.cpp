#include "utils.hpp"


/*
** reverse string in place 
*/
void reverse(char *s) {
char *j;
int c;
 
  j = s + strlen(s) - 1;
  while(s < j) {
    c = *s;
    *s++ = *j;
    *j-- = c;
  }
}

char getNumber(int n){
  if(n>9) {
    return n-10+'a';
  } else {
    return n+'0';
  }
}

namespace utils
{
void itoa(int n, char * s, int base_n)
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = getNumber(n % base_n);   /* get next digit */
     } while ((n /= base_n) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }
}

 

 void DelayS(u32 time) {
   for(int i = 0; i < 1000; i++) {
    for (int j = 0; j < time * 100; j++) {}
   }
 }