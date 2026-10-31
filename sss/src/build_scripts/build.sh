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

# Base the number of parallel jobs on the number of processor cores.
if [ "$PROCESSOR_LEVEL" != "" ]
then
   parallel_jobs=$((PROCESSOR_LEVEL * 2))
else
   parallel_jobs=4
fi


print_usage ()
{
   echo "Usage:"
   echo "   $0 [[local]|cluster|lp]"
   echo "   local [Default] - Performs build locally using emake."
   echo "   cluster         - Performs build using cluster servers."
   echo "   lp              - Performs build locally using $parallel_jobs parallel jobs"
   echo "Example:"
   echo "   $0  [[local]|cluster|lp]"
   echo "      - Builds of all of view populated build targets"
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

tgts=$ru_tgts

case "$1" in
"cluster")
   builder="$build_root/dev_tools/ec_tools/ec_build/ec_build.exe --file=$build_root/$ru_local_path/src/build_scripts/ec_build.xml --localBuild"
   ;;
"lp")
   builder="$build_root/oss/make/bin/make.exe -j$parallel_jobs"
   ;;
*)      
   builder="emake --win32"
   ;;
esac


dprint "view_root = $view_root"
dprint "build_root = $build_root"
dprint "tgts = $tgts"
dprint "builder = $builder"
dprint "parallel_jobs = $parallel_jobs"

for tgt in $tgts
do
   # Set the make targets based on the build target.
   case "$tgt" in
   "tgt_ar_diab_5.9.4.0_PPCVLEEF")
      make_tgts=libs
      make_tgts_app=apps
      ;;
   "tgt_diab_5.8.0.0_PPCVLEEF")
      make_tgts=libs
      make_tgts_app=apps
      ;;
   *)      
      die "Unsupported build target $tgt" 
      ;;
   esac
   

   # Build the target tree.
   if [ ! -z "$make_tgts" ]
   then
      echo "Cleaning the HAL Layer $tgt"
      rm -rf $build_root/$ru_local_path-a/$tgt/app
      rm -rf $build_root/$ru_local_path-a/$tgt/lib
      rm -rf $build_root/$ru_local_path-a/$tgt/doc
      cd $build_root/$ru_local_path/src/makefiles || die "Could not find hal/src/makefiles"
      echo "Creating the build target tree $tgt"
      emake --win32 $tgt tree || die "Error creating the target tree for $tgt"
      cd $build_root/$ru_local_path-a/$tgt
      echo "Building $make_tgts for $tgt"
      if [ -n "$EMAKE" ]
      then
         if [ -z "$libdirs" ]
         then
            emake --win32  $make_tgts -B || die "Error building $make_tgts for $tgt"
         else
            emake --win32  $make_tgts LIBDIRS="$libdirs" -B || die "Error building $make_tgts for $tgt"
         fi
         if [ -n "$make_tgts_app" ]
         then
            if [ -z "$appdirs" ]
            then
               emake --win32 $make_tgts_app || die "Error building $make_tgts for $tgt"
            else
               emake --win32 $make_tgts_app APPDIRS="$appdirs" || die "Error building $make_tgts for $tgt"
            fi
         else
            echo " No Test Apps to Build"
         fi
      else
         if [ -z "$libdirs" ]
         then
            $builder $make_tgts -B || die "Error building $make_tgts for $tgt"
         else
            $builder $make_tgts LIBDIRS="$libdirs" -B || die "Error building $make_tgts for $tgt"
         fi
         if [ -n "$make_tgts_app" ]
         then
            if [ -z "$appdirs" ]
            then
               $builder $make_tgts_app || die "Error building $make_tgts for $tgt"
            else
               $builder $make_tgts_app APPDIRS="$appdirs" || die "Error building $make_tgts for $tgt"
            fi
         else
            echo " No Test Apps to Build"
         fi
      fi
   fi

done

log_file=build_env.txt

cd $view_root
repos=`find . -name *.git`


# Assemble the log file.

# Print the environment variables to the log_file.
echo "Environment variables set at the time of the build." > $view_root/$log_file
echo "-------------------------------------------------------------------------------" >> $view_root/$log_file
env >> $view_root/$log_file
echo "-------------------------------------------------------------------------------" >> $view_root/$log_file

for repo in $repos
do 
   local_path=`echo $repo | sed "s|/.git||g"`
   # Print the local path in the log_file.
   echo "$local_path" >> $view_root/$log_file
   # Print the URL of the repo to the log_file.
   git --git-dir=$repo remote -v >> $view_root/$log_file
   # Print the commit ID to the log_file.
   git --git-dir=$repo log -1 --decorate >> $view_root/$log_file
   echo "-------------------------------------------------------------------------------" >> $view_root/$log_file
done


# Copy the log file to each of the build targets.
for tgt in $tgts
do
   cp  $view_root/$log_file $view_root/lib/$ru_local_path-a/$tgt/$log_file
done


rm $view_root/$log_file


echo "--------------------------------------------------------------------------------"
echo "Successfully built:"
for tgt in $tgts
do 
   echo "   $tgt"
done
echo "--------------------------------------------------------------------------------"
