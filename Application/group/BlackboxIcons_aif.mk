# ============================================================================
#  Name        : BlackboxIcons_aif.mk
#  Part of     : Blackbox
#  Aucherry    : Sun Jinbo
#
#  Copyright (c): Tieto, All rights reserved
# 
# ============================================================================


ifeq (WINS,$(findstring WINS, $(PLATFORM)))
ZDIR=$(EPOCROOT)epoc32\release\$(PLATFORM)\$(CFG)\Z
else
ZDIR=$(EPOCROOT)epoc32\data\z
endif

TARGETDIR=$(ZDIR)\resource\apps
ICONTARGETFILENAME=$(TARGETDIR)\Blackbox_icon.mif

ICONDIR=..\aif

do_nothing :
	@rem do_nothing

MAKMAKE : do_nothing

BLD : do_nothing

CLEAN : do_nothing

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : $(ICONTARGETFILENAME)

$(ICONTARGETFILENAME) : $(ICONDIR)\Blackbox_icon.svg
	mifconv $(ICONTARGETFILENAME) \
		/c32 $(ICONDIR)\Blackbox_icon.svg

FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo $(ICONTARGETFILENAME)

FINAL : do_nothing

