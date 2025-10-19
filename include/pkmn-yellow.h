#include <stdbool.h>

#ifndef _pkmn_yellow_h
#define _pkmn_yellow_h

#define SWAP(a, b, type)  { type c; c = a; a = b; b = c; }

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

bool read_save_file(char*);
uchar pkmn_to_ascii_char(uchar);
uchar* pkmn_to_ascii_range(uint offset, uint length);
char const* type_decode(uchar);
char const* item_decode(uchar);
char const* pkmn_decode(uchar);
char const* move_decode(uchar);
bool lies_between(uchar, uchar, uchar, bool);
uint get_slow_exp(uint);
uint get_fast_exp(uint);
uint get_medslow_exp(uint);
uint get_medfast_exp(uint);

class party_pkmn {
public:
   uchar index;
   ushort health;
   uchar pc_level;
   uchar status_ailment;
   uchar type1;
   uchar type2;
   uchar catch_rate;
   uchar move1_index;
   uchar move2_index;
   uchar move3_index;
   uchar move4_index;
   ushort ot;
   uint exp;
   ushort healthEV;
   ushort attackEV;
   ushort defenseEV;
   ushort speedEV;
   ushort specialEV;
   ushort dv;
   uchar move1_pp;
   uchar move2_pp;
   uchar move3_pp;
   uchar move4_pp;
   uchar level;
   ushort max_health;
   ushort attack;
   ushort defense;
   ushort speed;
   ushort special;
   uchar *name;

   party_pkmn(uint offset);
   ~party_pkmn();
   void print();
};

class pack_item {
public:
   uchar quantity, id;

   pack_item(uint offset);
   void print(uint offset);
};

typedef union _mkshort {
   uchar data[2];
   ushort value;
} mkshort;

typedef union _mkint {
   uchar data[4];
   uint value;
} mkint;

uint read_party_size();
uint read_pack_inv_size();

uchar get_checksum();
bool verify_checksum();

#endif /* defined _pkmn_yellow_h */
