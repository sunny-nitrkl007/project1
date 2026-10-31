#!/bin/sh

# This file is being provided for backward compatibility.
# Use the release_unit_info.sh file instead.

# Use the path from $0 to find the path to the other scripts.
my_script_name=`echo $0 | awk -F'/' '{print $(NF)}'`
build_scripts_path=`echo $0 | sed "s/\/$my_script_name//"`

release_unit_info="$build_scripts_path/release_unit_info.sh"

# Read the Release Unit Information.
. $release_unit_info


# This file provided tgt_repos which is now provided as ru_tgts.
tgt_repos="$ru_tgts"

