# PYSFR Manual
_and_ A DESCRIPTION OF THE SAVE FILE FORMAT FOR POKÉMON RED/BLUE/YELLOW VERSION (USA)

"Gotta catch 'em all!"

Version 2013.1

By William Ellison <wae@rt38.net>

## NOTES

### LEGAL

This document is licensed under CC-0, as close to public domain as I can get throughout the world.

The names of Pokémon and attacks, the term "Pokémon", and the titles of various games, are all the intellectual property of The Pokémon Company International, used here only in a referential capacity.

In particular:

* Pokemon Red and Blue are copyright (c) 1995-1998 by Game Freak, Creatures, TPCI, and Nintendo.
* Pokémon Yellow is copyright (c) 1995-1999 by Game Freak, Creatures, TPCI, and Nintendo.

### CONVENTIONS

The document assumes you have a basic knowledge of hexadecimal counting, computer hardware organization, and computer programming.  If you do not have such knowledge, you are still welcome to read this document, but it's likely to be quite useless to you.  Even better would be if you knew about the Z80-like processor used in the Game Boy.

This guide is specific to the English versions of Pokémon Red/Blue/Yellow.  The Japanese version, of course, uses Japanese text, and foreign versions use more accented letters than the English version.

This document requires Unicode text.  It's 2013 for crying out loud, so get with the program.

Hexadecimal numbers are indicated with a trailing "h".  Decimal numbers are indicated with a trailing "d" if disambiguation is important.  Finally, binary numbers, on the rare occasion that I use them, are indicated with a trailing "b".

I use "DV" in reference to the four-bit values used as "genes" for Pokémon prior to the Advance generation.  The community uses "DV" and "IV" interchangeably for the old games, while "IV" is preferred for the later games.  I also use the (newer) term "EV" in reference to the sixteen-bit values used as training values for affecting the stats by up to 63 points.  This might be confusing, since the EVs in RBY and GSC have no limit except for that of their data type -- all EVs can be maximized to their full limit, unlike the (vastly) different data type used in Advance and beyond.

### GETTING IN TOUCH

If you spot an inaccuracy, typographical error, misspelling, or something else worthy of my attention, don't hesitate to contact me at <wae@rt38.net> or submit a GitHub pull request at <https://github.com/tnwae/pysfr>.

### HOW THIS GUIDE WAS MADE

Research was performed with a clean ROM of Pokémon Yellow Version, using the free HxC hex editor by Maël Hörz.  The BGB emulator was used to run the game. BGB is considered the most accurate Game Boy emulator generally available to the community.  I wrote a few small C programs on Gentoo Linux x86_64, and wrote up this guide in GNU Emacs.  This file serves as documentation to those C programs.

### MOTIVATIONS

My key motivations in writing this guide are to provide a useful document to the community for those who wish to write programs that can modify the data contained in a game save, and to give back to the community that has given me so much over the thirteen years I've been playing Pokémon.  I also want to get involved in reverse-engineering, so I decided this would be an ideal, and fun, first project.

### ATTRIBUTIONS

I've got to thank RJones for his voluminous (and now hopelessly outdated) file, "pokemon_strategy.txt", which admirably lays the groundwork for the metagame as it existed a decade ago.  Part of the metagame is understanding the games' mechanics, and RJones laid out the mechanics in a masterful, technically sound way.

Thanks are also due to Kernighan and Ritchie for the C programming language, the FSF for the GCC, and the Linux community for an amazing family of operating  systems.

## BASICS

Pokémon Yellow is a popular video game for the Nintendo Game Boy, which was released in 1999 as an enhanced "third version" alongside its immediate predecessors, Pokémon Red and Blue Versions.  The Yellow Version is best known for being more faithful to the Pokémon anime, which includes (among other things) the following deviations from the original games:

* Your starting Pokémon is Pikachu, not one of Bulbasaur, Charmander, or   Squirtle.  Your rival's starting Pokémon is Eevee, and your actions in the   story determine which Pokémon he evolves it into.
* Pikachu harbors a certain amount of happiness toward you -- if you do "good"   things like giving it items and healing it at the Pokémon Center, it grows  happier, and if it faints in battle, it grows angrier.
* Your adversaries are still Team Rocket, but you're being chased by Jessie and   James instead of random unnamed Rockets, and their Meowth is their main weapon   against you.
* You can receive all three of the other starters throughout the main story.
* Because Ground-types are immune to Electrics, you can catch Mankey on Route 22   just outside Viridian City.

