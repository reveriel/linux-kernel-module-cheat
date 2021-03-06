.PHONY: all clean mkdir

ARCH = $(shell uname -m)
CCFLAGS = -ggdb3 -I$(COMMON_DIR) -O0 -Wall -Werror -Wextra -Wno-unused-function $(CCFLAGS_EXTRA) $(CCFLAGS_SCRIPT)
CFLAGS = -fopenmp -std=c99 $(CCFLAGS) $(CFLAGS_EXTRA)
CXXFLAGS = $(CCFLAGS) $(CXXFLAGS_EXTRA)
# -Wno-unused-function for function definitions on headers,
#  because we are lazy to make a shared object. TODO.
COMMON_DIR = $(CURDIR)/..
COMMON_BASENAME = common
COMMON_OBJ = $(OUT_DIR)/$(COMMON_BASENAME)$(OBJ_EXT)
IN_EXT_ASM = .S
IN_EXT_C = .c
IN_EXT_CXX = .cpp
LIBS = -lm
OBJ_EXT = .o
OUT_EXT = .out
OUT_DIR = $(CURDIR)

.DEFAULT_GOAL := all

-include params.mk

OUTS += $(foreach IN_EXT,$(IN_EXT_ASM) $(IN_EXT_C) $(IN_EXT_CXX),$(addsuffix $(OUT_EXT), $(basename $(wildcard *$(IN_EXT)))))
ifeq ($(HAS_EIGEN),y)
	CXXFLAGS_EXTRA += -I$(STAGING_DIR)/usr/include/eigen3
	# TODO: was failing with:
	# fatal error: Eigen/Dense: No such file or directory as of
	# 975ce0723ee3fa1fea1766e6683e2f3acb8558d6
	# http://lists.busybox.net/pipermail/buildroot/2018-June/222914.html
	#CXXFLAGS_EXTRA += $(shell $(PKG_CONFIG) --cflags eigen3)
else
	OUTS := $(filter-out eigen_%$(OUT_EXT),$(OUTS))
endif
ifeq ($(HAS_LIBDRM),y)
	LIBS += $(shell $(PKG_CONFIG) --libs libdrm)
	CFLAGS_EXTRA += $(shell $(PKG_CONFIG) --cflags libdrm)
else
	OUTS := $(filter-out libdrm_%$(OUT_EXT),$(OUTS))
endif
ifeq ($(HAS_OPENBLAS),y)
	LIBS += $(shell $(PKG_CONFIG) --libs openblas)
	CFLAGS_EXTRA += $(shell $(PKG_CONFIG) --cflags openblas)
else
	OUTS := $(filter-out openblas_%$(OUT_EXT),$(OUTS))
endif
OUTS := $(filter-out bst_vs_heap%$(OUT_EXT),$(OUTS))

OUTS := $(addprefix $(OUT_DIR)/,$(OUTS))

all: mkdir $(OUTS)
	for subdir in $(SUBDIRS); do \
	  $(MAKE) -C $${subdir} OUT_DIR="$(OUT_DIR)/$$subdir"; \
	done

$(COMMON_OBJ): $(COMMON_DIR)/$(COMMON_BASENAME)$(IN_EXT_C)
	$(CC) $(CFLAGS) -c -o '$@' '$<' $(LIBS)

$(OUT_DIR)/%$(OUT_EXT): %$(IN_EXT_ASM) $(COMMON_OBJ)
	$(CC) $(CFLAGS) $(COMMON_OBJ) -o '$@' '$<' $(LIBS)


$(OUT_DIR)/%$(OUT_EXT): %$(IN_EXT_C) $(COMMON_OBJ)
	$(CC) $(CFLAGS) $(COMMON_OBJ) -o '$@' '$<' $(LIBS)

$(OUT_DIR)/%$(OUT_EXT): %$(IN_EXT_CXX) $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o '$@' '$<' $(LIBS)

clean:
	rm -f *'$(OBJ_EXT)' *'$(OUT_EXT)'
	for subdir in $(SUBDIRS); do \
	  $(MAKE) -C $${subdir} clean; \
	done

mkdir:
	mkdir -p '$(OUT_DIR)'
