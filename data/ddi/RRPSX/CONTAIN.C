//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Container File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

// Include all Header Files

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
#include	"libgods.h"
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹


//------------------------------------------------------------

// This has been severely pruned, many functions are just
// empty stubs, for compatibility only.
// D3DRMFRAME references have been removed, so it should be
// Yaroze friendly.

//------------------------------------------------------------



Container_Globs	containerGlobs;

/*
	container stuff uses linear list now

	containers are created in a pool and re-used when discarded

*/

lpContainer	Container_Initialise(LPUCHAR gameName)
{
	lpContainer	root;
	Uint32		loop;
	
	if(containerGlobs.flags & CONTAINER_FLAG_INITIALISED)
	{
		// Error Already Initialised
		return	NULL;
	}

	for(loop=0; loop<MAX_CONTAINERS; loop++)
	{
		containerGlobs.listSet[loop]=Mem_Malloc(sizeof(Container));
		containerGlobs.listSet[loop]->in_use=FALSE;
		containerGlobs.listSet[loop]->id=loop;
	}

	containerGlobs.list_index=0;

	containerGlobs.gameName =	gameName;
	containerGlobs.flags =		CONTAINER_FLAG_INITIALISED;


	containerGlobs.rootContainer = root = Container_Create(NULL);

	return root;
}



VOID Container_Shutdown(VOID)
{
	ULONG loop;

	for (loop=0 ; loop<MAX_CONTAINERS ; loop++)
		Mem_Free(containerGlobs.listSet[loop]);

	containerGlobs.flags = 0x00000000;
}


/* return	a container, or NULL if all used */
lpContainer Container_getContainer(VOID)
{
	int	n=0,offset=containerGlobs.list_index;
	int	first,second;

	first=MAX_CONTAINERS;
	if (offset>0)
		first-=offset;
	second=offset;

	for (n=0; n<first; n++)
	{
		if (containerGlobs.listSet[offset]->in_use==FALSE)
		{
			containerGlobs.listSet[offset]->in_use=TRUE;
			containerGlobs.list_index=offset;
			return	containerGlobs.listSet[offset];
		}
		offset++;
	}

/* wrap back to 0 */

	offset=0;
	for (n=0; n<second; n++)
	{
		if (containerGlobs.listSet[offset]->in_use==FALSE)
		{
			containerGlobs.list_index=offset;
			return	containerGlobs.listSet[offset];
		}
		offset++;
	}

	
	return	NULL;
}

lpContainer Container_Create(lpContainer parent)
{
	lpContainer	newContainer;

	if (newContainer=Container_getContainer())
	{	
		memset((LPUCHAR)newContainer, 0, sizeof(Container));
		newContainer->in_use=TRUE;
		if(parent)
			newContainer->coords.coord.super = &parent->coords.coord;
		else
			newContainer->coords.coord.super = NULL;
		newContainer->scale=ONE;
		newContainer->red=128;
		newContainer->green=128;
		newContainer->blue=128;
	}

	return newContainer;
}



void Container_Remove(lpContainer dead)
{
	Container_Remove2(dead, FALSE);
}

void	Container_Remove2(lpContainer dead, BOOL kill)
{
	Container_SetParent(dead, NULL);
	containerGlobs.listSet[dead->id]->in_use=FALSE;		/* free for re-use */
}


void	Container_SetParent(lpContainer parent, lpContainer child)
{
	lpContainer	child_of_parent=parent->next;

	child->parent=parent;
	parent->next=child;
	child->next=child_of_parent;

	if (child->type==TYPE_HMD && parent->type==TYPE_HMD)
	{
		LPDIRECT3DRMMESH pmesh=(LPDIRECT3DRMMESH) parent->modelData;
		LPDIRECT3DRMMESH cmesh=(LPDIRECT3DRMMESH) child->modelData;
		HMD_SetParent(pmesh->model,cmesh->model);
	}
}

lpContainer	Container_GetParent(lpContainer child)
{
	return child->parent;
}



VOID Container_SetOrientation(lpContainer cont, lpContainer ref, REAL dirx, REAL diry, REAL dirz, REAL upx, REAL upy, REAL upz)
{
	G3D_SetVector(&cont->coords.orientation.up, upx, upy, upz);
	G3D_SetVector(&cont->coords.orientation.dir, dirx, diry, dirz);
}