Outside of the slight changes, Pokémon Yellow is mostly the same game as Red and Blue.  This is true at a technical level as well: most of the same algorithms, formulas, and constants control Yellow as control its predecessors.  They share a common format for the battery-backed save file.

### The cartridge PCB

Inside the RBY cartridge is a circuit board containing two large ICs, both surface mounted.  The larger one contains the game data and is marked (on my Red Version) as "DMG-APAE-0", Nintendo's internal abbreviation for Pokémon Red.  It is a 32-pin ROM chip with a capacity of 1,048,576 bytes.  The second-smallest chip on the board, with pins on all four sides, is the MBC3 memory controller with a built-in clock counter that allows game progress to be stored.  It relies upon an external quartz crystal at 32.768 KHz, which is in the smallest IC on the board.

The Sharp LH52256CN-10LL static RAM, which has a capacity of 262,144 bytes, is the chip where the data is stored.  This is a 28-pin IC that requires use of the onboard CR2025 button cell battery for storing data.  The battery has a life expectancy of five to seven years.

## TEXT ENCODING

The text encoding used in the Game Boy Pokémon games is simple.  It is of no relation to the ASCII, EBCDIC, Unicode, or any other system of text encoding; it stands on its own.

Text is stored on a per-character basis, using the standard single-byte representation analogous to the C `char`.  Characters are unsigned and eight bits wide.


### Encoding table

The following table shows the glyphs used in the text encoding for Pokémon Red, Blue, and Yellow.

#### Symbols

| Symbol      | Hex      | Dec     |
|-------------|---------:|--------:|
| `<Null-0>`  | 0x00     | 0       |
| `<End-80>`  | 0x50     | 80      |
| `<Space>`   | 0x7F     | 127     |
| (           | 0x9A     | 154     |
| )           | 0x9B     | 155     |
| :           | 0x9C     | 156     |
| ;           | 0x9D     | 157     |
| [           | 0x9E     | 158     |
| ]           | 0x9F     | 159     |
| é           | 0xBA     | 186     |
| '           | 0xE0     | 224     |
| PK          | 0xE1     | 225     |
| MN          | 0xE2     | 226     |
| -           | 0xE3     | 227     |
| ?           | 0xE6     | 230     |
| !           | 0xE7     | 231     |
| .           | 0xE8     | 232     |
| `<Male>`    | 0xEF     | 239     |
| `<MonetaryP>` | 0xF0     | 240     |
| `<TimesSign>` | 0xF1     | 241     |
| .           | 0xF2     | 242     |
| /           | 0xF3     | 243     |
| ,           | 0xF4     | 244     |
| `<Female>`  | 0xF5     | 245     |
| `<Numbers>` | 0xF6 + i | 246 + i |

For the numerical symbols, `i` is an integer between 0 and 9.  Number 9 occupies 0xFF.  The appearance of `.` twice is not a mistake; it appears at 0xE8 and at 0xF2.

#### Letters
    
| Letter | Hex  | Dec |
|--------|-----:|----:|
| A      | 0x80 | 128 |
| ...    | ...  | ... |
| Z      | 0x99 | 153 |
| a      | 0xA0 | 160 |
| ...    | ...  | ... |
| z      | 0xB9 | 185 |

## STORAGE OF POKÉMON AND ITEMS

The index numbers used for Pokémon RBY are not intuitive in the least.  Unlike later generations, where the index number is simply the hexadecimal representation of the Pokémon's number in the National Pokédex.  The following table gives the index number for each species in the games.  Empty spots are filled by the entry "Missingno.", short for "Missing Number," which comes from the Japanese word "ketsuban," which literally means "missing number."  These entries in the index table are listed in groups of 16.  There are 190 entries in the species table for RBY; according to an interview with game director Shigeki Morimoto, there were originally 190 Pokémon planned for the first games.

