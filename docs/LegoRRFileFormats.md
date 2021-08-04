# LegoRR File Formats

## Standard Formats

* .bmp (image, may support transparency?
* .avi (non-transparent video)
* .wav (sound effect, RIFF WAVE format, requires fmt size of at least 0x10? (For streamed?))
* .ogg (music, cannot be stored in WAD file)

## Binaries
* LegoRR.exe (game executable)
* CLGen.exe (no clue)

***

## Text Formats

### CFG
* Lego.cfg (Global)
* .ae (Object activities/model data?)
    * A for "Activities"
    * E for "Events"...maybe?
* .ol (Level object list)
* .ptl (Level message actions)
    * May not be "list", since unlike other list files, the type is always referred to as "PTL".
    * "P/T list"?
    * P for "Priorities"?
    * T for "Tutorial" or "Trigger"?

### LWS
* .lws (LightWave Scene)

### NERPs
* nerpnrn.h (header C++ preprocessor file)
* .nrm (.npl auto-generated build info)
* .nrn (source script?)

### Encyclopedia
* .epb (header line, separate by empty line, then information lines. Allows spaces)

### Text
* .txt (mission text+voice lines)
* ObjectiveText.txt (ini-like format with \[group\] and key: value properties, allows spaces)
* credits.txt (credits text shown with star field)
* LoaderProfile.txt (seems to be for testing...)

### Old Level
* .lev (list of level resource files?)


***

## Binary Formats

### Archive
* LegoRR%d.WAD

### LWO
* .lwo (LightWave Object, like a bodypart?)

### ProMesh
* .x

### FLH
* .flh (not too sure, but some type of animation/overlay/transparent animation?)

### Save game
* .osf (Saved objects??)
* .dat
* .sav

### NERPs
* .npl (compiled NERPs bytecode)

### Level
* .map
* .blx

### Old Level
* .blk

### Misc
* cd.key
* LegoRR.icd (SafeDisk DRM key stuff, empty = no DRM)

***

## Mission Text Format
* Replaces '\_' with spaces.
* Seems to be an ordered key/value type of file.
* Line with just "\_" signals something, most likely that there's no briefing, or end of briefing text?

#### Line Types
* \_
* LineText \#soundKey#
* $soundKey Sounds\\file\\path