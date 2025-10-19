Gathered notes on `pysfr`
=========================

charset.c
---------
There are several "apostrophe" characters like `'n` and `'t` that are used to display the two characters in one cell.  I found this out by dumping a cartridge using `game-dumper.c`.  The player cannot access these characters through ordinary gameplay, so I'm tempted to ignore them.

The (PK) and (MN) characters have been ignored.  Accented é has also been ignored.

The naive conversion in `pkmn_to_ascii_char` only works for alphabetic characters.

decoders.c
----------
Nothing particularly tricky or difficult here.  The `get_med_slow_exp` function will require a lookup table.  I did this in the C# version.  It'd be nice to also have a lookup table between Pokémon and their experience tier, but that will require extra work.

party_pkmn.c
------------
The byte at 2F2Ch indicates the size of the party, a value between 0 and 6.  You can corrupt memory to alter this field outside of normal values and do wacky shit.  (There's a new class of tools-assisted superplays that use just this mechanism to do whatever they want to, mostly with Yellow due to its slightly different memory layout.)