VOID Container_SetRotation(lpContainer cont, REAL x, REAL y, REAL z)
{

	G3D_SetVector(&cont->coords.rot, x, y, z);

	if(cont->type == TYPE_HMD)
	{
		LPDIRECT3DRMMESH	mesh = (LPDIRECT3DRMMESH)cont->modelData;
		VECTOR				scale={cont->scale,cont->scale,cont->scale};

		HMD_RotateAbsoluteRoot(mesh->model, x, y, z);

	/* rotation resets scale, so re-scale */

		HMD_Scale(mesh->model,&scale);
	}
}

VOID Container_SetRotationIndex(lpContainer cont, int index, REAL x, REAL y, REAL z)
{

	//G3D_SetVector(&cont->coords.rot, x, y, z);

	if(cont->type == TYPE_HMD)
	{
		LPDIRECT3DRMMESH	mesh = (LPDIRECT3DRMMESH)cont->modelData;

		HMD_RotateAbsolute(mesh->model,index, x, y, z);
	}
}


VOID Container_SetPosition(lpContainer cont, REAL x, REAL y, REAL z)
{
	VECTOR	position;

	G3D_SetVector(&cont->coords.pos, x, y, z);

/* we re-jig the position to reflect the different coordinate systems */

	if (cont->type == TYPE_HMD)
	{
		LPDIRECT3DRMMESH	mesh = (LPDIRECT3DRMMESH)cont->modelData;

		position.vx=-x;
		position.vy=z;
		position.vz=y;

		HMD_Translate(mesh->model, &position);
	}
}

/*
	set the offset for a hmd section
*/
VOID Container_SetPositionIndex(lpContainer cont, int index, REAL x, REAL y, REAL z)
{
	VECTOR	position;

/* we re-jig the position to reflect the different coordinate systems */

	if (cont->type == TYPE_HMD)
	{
		LPDIRECT3DRMMESH	mesh = (LPDIRECT3DRMMESH)cont->modelData;

		position.vx=x;
		position.vy=y;
		position.vz=z;

		HMD_TranslateIndex(mesh->model,index,&position);
	}
}



VOID Container_GetPosition(lpContainer cont, LPVECTOR3D pos)
{
	G3D_CopyVector(pos, &cont->coords.pos);
}

VOID Container_GetRotation(lpContainer cont, LPVECTOR3D rot)
{
	G3D_CopyVector(rot, &cont->coords.rot);
}




/*
	SteveD: new routine aded here, 'cos the other stuff makes no sense at all 
*/
lpContainer	Container_LoadHMDModel(lpContainer root, LPUCHAR fname)
{													 
	lpContainer		veh;
	unsigned long	*load_file=NULL;	
	void				*hmd_model=NULL;
	ULONG				file_size;
	Uint8				name[64];

	sprintf(name,"%s.HMD", fname);
	load_file=File_LoadBinary(name,&file_size);

	if (load_file)
	{
		hmd_model=HMD_InitModel(load_file,NULL);

		if ((veh=Container_ApplyMesh(root, hmd_model,TYPE_HMD)))
		{
			LPDIRECT3DRMMESH  mesh = (LPDIRECT3DRMMESH)veh->modelData;


	/* removed anim start, need a separate routine */
			//HMD_StartAnim(mesh->model,1,HMD_LOOP,HMD_NORMAL);

		}
		return	veh;
	}
	return NULL;
}



lpContainer Container_Load(lpContainer parent, LPUCHAR filename, LPUCHAR typestr)
{
	return	NULL;
}

VOID Container_Hide(lpContainer cont, BOOL hide)
{
	BOOL hidden = cont->Hidden;

	if (hide && !hidden)
	{
		cont->Hidden = TRUE;
	}
	else if (!hide && hidden)
	{
		cont->Hidden = FALSE;
	}
}


ULONG Container_ParseTypeString(LPUCHAR str, LPBOOL noTexture)
{
#ifdef SKIP_IT
	// For now, just check against one type...
	ULONG loop, argc;
	LPUCHAR argv[10];
	UCHAR string[40];

	if (str)
		{
		strcpy(string, str);
		argc = Config_Tokenize(string, argv, ":");
		if (argc > 1 && 0 == stricmp(argv[1], "NOTEXTURE")) *noTexture = TRUE;
		else *noTexture = FALSE;

		for (loop=0 ; loop<Container_TypeCount ; loop++)
			{
			if (NULL != containerGlobs.typeName[loop])
				{
				if (0 == stricmp(containerGlobs.typeName[loop], string)) return loop;
				}
			}
		}
	// Error Null string passed
#endif
	return Container_Invalid;
}

VOID Container_AddRotation(lpContainer cont, ULONG combine, REAL x, REAL y, REAL z, REAL angle)
{}

VOID Container_AddScale(lpContainer cont, ULONG combine, REAL x, REAL y, REAL z)
{}

