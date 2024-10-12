
#include <iostream>

char *get_string(int *len) {
   *len = 0;
   int capacity = 1;
   char *s = (char*) malloc(sizeof(char));
   char c = getchar();
   while (c != '\n') {
       s[(*len)++] = c;
       if (*len >= capacity) {
           capacity *= 2;
           s = (char*) realloc(s, capacity * sizeof(char));
       }
       c = getchar();
   }
   s[*len] = '\0';
   return s;
}
