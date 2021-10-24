//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Memory Manager File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

// Include all Header Files

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
#include	"..\inc\libgods.h"
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#ifdef	USEMYMALLOC

Mem_Globs	memGlobs;

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Functions Go Here
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

void	Mem_Clear(LPUCHAR addr, Uint32 size)
{
	Uint32	i;

	memset(addr, NULL, size);
	for(i=0; i<MAXMALLOCS; i++)
	{
		memGlobs.memBlk[i].Active = NULL;
	}

	Mem_GetAddr(0)=addr;
	Mem_GetSize(0)=size;
	memGlobs.memBlocks=NULL;
}

#ifdef	_DEBUG
Uint32	RamAvailableNow;

void	Mem_Available( void )
{
	Uint16	i;
	RamAvailableNow=NULL;
	for(i=0; i<memGlobs.memBlocks; i++)
	{
		if(!memGlobs.memBlk[i].Active)
		{
			RamAvailableNow+=Mem_GetSize(i);
		}
	}
	RamAvailableNow+=Mem_GetSize(memGlobs.memBlocks)
}
#endif

LPVOID	Mem_Malloc(Uint32 size)
{
	Uint16	cur, i;

	size = (size+3)&0xfffffc;

	// Not Enough Blocks
	#ifdef	_DEBUG
	if(memGlobs.memBlocks == MAXMALLOCS) return Mem_GetAddr(memGlobs.memBlocks++);
	if(memGlobs.memBlocks > MAXMALLOCS) return NULL;
	#endif
	
	if(!memGlobs.memBlocks)
	{
		cur=NULL;
		Mem_Allocate(memGlobs.memBlocks++, size);
	}
	else
	{
		for(i=0, cur=memGlobs.memBlocks; i<cur; i++)
		{
			if((!memGlobs.memBlk[i].Active) && (Mem_GetSize(i) >= size)) cur = i;
		}
		if(cur==memGlobs.memBlocks)
		{
			// Enough Memory ??
			if(Mem_GetSize(cur) < size) return NULL;
			// Yes
			Mem_Allocate(memGlobs.memBlocks++, size);
		}
		else
		{
			for(i=memGlobs.memBlocks++; i>=cur; i--)
			{
				memGlobs.memBlk[i+1]=memGlobs.memBlk[i];
			}
			Mem_Allocate(cur, size);
		}
	}
	return Mem_GetAddr(cur);
}

Uint32	Mem_MallocHandle(Uint32 size)
{
	Uint16	cur, i;

	size = (size+3)&0xfffffc;

	// Not Enough Blocks
	#ifdef	_DEBUG
	if(memGlobs.memBlocks == MAXMALLOCS) return memGlobs.memBlocks++;
	if(memGlobs.memBlocks > MAXMALLOCS) return -1;
	#endif
	
	if(!memGlobs.memBlocks)
	{
		cur=NULL;
		Mem_Allocate(memGlobs.memBlocks++, size);
	}
	else
	{
		for(i=0, cur=memGlobs.memBlocks; i<cur; i++)
		{
			if((!memGlobs.memBlk[i].Active) && (Mem_GetSize(i) >= size)) cur = i;
		}
		if(cur==memGlobs.memBlocks)
		{
			// Enough Memory ??
			if(Mem_GetSize(cur) < size) return -1;
			// Yes
			Mem_Allocate(memGlobs.memBlocks++, size);
		}
		else
		{
			for(i=memGlobs.memBlocks++; i>=cur; i--)
			{
				memGlobs.memBlk[i+1]=memGlobs.memBlk[i];
			}
			Mem_Allocate(cur, size);
		}
	}
	return cur;
}

void	Mem_Allocate(Uint16 blk, Uint32 size)
{
	lpMemStruct	m1, m2;

	m1 = &memGlobs.memBlk[blk];
	m2 = &memGlobs.memBlk[blk+1];

	m2->Addr=m1->Addr+size;
	m2->Size=m1->Size-size;
	m1->Size=size;
	m1->Active=YES;

	// Clear Memory So We Don't Need To Worry About It Later
//	memset(m1->Addr, null, size);

}

Uint32	Mem_Free( void* addr)
{
	Uint16	i;
	Uint32	size = NULL;

	for(i=0; i<memGlobs.memBlocks; i++)
	{
		if((memGlobs.memBlk[i].Active) && (Mem_GetAddr(i) == addr))
		{
			size = Mem_GetSize(i);
			Mem_DeAllocate( i );
			break;
		}
	}
	return(size);
}

