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

dprint ()
{
   # Comment the following line to suppress debug messages.
   echo "$1"
}

print_usage ()
{
   echo "Creates HAL Ivy Descriptors for $ru_ivy_name"
   echo "Usage:"
   echo "   create_descriptors.sh [Tag Name][IVY Version No] [Type] [[tgt_branch]]"
   echo "Where:"
   echo "   version = Version number, eg. 1.2.0"
   echo "   type    = pre_build, post_build, release, int_latest"
   echo "      pre_build  => src repo = version,    tgt repos = tgt_branch latest"
   echo "      post_build => src repo = no update,  tgt repos = version"
   echo "      release    => src repo = version,    tgt repos = version"
   echo "      int_latest => src repo = int_latest, tgt repos = int_latest"
   echo "   tgt_branch = Used only with the pre_build type"
   echo "Examples:"
   echo "   create_descriptors.sh  "$ru_git_prefix"_1.1.0.rc1 1.1.0.rc1  pre_build  "$ru_rel_branch"_1.1.0.rc"
   echo "   create_descriptors.sh  "$ru_git_prefix"_1.1.0.rc1 1.1.0.rc1  post_build"
   echo "   create_descriptors.sh  "$ru_git_prefix"_1.1.0.rc1 1.1.0      release"
   echo "   create_descriptors.sh  x x int_latest"
}

die ()
{
   msg=$1
   
   echo "$msg"
   exit 1
}

ver=$1

if [ "$ver" != "int_latest" ]
then
   # This is not the "int_latest" descriptor.
   ivy_ver=$2
   type=$3
    if [ $# -lt 3 ]
      then
         echo "Not enough parameters."
         
         print_usage
         exit 1
    fi
else
   # The first parameter was the int_latest option.
   # The second command line parameter is not used with this option.

   type=$1
fi

# src_ver    - Git tag used when creating the descriptors for the source repos
#              eg., 1.1.0, 1.1.0.rc1
# tgt_ver    - Git tag used when creating the descriptors for build output repos
#              eg., 1.1.0, 1.1.0.rc1
# tgt_branch - Git branch used when creating the pre-build descriptors for the build output repos
#              eg., master_1.1.0.rc
# pkg_ver    - Revision used with the package descriptors.
#              eg., 1.1.0, 1.1.0.rc1, 1.1.0.rc1.pre_build, 1.1.0.rc2.pre_build


case "$type" in
"pre_build")  
   src_ver=$ivy_ver
   tgt_ver=
   tgt_branch=$4
   src_ref_type=-t
   src_ref=$ver
   pkg_ver=$ivy_ver.pre_build
   ;;
"post_build")  
   src_ver=$ivy_ver
   tgt_ver=$ver
   tgt_branch=
   src_ref_type=-t
   src_ref=
   pkg_ver=$ivy_ver
   ;;
"release")  
   src_ver=$ivy_ver
   tgt_ver=$ver
   tgt_branch=
   src_ref_type=-t
   src_ref=$ver
   pkg_ver=$ivy_ver
   ;;
"int_latest")
   src_ver=int_latest
   tgt_ver=
   tgt_branch=$ru_int_branch
   src_ref_type=-b
   src_ref=$ru_int_branch
   pkg_ver=int_latest
   ;;
"maint_latest")
   src_ver=$ru_int_branch
   tgt_ver=
   tgt_branch=$ru_int_branch
   src_ref_type=-b
   src_ref=$ru_int_branch
   pkg_ver=$ru_int_branch
   ;;
*)      
   die "Unknown type $type, choose 'pre_build', 'post_build', 'release', 'int_latest' or 'maint_latest'" 
   ;;
esac

dprint "ver          = $ver"
dprint "type         = $type"
dprint "tgt_branch   = $tgt_branch"
dprint "pkg_ver      = $pkg_ver"
dprint "src_ref_type = $src_ref_type"
dprint "src_ref      = $src_ref"

# Determine if the user has the source version of ivyutils or the compiled
# executable version.
ivyu_exe=`which ivyu`
if [ ! -z "$ivyu_exe" ]
then
ivyu=ivyu
else
ivyu=ivyu.py
fi

# ------------------------------------------------------------------------------
template="$build_scripts_path/templates/template.xml"
template_pkg="$build_scripts_path/templates/template_pkg.xml"

