#
# Build targets
#
SO_LIBRARIES    := libthermalobject_surface

#
# Target composition and overrides
#
libthermalobject_surface_C_OBJS := thermalobject_surface.o thermalsensor_battery.o
thermalobject_surface.o:  C_EXTRA_GENFLAGS := -fPIC
thermalsensor_battery.o : C_EXTRA_GENFLAGS := -fPIC $$(pkg-config --cflags glib-2.0)
libthermalobject_surface_EXTRA_LDFLAGS := -lbmeipc $$(pkg-config --libs glib-2.0)

MKDEP_INCFLAGS	:= $$(pkg-config --cflags-only-I glib-2.0 dbus-glib-1)

#
# Install files in this directory
#
INSTALL_PERM    :=      644
INSTALL_OWNER   :=      $(shell id -u)
INSTALL_GROUP   :=      $(shell id -g)

INSTALL_SO_LIBRARIES	=	libthermalobject_surface.so

$(INSTALL_SO_LIBRARIES): INSTALL_PERM := 755
$(INSTALL_SO_LIBRARIES): INSTALL_DIR  := $(DESTDIR)/usr/lib/dsme
INSTALL_INCLUDES                      := 
$(INSTALL_INCLUDES): INSTALL_PERM     := 644
$(INSTALL_INCLUDES): INSTALL_DIR      := $(DESTDIR)/usr/include/dsme

include $(TOPDIR)/Rules.make
