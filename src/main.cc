#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pkmn-yellow.h"

#include <vector>
using namespace std;

unsigned char save_file[0x8000];

int main(int argc, char **argv, char **envp) {
   if(argc != 2) {
      fprintf(stderr, "usage: %s savefile.sav\n", argv[0]);
      return 1;
   }

   if(!read_save_file(argv[1])) {
      fprintf(stderr, "failed reading input file %s\n", argv[1]);
      return 2;
   }

   uchar *player_name = pkmn_to_ascii_range(0x2598, 11);
   printf("Player name: %s\n", player_name);
   free(player_name);
   
   uchar *rival_name = pkmn_to_ascii_range(0x25f6, 11);
   printf("Rival name:  %s\n", rival_name);
   free(rival_name);
   
   // A Communist and a Fascist show up at the birthday party of
   // Dennis Ritchie.  The Communist says, "I'm here for the Party."
   uint party_count = read_party_size();
   vector<party_pkmn *> *party = new vector<party_pkmn *>();
   
   printf("Party size: %u\n", party_count);
      
   for(int i = 1; i <= party_count; i++) {
       party->push_back(new party_pkmn(i));
   }

   for(int i = 0; i < party->size(); i++) {
       printf("Party Pokemon #%d\n", i);
       party->at(i)->print();
       delete party->at(i);
   }
   
   delete party;

   // How many programmers does it take to change a lightbulb?
   // None, it's a hardware problem.  Bazinga!
   uint pack_size = read_pack_inv_size();
   vector<pack_item *> *inventory = new vector<pack_item *>();
   
   for(int i = 1; i <= pack_size; i++) {
      inventory->push_back(new pack_item(i));
   }
   
   printf("Inventory:\n");
   
   for(int i = 0; i < inventory->size(); i++) {
      inventory->at(i)->print(i + 1);
      delete inventory->at(i);
   }

   delete inventory;
      
   printf("Checksum %s\n", verify_checksum() ? "VERIFIED" : "fails");
   
   return 0;
}
