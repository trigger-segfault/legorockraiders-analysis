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
INC=src
SRC=src

##############################################################
# Inclide Files Here
##############################################################

INCFILES=gods/libgods.h \
	 rrgods.mak \
	 rrpsx.mak \
	 rrpsxd.lnk \
	 rrpsxr.lnk \
	 src/globals.h \
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
	 gods/asmcode.h \
	 src/steve.h \
	 src/objects.h \
	 src/lego.h \
	 src/map3d.h \
	 src/loader.h \
	 src/sfx.h \
	 src/console.h \
	 src/control.h \
	 src/surface.h \
	 src/camera.h \
	 src/craft.h \
	 src/player.h \
	 src/cd.h \
	 src/boulder.h \
	 src/trigger.h \
	 src/creature.h \
	 src/snake.h \
	 src/spider.h \
	 src/scorpion.h \
	 src/rmonster.h \
	 src/rwhale.h \
	 src/radar.h \
	 src/menu.h \
	 src/pause.h \
	 src/movie.h \
	 src/front.h \
	 src/card.h \
	 src/lang.h \
	 src/weapons.h \
	 src/particle.h \
	 src/editor.h 


##############################################################
# Pre-DMPSX object Files Here
##############################################################

PREFILES=pre/steve.obj \
	 pre/objects.obj \
	 pre/lego.obj \
	 pre/map3d.obj \
	 pre/loader.obj \
	 pre/sfx.obj \
	 pre/console.obj \
	 pre/control.obj \
	 pre/surface.obj \
	 pre/camera.obj \
	 pre/craft.obj \
	 pre/player.obj \
	 pre/cd.obj \
	 pre/boulder.obj \
	 pre/trigger.obj \
	 pre/creature.obj \
	 pre/snake.obj \
	 pre/spider.obj \
	 pre/scorpion.obj \
	 pre/rmonster.obj \
	 pre/rwhale.obj \
	 pre/radar.obj \
	 pre/menu.obj \
	 pre/pause.obj \
	 pre/movie.obj \
	 pre/front.obj \
	 pre/card.obj \
	 pre/lang.obj \
	 pre/weapons.obj \
	 pre/particle.obj \
	 pre/editor.obj

##############################################################
# Object Files Here
##############################################################

OBJFILES=obj/steve.obj \
	 obj/objects.obj \
	 obj/lego.obj \
	 obj/map3d.obj \
	 obj/loader.obj \
	 obj/sfx.obj \
	 obj/console.obj \
	 obj/control.obj \
	 obj/surface.obj \
	 obj/camera.obj \
	 obj/craft.obj \
	 obj/player.obj \
	 obj/cd.obj \
	 obj/boulder.obj \
	 obj/trigger.obj \
	 obj/creature.obj \
	 obj/snake.obj \
	 obj/spider.obj \
	 obj/scorpion.obj \
	 obj/rmonster.obj \
	 obj/rwhale.obj \
	 obj/radar.obj \
	 obj/menu.obj \
	 obj/pause.obj \
	 obj/front.obj \
	 obj/movie.obj \
	 obj/card.obj \
	 obj/lang.obj \
	 obj/weapons.obj \
	 obj/particle.obj \
	 obj/editor.obj


##############################################################
# Link The Cpe File
##############################################################



$(CPE)/rrpsxd.cpe: $(OBJFILES) rrpsxd.lnk
 $(LINK) $(LINKOPTS) @rrpsxd.lnk,$(CPE)/rrpsxd.cpe,$(CPE)/maind.sym,$(CPE)/maind.map



##############################################################
# Compile The C Files
##############################################################