VOID Container_AddTranslation(lpContainer cont, ULONG combine, REAL x, REAL y, REAL z)
{}

VOID Container_AddTransform(lpContainer cont, ULONG combine, MATRIX4D mat)
{}

lpContainer_Texture Container_LoadTexture(LPUCHAR fname, LPULONG width, LPULONG height)
{
	lpContainer_Texture	texture;

	if(Container_Texture_LoadTexture(fname, &texture))
		{
			if(width) *width = texture->image->width;
			if(height) *height = texture->image->height;
			return texture;
		}
	return NULL;
}


lpContainer Container_Clone(lpContainer orig)
{
	lpContainer cont = NULL;
	HMD_Model*	mod;	
	cont = Container_Create(Container_GetParent(orig));

	memcpy(cont,orig,sizeof(Container));

	if (orig->type==TYPE_HMD)
	{
		LPDIRECT3DRMMESH mesh;

		if (Container_Mesh_CreateMesh(&mesh))
		{
			mesh->coords = &cont->coords;
			Container_Mesh_SetMesh(cont, mesh);
		}
		mod=Container_Mesh_GetModel(orig);
		Container_Mesh_SetModel(cont, HMD_InitInstance(mod));
	}

	return cont;
}

VOID Container_Transform(lpContainer cont, LPVECTOR3D dest, LPVECTOR3D src)
{
}

VOID Container_InverseTransform(lpContainer cont, LPVECTOR3D dest, LPVECTOR3D src)
{
}

VOID Container_SetUserData(lpContainer cont, LPVOID data)
{
	cont->userData = data;
}

LPVOID Container_GetUserData(lpContainer cont)
{
	return cont->userData;
}

VOID	Container_Move(lpContainer root, REAL delta)
{
}



//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Mesh Based Functions Here
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

lpContainer Container_MakeMesh2(lpContainer parent, BOOL seperateGroups)
{
	lpContainer cont = Container_Create(parent);
	LPDIRECT3DRMMESH mesh;

	if (cont)
	{
		cont->type = TYPE_MESH;
		if (Container_Mesh_CreateMesh(&mesh))
		{
			mesh->coords = &cont->coords;
			cont->modelData = mesh;
		}
		else
		{
			// Error Cannot create mesh object
			RELEASE(cont);
			cont = NULL;
		}
	}
	return cont;
}


lpContainer	Container_MakeMeshSeperateGroups(lpContainer root)
{
	return Container_MakeMesh2(root, TRUE);
}

VOID Container_Mesh_Swap(lpContainer target, lpContainer origin, BOOL restore)
{}

LPBOX3D	Container_Mesh_MeshGetBox(LPDIRECT3DRMMESH obj, LPBOX3D box)
{
	return	 NULL;
}

BOOL Container_Mesh_GetBox(lpContainer cont, LPBOX3D box)
{
	return FALSE;
}

ULONG Container_Mesh_GetVertices(lpContainer cont, ULONG groupID, ULONG index, ULONG count, LPVERTEX3D retArray)
{
	return OK;
}

ULONG Container_Mesh_SetVertices(lpContainer cont, ULONG groupID, ULONG index, ULONG count, LPVERTEX3D values)
{
	return OK;
}

VOID Container_Mesh_SetQuality(lpContainer cont, ULONG groupID, ULONG quality)
{
}

ULONG Container_Mesh_AddGroup(lpContainer cont, ULONG vertexCount, ULONG faceCount, ULONG vPerFace, LPULONG faceData)
{}

BOOL Container_Mesh_IsGroupHidden(lpContainer cont, ULONG group)
{
	return OK;
}

VOID Container_Mesh_HideGroup(lpContainer cont, ULONG group, BOOL hide)
{}

BOOL Container_Mesh_GetGroup(lpContainer cont, ULONG groupID, LPULONG vertexCount, LPULONG faceCount, LPULONG vPerFace, LPULONG faceDataSize, LPULONG faceData)
{}

ULONG Container_Mesh_GetGroupCount(lpContainer cont)
{}

VOID Container_Mesh_SetTexture(lpContainer cont, ULONG groupID, lpContainer_Texture itext)
{}

lpContainer_Texture Container_Mesh_GetTexture(lpContainer cont, ULONG groupID)
{
	return (lpContainer_Texture)OK;
}

VOID Container_Mesh_SetPerspectiveCorrection(lpContainer cont, ULONG groupID, BOOL on)
{}

VOID Container_Mesh_SetMaterial(lpContainer cont, ULONG groupID, lpMaterial material)
{}

BOOL Container_Mesh_Scale(lpContainer cont, REAL x, REAL y, REAL z)
{
	return OK;
}

