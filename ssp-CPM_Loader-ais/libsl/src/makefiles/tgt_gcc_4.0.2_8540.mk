########################################################################
# src/makefiles/tgt_rvct_2.1_ARM7TDMI.mk                clearmake -C gnu
########################################################################

# Allow C++ style comments
#     Some files in lib_a4 use them...
# Don't require function prototypes
#     Some in Simulink's files don't provide them
#   Original:
#     GCC_FLAGS = -V $(GCC_VERSION) -B $(CC_ROOT) -ansi \
#       -Wimplicit -Wmissing-prototypes -Wno-long-long -Wreturn-type \
#       -Wuninitialized -Werror
GCC_FLAGS = -V $(GCC_VERSION) -B $(CC_ROOT) \
  -Wimplicit -Wno-long-long -Wreturn-type \
  -Wuninitialized -Werror

