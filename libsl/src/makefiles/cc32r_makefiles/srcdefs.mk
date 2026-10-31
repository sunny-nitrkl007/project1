########################################################################
# environment/makefiles/srcdefs.mk                      clearmake -C gnu
########################################################################

########################################
# building lib or app
########################################
ifdef BUILDING_OBJS

# get src directory specific defs
# define OBJS after this in case it redirects the SRC_DIR
#
-include $(SRC_DIR)$/defs.mk

# Expand the following macros after these source specific
# definitions.  The := causes them to be evaluated once, at this
# point.  Conditionals are used to avoid the expansion and the
# redefinition if they have already been defined.

ifeq ($(origin OBJS), undefined)
  OBJS := $(_OBJS)
endif

endif