VOID Container_Mesh_SetColourAlpha(lpContainer cont, ULONG groupID, REAL r, REAL g, REAL b, REAL a)
{}

VOID Container_Mesh_GetColourAlpha(lpContainer cont, ULONG groupID, LPREAL r, LPREAL g, LPREAL b, LPREAL a)
{}

VOID Container_Mesh_SetColour(lpContainer cont, ULONG groupID, REAL r, REAL g, REAL b)
{
	Container_Mesh_SetColourAlpha(cont, groupID, r, g, b, ONE);
}

VOID Container_Mesh_GetColour(lpContainer cont, ULONG groupID, LPREAL r, LPREAL g, LPREAL b)
{
	Container_Mesh_GetColourAlpha(cont, groupID, r, g, b, NULL);
}


LPDIRECT3DRMMESH	Container_Mesh_CreateMesh(LPDIRECT3DRMMESH *mesh)
{
	LPDIRECT3DRMMESH	newMesh;

	newMesh = (LPDIRECT3DRMMESH)Mem_Alloc(sizeof(DIRECT3DRMMESH));
	*mesh = newMesh;
	return newMesh;

}


void	Container_Mesh_SetModel(lpContainer cont, LPVOID mod)
{
	if (cont->type & TYPE_MESH)
	{
		LPDIRECT3DRMMESH	mesh = (LPDIRECT3DRMMESH)cont->modelData;

		if (mesh)
			mesh->model=mod;
	}
}

void	Container_Mesh_SetMesh(lpContainer cont, LPDIRECT3DRMMESH mesh)
{
	if(cont->type & TYPE_MESH)
		{
		cont->modelData = mesh;
		}
}

LPVOID	Container_Mesh_GetModel(lpContainer cont)
{
	if(cont->type & TYPE_MESH)
		{
		LPDIRECT3DRMMESH	mesh = (LPDIRECT3DRMMESH)cont->modelData;

		if(mesh) return mesh->model;
		}
	return NULL;
}

LPDIRECT3DRMMESH	Container_Mesh_GetMesh(lpContainer cont)
{
	if(cont->type & TYPE_MESH)
		{
		return (LPDIRECT3DRMMESH)cont->modelData;
		}
	return NULL;
}

void	Container_Mesh_SetPolyList(lpContainer cont, LPULONG list, ULONG size)
{
	if(cont->type & TYPE_MESH)
		{
		LPDIRECT3DRMMESH	mesh = (LPDIRECT3DRMMESH)cont->modelData;

		if(mesh)
			{
			switch(cont->type)
				{
				case	TYPE_TMD:
						{	
						lpTMDhead	tmd = (lpTMDhead)mesh->model;
						lpTMDobj		obj = (lpTMDobj)&tmd[1];

						obj->PrimT = list;
						obj->PrimN = size;
						break;
						}
				}	
			}
		}
}

void	Container_Mesh_SetVertexList(lpContainer cont, LPULONG list, ULONG size)
{
	if(cont->type & TYPE_MESH)
		{
		LPDIRECT3DRMMESH	mesh = (LPDIRECT3DRMMESH)cont->modelData;

		if(mesh)
			{
			switch(cont->type)
				{
				case	TYPE_TMD:
						{	
						lpTMDhead	tmd = (lpTMDhead)mesh->model;
						lpTMDobj		obj = (lpTMDobj)&tmd[1];
					
						obj->VertT = (lpSVECTOR)list;
						obj->VertN = size;
						break;
						}

				case	TYPE_HMD:
				{
						HMD_SetVertexList(mesh->model,(SVECTOR*)list);
						break;
				}

				}
			}	
		}
}

void	Container_Mesh_SetNormalList(lpContainer cont, LPULONG list, ULONG size)
{
	if(cont->type & TYPE_MESH)
		{
		LPDIRECT3DRMMESH	mesh = (LPDIRECT3DRMMESH)cont->modelData;

		if(mesh)
			{
			switch(cont->type)
				{
				case	TYPE_TMD:
						{	
						lpTMDhead	tmd = (lpTMDhead)mesh->model;
						lpTMDobj		obj = (lpTMDobj)&tmd[1];

						obj->NormT = (lpSVECTOR)list;
						obj->NormN = size;
						break;
						}
				case	TYPE_HMD:
				{
						HMD_SetNormalList(mesh->model,(SVECTOR*)list);
						break;
				}

				}

			}
		}
}

