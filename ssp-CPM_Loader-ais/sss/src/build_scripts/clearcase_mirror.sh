#!/bin/sh
## Mirror Target Script 

## GIT to Clearcase Mirror Script for SCL Layer
print_usage ()
{
   echo "Usage:"
   echo "   mirror_git_changes_to_cc.sh <options> [ivy_view] [BRANCHPOINT_TAG] [NEW_TAG] [clearcase_view] "
   echo "   clearcase_SCL_mirror.sh /c/ivy/test_view AFSW_SCL_2014.1.0 AFSW_SCL_2013.22.0 /m/cswcm_view/ "
}

die ()
{
   msg=$1
   echo "$msg"
   exit 1
}
cwd=$(pwd)

ivy_view=$1
git_branch_point=$2
git_tag_name=$3
cc_view_path=$4

compare ()
 {
    # compare files
    ivy_path=$1
    ClearCase_path=$2
    layer=$3
    SAVEIFS=$IFS
    IFS=$(echo -en "\n\b")  
    for i in `cat $layer`; do
    cd $ivy_path
#   if cmp -s "$ivy_path/$i" "$ClearCase_path/$i"; then
    if diff -w -arq "$ivy_path/$i" "$ClearCase_path/$i"; then
        echo "-------------------------------------------------------------"
        echo "$ClearCase_path/$i Data are Identical"
        echo "  "
    else
        echo "-------------------------------------------------------------"
        echo "$ClearCase_path/$i Data are not identical"
        echo "  "
        die "Mirrored files are not identical"
    fi
    done
    IFS=$SAVEIFS
}

#Source Repositories 
srcs="lib_sss/sss lib_sss/sss-a"


echo "cwd $cwd"
for src in $srcs
do
temp_del=$cwd/_mirror_temp_del.txt 
temp_add=$cwd/_mirror_temp_add.txt 
temp_mod=$cwd/_mirror_temp_mod.txt
temp_all=$cwd/_mirror_temp_all.txt 

cd $ivy_view/lib/$src
#Find the Added files 
echo "-------------------------------------------------------------"
echo "Find the file Added between $git_branch_point and $git_tag_name"
git diff --diff-filter=A --name-only --summary $git_branch_point $git_tag_name >$temp_add
echo " "

#Find the Deleted files 
echo "-------------------------------------------------------------"
echo "Find the file Deleted between $git_branch_point and $git_tag_name"
git diff --diff-filter=D --name-only --summary $git_branch_point $git_tag_name >$temp_del
echo " "

#Find the Modified files 
echo "-------------------------------------------------------------"
echo "Find the file Changed between $git_branch_point and $git_tag_name"
git diff --diff-filter=M --name-only --summary $git_branch_point $git_tag_name >$temp_mod
echo " "

#Listing all files 
echo "-------------------------------------------------------------"
echo "Listing files on $git_tag_name"
git ls-tree -r --name-only $git_tag_name | grep -v gitignore >$temp_all
echo " "

cd $cwd
#Run the mirroring script passing the temp files 
echo "-------------------------------------------------------------"
echo "Run the mirroring script passing the temp files "
python /c/ivy/scripts/git_to_cc_mirror_diff.py $cc_view_path/$src $ivy_view/lib/$src $temp_mod $temp_add $temp_del

# compare files
compare $ivy_view/lib/$src $cc_view_path/$src $temp_all

# Clearcase Check-in process
cd $cc_view_path/$src
# Checks in all files that are non-identical to predecessor.
cleartool lsco -r -cvi -fmt "ci -nc \"%n\"\n" | cleartool

# cancelling checkout of files that are identical to predecessor. 
cleartool lsco -r -cvi -fmt "unco -rm %n\n" | cleartool
#Delete the temp files 
rm $temp_del
rm $temp_add
rm $temp_mod
rm $temp_all

done
