CC   = ccpsx
DD   = dmpsx
ASM  = asmpsx
LINK = psylink

CCOPTIONS  =-O3
CCOPTIONS  =-O0 -g 
ASMOPTIONS =/l /i /o c+,h+,at-
ASMOPTIONS =/l /i /o c+,h+,at- /zd 
LINKOPTS   =/m /d /c /i /n1024

##############################################################
 
OBJ=obj
PRE=pre
CPE=cpe
INC=gods
SRC=gods

##############################################################
# Include Files Here
##############################################################

INCFILES=gods/libgods.h \
	 rrgods.mak \
	 rrpsxd.lnk \
	 rrpsxr.lnk \
	 gods/main.h \
	 gods/material.h \
	 gods/maths.h \
	 gods/file.h \
	 gods/3d.h \
	 gods/mem.h \
	 gods/sound.h \
	 gods/input.h \
	 gods/config.h \
	 gods/graphics.h \
	 gods/viewport.h \
	 gods/image.h \
	 gods/textwind.h \
	 gods/fonts.h \
	 gods/contain.h \
	 gods/activity.h \
	 gods/draw.h \
	 gods/error.h \
	 gods/hmd.h \
	 gods/asmcode.h


##############################################################
# Pre-DMPSX object Files Here
##############################################################

PREFILES= pre/main.obj \
	 pre/filepc.obj \
	 pre/mem.obj \
	 pre/3d.obj \
	 pre/sound.obj \
	 pre/input.obj \
	 pre/config.obj \
	 pre/graphics.obj \
	 pre/viewport.obj \
	 pre/image.obj \
	 pre/textwind.obj \
	 pre/fonts.obj \
	 pre/contain.obj \
	 pre/activity.obj \
	 pre/material.obj \
	 pre/maths.obj \
	 pre/draw.obj \
	 pre/error.obj \
	 pre/hmd.obj \
	 pre/asmcode.obj

##############################################################
# Object Files Here
##############################################################

OBJFILES= obj/main.obj \
	 obj/filepc.obj \
	 obj/mem.obj \
	 obj/3d.obj \
	 obj/sound.obj \
	 obj/input.obj \
	 obj/config.obj \
	 obj/graphics.obj \
	 obj/viewport.obj \
	 obj/image.obj \
	 obj/textwind.obj \
	 obj/fonts.obj \
	 obj/contain.obj \
	 obj/activity.obj \
	 obj/material.obj \
	 obj/maths.obj \
	 obj/draw.obj \
	 obj/error.obj \
	 obj/hmd.obj \
	 obj/asmcode.obj


##############################################################
# Link The Cpe File
##############################################################


$(CPE)/gods.cpe: $(OBJFILES) rrpsxd.lnk
 $(LINK) $(LINKOPTS) @rrpsxd.lnk,$(CPE)/gods.cpe,$(CPE)/gods.sym,$(CPE)/gods.map








##############################################################
# Compile The C Files
##############################################################

$(PRE)/main.pre:	$(SRC)/main.c $(INCFILES)
$(PRE)/3d.pre:		$(SRC)/3d.c $(INCFILES)
$(PRE)/mem.pre:		$(SRC)/mem.c $(INCFILES)
$(PRE)/filepc.pre:	$(SRC)/filepc.c $(INCFILES)
$(PRE)/sound.pre:	$(SRC)/sound.c $(INCFILES)
$(PRE)/input.pre:	$(SRC)/input.c $(INCFILES)
$(PRE)/config.pre:	$(SRC)/config.c $(INCFILES)
$(PRE)/graphics.pre:	$(SRC)/graphics.c $(INCFILES)
$(PRE)/viewport.pre:	$(SRC)/viewport.c $(INCFILES)
$(PRE)/image.pre:	$(SRC)/image.c $(INCFILES)
$(PRE)/textwind.pre:	$(SRC)/textwind.c $(INCFILES)
$(PRE)/fonts.pre:	$(SRC)/fonts.c $(INCFILES)
$(PRE)/contain.pre:	$(SRC)/contain.c $(INCFILES)
$(PRE)/activity.pre:	$(SRC)/activity.c $(INCFILES)
$(PRE)/material.pre:	$(SRC)/material.c $(INCFILES)
$(PRE)/maths.pre:	$(SRC)/maths.c $(INCFILES)
$(PRE)/draw.pre:	$(SRC)/draw.c $(INCFILES)
$(PRE)/error.pre:	$(SRC)/error.c $(INCFILES)
$(PRE)/hmd.pre:		$(SRC)/hmd.c $(INCFILES)
$(OBJ)/asmcode.obj:	$(SRC)/asmcode.s $(INCFILES)

##############################################################
# Run .PRE object files through DMPSX and create .OBJ
##############################################################

$(OBJ)/main.obj:	$(PRE)/main.pre
$(OBJ)/3d.obj:		$(PRE)/3d.pre
$(OBJ)/mem.obj:		$(PRE)/mem.pre
$(OBJ)/filepc.obj:	$(PRE)/filepc.pre
$(OBJ)/sound.obj:	$(PRE)/sound.pre
$(OBJ)/input.obj:	$(PRE)/input.pre
$(OBJ)/config.obj:	$(PRE)/config.pre
$(OBJ)/graphics.obj:	$(PRE)/graphics.pre
$(OBJ)/viewport.obj:	$(PRE)/viewport.pre
$(OBJ)/image.obj:	$(PRE)/image.pre
$(OBJ)/textwind.obj:	$(PRE)/textwind.pre
$(OBJ)/fonts.obj:	$(PRE)/fonts.pre
$(OBJ)/contain.obj:	$(PRE)/contain.pre
$(OBJ)/activity.obj:	$(PRE)/activity.pre
$(OBJ)/material.obj:	$(PRE)/material.pre
$(OBJ)/maths.obj:	$(PRE)/maths.pre
$(OBJ)/draw.obj:	$(PRE)/draw.pre
$(OBJ)/error.obj:	$(PRE)/error.pre
$(OBJ)/hmd.obj:		$(PRE)/hmd.pre

.pre.obj:
	$(DD) $(PRE)/$&.pre -o$(OBJ)/$&.obj

.c.pre:
	$(CC) $(CCOPTIONS) $(SRC)/$&.c -o$(PRE)/$&.pre

.s.obj:
	$(ASM) $(ASMOPTIONS) $(SRC)/$&.s,$(OBJ)/$&.obj,$(OBJ)/$&.sym
