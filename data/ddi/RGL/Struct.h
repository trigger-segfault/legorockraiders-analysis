
#ifndef _STRUCT_H_
#define _STRUCT_H_

#define STRUCT_FILEID					'CRTS'

#define STRUCT_MAXELEMENTNAMELENGTH		128

#define Struct_Register(s,a)			Struct_RegisterType(sizeof(s),a)
#define Struct_AddElement(s,e)			Struct_RegisterElement((s),#e,sizeof(e),&(e))
#define Struct_End()					Struct_RegisterType(0,NULL);

struct Struct {

	ULONG size;
	LPVOID address;
	struct StructElement *elementList;
	ULONG elementCount;
};

struct StructElement {

	UCHAR name[STRUCT_MAXELEMENTNAMELENGTH];
	ULONG size;
	ULONG offset;
};

typedef struct Struct			*lpStruct;
typedef struct StructElement	*lpStructElement;

#ifndef _AUTOPROTOTYPES
// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern struct Struct *__cdecl Struct_RegisterType(unsigned long size,void *address);
extern void __cdecl Struct_RegisterElement(struct Struct *structure,unsigned char *name,unsigned long size,void *address);
extern void *__cdecl Struct_BuildHeaderBlock(struct Struct *structure,unsigned long *lpSize);
static unsigned char *__cdecl Struct_ConvertStoredString(unsigned char *address,unsigned long *skip);
static struct Struct *__cdecl Struct_ExtractHeaderBlock(unsigned long *buffer,unsigned long elementCount,unsigned long size);
static void __cdecl Struct_FreeExtractedHeaderBlock(struct Struct *structure);
extern int __cdecl Struct_Write(struct Struct *structure,unsigned char *fname,void *list,unsigned long count);
extern int __cdecl Struct_Remap(struct Struct *srcStructure,struct Struct *destStructure,void *srcData,void *destData);
extern void *__cdecl Struct_Read(struct Struct *structure,unsigned char *fname,unsigned long start,unsigned long *count);
// Auto Prototypes
#endif // !_AUTOPROTOTYPES

#endif // !_STRUCT_H_
