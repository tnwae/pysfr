/*
 * Functions for decoding data from the save.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "pkmn-yellow.h"

char const *type_decode(uchar type) {
   switch(type) {
      case 0x00: return "Normal";    // Giga Impact!
      case 0x01: return "Fighting";  // Submission!
      case 0x02: return "Flying";    // Hurricane!
      case 0x03: return "Poison";    // Cross Poison!
      case 0x04: return "Ground";    // Earthquake!
      case 0x05: return "Rock";      // Stone Edge!
      case 0x07: return "Bug";       // Megahorn!
      case 0x08: return "Ghost";     // Shadow Ball!

      // big jump for special types.
      case 0x14: return "Fire";      // V-create!
      case 0x15: return "Water";     // Water Spout!
      case 0x16: return "Grass";     // Wood Hammer!
      case 0x17: return "Electric";  // Thunder!
      case 0x18: return "Psychic";   // Psystrike!
      case 0x19: return "Ice";       // Blizzard!
      case 0x1a: return "Dragon";    // Spacial Rend!

      // error handler.
      default: return "Bird";        // Missingno!
   }
}

char const *item_decode(uchar itm) {
   switch(itm) {
      case 0x01: return "Master Ball";
      case 0x02: return "Ultra Ball";
      case 0x03: return "Great Ball";
      case 0x04: return "Poke Ball";
      case 0x05: return "Town Map";
      case 0x06: return "Bicycle";
      case 0x07: return "\"Surfboard\"";
      case 0x08: return "Safari Ball";
      case 0x09: return "Pokedex";
      case 0x0A: return "Moon Stone";
      case 0x0B: return "Antidote";
      case 0x0C: return "Burn Heal";
      case 0x0D: return "Ice Heal";
      case 0x0E: return "Awakening";
      case 0x0F: return "Parlyz Heal";
      case 0x10: return "Full Restore";
      case 0x11: return "Max Potion";
      case 0x12: return "Hyper Potion";
      case 0x13: return "Super Potion";
      case 0x14: return "Potion";
      case 0x15: return "BoulderBadge";
      case 0x16: return "CascadeBadge";
      case 0x17: return "ThunderBadge";
      case 0x18: return "RainbowBadge";
      case 0x19: return "SoulBadge";
      case 0x1A: return "MarshBadge";
      case 0x1B: return "VolcanoBadge";
      case 0x1C: return "EarthBadge";
      case 0x1D: return "Escape Rope";
      case 0x1E: return "Repel";
      case 0x1F: return "Old Amber";
      case 0x20: return "Fire Stone";
      case 0x21: return "ThunderStone";
      case 0x22: return "Water Stone";
      case 0x23: return "HP Up";
      case 0x24: return "Protein";
      case 0x25: return "Iron";
      case 0x26: return "Carbos";
      case 0x27: return "Calcium";
      case 0x28: return "Rare Candy";
      case 0x29: return "Dome Fossil";
      case 0x2A: return "Helix Fossil";
      case 0x2B: return "Secret Key";
      case 0x2C: return "<unused>";
      case 0x2D: return "Bike Voucher";
      case 0x2E: return "X Accuracy";
      case 0x2F: return "Leaf Stone";
      case 0x30: return "Card Key";
      case 0x31: return "Nugget";
      case 0x32: return "PP Up";
      case 0x33: return "Poke Doll";
      case 0x34: return "Full Heal";
      case 0x35: return "Revive";
      case 0x36: return "Max Revive";
      case 0x37: return "Guard Spec.";
      case 0x38: return "Super Repel";
      case 0x39: return "Max Repel";
      case 0x3A: return "Dire Hit";
      case 0x3B: return "Coin";
      case 0x3C: return "Fresh Water";
      case 0x3D: return "Soda Pop";
      case 0x3E: return "Lemonade";
      case 0x3F: return "S.S. Ticket";
      case 0x40: return "Gold Teeth";
      case 0x41: return "X Attack";
      case 0x42: return "X Defend";
      case 0x43: return "X Speed";
      case 0x44: return "X Special";
      case 0x45: return "Coin Case";
      case 0x46: return "Oak's Parcel";
      case 0x47: return "ItemFinder";
      case 0x48: return "Silph Scope";
      case 0x49: return "Poke Flute";
      case 0x4A: return "Lift Key";
      case 0x4B: return "Exp. All";
      case 0x4C: return "Old Rod";
      case 0x4D: return "Good Rod";
      case 0x4E: return "Super Rod";
      case 0x4F: return "PP Up";
      case 0x50: return "Ether";
      case 0x51: return "Max Ether";
      case 0x52: return "Elixir";
      case 0x53: return "Max Elixir";

      case 0xC4: return "HM01";
      case 0xC5: return "HM02";
      case 0xC6: return "HM03";
      case 0xC7: return "HM04";
      case 0xC8: return "HM05";
         
      case 0xC9: return "TM01";
      case 0xCA: return "TM02";
      case 0xCB: return "TM03";
      case 0xCC: return "TM04";
      case 0xCD: return "TM05";
      case 0xCE: return "TM06";
      case 0xCF: return "TM07";
      case 0xD0: return "TM08";
      case 0xD1: return "TM09";
      case 0xD2: return "TM10";
      case 0xD3: return "TM11";
      case 0xD4: return "TM12";
      case 0xD5: return "TM13";
      case 0xD6: return "TM14";
      case 0xD7: return "TM15";
      case 0xD8: return "TM16";
      case 0xD9: return "TM17";
      case 0xDA: return "TM18";
      case 0xDB: return "TM19";
      case 0xDC: return "TM20";
      case 0xDD: return "TM21";
      case 0xDE: return "TM22";
      case 0xDF: return "TM23";
      case 0xE0: return "TM24";
      case 0xE1: return "TM25";
      case 0xE2: return "TM26";
      case 0xE3: return "TM27";
      case 0xE4: return "TM28";
      case 0xE5: return "TM29";
      case 0xE6: return "TM30";
      case 0xE7: return "TM31";
      case 0xE8: return "TM32";
      case 0xE9: return "TM33";
      case 0xEA: return "TM34";
      case 0xEB: return "TM35";
      case 0xEC: return "TM36";
      case 0xED: return "TM37";
      case 0xEE: return "TM38";
      case 0xEF: return "TM39";
      case 0xF0: return "TM40";
      case 0xF1: return "TM41";
      case 0xF2: return "TM42";
      case 0xF3: return "TM43";
      case 0xF4: return "TM44";
      case 0xF5: return "TM45";
      case 0xF6: return "TM46";
      case 0xF7: return "TM47";
      case 0xF8: return "TM48";
      case 0xF9: return "TM49";
      case 0xFA: return "TM50";

      case 0xFF: return NULL;
      default: return "Unknown";
   }
}


char const *pkmn_decode(uchar pkmn) {
   switch (pkmn) {
      case 0x00: return "Empty";
      case 0x99: return "Bulbasaur";
      case 0x09: return "Ivysaur";
      case 0x9A: return "Venusaur";
      case 0xB0: return "Charmander";
      case 0xB2: return "Charmeleon";
      case 0xB4: return "Charizard";
      case 0xB1: return "Squirtle";
      case 0xB3: return "Wartortle";
      case 0x1C: return "Blastoise";
      case 0x7B: return "Caterpie";
      case 0x7C: return "Metapod";
      case 0x7D: return "Butterfree";
      case 0x70: return "Weedle";
      case 0x71: return "Kakuna";
      case 0x72: return "Beedrill";
      case 0x24: return "Pidgey";
      case 0x96: return "Pidgeotto";
      case 0x97: return "Pidgeot";
      case 0xA5: return "Rattata";
      case 0xA6: return "Raticate";
      case 0x05: return "Spearow";
      case 0x23: return "Fearow";
      case 0x6C: return "Ekans";
      case 0x2D: return "Arbok";
      case 0x54: return "Pikachu";
      case 0x55: return "Raichu";
      case 0x60: return "Sandshrew";
      case 0x61: return "Sandslash";
      case 0x0F: return "Nidoran F";
      case 0xA8: return "Nidorina";
      case 0x10: return "Nidoqueen";
      case 0x03: return "Nidoran M";
      case 0xA7: return "Nidorino";
      case 0x07: return "Nidoking";
      case 0x04: return "Clefairy"; 
      case 0x8E: return "Clefable";
      case 0x52: return "Vulpix";
      case 0x53: return "Ninetales";
      case 0x64: return "Jigglypuff";
      case 0x65: return "Wigglytuff";
      case 0x6B: return "Zubat";
      case 0x82: return "Golbat";
      case 0xB9: return "Oddish";
      case 0xBA: return "Gloom";
      case 0xBB: return "Vileplume";
      case 0x6D: return "Paras";
      case 0x2E: return "Parasect";
      case 0x41: return "Venonat";
      case 0x77: return "Venomoth";
      case 0x3B: return "Diglett";
      case 0x76: return "Dugtrio";
      case 0x4D: return "Meowth";
      case 0x90: return "Persian";
      case 0x2F: return "Psyduck";
      case 0x80: return "Golduck";
      case 0x34: return "Mankey";
      case 0x75: return "Primeape";
      case 0x21: return "Growlithe";
      case 0x14: return "Arcanine";
      case 0x47: return "Poliwag";
      case 0x6E: return "Poliwhirl";
      case 0x6F: return "Poliwrath";
      case 0x94: return "Abra";
      case 0x26: return "Kadabra";
      case 0x95: return "Alakazam";
      case 0x6A: return "Machop";
      case 0x29: return "Machoke";
      case 0x7E: return "Machamp";
      case 0xBC: return "Bellsprout";
      case 0xBD: return "Weepinbell";
      case 0xBE: return "Victreebel";
      case 0x18: return "Tentacool";
      case 0x9B: return "Tentacruel";
      case 0xA9: return "Geodude";
      case 0x27: return "Graveler";
      case 0x31: return "Golem";
      case 0xA3: return "Ponyta";
      case 0xA4: return "Rapidash";
      case 0x25: return "Slowpoke";
      case 0x08: return "Slowbro";
      case 0xAD: return "Magnemite";
      case 0x36: return "Magneton";
      case 0x40: return "Farfetch'd";
      case 0x46: return "Doduo";
      case 0x74: return "Dodrio";
      case 0x3A: return "Seel";
      case 0x78: return "Dewgong";
      case 0x0D: return "Grimer";
      case 0x88: return "Muk";
      case 0x17: return "Shellder";
      case 0x8B: return "Cloyster";
      case 0x19: return "Gastly";
      case 0x93: return "Haunter";
      case 0x0E: return "Gengar";
      case 0x22: return "Onix";
      case 0x30: return "Drowzee";
      case 0x81: return "Hypno";
      case 0x4E: return "Krabby";
      case 0x8A: return "Kingler";
      case 0x06: return "Voltorb";
      case 0x8D: return "Electrode";
      case 0x0C: return "Exeggcute";
      case 0x0A: return "Exeggutor";
      case 0x11: return "Cubone";
      case 0x91: return "Marowak";
      case 0x2B: return "Hitmonlee";
      case 0x2C: return "Hitmonchan";
      case 0x0B: return "Lickitung";
      case 0x37: return "Koffing";
      case 0x8F: return "Weezing";
      case 0x12: return "Rhyhorn";
      case 0x01: return "Rhydon";
      case 0x28: return "Chansey";
      case 0x1E: return "Tangela";
      case 0x02: return "Kangaskhan";
      case 0x5C: return "Horsea";
      case 0x5D: return "Seadra";
      case 0x9D: return "Goldeen";
      case 0x9E: return "Seaking";
      case 0x1B: return "Staryu";
      case 0x98: return "Starmie";
      case 0x2A: return "Mr. Mime";
      case 0x1A: return "Scyther";
      case 0x48: return "Jynx";
      case 0x35: return "Electabuzz";
      case 0x33: return "Magmar";
      case 0x1D: return "Pinsir";
      case 0x3C: return "Tauros";
      case 0x85: return "Magikarp";
      case 0x16: return "Gyarados";
      case 0x13: return "Lapras";
      case 0x4C: return "Ditto";
      case 0x66: return "Eevee";
      case 0x69: return "Vaporeon";
      case 0x68: return "Jolteon";
      case 0x67: return "Flareon";
      case 0xAA: return "Porygon";
      case 0x62: return "Omanyte";
      case 0x63: return "Omastar";
      case 0x5A: return "Kabuto";
      case 0x5B: return "Kabutops";
      case 0xAB: return "Aerodactyl";
      case 0x84: return "Snorlax";
      case 0x4A: return "Articuno";
      case 0x4B: return "Zapdos";
      case 0x49: return "Moltres";
      case 0x58: return "Dratini";
      case 0x59: return "Dragonair";
      case 0x42: return "Dragonite";
      case 0x83: return "Mewtwo";
      case 0x15: return "Mew";
      default:   return "Missingno.";
   }
}

char const *move_decode(uchar move) {
   switch(move) {
      case 0x00: return "Empty";
      case 0x01: return "Pound";
      case 0x02: return "Karate Chop";
      case 0x03: return "Double Slap";
      case 0x04: return "Comet Punch";
      case 0x05: return "Mega Punch";
      case 0x06: return "Pay Day";
      case 0x07: return "Fire Punch";
      case 0x08: return "Ice Punch";
      case 0x09: return "Thunderpunch";
      case 0x0A: return "Scratch";
      case 0x0B: return "Vice Grip";
      case 0x0C: return "Guillotine";
      case 0x0D: return "Razor Wind";
      case 0x0E: return "Swords Dance";
      case 0x0F: return "Cut";
      case 0x10: return "Gust";
      case 0x11: return "Wing Attack";
      case 0x12: return "Whirlwind";
      case 0x13: return "Fly";
      case 0x14: return "Bind";
      case 0x15: return "Slam";
      case 0x16: return "Vine Whip";
      case 0x17: return "Stomp";
      case 0x18: return "Double Kick";
      case 0x19: return "Mega Kick";
      case 0x1A: return "Jump Kick";
      case 0x1B: return "Rolling Kick";
      case 0x1C: return "Sand-Attack";
      case 0x1D: return "Headbutt";
      case 0x1E: return "Horn Attack";
      case 0x1F: return "Fury Attack";
      case 0x20: return "Horn Drill";
      case 0x21: return "Tackle";
      case 0x22: return "Body Slam";
      case 0x23: return "Wrap";
      case 0x24: return "Take Down";
      case 0x25: return "Thrash";
      case 0x26: return "Double-Edge";
      case 0x27: return "Tail Whip";
      case 0x28: return "Poison Sting";
      case 0x29: return "Twineedle";
      case 0x2A: return "Pin Missile";
      case 0x2B: return "Leer";
      case 0x2C: return "Bite";
      case 0x2D: return "Growl";
      case 0x2E: return "Roar";
      case 0x2F: return "Sing";
      case 0x30: return "Supersonic";
      case 0x31: return "Sonicboom";
      case 0x32: return "Disable";
      case 0x33: return "Acid";
      case 0x34: return "Ember";
      case 0x35: return "Flamethrower";
      case 0x36: return "Mist";
      case 0x37: return "Water Gun";
      case 0x38: return "Hydro Pump";
      case 0x39: return "Surf";
      case 0x3A: return "Ice Beam";
      case 0x3B: return "Blizzard";
      case 0x3C: return "Psybeam";
      case 0x3D: return "Bubblebeam";
      case 0x3E: return "Aurora Beam";
      case 0x3F: return "Hyper Beam";
      case 0x40: return "Peck";
      case 0x41: return "Drill Peck";
      case 0x42: return "Submission";
      case 0x43: return "Low Kick";
      case 0x44: return "Counter";
      case 0x45: return "Seismic Toss";
      case 0x46: return "Strength";
      case 0x47: return "Absorb";
      case 0x48: return "Mega Drain";
      case 0x49: return "Leech Seed";
      case 0x4A: return "Growth";
      case 0x4B: return "Razor Leaf";
      case 0x4C: return "Solar Beam";
      case 0x4D: return "Poisonpowder";
      case 0x4E: return "Stun Spore";
      case 0x4F: return "Sleep Powder";
      case 0x50: return "Petal Dance";
      case 0x51: return "String Shot";
      case 0x52: return "Dragon Rage";
      case 0x53: return "Fire Spin";
      case 0x54: return "Thundershock";
      case 0x55: return "Thunderbolt";
      case 0x56: return "Thunder Wave";
      case 0x57: return "Thunder";
      case 0x58: return "Rock Throw";
      case 0x59: return "Earthquake";
      case 0x5A: return "Fissure";
      case 0x5B: return "Dig";
      case 0x5C: return "Toxic";
      case 0x5D: return "Confusion";
      case 0x5E: return "Psychic";
      case 0x5F: return "Hypnosis";
      case 0x60: return "Meditate";
      case 0x61: return "Agility";
      case 0x62: return "Quick Attack";
      case 0x63: return "Rage";
      case 0x64: return "Teleport";
      case 0x65: return "Night Shade";
      case 0x66: return "Mimic";
      case 0x67: return "Screech";
      case 0x68: return "Double Team";
      case 0x69: return "Recover";
      case 0x6A: return "Harden";
      case 0x6B: return "Minimize";
      case 0x6C: return "Smokescreen";
      case 0x6D: return "Confuse Ray";
      case 0x6E: return "Withdraw";
      case 0x6F: return "Defense Curl";
      case 0x70: return "Barrier";
      case 0x71: return "Light Screen";
      case 0x72: return "Haze";
      case 0x73: return "Reflect";
      case 0x74: return "Focus Energy";
      case 0x75: return "Bide";
      case 0x76: return "Metronome";
      case 0x77: return "Mirror Move";
      case 0x78: return "Selfdestruct";
      case 0x79: return "Egg Bomb";
      case 0x7A: return "Lick";
      case 0x7B: return "Smog";
      case 0x7C: return "Sludge";
      case 0x7D: return "Bone Club";
      case 0x7E: return "Fire Blast";
      case 0x7F: return "Waterfall";
      case 0x80: return "Clamp";
      case 0x81: return "Swift";
      case 0x82: return "Skull Bash";
      case 0x83: return "Spike Cannon";
      case 0x84: return "Constrict";
      case 0x85: return "Amnesia";
      case 0x86: return "Kinesis";
      case 0x87: return "Softboiled";
      case 0x88: return "Hi Jump Kick";
      case 0x89: return "Glare";
      case 0x8A: return "Dream Eater";
      case 0x8B: return "Poison Gas";
      case 0x8C: return "Barrage";
      case 0x8D: return "Leech Life";
      case 0x8E: return "Lovely Kiss";
      case 0x8F: return "Sky Attack";
      case 0x90: return "Transform";
      case 0x91: return "Bubble";
      case 0x92: return "Dizzy Punch";
      case 0x93: return "Spore";
      case 0x94: return "Flash";
      case 0x95: return "Psywave";
      case 0x96: return "Splash";
      case 0x97: return "Acid Armor";
      case 0x98: return "Crabhammer";
      case 0x99: return "Explosion";
      case 0x9A: return "Fury Swipes";
      case 0x9B: return "Bonemerang";
      case 0x9C: return "Rest";
      case 0x9D: return "Rock Slide";
      case 0x9E: return "Hyper Fang";
      case 0x9F: return "Sharpen";
      case 0xA0: return "Conversion";
      case 0xA1: return "Tri Attack";
      case 0xA2: return "Super Fang";
      case 0xA3: return "Slash";
      case 0xA4: return "Substitute";
      case 0xA5: return "Struggle";
      default: return "Invalid";
   }
}

uint get_slow_exp(uint exp) {
   return (uint) cbrt( (double) ((4*exp)/5) );
}

uint get_fast_exp(uint exp) {
   return (uint) cbrt( (double) ((5*exp)/4) );
}

uint get_medslow_exp(uint exp) {
   return -1;
}

uint get_medfast_exp(uint exp) {
   return (uint) cbrt((double)exp);
}
