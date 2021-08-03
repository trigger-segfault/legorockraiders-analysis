# LegoRR.exe source dump

This is a collection of **everything** in the LegoRR.exe assembly (as portrayed by Ghidra). The symbols present here are either identified by Ghidra automatically, or by hand. Many symbol names are poorly chosen (by hand), and are just complete and utterly disorganized. *Anyway\~*, enjoy the *multi-megabyte* source files. Or use a file text search to keep your sanity&star;

**First note** that the `datatypes.h` and `source.c` files are **directly exported** from Ghidra, with little modification... *Yes* it's all in one file, *no* sorting this out would be a nightmare. **However**, global variables, and function declarations **have** been organized into respective files, making things at least *slightly* easier.

The global variables file was built over the course of 5 hours, using Regex magic (and a bit of Python) to get things into a sane format (using Ghidra's ascii export). Some of this regex magic can be viewed in `regex_magic.txt`, but it's not organized.

***

## Directory

* `datatypes_unfiltered.h` - This is the near-raw version of the header file exported by Ghidra, just over 85% of all lines are being consumed by `undefined field_0xXXX` fields.
* `datatypes.h` - Structures and typedefs exported by Ghidra. This includes a lot of predefined garbage, *especially* standard library/WINAPI structures that you already know and love. Excess `field_0xXXX` lines have been compacted into arrays: `undefined field_0xXXX_0xXXX[0xXX]`.
* `functypes.h` - Function typedef declarations, thrown together because Ghidra **does not** export these in any shape or form...
* `globals.h` - **All the globals!**, seriously, everything. Notation is not fully C-compliant, since Ghidra exports symbols (*labels*) with non-identifier characters. Also note that prefixes `const` and `extern` are positioned in front of all globals. **But this is wrong,** these only specify whether data is pre-defined, or uninitialized on boot.
* `source_unfiltered.h` - The other half of the near-raw header file exported by Ghidra. This contains only function declarations.
* `source.h` - Organized-by-hand header file listing all function declarations and their addresses.
* `source.c` - The kitchen sink. Every function definition (source code) within the LegoRR assembly (at least for all functions that have been identified). There are possibly a handful of outlier labels used as function pointers that never got identified.


***


Despite these monolithic files, quite a lot of functions, global variables, and structures have been accurately identified. It's worth doing some keyword searches through the files if you want to learn something in particular about LegoRR (just don't expect all naming conventions to be consistent, or match that or LegoRR's configuration files).
