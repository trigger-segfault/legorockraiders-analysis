# CLGen.exe

Bundled with the PC version of LEGO Rock Raiders is the program `CLGen.exe`, the ***Command Line Generator*** *(presumably)*. This tool is a simple GUI interface for choosing default command-line arguments *("based on your Video Card")* that will automatically be inserted by LEGO Rock Raiders on boot. In actuality this tool is much more simple, and can even be reconfigured using the `CLGen.dat` configuration file. The program takes an input registry key / value name, and gives options to choose from to modify the registry value (although the resulting command-line options are not shown in the dropdown display).

<p align="center"><img src="../../../assets/CLGen/CLGen_preview.png"></p>


## CLGen.dat file

This is the configuration file for the program's behavior and display. Unlike with `LegoRR.exe`, the filename `CLGen.dat` is hardcoded into the program, and **is not** based on the executable name.

### Syntax

* Keywords (command and action names) are case-insensitive.
* Comments are not supported.
* Empty lines are allowed.
* Extra whitespace around keywords or on empty lines is prohibited.
* The pipe `|` character is not allowed for use outside of separators.


### Default configuration

This is the default configuration for `CLGen.dat`. At least, as seen from an English U.S. CD installation.

`StandardParameters` is the name of the registry value used by LEGO Rock Raiders when inserting default command line arguments. Changing this will remove the ability to change default command-line options.

```
TITLE|Video Card selector
INSTRUCTION|Select Video Card type:
ACTION|WRITEKEY|HKEY_LOCAL_MACHINE\SOFTWARE\LEGO Media\Games\Rock Raiders\StandardParameters
ADDITEM|Default|
ADDITEM|Voodoo2|-ftm
ADDITEM|Savage3D|-fvf
```


***

### Commands

#### Command: TITLE

Change the window title.

```
Usage TITLE|<Window title text>
```

#### Command: INSTRUCTION

Change the label text shown below above the mode dropdown list.

```
Usage INSTRUCTION|<Instruction message text>
```

#### Command: ACTION

Choose the registry key path to write to. Only the `HKEY_LOCAL_MACHINE` root key is supported.

```
Usage ACTION|WRITEKEY|<registry key>
```

#### Command: ADDITEM

Add an item to the dropdown list of selectable choices. The argument `<Mode Name>` is shown in the dropdown, and `<Options>` are the string value written to the registry key.

```
Usage ADDITEM|<Mode Name>|<Options>
```
