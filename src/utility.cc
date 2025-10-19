#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pkmn-yellow.h"

extern uchar save_file[0x8000];

bool read_save_file(char *path) {
   FILE *stream = fopen(path, "rb");

   if(stream == NULL) {
      perror(__func__);
      exit(1);
   }

   size_t sz = fread(save_file, 1, 0x8000, stream);

   if(sz != 0x8000) {
      return false;
   }

   fclose(stream);

   return true;
}

bool lies_between(uchar test, uchar low, uchar high, bool inclusive) {
   if(inclusive) {
      return (test >= low && test <= high);
   } else {
      return (test >  low && test <  high);
   }
}
