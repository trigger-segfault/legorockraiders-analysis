//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Mem.c - [Memory Management Code]
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹


#ifdef	USEMYMALLOC

#define	MAXMALLOCS		256
#define	SIZE_STACK		0x04000
#define	SIZE_RAM			0x00200000
#define	MEM_TOP			0x80200000
#define	MEM_STACK		(MEM_TOP-SIZE_STACK)
#define	SIZE_TOP			(SIZE_STACK)


typedef	struct MemStruct
{
	char		*Addr;
	Uint32	Size;
	Uint32	Active;
} MemStruct, *lpMemStruct;

typedef	struct Mem_Globs
{
	MemStruct	memBlk[MAXMALLOCS];
	Uint32		memAvailable;
	LPUCHAR		memStart;
	Uint16		memBlocks;
	Uint16		flags;
} Mem_Globs, *lpMem_Globs;

#define	Mem_GetAddr(_h_)			memGlobs.memBlk[_h_].Addr
#define	Mem_GetSize(_h_)			memGlobs.memBlk[_h_].Size
#define	Mem_AddressHandle(_h_)	memGlobs.memBlk[_h_].Addr
void	Mem_Reset(unsigned int bank);

ext	Mem_Globs	memGlobs;

void		Mem_Clear(LPUCHAR addr, Uint32 size);
LPVOID	Mem_Malloc(Uint32 size);
void		Mem_Allocate(Uint16 blk, Uint32 size);
Uint32	Mem_Free(LPVOID addr);
void		Mem_FreeHandle(Uint32 handle);
void		Mem_DeAllocate(Uint16 blk);
LPVOID	Mem_ReAlloc(LPVOID addr, Uint32 size);
void		Mem_BlkAdjust(Uint16 blk);

#else

//-----------------------------------------------------------------

//#define MEMORY_TRACKING


#ifdef MEMORY_TRACKING

#define	Mem_Malloc(_size)		malloc3_watch(_size,__FILE__,__LINE__,NULL)
#define	Mem_Free(_addr)		free3_watch(_addr)


void memory_watch_init(void);
void *malloc3_watch(unsigned int size, char *file, int line, char *fname);
void free3_watch(void *ptr);
void mem_show_total(void);
void	memory_watch_on(void);
void	memory_watch_off(void);

#define	Mem_Initialise()				memory_watch_init()

#define	MEMORY_WATCH_ON					memory_watch_on()
#define	MEMORY_WATCH_OFF				memory_watch_off()
#define MEMORY_SHOW_TOTAL				mem_show_total();

#else

//void *malloc_mem(unsigned int _size,char *file,unsigned int line);
void *malloc_mem(Uint32 _size,char *file,unsigned int line);
void free_mem(void *mem);

#define	Mem_Initialise()
#define	Mem_Malloc(_size)				malloc_mem(_size,__FILE__,__LINE__)
#define	Mem_Free(_addr)				free_mem(_addr)
#define	MEMORY_WATCH_ON
#define	MEMORY_WATCH_OFF			
#define MEMORY_SHOW_TOTAL

#endif
//---------- memory tracking -------------------------------------------------------

#define	Mem_Clear(_addr,_size)
#define	Mem_FreeHandle(_handle)

#define	Mem_ReAlloc(_addr, _size)	realloc3(_addr,_size)

#endif

#define	Mem_Alloc			Mem_Malloc
#define	RELEASE(_m_)				if(_m_) Mem_Free(_m_)