### POKÉMON TABLE

Pokémon Table:

    00 EMPTY       10 Nidoqueen    20 Missingno.   30 Drowzee      40 Farfetch'd
    01 Rhydon      11 Cubone       21 Growlithe    31 Golem        41 Venonat
    02 Kangaskhan  12 Rhyhorn      22 Onix         32 Missingno.   42 Dragonite 
    03 Nidoran M   13 Lapras       23 Fearow       33 Magmar       43 Missingno.
    04 Clefairy    14 Arcanine     24 Pidgey       34 Mankey       44 Missingno.
    05 Spearow     15 Mew          25 Slowpoke     35 Electabuzz   45 Missingno.
    06 Voltorb     16 Gyarados     26 Kadabra      36 Magneton     46 Doduo
    07 Nidoking    17 Shellder     27 Graveler     37 Koffing      47 Poliwag
    08 Slowbro     18 Tentacool    28 Chansey      38 Missingno.   48 Jynx
    09 Ivysaur     19 Gastly       29 Machoke      39 Missingno.   49 Moltres
    0A Exeggutor   1A Scyther      2A Mr. Mime     3A Seel         4A Articuno
    0B Lickitung   1B Staryu       2B Hitmonlee    3B Diglett      4B Zapdos
    0C Exeggcute   1C Blastoise    2C Hitmonchan   3C Tauros       4C Ditto
    0D Grimer      1D Pinsir       2D Arbok        3D Missingno.   4D Meowth
    0E Gengar      1E Tangela      2E Parasect     3E Missingno.   4E Krabby
    0F Nidoran F   1F Missingno.   2F Psyduck      3F Missingno.   4F Missingno.
    
    50 Missingno.  60 Sandshrew    70 Weedle       80 Golduck      90 Persian
    51 Missingno.  61 Sandslash    71 Kakuna       81 Hypno        91 Marowak
    52 Vulpix      62 Omanyte      72 Beedrill     82 Golbat       92 Missingno.
    53 Ninetales   63 Omastar      73 Missingno.   83 Mewtwo       93 Haunter
    54 Pikachu     64 Jigglypuff   74 Dodrio       84 Snorlax      94 Abra
    55 Raichu      65 Wigglytuff   75 Primeape     85 Magikarp     95 Alakazam
    56 Missingno.  66 Eevee        76 Dugtrio      86 Missingno.   96 Pidgeotto
    57 Missingno.  67 Flareon      77 Venomoth     87 Missingno.   97 Pidgeot
    58 Dratini     68 Jolteon      78 Dewgong      88 Muk          98 Starmie
    59 Dragonair   69 Vaporeon     79 Missingno.   89 Missingno.   99 Bulbasaur
    5A Kabuto      6A Machop       7A Missingno.   8A Kingler      9A Venusaur
    5B Kabutops    6B Zubat        7B Caterpie     8B Cloyster     9B Tentacruel
    5C Horsea      6C Ekans        7C Metapod      8C Missingno.   9C Missingno.
    5D Seadra      6D Paras        7D Butterfree   8D Electrode    9D Goldeen
    5E Missingno.  6E Poliwhirl    7E Machamp      8E Clefable     9E Seaking
    5F Missingno.  6F Poliwrath    7F Missingno.   8F Weezing      9F Missingno.
    
    A0 Missingno.  B0 Charmander
    A1 Missingno.  B1 Squirtle
    A2 Missingno.  B2 Charmeleon
    A3 Ponyta      B3 Wartortle
    A4 Rapidash    B4 Charizard
    A5 Rattata     B5 Missingno.
    A6 Raticate    B6 Missingno.
    A7 Nidorino    B7 Missingno.
    A8 Nidorina    B8 Missingno.
    A9 Geodude     B9 Oddish
    AA Porygon     BA Gloom
    AB Aerodactyl  BB Vileplume
    AC Missingno.  BC Bellsprout
    AD Magnemite   BD Weepinbell
    AE Missingno.  BE Victreebel
    AF Missingno.