add_dep2 ()
{
   none="none"
   desc_name=$1
   desc_ver=$2
   name=$3
   org=$4
   dom=$5
   rev=$6
   cfg=$7

   if [ -z "$cfg" ]
   then
      cfg="*->rel"
   fi 
      echo "Adding dependency to $desc_name $desc_ver"   
   if [ "$cfg" != "$none" ]
   then
        echo "Adding dependency to $desc_name $desc_ver"   
        dprint "$ivyu -d $desc_name $desc_ver addDep -id $dom -dd $name $rev -do $org -c \"$cfg\""
        $ivyu -d $desc_name $desc_ver addDep -id $dom -dd $name $rev -do $org -c "$cfg" || die "Error adding dependency $name $rev to $file"
   else
   
        echo "Adding dependency to $desc_name $desc_ver"   
        dprint "$ivyu -d $desc_name $desc_ver addDep -id $dom -dd $name $rev -do $org "
        $ivyu -d $desc_name $desc_ver addDep -id $dom -dd $name $rev -do $org || die "Error adding dependency $name $rev to $file"
   fi
}


root_dir=`pwd`

tag=$ver

$ivyu cleancache

echo "--------------------------------------------------------------------------------"
echo ">>> Release $tag <<<"
 
# Create the package descriptors that provide combinations of build targets.
# The hal_pkg_all descriptor is used to hold all of the targets.
echo "--------------------------------------------------------------------------------"
echo "Creating Ivy descriptor for "$ru_ivy_name"_pkg_all"
$ivyu -d $ru_ivy_path/$ru_ivy_name"_pkg_all" $pkg_ver newMod -id ivy-csf -tmpli $template_pkg -ovm always || die "Error: Creating "$ru_ivy_name"_pkg_all descriptor."
 
if [ "$type" != "post_build" ]
then
   # Create the Ivy descriptors for the source repos.
   echo "--------------------------------------------------------------------------------"
   echo "Creating $ru_ivy_name $src_ver descriptor."
   $ivyu -d $ru_ivy_path/$ru_ivy_name $src_ver newMod.git -id ivy-csf -s $ru_git_url $src_ref_type $src_ref -l $ru_local_path -ovm always || die "Error: Creating $ru_ivy_name $src_ver descriptor."
fi

echo "--------------------------------------------------------------------------------"
echo "Creating Ivy descriptor for $ru_ivy_name-a"
# HAL Layer
if [ ! -z "$tgt_ver" ]
then
   $ivyu -d $ru_ivy_path/$ru_ivy_name-a $pkg_ver newMod.git -id ivy-csf -s  $ru_git_url-a -t $tgt_ver -l $ru_local_path-a -tmpli $template -ovm always || die "Error: Creating $ru_ivy_name-a $pkg_ver descriptor"
fi

if [ ! -z "$tgt_branch" ]
then
   $ivyu -d $ru_ivy_path/$ru_ivy_name-a $pkg_ver newMod.git -id ivy-csf -s  $ru_git_url-a -b $tgt_branch -l $ru_local_path-a -tmpli $template -ovm always || die "Error: Creating $ru_ivy_name-a $pkg_ver descriptor"
fi