LPVOID	Container_Mesh_GetPolyList(lpContainer cont)
{
	if(cont->type & TYPE_MESH)
		{
		LPDIRECT3DRMMESH	mesh = (LPDIRECT3DRMMESH)cont->modelData;

		if(mesh)
			{
			switch(cont->type)
				{
				case	TYPE_TMD:
						{	
						lpTMDhead	tmd = (lpTMDhead)mesh->model;
						lpTMDobj		obj = (lpTMDobj)&tmd[1];
					
						return obj->PrimT;
						break;
						}
				}	
			}
		}
	return NULL;
}

LPVOID	Container_Mesh_GetNormalList(lpContainer cont)
{
	if(cont->type & TYPE_MESH)
		{
		LPDIRECT3DRMMESH	mesh = (LPDIRECT3DRMMESH)cont->modelData;

		if(mesh)
			{
			switch(cont->type)
				{
				case	TYPE_TMD:
						{	
						lpTMDhead	tmd = (lpTMDhead)mesh->model;
						lpTMDobj		obj = (lpTMDobj)&tmd[1];
					
						return obj->NormT;
						break;
						}
				case	TYPE_HMD:
				{
						return	HMD_GetNormalList(mesh->model);
						break;
				}

				}

			}
		}
	return NULL;
}

LPVOID	Container_Mesh_GetVertexList(lpContainer cont)
{
	if(cont->type & TYPE_MESH)
		{
		LPDIRECT3DRMMESH	mesh = (LPDIRECT3DRMMESH)cont->modelData;

		if(mesh)
			{
			switch(cont->type)
				{
				case	TYPE_TMD:
						{
						lpTMDhead	tmd = (lpTMDhead)mesh->model;
						lpTMDobj		obj = (lpTMDobj)&tmd[1];

						return obj->NormT;
						break;
						}

				case	TYPE_HMD:
				{
						return	HMD_GetVertexList(mesh->model);
						break;
				}


				}
			}	
		}
	return NULL;
}


VOID Container_Light_SetEnableContainer(lpContainer light, lpContainer enable)
{}




lpContainer Container_SearchTree(lpContainer root, LPUCHAR name)
{}


VOID Container_GetOrientation(lpContainer cont, lpContainer ref, LPVECTOR3D dir, LPVECTOR3D up)
{}

REAL Container_GetZXRatio(lpContainer cont)
{}

REAL Container_GetTransCoef(lpContainer cont)
{}

REAL Container_MoveAnimation(lpContainer cont, REAL delta)
{
	return 0;
}

REAL Container_SetAnimationTime(lpContainer cont, REAL time)
{
	return 0;
}

REAL Container_GetAnimationTime(lpContainer cont)
{
	return 0;
}

ULONG Container_GetAnimationFrames(lpContainer cont)
{
	return NULL;
}


/* call this after working out the sequence id */
BOOL Container_SetActivityByType(lpContainer cont, int activityType)
{

	if (cont->type==TYPE_HMD)		/* lovely meshes */
	{
		LPDIRECT3DRMMESH  mesh = (LPDIRECT3DRMMESH) cont->modelData;

		cont->activitySeq=activityType;
		HMD_StartAnim(mesh->model,activityType,HMD_LOOP,HMD_NORMAL);
		return	TRUE;
	}

	if ((cont->type & TYPE_DECAL)==TYPE_DECAL)		/* sprites, or floor sprites */
	{
		lpSPRITE_ANIM_DATA	sad=(SPRITE_ANIM_DATA*) cont->userData;
		
		cont->activitySeq=activityType;
		cont->modelData=sad->activitySet->seq_list[activityType];

	/* reset frame index, since it may go out of range for the new activity */

		sad->animIndex=0;
		sad->animTotal=0;

		return	TRUE;
	}

	return	FALSE;		/* couldn't set activity */
}


/* ugh, set by looking up string */
BOOL Container_SetActivity(lpContainer cont, LPUCHAR actname)
{
#ifdef SKIP_IT		/* this is never used */
	int	activityType=0;

	if (cont->type==TYPE_HMD)		/* lovely meshes */
	{
		LPDIRECT3DRMMESH  mesh = (LPDIRECT3DRMMESH) cont->modelData;

		cont->activitySeq=activityType;
		HMD_StartAnim(mesh->model,activityType,HMD_LOOP,HMD_NORMAL);
		return	TRUE;
	}

	if ((cont->type & TYPE_DECAL)==TYPE_DECAL)		/* sprites, or floor sprites */
	{
		lpSPRITE_ANIM_DATA	sad=(SPRITE_ANIM_DATA*) cont->userData;
		lpSPR_ACTIVITY_SET	sas=sad->activitySet;	
		int						n;

		for (n=0; n<sas->num_anim_seqs; n++)
		{
			if (stricmp(actname,sas->seq_list[n]->name))
			{
				cont->activitySeq=n;
				cont->modelData=sas->seq_list[n];

			/* reset frame index, since it may go out of range for the new activity */

				sad->animIndex=0;
		
				return	TRUE;
			}
		}

	}
#endif
	return	FALSE;		/* couldn't set activity */
}



