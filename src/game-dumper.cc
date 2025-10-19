#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef unsigned char uchar;
typedef unsigned int uint;

unsigned char *save_file;

bool read_rom_file(char *path) {
   FILE *stream = fopen(path, "rb");
   size_t sz = fread(save_file, 1, 0x100000, stream);

   if(sz != 0x100000) {
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

/*
 * Convert characters to their ASCII equivalents.
 */
uchar pkmn_to_ascii_char(uchar pkmn_char) {
   return pkmn_char - 0x3f;
}

int main(int argc, char **argv, char **envp) {
   if(argc != 2) {
      fprintf(stderr, "usage: %s rom.sgb\n", argv[0]);
      return 1;
   }

   save_file = (unsigned char*) malloc(0x100000);

   if(save_file == NULL)
      return 3;

   if(!read_rom_file(argv[1])) {
      fprintf(stderr, "failed reading input file %s\n", argv[1]);
      return 2;
   }

   printf("Offset |  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F | ASCII Output\n");

   for(uint i = 0x0; i < 0x100000; i += 0x10) {
      printf("0x%04X | ", i);
      
      for(uint j = 0x0; j < 0x10; j++) {
	 printf("%02x ", save_file[i + j]);
      }

      printf("| ");

      for(uint j = 0x0; j < 0x10; j++) {
	 if(lies_between(save_file[i + j], 0x80, 0x99, true) ||
	    lies_between(save_file[i + j], 0xA0, 0xB9, true))
	    printf("%c", pkmn_to_ascii_char(save_file[i+j]));
	 else
	    printf(".");
      }

      printf("\n");
   }

   printf("Offset |  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F | ASCII Output\n");

   return 0;
}