void		Mem_FreeHandle(Uint32 handle)
{
	if(memGlobs.memBlk[handle].Active) Mem_DeAllocate(handle);
}

void	Mem_DeAllocate(Uint16 blk)
{

	memGlobs.memBlk[blk].Active = NO;
	
	if(blk<(memGlobs.memBlocks)) Mem_BlkAdjust(blk);
	if((blk>0) && (!memGlobs.memBlk[blk-1].Active)) Mem_BlkAdjust(blk-1);
}

LPVOID	Mem_ReAlloc(LPVOID addr, Uint32 size)
{
	Mem_Free(addr);
	addr = Mem_Alloc(size);
	return addr;
}

void	Mem_BlkAdjust(Uint16 blk)
{
	Uint32	size, i;
	void*		addr;

	if(memGlobs.memBlk[blk+1].Active) return;
	size=Mem_GetSize(blk)+Mem_GetSize(blk+1);
	addr=Mem_GetAddr(blk);
	for(i=blk; i<memGlobs.memBlocks; i++)
	{
		memGlobs.memBlk[i]=memGlobs.memBlk[i+1];
	}
	memGlobs.memBlocks--;
	Mem_GetAddr(blk)=addr;
	Mem_GetSize(blk)=size;
}


void	Mem_Initialise( void )
{
	memGlobs.memAvailable = Asm_GetMemAvailable(SIZE_RAM, SIZE_TOP);
	memGlobs.memStart = Asm_GetMemStart(memGlobs.memAvailable);
	Mem_Clear(memGlobs.memStart, memGlobs.memAvailable);
}

#endif


#ifdef MEMORY_TRACKING

WATCH	watch;


/*

	Initialise watch list and file name directory

*/
void memory_watch_init(void)
{
	int		n;

	for (n=0; n<MAX_WATCHES; n++)
	{
		watch.list[n].malloc_ptr=NULL;
		watch.list[n].size=0;
	}
	watch.total=0;
	watch.blocks=0;
}

/* malloc block and record details */
void* malloc3_watch(unsigned int size, char *file, int line)
{
	void		*temp=NULL;
	int		n;

	temp=malloc3(size);
	if (temp!=NULL)
	{
		for (n=0; n<MAX_WATCHES; n++)
		{
		 	if (watch.list[n].malloc_ptr==NULL)
			{
				watch.list[n].malloc_ptr=temp;
				watch.list[n].size=size;
				watch.blocks++;
				watch.total+=size;

				/* add name and line number info */

				watch.list[n].file_index=file;
				watch.list[n].line_number=line;

				return	(temp);
			}
		}
		printf("WARNING - malloc could not be added to watch list\n");
	}
	else
		printf("ERROR! - malloc failed file=%s,line:%d,size:%d\n",file,line,size);

	return	(temp);
}




void free3_watch(void *ptr)
{
	int		n;

	for (n=0; n<MAX_WATCHES; n++)
	{
	 	if (watch.list[n].malloc_ptr==ptr)
		{			
			watch.list[n].malloc_ptr=NULL;		/* return to pool */
			free3(ptr);
			watch.blocks--;
			watch.total-=watch.list[n].size;
			return;
		}
	}
	printf("WARNING - block to be freed not in watch list\n");
	free3(ptr);
}


void show_total(void)
{

#ifdef 0		/* removed for now because of printing problems */

	char	string[80];
	int	n,y=16,len;
	char	*temp;

	for (n=0; n<MAX_WATCHES; n++)
	{

		if (watch.list[n].malloc_ptr)
		{
			temp=watch.list[n].file_index;
			len=strlen(temp);
			while(len>0)
			{
				if (temp[len]=='\\' || temp[len]=='/')
					break;
				len--;
			}			
			temp+=len+1;
			sprintf(string,"[%d] %s,%d S=%d",n,temp,watch.list[n].line_number,watch.list[n].size);
			dump_string(4,y,string);
			y+=8;
			if (y>(20*8))	/* only show first 20 entries */
				break;
		}
	}

	sprintf(string,"total=%d, blocks=%d",watch.total,watch.blocks);
	dump_string(4,240-14,string);

#endif

}


#endif