VOID	Container_SetTypeData(lpContainer cont, LPUCHAR name, lpGsF_LIGHT light, LPDIRECT3DRMMESH mesh)
{}

void	Container_Map_SetMesh(lpContainer cont, ContainerType type)
{
	LPDIRECT3DRMMESH	newmesh = (LPDIRECT3DRMMESH)cont->modelData;

	if(!newmesh)
		{
		if(Container_Mesh_CreateMesh(&newmesh))
			{
			newmesh->coords = &cont->coords;
			cont->modelData = newmesh;
			}
		// Error Cannot Create Mesh
		}
	cont->type = type;
}

void	Container_Map_SetVertices(lpContainer cont, Uint16 x, Uint16 y, LPUWORD vert, Uint16 wide)
{
	Uint32		id;
	lpPOLY_T3	poly = (lpPOLY_T3) Container_Mesh_GetPolyList(cont);

	id = ((y*wide)+x)*2;

	poly[id].Vert0 = vert[0];
	poly[id].Vert1 = poly[id+1].Vert0 = vert[1];
	poly[id].Vert2 = poly[id+1].Vert2 = vert[2];
	poly[id+1].Vert1 = vert[3];
}

void	Container_Map_GetVertices(lpContainer cont, Uint16 x, Uint16 y, LPUWORD vert, Uint16 wide)
{
	Uint32		id;
	lpPOLY_T3	poly = (lpPOLY_T3) Container_Mesh_GetPolyList(cont);

	id = ((y*wide)+x)*2;

	vert[0] = poly[id].Vert0;
	vert[1] = poly[id].Vert1;
	vert[2] = poly[id].Vert2;
	vert[3] = poly[id+1].Vert1;
}

lpSVECTOR	Container_Map_GetNormal(lpContainer cont, Uint16 x, Uint16 y, Uint16 w, Uint16 n)
{
	lpSVECTOR	norm = (lpSVECTOR)Container_Mesh_GetNormalList(cont);

	return &norm[(((y*w)+x)*2)+n];
}

void	Container_Map_PlaneNormal(lpContainer cont, Uint32 id, Uint16 v0, Uint16 v1, Uint16 v2)
{
	VECTOR3D		vv1, vv2, vv0, n;
	lpSVECTOR	vert = (lpSVECTOR)Container_Mesh_GetVertexList(cont);
	lpSVECTOR	norm = (lpSVECTOR)Container_Mesh_GetNormalList(cont);

	G3D_CopySVectorV3D(&vv0, &vert[v0]);
	G3D_CopySVectorV3D(&vv1, &vert[v1]);
	G3D_CopySVectorV3D(&vv2, &vert[v2]);

	Maths_PlaneNormal(&n, &vv0, &vv1, &vv2);

	G3D_CopyV3DSVector(&norm[id], &n);

//	Maths_PlaneNormal(&norm[id], &vert[v0], &vert[v1], &vert[v2]);
}



/* -------------------------------------------------------------------------------------- */
/* CHECKME: we are loading textures into main ram, and then ignoring them. Why? Not nice. */
/* -------------------------------------------------------------------------------------- */
lpContainer_Texture	Container_Texture_LoadTexture(LPUCHAR fname, lpContainer_Texture* texture)
{
	lpImage		image;
	lpContainer_Texture	tex;

	if (image = Image_LoadTIM(fname))
	{
		if (tex = Mem_Alloc(sizeof(Container_Texture)))
		{
			tex->image = image;
			*texture = tex;
			return tex;
		}
	}
	*texture = NULL;
	return NULL;
}

BOOL	Container_FindRoot(lpContainer cont, lpContainer *root)
{
	if (!cont)
		return NULL;

	while (cont->parent)
		cont=cont->parent;
	*root = cont;
	return OK;
}


lpContainer	Container_ApplyMesh(lpContainer parent, LPVOID model, ContainerType type)
{
	lpContainer			cont;
	LPDIRECT3DRMMESH	mesh;

	if(cont = Container_MakeMesh(parent))
	{
		Container_SetMesh(cont, type);
		Container_Mesh_SetModel(cont, model);
	}
	return cont;
}

/* -------------------------------------------------------------------------------------*/
/* added by SteveD */
/* -------------------------------------------------------------------------------------*/



