#!/bin/sh

# Use the path from $0 to find the path to the platform root and view root directories.
# The view_root variable is used to specify the <view>/lib directory.
my_script_name=`echo $0 | awk -F'/' '{print $(NF)}'`
build_scripts_rel_path=`echo $0 | sed "s/\/$my_script_name//"`
cd $build_scripts_rel_path
build_scripts_path=`pwd`

cd ../../../..
view_root=`pwd`

release_unit_info="$build_scripts_path/release_unit_info.sh"

# Read the release unit information.
. $release_unit_info

# Set the script_test variable equal to 1 to test the script without actually 
# committing and pushing changes to the repo.
if [ "$script_test" = "1" ]
then
   pre_cmd=echo
else
   pre_cmd=
fi

dprint ()
{
   # Comment the following line to suppress debug messages.
   echo "$1"
}

print_usage ()
{
   echo "Usage:"
   echo "   $0 [atest_tag] \"[tgts|all]\""
   echo "   This script will apply an ATEST tag to the source and specified build targets."
   echo "   This script can be run interactively by passing no parameters on the command line."
   echo "Parameters:"
   echo "   atest_tag - ATEST tag to be applied to the source and build output repos."
   echo "   tgts - Specifying the individual build targets or \"all\" for all build targets." 
   echo "Examples:"
   echo "   $0 "
   echo "     - Invokes the script in interactive mode."
   echo "   $0  ATEST_2015.1.0_MY_CHANGES  tgt_ar_diab_5.9.4.0_PPCVLEEF"
   echo "     - Applies the tag ATEST_2015.1.0_MY_CHANGES on the source and"
   echo "       tgt_ar_diab_5.9.4.0_PPCVLEEF repos."
   echo "   $0  ATEST_2015.1.0_MY_CHANGES  all"
   echo "     - Applies the tag ATEST_2015.1.0_MY_CHANGES on the source and"
   echo "       all of the build output repos."
   echo "Supported build output repos are:"
   echo "   all"
   for tgt in $ru_tgts
   do
      echo "   $tgt"
   done
}

die ()
{
   msg=$1
   
   echo "$msg"
   exit 1
}

if [ "$#" = "2" ]
then
   tag=$1
   tgts=$2
else
   echo -n "Enter ATEST Tag Name:"
   read tag
   echo "Supported Build Target names:"
   echo "   all"
   for tgt in $ru_tgts
   do
      echo "   $tgt"
   done 
   echo -n "Enter Compiler Target Name:"
   read tgts
fi

if [ -z $tag ] || [ -z "$tgts" ]
then
   echo "Both the atest_tag and tgts need to be specified."
   print_usage
   exit 1
fi

dprint "tag = $tag"
dprint "tgts = $tgts"
dprint "pre_cmd = $pre_cmd"

if [ "$tgts" = "all" ]
then
   tgts=$ru_tgts
fi

cd $view_root/$ru_local_path || die "$view_root/$ru_local_path not found"
test -d "$view_root/$ru_local_path/.git" || die "Local $ru_local_path repo does not exist"
branch_name=$(git rev-parse --abbrev-ref HEAD)
if [ -n "$(git status --porcelain)" ]
then 
   echo "Uncommitted changes found on $view_root/$ru_local_path Repo";
   echo "Do you wish commit the changes?"  
   select yn in "Yes" "No"
   do  
      case $yn in
      Yes )
         $pre_cmd git add .
         $pre_cmd git commit -a -m " Committing changes to for ATEST TAG: $tag"
         $pre_cmd git push origin $branch_name
         break;;
      No )
         echo "Please Commit Changes and run the Script again"
         exit;;
      esac
   done
else 
   echo "No uncommitted changes found on $ru_local_path Repo";
fi

for tgt in $tgts
do
   cd $view_root/$ru_local_path-a/$tgt || die "Target $tgt not found under $view_root/$ru_local_path-a"
   test -d "$view_root/$ru_local_path-a/$tgt/.git" || die "Local $view_root/$ru_local_path-a/$tgt repo does not exist"
   branch_name=$(git rev-parse --abbrev-ref HEAD)
   if [ -n "$(git status --porcelain)" ]
   then 
      echo "Uncommitted changes found on $ru_local_path-a/$tgt Repo";
      echo "Do you wish commit the changes?"  
      select yn in "Yes" "No"
      do  
         case $yn in
         Yes )
            if [ $branch_name = master_int ]
            then 
               $pre_cmd git checkout -b $tag
               $pre_cmd git add .
               $pre_cmd git commit -a -m " Committing changes to for ATEST TAG: $tag"
               $pre_cmd git push origin $tag
            else
               $pre_cmd git add .
               $pre_cmd git commit -a -m " Committing changes to for ATEST TAG: $tag"
               $pre_cmd git push origin $branch_name
            fi
            break;;
         No )
            echo "Please Commit Changes and run the Script again"
            exit;;
         esac
      done
   else 
      echo "No uncommitted changes found on $ru_local_path-a/$tgt Repo ";
   fi
done


cd $view_root/$ru_local_path
echo "Applying $tag Tag on $ru_local_path ";
$pre_cmd git tag -m 'ATEST Tag $tag' $tag || die "Error: Setting the ATEST Tag in $ru_local_path"
$pre_cmd git push origin refs/tags/$tag || die "Error: Push tag $tag for $ru_local_path"

for tgt in $tgts
do
   cd $view_root/$ru_local_path-a/$tgt
   echo "Applying $tag TAG on $ru_local_path-a/$tgt Repo ";
   $pre_cmd git tag -m 'ATEST Tag $tag' $tag || die "Error: Setting the ATEST Tag in $ru_local_path-a/$tgts"
   $pre_cmd git push origin refs/tags/$tag || die "Error: Push tag $tag for $ru_local_path-a/$tgts"
done
