#!/bin/bash

# Use the path from $0 to find the path to the platform root and view root directories.
# The platform_root variable is used to specify the <view>/lib/lib_hal_<platform> directory.
# The view_root variable is used to specify the <view>/lib directory.
my_script_name=`echo $0 | awk -F'/' '{print $(NF)}'`
partial_build_scripts_path=`echo $0 | sed "s/\/$my_script_name//"`
cd $partial_build_scripts_path
build_scripts_path=`pwd`
cd ../../../..
build_root=`pwd`
cd ..
view_root=`pwd`

release_unit_info="$build_scripts_path/release_unit_info.sh"

# Read the release unit information.
. $release_unit_info


print_usage ()
{
   echo "Tags and pushes the specified build targets to the origin."
   echo "Usage:"
   echo "   $0 [tag] \"[tgts|all]\""
   echo "Example:"
   echo "   $0 1.1.0.rc1 \"$ru_tgts\""
   echo "      - Tags and pushes the 1.1.0.rc1 build of the $ru_tgts build target"
   echo "   $0 1.1.0.rc1 all"
   echo "      - Tags and pushes the 1.1.0.rc1 build of all of view populated build targets"
   echo " "
}

die ()
{
   msg=$1
   echo "$msg"
   exit 1
}

dprint ()
{
   # Comment the following line to suppress debug messages.
   echo "$1"
}

cd $build_root
if [ ! -d "$ru_local_path" ]
then
   echo "Error could not find the $ru_local_path directory."
   print_usage
   exit 1
fi

# Parameters
if [ $# -lt 1 ]
then
   echo "Error: Not enough parameters."
   print_usage
   exit 1
fi

tag=$1

dprint "build_root = $build_root"
dprint "tag = $tag"
dprint "tgts = $tgts"

cd $build_root/$ru_local_path-a || die "Unable to find $tgt"
atag $tag || die "Error creating the orphan commit for $tgt"
# Remove any intermediate build output.
dprint "Cleaning the build output for $tgt"
git clean -d -f || die "Error cleaning the build output for $tgt"
# Push the output of the build to the server.
echo "Pushing the build output to the server for $tgt $tag"
git push origin refs/tags/$tag || die "Failure pushing $tag for $tgt"

echo "--------------------------------------------------------------------------------"
echo "Successfully tagged and pushed:"
cd $build_root/$ru_local_path-a
url=`git remote -v | grep push | awk '{print $2}'`
echo "   $url  $build_root/$ru_local_path-a"
echo "--------------------------------------------------------------------------------"
