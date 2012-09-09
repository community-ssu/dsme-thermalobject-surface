#
# Build targets
#
SUBDIRS      := modules

VERSION := 0.0.1

#
# Install files in this directory
#
INSTALL_PERM  := 644
INSTALL_OWNER := $(shell id -u)
INSTALL_GROUP := $(shell id -g)

#
# Compiler and tool flags
# C_OPTFLAGS are not used for debug builds (ifdef DEBUG)
# C_DBGFLAGS are not used for normal builds
#
C_GENFLAGS     := -DPRG_VERSION=$(VERSION) -pthread -g -std=c99 \
                  -Wall -Wwrite-strings -Wmissing-prototypes -Werror
C_OPTFLAGS     := -O2 -s
C_DBGFLAGS     := -g -DDEBUG -DDSME_LOG_ENABLE
C_INCDIRS      := $(TOPDIR)/include $(TOPDIR)/modules $(TOPDIR) 
MKDEP_INCFLAGS := $$(pkg-config --cflags-only-I glib-2.0)


#LD_GENFLAGS := -pthread

# If OSSO_DEBUG is defined, compile in the logging
#ifdef OSSO_LOG
C_OPTFLAGS += -DDSME_LOG_ENABLE
#endif

#
# This is the topdir for build
#
TOPDIR := $(shell /bin/pwd)

#
# Non-target files/directories to be deleted by distclean
#
DISTCLEAN_DIRS	:=	doc tags

#DISTCLN_SUBDIRS := _distclean_tests

#
# Actual rules
#
include $(TOPDIR)/Rules.make

.PHONY: tags
tags:
	find . -name '*.[hc]'  |xargs ctags

.PHONY: doc
doc:
	doxygen

.PHONY: test
test: all
	make -C test depend
	make -C test
	make -C test run
