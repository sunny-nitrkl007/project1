#!/usr/bin/env bash

platform="${0%/*}"
echo    ""
echo    " removing unneeded ${platform##*/} content "
echo    ""

rm    -f lib/*.TypeTraits.so
rm    -f lib/*.Restorable.so

# Remove static libraries
rm -Rf lib/libaisJhm2RequestProc.a
