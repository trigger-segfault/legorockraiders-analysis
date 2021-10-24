CC   = ccpsx
DD   = dmpsx
ASM  = asmpsx
LINK = psylink

CCOPTIONS  =-O3
CCOPTIONS  =-O2 -g 
ASMOPTIONS =/l /i /o c+,h+,at-
ASMOPTIONS =/l /i /o c+,h+,at- /zd 
LINKOPTS   =/m /d /c /i /n1024

##############################################################
 
OBJ=obj
PRE=pre
CPE=cpe
INC=src
SRC=src


GODSFILES=gods/libgods.h \
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
	 gods/main.c \
	 gods/filepc.c \
	 gods/mem.c \
	 gods/3d.c \
	 gods/sound.c \
	 gods/input.c \
	 gods/config.c \
	 gods/graphics.c \
	 gods/viewport.c \
	 gods/image.c \
	 gods/textwind.c \
	 gods/fonts.c \
	 gods/contain.c \
	 gods/activity.c \
	 gods/material.c \
	 gods/maths.c \
	 gods/draw.c \
	 gods/error.c \
	 gods/hmd.c \
	 gods/asmcode.s


##############################################################
# Inclide Files Here
##############################################################

INCFILES=gods/libgods.h \
	 rrgods.mak \
	 rrpsx.mak \
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
	 src/front.h \
	 src/lang.h \
	 src/particle.h \
	 src/teleport.h \
	 src/weapons.h \
	 src/freezer.h \
	 src/laser.h \
	 src/dynamite.h \
	 src/pusher.h \
	 src/geoscan.h \
	 src/pause.h \
	 src/menu.h \
	 src/editor.h \
	 src/pickup.h \
	 src/gameinfo.h \
	 src/movie.h \
	 src/landpad.h \
	 src/timer.h


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
	 pre/lang.obj \
	 pre/particle.obj \
	 pre/weapons.obj \
	 pre/freezer.obj \
	 pre/laser.obj \
	 pre/dynamite.obj \
 	 pre/teleport.obj \
	 pre/pusher.obj \
	 pre/geoscan.obj \
	 pre/pause.obj \
	 pre/menu.obj \
	 pre/front.obj \
	 pre/pickup.obj \
	 pre/gameinfo.obj \
	 pre/editor.obj \
	 pre/movie.obj \
	 pre/landpad.obj \
	 pre/timer.obj


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
	 obj/lang.obj \
	 obj/particle.obj \
	 obj/weapons.obj \
	 obj/freezer.obj \
	 obj/laser.obj \
	 obj/dynamite.obj \
	 obj/teleport.obj \
	 obj/pusher.obj \
	 obj/geoscan.obj \
	 obj/editor.obj \
	 obj/pause.obj \
	 obj/front.obj \
	 obj/pickup.obj \
	 obj/gameinfo.obj \
	 obj/menu.obj \
	 obj/movie.obj \
	 obj/landpad.obj \
	 obj/timer.obj


##############################################################
# Link The Cpe File
##############################################################



$(CPE)/rrpsxd.cpe: $(OBJFILES) rrpsxd.lnk $(GODSFILES)
 $(LINK) $(LINKOPTS) @rrpsxd.lnk,$(CPE)/rrpsxd.cpe,$(CPE)/rrpsxd.sym,$(CPE)/rrpsxd.map



##############################################################
# Compile The C Files
##############################################################

$(PRE)/steve.pre:	$(SRC)/steve.c $(INCFILES)
$(PRE)/objects.pre:	$(SRC)/objects.c $(INCFILES)
$(PRE)/lego.pre:	$(SRC)/lego.c $(INCFILES) $(SRC)/myheader.h
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
$(PRE)/editor.pre:	$(SRC)/editor.c $(INCFILES)
$(PRE)/radar.pre:	$(SRC)/radar.c $(INCFILES)
$(PRE)/lang.pre:	$(SRC)/lang.c $(INCFILES)
$(PRE)/particle.pre:	$(SRC)/particle.c $(INCFILES)
$(PRE)/teleport.pre:	$(SRC)/teleport.c $(INCFILES)
$(PRE)/weapons.pre:	$(SRC)/weapons.c $(INCFILES)
$(PRE)/freezer.pre:	$(SRC)/freezer.c $(INCFILES)
$(PRE)/laser.pre:	$(SRC)/laser.c $(INCFILES)
$(PRE)/dynamite.pre:	$(SRC)/dynamite.c $(INCFILES)
$(PRE)/pusher.pre:	$(SRC)/pusher.c $(INCFILES)
$(PRE)/geoscan.pre:	$(SRC)/geoscan.c $(INCFILES)
$(PRE)/pause.pre:	$(SRC)/pause.c $(INCFILES)
$(PRE)/menu.pre:	$(SRC)/menu.c $(INCFILES)
$(PRE)/front.pre:	$(SRC)/front.c $(INCFILES)
$(PRE)/pickup.pre:	$(SRC)/pickup.c $(INCFILES)
$(PRE)/gameinfo.pre:	$(SRC)/gameinfo.c $(INCFILES)
$(PRE)/movie.pre:	$(SRC)/movie.c $(INCFILES)
$(PRE)/landpad.pre:	$(SRC)/landpad.c $(INCFILES)
$(PRE)/timer.pre:	$(SRC)/timer.c $(INCFILES)


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
$(OBJ)/editor.obj:	$(PRE)/editor.pre
$(OBJ)/radar.obj:	$(PRE)/radar.pre
$(OBJ)/lang.obj:	$(PRE)/lang.pre
$(OBJ)/particle.obj:	$(PRE)/particle.pre
$(OBJ)/teleport.obj:	$(PRE)/teleport.pre
$(OBJ)/weapons.obj:	$(PRE)/weapons.pre
$(OBJ)/freezer.obj:	$(PRE)/freezer.pre
$(OBJ)/laser.obj:	$(PRE)/laser.pre
$(OBJ)/dynamite.obj:	$(PRE)/dynamite.pre
$(OBJ)/pusher.obj:	$(PRE)/pusher.pre
$(OBJ)/geoscan.obj:	$(PRE)/geoscan.pre
$(OBJ)/pause.obj:	$(PRE)/pause.pre
$(OBJ)/menu.obj:	$(PRE)/menu.pre
$(OBJ)/front.obj:	$(PRE)/front.pre
$(OBJ)/pickup.obj:	$(PRE)/pickup.pre
$(OBJ)/gameinfo.obj:	$(PRE)/gameinfo.pre
$(OBJ)/movie.obj:	$(PRE)/movie.pre
$(OBJ)/landpad.obj:	$(PRE)/landpad.pre
$(OBJ)/timer.obj:	$(PRE)/timer.pre

.pre.obj:
	$(DD) $(PRE)/$&.pre -o$(OBJ)/$&.obj

.c.pre:
	$(CC) $(CCOPTIONS) $(SRC)/$&.c -o$(PRE)/$&.pre

.s.obj:
	$(ASM) $(ASMOPTIONS) $(SRC)/$&.s,$(OBJ)/$&.obj,$(OBJ)/$&.sym

