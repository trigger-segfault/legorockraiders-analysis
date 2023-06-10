
#ifndef _RGL_LISTS_H_
#define _RGL_LISTS_H_

#define LIST_COUNT							32

#ifdef _DEBUG

#define LIST_DEBUG_MAXRETURNEDLISTSIZE		1000	// Hold up to 'n' items in a list before reusing them...
#define LIST_DEBUG_FILLVALUE				0xcc	// Fill the item with this when value returned...
#define LIST_DEBUG_FLAG_RETURNED			0x00000001
#define List_CheckItem(t,i)					List_Debug_CheckDead((t),(i),__FILE__,__LINE__)

#else // _DEBUG

#define List_CheckItem(t,i)

#endif // _DEBUG

struct ListGenericItemType {

	struct ListGenericItemType *nextFree;
#ifdef _DEBUG
	ULONG flags;
	struct List *ownerList;
#endif // _DEBUG
	ULONG itemSpace[];
};

struct List {

	size_t itemWidth;
	LPVOID listSet[LIST_COUNT];
	ULONG listCount;//, maxLists;
	struct ListGenericItemType *freeList;

#ifdef _DEBUG
	LPUCHAR file;
	ULONG line;
	struct ListGenericItemType *returnedList;
	struct ListGenericItemType *returnedListEnd;
	ULONG returnedCount;
//	LPUCHAR compareBuffer;
#endif // _DEBUG

	struct List *globalListNext, *globalListPrev;
};

typedef struct ListGenericItemType		*lpListGenericItemType;
typedef struct List						*lpList;

// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern struct List * __cdecl List_Create(unsigned int itemWidth);
extern struct List * __cdecl List_Debug_Create(unsigned int itemWidth, unsigned char *file, unsigned long line);
extern void *__cdecl List_ObtainItem(struct List *type);
extern void __cdecl List_ReturnItem(struct List *type,void *dead);
extern void __cdecl List_Debug_CheckDead(struct List *type,void *check,unsigned char *file,unsigned long line);
extern void *__cdecl List_RunThrough(struct List *type,int (*Callback)(void *,void *),void *data);
static void __cdecl List_RemoveItemFromFreeList(struct List *type,struct ListGenericItemType *item);
extern void __cdecl List_Deflate(struct List *type,int force);
static void __cdecl List_AddArray(struct List *type);
extern void __cdecl List_Remove(struct List *list);
extern void __cdecl List_Shutdown(void);
extern unsigned long __cdecl List_GetItemCount(struct List *list);
// Auto Prototypes


#ifdef _DEBUG
#define List_Create(s)					List_Debug_Create((s),__FILE__,__LINE__)
#endif // _DEBUG

#endif // !_RGL_LISTS_H_
