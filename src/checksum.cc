/*
 * Checksumming functions.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pkmn-yellow.h"

extern uchar save_file[0x8000];

static ushort start = 0x2598;
static ushort end   = 0x3522;

uchar get_checksum() {
   return save_file[0x3523];
}

bool verify_checksum() {
   uchar my_cksum = 0;
   uchar file_cksum = get_checksum();
   
// Add all the bytes from the start to end addresses above.
   for(int i = start; i <= end; i++) {
      my_cksum += save_file[i];
   }

// Invert the bits.
   my_cksum ^= 0xFF;

// Do they match what's in the save file?
   return file_cksum == my_cksum;
}