$(PRE)/steve.pre:	$(SRC)/steve.c $(INCFILES)
$(PRE)/objects.pre:	$(SRC)/objects.c $(INCFILES)
$(PRE)/lego.pre:	$(SRC)/lego.c $(INCFILES)
$(PRE)/map3d.pre:	$(SRC)/map3d.c $(INCFILES)
$(PRE)/loader.pre:	$(SRC)/loader.c $(INCFILES)
$(PRE)/sfx.pre:		$(SRC)/sfx.c $(INCFILES)
$(PRE)/console.pre:	$(SRC)/console.c $(INCFILES)
$(PRE)/control.pre:	$(SRC)/control.c $(INCFILES)
$(PRE)/surface.pre:	$(SRC)/surface.c $(INCFILES)
$(PRE)/camera.pre:	$(SRC)/camera.c $(INCFILES)
$(PRE)/craft.pre:	$(SRC)/craft.c $(INCFILES)
$(PRE)/player.pre:	$(SRC)/player.c $(INCFILES)
$(PRE)/cd.pre:		$(SRC)/cd.c $(INCFILES)
$(PRE)/boulder.pre:	$(SRC)/boulder.c $(INCFILES)
$(PRE)/trigger.pre:	$(SRC)/trigger.c $(INCFILES)
$(PRE)/creature.pre:	$(SRC)/creature.c $(INCFILES)
$(PRE)/snake.pre:	$(SRC)/snake.c $(INCFILES)
$(PRE)/spider.pre:	$(SRC)/spider.c $(INCFILES)
$(PRE)/scorpion.pre:	$(SRC)/scorpion.c $(INCFILES)
$(PRE)/rmonster.pre:	$(SRC)/rmonster.c $(INCFILES)
$(PRE)/rwhale.pre:	$(SRC)/rwhale.c $(INCFILES)
$(PRE)/radar.pre:	$(SRC)/radar.c $(INCFILES)
$(PRE)/editor.pre:	$(SRC)/editor.c $(INCFILES)
$(PRE)/menu.pre:	$(SRC)/menu.c $(INCFILES)
$(PRE)/pause.pre:	$(SRC)/pause.c $(INCFILES)
$(PRE)/movie.pre:	$(SRC)/movie.c $(INCFILES)
$(PRE)/front.pre:	$(SRC)/front.c $(INCFILES)
$(PRE)/card.pre:	$(SRC)/card.c $(INCFILES)
$(PRE)/lang.pre:	$(SRC)/lang.c $(INCFILES)
$(PRE)/weapons.pre:	$(SRC)/weapons.c $(INCFILES)
$(PRE)/particle.pre:	$(SRC)/particle.c $(INCFILES)


##############################################################
# Run .PRE object files through DMPSX and create .OBJ
##############################################################

$(OBJ)/steve.obj:	$(PRE)/steve.pre
$(OBJ)/objects.obj:	$(PRE)/objects.pre
$(OBJ)/lego.obj:	$(PRE)/lego.pre
$(OBJ)/map3d.obj:	$(PRE)/map3d.pre
$(OBJ)/loader.obj:	$(PRE)/loader.pre
$(OBJ)/sfx.obj:		$(PRE)/sfx.pre
$(OBJ)/console.obj:	$(PRE)/console.pre
$(OBJ)/control.obj:	$(PRE)/control.pre
$(OBJ)/surface.obj:	$(PRE)/surface.pre
$(OBJ)/camera.obj:	$(PRE)/camera.pre
$(OBJ)/craft.obj:	$(PRE)/craft.pre
$(OBJ)/player.obj:	$(PRE)/player.pre
$(OBJ)/cd.obj:		$(PRE)/cd.pre
$(OBJ)/boulder.obj:	$(PRE)/boulder.pre
$(OBJ)/trigger.obj:	$(PRE)/trigger.pre
$(OBJ)/creature.obj:	$(PRE)/creature.pre
$(OBJ)/snake.obj:	$(PRE)/snake.pre
$(OBJ)/spider.obj:	$(PRE)/spider.pre
$(OBJ)/scorpion.obj:	$(PRE)/scorpion.pre
$(OBJ)/rmonster.obj:	$(PRE)/rmonster.pre
$(OBJ)/rwhale.obj:	$(PRE)/rwhale.pre
$(OBJ)/radar.obj:	$(PRE)/radar.pre
$(OBJ)/editor.obj:	$(PRE)/editor.pre
$(OBJ)/menu.obj:	$(PRE)/menu.pre
$(OBJ)/pause.obj:	$(PRE)/pause.pre
$(OBJ)/movie.obj:	$(PRE)/movie.pre
$(OBJ)/front.obj:	$(PRE)/front.pre
$(OBJ)/card.obj:	$(PRE)/card.pre
$(OBJ)/lang.obj:	$(PRE)/lang.pre
$(OBJ)/weapons.obj:	$(PRE)/weapons.pre
$(OBJ)/particle.obj:	$(PRE)/particle.pre

.pre.obj:
	$(DD) $(PRE)/$&.pre -o$(OBJ)/$&.obj

.c.pre:
	$(CC) $(CCOPTIONS) $(SRC)/$&.c -o$(PRE)/$&.pre

.s.obj:
	$(ASM) $(ASMOPTIONS) $(SRC)/$&.s,$(OBJ)/$&.obj,$(OBJ)/$&.sym

