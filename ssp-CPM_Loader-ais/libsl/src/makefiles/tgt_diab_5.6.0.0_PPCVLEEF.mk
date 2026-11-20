########################################################################
# src/makefiles/tgt_diab_5.6.0.0_PPCVLEEF.mk            clearmake -C gnu
########################################################################

# Use PPCE200Z6NEF:simple instead of the default PPCVLEEN:simple
#   The target is called PPCVLEEF, but the default is actually
#   PPCVLEEN - no floating point support.  Additionally, diab
#   5.6.0.0 has a bug and does not generate floating point
#   instructions when using the PPCVLEEF, so we fall back to
#   using the PowerPC instruction set.  For now, using the
#   option to use hardware for single precision and software
#   for double precision.  If an application decides to compile
#   with PPCE200Z6NEG:simple, use hardware for single precision
#   and treat double precision as single precision, we will need
#   to create another target compiled in that way, in addition
#   to this target.
#
#   It is presumed that only the A5:E2 will remain on version
#   5.6.0.0 of the diab compiler, and that it is not ROM
#   constrained and so compiling everything with the PowerPC
#   instruction set will be acceptable.  The other platforms
#   where the 30% size reduction is more important will be
#   moving to a later release of the diab compiler, which
#   fixes the bug.  When the new compiler is available, we
#   will add another target alongside this one that actually
#   uses the PPCVLEEF:simple target.
CTARGET = -tPPCE200Z6NEF:simple