/* create a camera container */
lpContainer	Container_CreateCameraContainer(lpContainer parent)
{
	lpContainer	new_container;

	if (new_container=Container_Create(parent))
	{
		LPVECTOR3D	cam=Mem_Malloc(sizeof(VECTOR));

		new_container->type=TYPE_HMDCAMERA;
		new_container->modelData=cam;
		Container_SetParent(parent,new_container);

		return	new_container;
	}
	return	NULL;		/* failed */
}

/* set position and viewpoint of camera */
BOOL Container_SetCamera(lpContainer camera, int cpx, int cpy, int cpz, int clx, int cly, int clz)
{
	LPVECTOR3D	cam=camera->modelData;

	if (camera->type!=TYPE_HMDCAMERA)
		return	FALSE;								/* not a camera container */

	G3D_SetVector(cam,clx,cly,clz);
	G3D_SetVector(&camera->coords.pos,cpx,cpy,cpz);

	return	TRUE;	
}



/* set position camera */
BOOL Container_SetCameraPosition(lpContainer camera, int cpx, int cpy, int cpz)
{
	if (camera->type!=TYPE_HMDCAMERA)
		return	FALSE;								/* not a camera container */

	G3D_SetVector(&camera->coords.pos,cpx,cpy,cpz);

	return	TRUE;	
}


/* set position and viewpoint of camera */
BOOL Container_SetCameraViewpoint(lpContainer camera, int clx, int cly, int clz)
{
	LPVECTOR3D	cam=camera->modelData;

	if (camera->type!=TYPE_HMDCAMERA)
		return	FALSE;								/* not a camera container */

	G3D_SetVector(cam,clx,cly,clz);

	return	TRUE;	
}





/*
	added to give some flags for clipping etc
*/
void	Container_SetRenderFlags(lpContainer cont, RenderFlags flags)
{
	cont->renderFlags=flags;
}





void Container_SetRenderCallback(lpContainer cont, void (*Callback)(lpContainer callbackCont))
{
	cont->renderCallback=Callback;
}

/*
	create a container for a floor sprite and setup the sequence
*/
lpContainer Container_CreateFloorSprite(lpContainer parent, SPR_ACTIVITY_SET *activitySet)
{
	lpContainer cont = Container_Create(parent);

	if (cont)
	{
		lpSPRITE_ANIM_DATA	sad=Mem_Malloc(sizeof(SPRITE_ANIM_DATA));

		cont->type=TYPE_FLOOR_DECAL;
		cont->userData=sad;
		cont->modelData=activitySet->seq_list[0];		/* default to first activity */
		cont->activitySeq=0;

		sad->activitySet=activitySet;
		sad->animTotal=0;
		sad->animIndex=0;
		sad->animRepeatCount=0;

		sad->clutIndex=0;
		sad->brightness=128;		/* default normal brightness */
		sad->flags=0;
	}

	return	cont;
}


/*
	create a container for  sprite and setup the sequence
*/
lpContainer Container_CreateSprite(lpContainer parent, SPR_ACTIVITY_SET *activitySet)
{
	lpContainer cont = Container_Create(parent);

	if (cont)
	{
		lpSPRITE_ANIM_DATA	sad=Mem_Malloc(sizeof(SPRITE_ANIM_DATA));

		cont->type=TYPE_DECAL;
		cont->userData=sad;
		cont->activitySeq=0;
		cont->modelData=activitySet->seq_list[0];		/* default to first activity */

		sad->activitySet=activitySet;
		sad->animTotal=0;
		sad->animIndex=0;
		sad->animRepeatCount=0;

		sad->clutIndex=0;
		sad->brightness=128;		/* default normal brightness */
		sad->flags=0;
	}

	return	cont;
}





/*
	set an activitySet for an existing sprite container
*/
BOOL	Container_SetSpriteActivitySet(lpContainer cont, SPR_ACTIVITY_SET *activitySet)
{

	if (cont->type==TYPE_DECAL || cont->type==TYPE_FLOOR_DECAL)
	{
		lpSPRITE_ANIM_DATA	sad=(SPRITE_ANIM_DATA*) cont->userData;

		cont->modelData=activitySet->seq_list[0];		/* default to first activity */
		sad->activitySet=activitySet;
		sad->animTotal=0;
		sad->animIndex=0;
		sad->animRepeatCount=0;
		return	TRUE;
	}
	return	FALSE;
}



/*
	set frame directly
*/	
void Container_SpriteSetFrame(lpContainer cont, Uint8 frame)
{
	lpSPRITE_ANIM_DATA	sad=(SPRITE_ANIM_DATA*) cont->userData;

	//sad->animSeq=frame;		/* Mmm, terse */
}


