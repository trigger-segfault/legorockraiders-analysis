# Format: WAD archive

## File format


|Type|Value|Description|
|:-|:-|:-|
|`char[4]`|"WWAD"|File signature|
|`uint32`|Count|Number of file entries in WAD|
|*`cstring[Count]`*|FilePaths|Relative file paths for entries|
|*`cstring[Count]`*|BuildPaths|Absolute file paths (source file path when WAD was built)|
|[Entry\[Count\]](#entry-structure)|Entries|File version, offset, and size of entries|
|...|Data| *File data region (not enforced)*|


### Entry structure

|Type|Value|Description|
|:-|:-|:-|
|`uint32`|Version|Version of the file, usually `1` (unrelated to WAD format)|
|`uint32`|Size|Size of the file data|
|`uint32`|Size2|Size of the file data (again!?)|
|`uint32`|Offset|Absolute offset to the file data|

