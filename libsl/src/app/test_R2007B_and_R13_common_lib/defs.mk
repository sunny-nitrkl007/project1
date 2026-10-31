########################################################################
# src/app/test_R2007B_and_R13_common_lib/defs.mk        clearmake -C gnu
########################################################################

# INCS - compiler include path option
#
# NOTE:  Use macro $/ for path separators and $(I) for the compiler
# include path option.  These provide target independence.
# The public headers $(I)$(REL_ROOT)$/include and internal
# library scoped headers $(I)$(REL_ROOT)$/src$/include_lib are
# already included.  Internal directory scoped headers should
# be directly in the source directory, included with #include ""
# (not <>), and the include path is implied and NOT specified.  All
# other headers should be included with #include <>.
#
# $(I)$(HAL_ROOT)$/include - hal_types.h
# $(I)$(OEL_ROOT)$/include - std_t.h
# $(I)$(OEL_ROOT)$/environment$/isi$/posek_30.1$/include - posek.h
#

# OBJS - Object files to create
#   Remove all object files - don't build this app automatically
OBJS :=