/*
	set actual frame from sprite set and angle
	we could do in the render code, but it means storing the direction in the container and
	re-calculating the angle every render, which is probably unnecessary.
*/
void Container_SpriteSetFrameFromRotation(lpContainer cont, Uint8 frame, int angle)
{
	lpSPRITE_ANIM_DATA	sad=(SPRITE_ANIM_DATA*) cont->userData;
	SPRITE_SET				*set=(SPRITE_SET*) cont->modelData;

//	sad->animSeq=((Image_GetDirection(set,angle))*set->frames_per_direction)+frame;

}


/*
	set clut index for sprite container
*/
void Container_SpriteSetSpriteClut(lpContainer cont, Uint8 clutIndex)
{
	lpSPRITE_ANIM_DATA	sad=(SPRITE_ANIM_DATA*) cont->userData;

	sad->clutIndex=clutIndex;
}


/*
	set brightness for sprite container
*/
void Container_SpriteSetSpriteBrightness(lpContainer cont, Uint8 brightness)
{
	lpSPRITE_ANIM_DATA	sad=(SPRITE_ANIM_DATA*) cont->userData;

	sad->brightness=brightness;
}

/*
	set size for sprite container

	redundant, set container scale instead
*/
void Container_SpriteSetSpriteSize(lpContainer cont, Uint16 size)
{
}



/*
	update animation for a container

	assumed to be sprite type at present,
	but doesn't have to be.

	animation can screw up if update is larger than
	a complete cycle. Obviously it shouldn't be because
	it wouldn't work visually, but it can happen;

*/
void Container_UpdateAnimation(lpContainer cont, int update)
{
	SPRITE_SET				*set=(SPRITE_SET*) cont->modelData;
	lpSPRITE_ANIM_DATA	sad=(SPRITE_ANIM_DATA*) cont->userData;
	int						index;

	sad->animTotal+=update;
	index=sad->animTotal>>12;

	if (index>=set->loop_seq_len)
	{
		sad->animTotal-=(set->loop_seq_len<<12);
		index-=set->loop_seq_len;
	}
	else if (index<0)		/* animation can go backwards */
	{
		sad->animTotal+=(set->loop_seq_len<<12);
		index+=set->loop_seq_len;
	}	

	if (index>=set->loop_seq_len)
	{
		index=0;
		sad->animTotal=0;
	}

	sad->animIndex=index;
}

/*
	set scale for mesh/sprite container
*/
void	Container_SetScale(lpContainer cont, int scale)
{

	cont->scale=scale;

	if (cont->type==TYPE_HMD)
	{
		VECTOR		mesh_scale={scale,scale,scale};

		HMD_Scale(Container_Mesh_GetModel(cont),&mesh_scale);
	}
}

/*
	set scale for model block
*/
void	Container_SetScaleBlock(lpContainer cont, int index, int scale)
{
	if (cont->type==TYPE_HMD)
	{
		VECTOR		mesh_scale={scale,scale,scale};

		HMD_ScaleBlock(Container_Mesh_GetModel(cont),index,&mesh_scale);
	}
}







/*
	start HMD animation
*/
void Container_StartAnimation(lpContainer cont,int seq, int frames, int speed)
{
	LPDIRECT3DRMMESH  mesh = (LPDIRECT3DRMMESH) cont->modelData;

	if (cont->type==TYPE_HMD)
		HMD_StartAnim(mesh->model,seq,frames,speed);
}

void Container_PauseAnimation(lpContainer cont)
{
	LPDIRECT3DRMMESH  mesh = (LPDIRECT3DRMMESH) cont->modelData;

	if (cont->type==TYPE_HMD)
		HMD_PauseAnim(mesh->model);
}

void Container_UnPauseAnimation(lpContainer cont)
{
	LPDIRECT3DRMMESH  mesh = (LPDIRECT3DRMMESH) cont->modelData;

	if (cont->type==TYPE_HMD)
		HMD_UnPauseAnim(mesh->model);
}

void Container_SetAnimSpeed(lpContainer cont, int speed)
{
	LPDIRECT3DRMMESH  mesh = (LPDIRECT3DRMMESH) cont->modelData;

	if (cont->type==TYPE_HMD)
		HMD_SetAnimSpeed(mesh->model,speed);
}


/*
	set colour components for a container
*/
void	Container_SetRGB(lpContainer cont, Uint8 red, Uint8 green, Uint8 blue)
{
	if (cont)
	{
		cont->red=red;
		cont->green=green;
		cont->blue=blue;
	}
}
