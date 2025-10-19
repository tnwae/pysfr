/*
 * Functions for dealing with party pokemon.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pkmn-yellow.h"

extern uchar save_file[0x8000];

uint read_party_size() {
   uchar sz = save_file[0x2F2C];
   return (uint) sz;
}


party_pkmn::party_pkmn(uint offset) {
   offset -= 1;
   uchar data[0x2c];
   mkshort health, ot, health_ev, attack_ev, defense_ev, speed_ev, special_ev, dv;
   mkint exp;

   memcpy(data, save_file + offset * 0x2c + 0x2f34, 0x2c);

   this->index = data[0];

   health.data[0] = data[2];
   health.data[1] = data[1];
   this->health = health.value;

   this->pc_level = data[3];
   this->status_ailment = data[4];
   this->type1 = data[5];
   this->type2 = data[6];
   this->catch_rate = data[7];
   this->move1_index = data[8];
   this->move2_index = data[9];
   this->move3_index = data[10];
   this->move4_index = data[11];
   
   ot.data[0] = data[13];
   ot.data[1] = data[12];
   this->ot = ot.value;

   exp.data[0] = data[16];
   exp.data[1] = data[15];
   exp.data[2] = data[14];
   exp.data[3] = 0;
   this->exp = exp.value;

   health_ev.data[0] = data[18];
   health_ev.data[1] = data[17];
   this->healthEV = health_ev.value;

   attack_ev.data[0] = data[20];
   attack_ev.data[1] = data[19];
   this->attackEV = attack_ev.value;

   defense_ev.data[0] = data[22];
   defense_ev.data[1] = data[21];
   this->defenseEV = defense_ev.value;

   speed_ev.data[0] = data[24];
   speed_ev.data[1] = data[23];
   this->speedEV = speed_ev.value;

   special_ev.data[0] = data[26];
   special_ev.data[1] = data[25];
   this->specialEV = special_ev.value;

   dv.data[0] = data[28];
   dv.data[1] = data[27];
   this->dv = dv.value;

   this->move1_pp = data[29];
   this->move2_pp = data[30];
   this->move3_pp = data[31];
   this->move4_pp = data[32];

   this->name = pkmn_to_ascii_range(offset * 0x0b + 0x307e, 0x0b);
}

party_pkmn::~party_pkmn() {
   free(this->name);
}


void party_pkmn::print() {
   printf("  NAME:   %s\n", this->name);
   printf("  Index:  0x%x (%s)\n", this->index, pkmn_decode(this->index));
   printf("  HP:     0x%x (%d)\n", this->health, this->health);
   printf("  Status: 0x%x\n", this->status_ailment);
   printf("  Type1:  0x%x (%s)\n", this->type1, type_decode(this->type1));
   printf("  Type2:  0x%x (%s)\n", this->type2, type_decode(this->type2));
   printf("  Rate:   0x%x\n", this->catch_rate);

   uchar move1_pp = this->move1_pp & 0x3f;
   uchar move2_pp = this->move2_pp & 0x3f;
   uchar move3_pp = this->move3_pp & 0x3f;
   uchar move4_pp = this->move4_pp & 0x3f;

   uchar move1_ppup = (this->move1_pp & 0xc0) >> 6;
   uchar move2_ppup = (this->move2_pp & 0xc0) >> 6;
   uchar move3_ppup = (this->move3_pp & 0xc0) >> 6;
   uchar move4_ppup = (this->move4_pp & 0xc0) >> 6;

   printf("  Move 1: %-12s (%d+%d PP)\n", move_decode(this->move1_index),
	  move1_pp, move1_ppup);
   printf("  Move 2: %-12s (%d+%d PP)\n", move_decode(this->move2_index),
	  move2_pp, move2_ppup);
   printf("  Move 3: %-12s (%d+%d PP)\n", move_decode(this->move3_index),
	  move3_pp, move3_ppup);
   printf("  Move 4: %-12s (%d+%d PP)\n", move_decode(this->move4_index),
	  move4_pp, move4_ppup);
   printf("  OT ID:  %d\n", this->ot);
   printf("  EXP:    %d (F: %d  MF: %d  S: %d  MS: %d)\n", this->exp,
	  get_fast_exp(this->exp), get_medfast_exp(this->exp),
	  get_slow_exp(this->exp), get_medslow_exp(this->exp));
   printf("  EVs:   (%d, %d, %d, %d, %d)\n", this->healthEV,
	  this->attackEV, this->defenseEV, this->speedEV,
	  this->specialEV);

   health = 0;
   attack = 0;
   defense = 0;
   speed = 0;
   special = 0;

   attack  = (this->dv & 0xf000) >> 12;
   defense = (this->dv & 0x0f00) >> 8;
   speed   = (this->dv & 0x00f0) >> 4;
   special = this->dv & 0x000f;
   health  = ((attack & 1) * 8) + ((defense & 1) * 4) + ((speed & 1) * 2) + (special & 1);

   printf("  DVs:    %d/%d/%d/%d/%d (0x%x)\n", health, attack, defense, speed, special,
	  this->dv);

}