Index numbers after BEh (190d) are filled with garbage data.  In the famous Missingno.  glitch, activating data after BEh causes battles with glitched trainers, as the game attempts to interpret the data as a trainer instead of as a Pokémon.  The lesson to take away is that if you should ever find yourself hex-editing a save file, don't use anything greater than BEh for a Pokémon.

### MOVE TABLE

    00 EMPTY           10 Gust            20 Horn Drill      30 Supersonic 
    01 Pound           11 Wing Attack     21 Tackle          31 SonicBoom
    02 Karate Chop     12 Whirlwind       22 Body Slam       32 Disable
    03 Double Slap     13 Fly             23 Wrap            33 Acid
    04 Comet Punch     14 Bind            24 Take Down       34 Ember
    05 Mega Punch      15 Slam            25 Thrash          35 Flamethrower
    06 Pay Day         16 Vine Whip       26 Double-Edge     36 Mist
    07 Fire Punch      17 Stomp           27 Tail Whip       37 Water Gun
    08 Ice Punch       18 Double Kick     28 Poison Sting    38 Hydro Pump
    09 Thunderpunch    19 Mega Kick       29 Twineedle       39 Surf
    0A Scratch         1A Jump Kick       2A Pin Missile     3A Ice Beam
    0B Vice Grip       1B Rolling Kick    2B Leer            3B Blizzard
    0C Guillotine      1C Sand-Attack     2C Bite            3C Psybeam
    0D Razor Wind      1D Headbutt        2D Growl           3D Bubblebeam
    0E Swords Dance    1E Horn Attack     2E Roar            3E Aurora Beam
    0F Cut             1F Fury Attack     2F Sing            3F Hyper Beam
    
    40 Peck            50 Petal Dance     60 Meditate        70 Barrier
    41 Drill Peck      51 String Shot     61 Agility         71 Light Screen
    42 Submission      52 Dragon Rage     62 Quick Attack    72 Haze
    43 Low Kick        53 Fire Spin       63 Rage            73 Reflect
    44 Counter         54 ThunderShock    64 Teleport        74 Focus Energy
    45 Seismic Toss    55 Thunderbolt     65 Night Shade     75 Bide
    46 Strength        56 Thunder Wave    66 Mimic           76 Metronome
    47 Absorb          57 Thunder         67 Screech         77 Mirror Move
    48 Mega Drain      58 Rock Throw      68 Double Team     78 SelfDestruct
    49 Leech Seed      59 Earthquake      69 Recover         79 Egg Bomb
    4A Growth          5A Fissure         6A Harden          7A Lick
    4B Razor Leaf      5B Dig             6B Minimize        7B Smog
    4C Solar Beam      5C Toxic           6C Smokescreen     7C Sludge
    4D Poisonpowder    5D Confusion       6D Confuse Ray     7D Bone Club
    4E Stun Spore      5E Psychic         6E Withdraw        7E Fire Blast
    4F Sleep Powder    5F Hypnosis        6F Defense Curl    7F Waterfall
    
    80 Clamp           90 Transform       A0 Transform
    81 Swift           91 Bubble          A1 Tri Attack
    82 Skull Bash      92 Dizzy Punch     A2 Super Fang
    83 Spike Cannon    93 Spore           A3 Slash
    84 Constrict       94 Flash           A4 Substitute
    85 Amnesia         95 Psywave         A5 Struggle
    86 Kinesis         96 Splash
    87 Softboiled      97 Acid Armor
    88 Hi Jump Kick    98 Crabhammer
    89 Glare           99 Explosion
    8A Dream Eater     9A Fury Swipes
    8B Poison Gas      9B Bonemerang
    8C Barrage         9C Rest
    8D Leech Life      9D Rock Slide
    8E Lovely Kiss     9E Hyper Fang
    8F Sky Attack      9F Sharpen

Index numbers after A5 are filled with glitchy moves.

### Item table

