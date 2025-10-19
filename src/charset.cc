/*
 * Utility functions for dealing with the Pokemon GB/C charset.
 *
 * Author: wae
 * Date: 8/3/12
 */
#include <stdlib.h>
#include "pkmn-yellow.h"

extern uchar save_file[0x8000];

/*
 * Convert characters to their ASCII equivalents.
 * TODO: Make it handle all characters.
 */
uchar pkmn_to_ascii_char(uchar pkmn_char) {
   return pkmn_char - 0x3f;
}

/*
 * Convert ranges of characters to their ASCII equivalents.
 */
uchar *pkmn_to_ascii_range(uint offset, uint length) {
    uchar *retval = (uchar *) malloc(length);

   if(retval == NULL)
      return NULL;

   for(uint i = 0 ; i < length; i ++) {
      retval[i] = pkmn_to_ascii_char(save_file[offset + i]);
      if(save_file[offset+i] == 0x50) {
	 retval[i] = '\0';
	 break;
      }
   }

   return retval;
}