# Create the Ivy descriptors for each of the build target repos.
for tgt in $ru_tgts
do
   echo "--------------------------------------------------------------------------------"
   echo "Creating Ivy descriptor for $ru_ivy_name-a"
   # HAL Layer
   if [ ! -z "$tgt_ver" ]
   then
      $ivyu -d $ru_ivy_path/$ru_ivy_name-$tgt-a $pkg_ver newMod -id ivy-csf -tmpli $template_pkg -ovm always || die "Error: Creating $ru_ivy_name-$tgt-a $pkg_ver descriptor"
   fi

   if [ ! -z "$tgt_branch" ]
   then
      $ivyu -d $ru_ivy_path/$ru_ivy_name-$tgt-a $pkg_ver newMod -id ivy-csf -tmpli $template_pkg -ovm always || die "Error: Creating $ru_ivy_name-$tgt-a $pkg_ver descriptor"
   fi

   # Add the dependencies of the source repo.
   add_dep2 $ru_ivy_path/$ru_ivy_name-$tgt-a $pkg_ver $ru_ivy_path/$ru_ivy_name     com.cat.e  ivy-csf  $src_ver            "*->rel"

   echo "Adding dependencies descriptor to $ru_ivy_path/$ru_ivy_name-"$tgt"-a"
   add_dep2 $ru_ivy_path/$ru_ivy_name-$tgt-a $pkg_ver $ru_ivy_path/$ru_ivy_name-a   com.cat.e  ivy-csf  $pkg_ver            "*->rel"

   
   echo "Adding target specific dependencies to $ru_ivy_path/$ru_ivy_name-$tgt-a "
   num_deps=${#ru_common_deps[@]}
   for (( index = 0; index < $num_deps; index = index + 5 ))
   do
      dep_name=${ru_common_deps[$index]}
      dep_ver=${ru_common_deps[$index + 1]}
      dep_org=${ru_common_deps[$index + 2]}
      dep_dom=${ru_common_deps[$index + 3]}
      dep_cfg=${ru_common_deps[$index + 4]}
   
      add_dep2 $ru_ivy_path/$ru_ivy_name-$tgt-a   $pkg_ver  $dep_name  $dep_org  $dep_dom  $dep_ver  $dep_cfg
   done

   # Add each tgt descriptor to the pkg descriptor using the nodep config.
   add_dep2 $ru_ivy_path/$ru_ivy_name"_pkg_all" $pkg_ver $ru_ivy_path/$ru_ivy_name-$tgt-a        com.cat.e ivy-csf  $pkg_ver              "none"


   echo "--------------------------------------------------------------------------------"
   echo "Adding target specific dependencies to $ru_ivy_name-$tgt-a "
   case "$tgt" in
   "tgt_ar_diab_5.9.4.0_PPCVLEEF")
       echo "Adding target specific dependencies to $ru_ivy_path/boot-a "
       num_deps=${#ru_tgt_ar_diab_5_9_4_0_PPCVLEEF_deps[@]}
       for (( index = 0; index < $num_deps; index = index + 5 ))
       do
          dep_name=${ru_tgt_ar_diab_5_9_4_0_PPCVLEEF_deps[$index]}
          dep_ver=${ru_tgt_ar_diab_5_9_4_0_PPCVLEEF_deps[$index + 1]}
          dep_org=${ru_tgt_ar_diab_5_9_4_0_PPCVLEEF_deps[$index + 2]}
          dep_dom=${ru_tgt_ar_diab_5_9_4_0_PPCVLEEF_deps[$index + 3]}
          dep_cfg=${ru_tgt_ar_diab_5_9_4_0_PPCVLEEF_deps[$index + 4]}
       
          add_dep2 $ru_ivy_path/$ru_ivy_name-$tgt-a   $pkg_ver  $dep_name  $dep_org  $dep_dom  $dep_ver  $dep_cfg
       done
      ;;
   "tgt_diab_5.8.0.0_PPCVLEEF")
       echo "Adding target specific dependencies to $ru_ivy_path/boot-a "
       num_deps=${#ru_tgt_diab_5_8_0_0_PPCVLEEF_deps[@]}
       for (( index = 0; index < $num_deps; index = index + 5 ))
       do
          dep_name=${ru_tgt_diab_5_8_0_0_PPCVLEEF_deps[$index]}
          dep_ver=${ru_tgt_diab_5_8_0_0_PPCVLEEF_deps[$index + 1]}
          dep_org=${ru_tgt_diab_5_8_0_0_PPCVLEEF_deps[$index + 2]}
          dep_dom=${ru_tgt_diab_5_8_0_0_PPCVLEEF_deps[$index + 3]}
          dep_cfg=${ru_tgt_diab_5_8_0_0_PPCVLEEF_deps[$index + 4]}
       
          add_dep2 $ru_ivy_path/$ru_ivy_name-$tgt-a   $pkg_ver  $dep_name  $dep_org  $dep_dom  $dep_ver  $dep_cfg
       done
      ;;
   *)
      die "Unsupported build target $tgt."
      ;;
   esac


done
# Publish the descriptors.
if [ ! -z "$src_ver" ]
then
   # Publish the source descriptors.
   echo "--------------------------------------------------------------------------------"
   echo "Publishing $ru_ivy_name $src_ver"
   $ivyu -d $ru_ivy_path/$ru_ivy_name $src_ver  publish -ov || die "Error: Publishing $ru_ivy_name $src_ver"
fi

# Publish the target descriptors.
echo "--------------------------------------------------------------------------------"
echo "Publishing $ru_ivy_name-a $pkg_ver"
$ivyu -d $ru_ivy_path/$ru_ivy_name-a $pkg_ver  publish -ov || die "Error: Publishing $ru_ivy_name-a $pkg_ver"

for tgt in $ru_tgts
do
   # Publish the target descriptors.
   echo "--------------------------------------------------------------------------------"
   echo "Publishing $ru_ivy_name-$tgt-a $pkg_ver"
   $ivyu -d $ru_ivy_path/$ru_ivy_name-$tgt-a     $pkg_ver  publish -ov || die "Error: Publishing the $tgt descriptor"
done

echo "--------------------------------------------------------------------------------"
echo "Publishing "$ru_ivy_name"_pkg_all $pkg_ver"
$ivyu -d cat/ess-csf/$ru_ivy_name"_pkg_all" $pkg_ver publish -ov  || die "Error: Publishing "$ru_ivy_name"_pkg_all descriptor."

echo "Success"