First, the regular items.  Item 07h is a "surfboard" that allows you to surf (provided you're near water) if you select it.  Curiously, index item 09h is a Pokedex you can carry in the inventory, suggesting it was slated to be that way to begin with.  Finally, items 15h through 1Ch are badges you can carry in your inventory, each of which has various effects when activated.

    00 Unknown         10 Full Restore    20 Fire Stone     30 Card Key
    01 Master Ball     11 Max Potion      21 Thunderstone   31 Nugget
    02 Ultra Ball      12 Hyper Potion    22 Water Stone    32 PP Up
    03 Great Ball      13 Super Potion    23 HP Up          33 Poké Doll
    04 Poke Ball       14 Potion          24 Protein        34 Full Heal
    05 Town Map        15 BoulderBadge    25 Iron           35 Revive
    06 Bicycle         16 CascadeBadge    26 Carbos         36 Max Revive
    07 ?????           17 ThunderBadge    27 Calcium        37 Guard Spec.
    08 Safari Ball     18 RainbowBadge    28 Rare Candy     38 Super Repel
    09 Pokedex         19 SoulBadge       29 Dome Fossil    39 Max Repel
    0A Moon Stone      1A MarshBadge      2A Helix Fossil   3A Dire Hit
    0B Antidote        1B VolcanoBadge    2B Secret Key     3B Coin
    0C Burn Heal       1C EarthBadge      2C ????? (unused) 3C Fresh Water
    0D Ice Heal        1D Escape Rope     2D Bike Voucher   3D Soda Pop
    0E Awakening       1E Repel           2E X Accuracy     3E Lemonade
    0F Parlyz Heal     1F Old Amber       2F Leaf Stone     3F S.S. Ticket
    
    40 Gold Teeth      50 Ether
    41 X Attack        51 Max Ether
    42 X Defend        52 Elixir
    43 X Speed         53 Max Elixir
    44 X Special
    45 Coin Case
    46 Oak's Parcel
    47 Item Finder
    48 Silph Scope
    49 Poke Flute
    4A Lift Key
    4B Exp. All
    4C Old Rod
    4D Good Rod
    4E Super Rod
    4F PP Up
    
There's a big jump for TMs and HMs.  TM01 has index number C9h, and TM50 has index number FAh.  HM01 has index number C4h and HM05 has index number C8h.

    FF EMPTY

Finally, any inventory entry with an index value of FFh is an empty value.  The game interprets the first such item as the "CANCEL" entry in the relevant menu. By memory corruption techniques, this can be overwritten, allowing the player to access important areas of memory.  The fastest tool-assisted speed-runs of the game use save corruption (see [this video][3] for an example) and inventory overflow to manipulate the memory directly.

## Storage of party Pokémon

Zeroth, the important part: how the game stores the size of the party.  In normal play, you can have between one and six Pokémon in your party.  The byte at 2F2Ch ranges between zero (before you visit Oak's lab) and six for the purpose of storing the size of the party.

Next, the obvious bit: the offsets for each party Pokémon in the save file.

    Pokémon 1 -- 2F34h
    Pokémon 2 -- 2F60h
    Pokémon 3 -- 2F8Ch
    Pokémon 4 -- 2FB8h
    Pokémon 5 -- 2FE4h
    Pokémon 6 -- 3010h

Each of the six Pokémon in your party are stored as 44 (2Ch)-byte structures starting at the address 2F34h.  These structures have been well documented and you can read [the particulars][1].  I'll briefly reproduce them here in a C struct.

    typedef struct PARTY_PKMN {n
      unsigned char speciesIndexNumber;
      unsigned short currentHP;
      unsigned char unknown;                /* Note 0 */
      unsigned char statusAilment;          /* Note 1 */
      unsigned char type1;                  /* Note 2 */
      unsigned char type2;                  /* Note 2 */
      unsigned char catchRate;              /* Note 3 */
      unsigned char move1IndexNumber;
      unsigned char move2IndexNumber;
      unsigned char move3IndexNumber;
      unsigned char move4IndexNumber;
      unsigned short originalTrainerID;
      unsigned char experiencePoints[3];    /* Note 4 */
      unsigned short healthEV;
      unsigned short attackEV;
      unsigned short defenseEV;
      unsigned short speedEV;
      unsigned short specialEV;             /* Note 5 */
      unsigned short diversificationValues; /* Note 6 */
      unsigned char move1PowerPoints;       /* Note 7 */
      unsigned char move2PowerPoints;       /* Note 7 */
      unsigned char move3PowerPoints;       /* Note 7 */
      unsigned char move4PowerPoints;       /* Note 7 */
      /* Note 8 */
      unsigned char level;                  /* Note 9 */
      unsigned short maxHP;
      unsigned short attack;
      unsigned short defense;
      unsigned short speed;
      unsigned short special;
      /* Note 10 */
    } party_pkmn;

NOTES:

0.  Bulbapedia describes this as "level", but preliminary investigation doesn't     reveal as such in my own reverse engineering, at least not for party Pokemon.

1.  Status ailments are stored in packed binary form.  Confusion and "badly    poisoned" are in-battle conditions only and as such are not stored here.

        Sleep: 0x04
        Poison: 0x08
        Burn: 0x10
        Freeze: 0x20
        Paralysis: 0x40
    
2.  If a Pokémon is mono-typed, like Pikachu, then type1 == type2.  Otherwise,     type1 and type2 differ.

3.  GSC co-opts this field for storing the held item of the Pokémon.

4.  Experience points are stored as an unsigned 24-bit integer.  Because the Z80     is a little-endian processor, the least significant byte is stored first in this array of uchars.

5.  For backward compatibility, Generation II games use the Special EV bank for    Special Attack and Special Defense.

6.  The DVs are stored as one sixteen-bit value that contains each of the five    DVs.  The first nibble is for Attack, the second for Defense, the third for    Speed, and the fourth for Special.  The least-significant bit of each nibble    is used to determine the health DV in this way:

        healthDV = (atk & 1) * 8 + (def & 1) * 4 + (spd & 1) * 2 + (spc & 1)

    As with the EVs, the Special DV is used for both Special Attack and Special    Defense in Generation 2 games.

7.  Each move's Power Points are stored as a bitfield.  The first two bits  denote the number of PP UP items used on the move, and the final six bits denote the number of PP for the move.  This gives a maximum of 3 PP UPs used, and a (theoretical) maximum of 63 PP for each move.
   
8.  Pokémon stored in Bill's PC stop at this point.  Thus, putting a Pokémon in the PC and taking it back out forces a recalculation of its stats.

9.  Level is computed from the amount of experience points according to one of four formulas.  The page at [2] has the particulars on the level formulas.

10. Name and OT name data are stored separately from the information on the Pokémon.

You will thus notice blocks of hex like the following in your save file if you open it up in a hex editor (the bytes being bunched up by field in this case):

    54 0015 00 00 17 17 A3 54 2D 27 00 A6A8 0000EE 0055 006F 0055 007F 005A 
    CF51 1E 28 1E 00 06 0015 000D 000A 0010 000B

It should be fairly easy to make out what this blob of bytes means.  Let's go through each field.

    Index number: 54 (Pikachu)
    Current HP: 21
    Unknown field: 0
    Status ailment: None
    Type1: Electric
    Type2: Electric
    Catch Rate: 163/256 (63.671875%)
    Move1: ThunderShock
    Move2: Growl
    Move3: Tail Whip
    Move4: -
    OT ID: 42664
    Experience: 238 pts.
    EVs: 85 Health, 111 Attack, 85 Defense, 127 Speed, 90 Special
    DVs: 12 Attack, 15 Defense, 5 Speed, 1 Special, 7 Health (do you see why?)
    PP: 30, 40, 30, None
    Level: 6
    Max HP: 21
    Attack: 13
    Defense: 10
    Speed: 16
    Special: 11

As you can see, the Pikachu I got from Prof Oak isn't the greatest in the world, but it does have a perfect Defense DV and I got it for free.  (Not that it matters; Pikachu's defense is rubbish.)

### Storage of pack items

Pack items begin at address 25C9h.  The byte at that address indicates the size of the pack inventory, which ranges from zero to twenty (14h) items.  The next twenty short ints, from 25CAh to 25F3h are 

### Storage of PC Pokémon

### Storage of PC items

## STORAGE OF TEXT STRINGS AND PLAYER INFO

Using the text encoding described in section 1.1, quite a few strings are stored in the save file.  Strings are terminated in a 50h marker, called here EndStr.

### Player's and rival's names

    Your name:                             Rival's name:
    2598h to 25A2h                         25F6h to 2600h

Your name and your rival's name are stored close together.  Each is stored in a string of 11 bytes inclusive of the end marker, which is the standard length of user-configurable strings in these games, even if the max length of a player's name is 7 characters.  If you choose a canned name (YELLOW, ASH, etc.), you get a little extra along with it.  This is because when you choose one of those names, the game program copies that area of memory to the buffer containing your name, à la `memcpy`.  The strings are stored on the ROM as series of strings broken up by EndStr bytes at the end of each.

    NEW NAME<EndStr>YELLOW<EndStr>ASH<EndStr>...

Your rival's name is the same way:

    NEW NAME<EndStr>BLUE<EndStr>GARY<EndStr>...

However, if you choose the "NEW NAME" option for either character, and input your own name, the name simply terminates after your last character of input: if I were to use my standard nickname, BIL, then 2598h through 25A2h would simply contain BIL<EndStr> followed by seven null characters.  The EndStr character functions just like the null terminator for strings in the C programming language, only it has a different value.

Your trainer ID number is stored at 2606h and is a two-byte unsigned quantity.

    Pokémon OT name data:
    303Ch to 307Dh

Nickname data is held independently of the structures for each Pokémon.  Names are stored in blocks of 11 bytes, each one ending in EndStr and thus padded up to a length of 11 bytes.

    Pokémon nickname data:
    307Eh to 30BFh

As before, names are stored in blocks of 11 bytes, each one ending in EndStr.

    First Pokémon's name:
    0x307E to 0x3088

## STORAGE OF EVENT FLAGS AND POKÉDEX INFORMATION

This section shall describe the storage of event flags, including trainer battles, and seen/caught information in the Pokédex.


## THE SAVING PROCESS

This section shall describe the process of saving a game, from the end of user input at the menu to the point at which the user can give input again.

## CHECKSUMMING THE SAVE FILE

To validate the integrity of saved data, when the save file is loaded into memory, the game software uses a simple algorithm:

0.  Initialize the checksum value to zero.
1.  For every byte from 0x2598 to 0x3522 inclusive, add its value to the checksum, ignoring 8-bit overflows.  (Equivalently, take this sum mod 256.)
2.  Invert the bits of the result; i.e., `cksum = cksum ^ 1`.
3.  Compare that result to the value stored in 0x3523.  If they match, load the file.

If you go modifying the save file, you'd better change the checksum value if you want the game to load your save file.

## MISCELLANY

### Pokemon Yellow Save File Reader

I am working on a C program as I write this guide.  This program is designed to read the information in a Pokemon Yellow save file and display (some of) it to the user in a friendly format.  I'm considering generating data in a format like XML so that it can be viewed and interpreted by other programs.  I hope to be able to use the knowledge gained here to generate save files someday.

To compile the PYSFR, simply issue the `make` command in a command shell after cloning the source distribution:

    UNIX> git clone https://github.com/tnwae/pysfr
    UNIX> cd pysfr
    UNIX> make

PYSFR is a command line application.  You use it by opening a terminal window and pointing the executable at a raw save file:

    UNIX> ./pysfr some-save-file.sav

PYSFR comes with two utility programs, `game-dumper` and `dumper`, which dump the information from a game ROM and from the save file respectively, adjusting (most) characters to the ASCII character set.  To use them, type `make game-dumper` and `make dumper` at the command line, then call the programs:

    UNIX> ./dumper some-save-file.sav
    UNIX> ./game-dumper some-game-rom.sgb

I found the save dumper to be quite useful, even if the same wasn't true of the game dumper.  It was still fun to adapt a little code.  You can get the source code to PYSFR by pointing your browser at <http://github.com/tnwae/pysfr>.

PYSFR should run on any little-endian system supported by GCC.

I discovered soon after naming the PYSFR that Red and Blue use exactly the same save file format with extremely minor differences, so the name isn't entirely accurate.  Deal with it.

[1]: http://bulbapedia.bulbagarden.net/wiki/Pokémon_data_structure_in_Generation_I

[2]: http://bulbapedia.bulbagarden.net/wiki/Experience

[3]: http://tasvideos.org/1860M.html
