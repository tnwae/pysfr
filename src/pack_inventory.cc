/*
 * Functions for dealing with party pokemon.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pkmn-yellow.h"

extern uchar save_file[0x8000];

static ushort beginning_offset = 0x25CA;

uint read_pack_inv_size() {
   uchar sz = save_file[0x25C9];
   return (uint) sz;
}

pack_item::pack_item(uint off) {
   uint offset = beginning_offset + 2 * off;
      
   this->quantity = save_file[offset + 1];
   this->id = save_file[offset];
}

void pack_item::print(uint offset) {
   printf("  %02d. %-15s x%d\n", offset, item_decode(this->id), this->quantity);
}
