#! /usr/bin/env python
"""
0executeBuildOrRelease.py
  Usage:
    Double-click 0executeBuildOrRelease.cmd

  Description:
    This function is meant to be used by the
    developer to launch either a build or
    release.

    In a build, all of the derived content in
    /lib_simulink-a/ is removed and then recreated
    from the source files in /lib_simulink/.  The
    derived content is committed and Ivy
    descriptors published using the current
    branch of lib_simulink.

    The user will be able to select which
    supported targets are built.

    In a release, new tags are applied in git
    and new Ivy descriptors are published for
    existing content.  This requires a new
    commit for the derived content.

    Both of these create a new view, and thus
    update the local descriptor for /lib_simulink/.
"""

import collections
import datetime
import logging
import os
import re
import shutil
import subprocess
import time
import xml.etree.ElementTree as ET


# Global configuration
#   _PUSH_TO_SERVER, whether to push anything off this PC
_PUSH_TO_SERVER = True
#   _TARGETS, set of supported targets and a description for each
BuildTarget = collections.namedtuple('BuildTarget', ['name', 'desc', 'has_aggregate'])
_TARGETS = frozenset([
    BuildTarget(r'tgt_ar_diab_5.9.4.0_PPCVLEEF', r'diab 5.9.4 - A6 / AUTOSAR', True),
    BuildTarget(r'tgt_cc32r_4.30_M32Rx'        , r'cc32r 4.30 - B4M1/B5M1'   , False),
    BuildTarget(r'tgt_diab_4.2b_PPC555EH'      , r'diab 4.2b  - A4'          , True),
    BuildTarget(r'tgt_diab_5.8.0.0_PPCVLEEF'   , r'diab 5.8   - A5'          , True),
    BuildTarget(r'tgt_sim_gcc_4.8.2_x86-64'    , r'gcc 4.8.2  - PC'          , True),
    BuildTarget(r'tgt_rvct_2.1_ARM7TDMI'       , r'rvct 2.1   - A5M1/2/8'    , True)
])


def main():
    """ Main entry point to application """

    # Initialize logging
    configure_logging()

    # Notify user process has started
    log_and_print_info("lib_simulink executeBuildOrRelease.py started")

    # Query user for information
    usr_choice = query_user()
    if 'cancel' == usr_choice.action:
        return

    # Notify user automated process has started
    log_and_print_info("\n\nUser input complete, automated build starting")

    # Create new view if required
    if 'LocallyBuildOneTarget' == usr_choice.action:
        ivy_view = retrieve_current_view_lib()
    else:
        ivy_view = create_new_view(usr_choice)

    # If simply retagging, go do that and exit
    if 'RetagRelease' == usr_choice.action:
        retag_release(usr_choice, ivy_view)
        log_and_print_info("Successfully completed applying {0} in {1}".format(usr_choice.new_tag, ivy_view))
        return

    # Tag the source repo so it can be referenced
    tag_lib_simulink_at_start(ivy_view, usr_choice.new_tag)

    # Call oel build scripts to regenerate the tree
    #   Must delete what's there first, or the build script fails
    delete_lib_simulink_a_contents(ivy_view)
    call_make(ivy_view, r'lib_autocode_release\lib_simulink\src\makefiles', ['tree', 'all'], True)

    # For each target, rebuild from source and commit to orphan commit
    if 'LocallyBuildOneTarget' == usr_choice.action:
        targets = None
        for tst in _TARGETS:
            if tst.name == usr_choice.target:
                targets = frozenset([tst])
        if targets is None:
            log_and_raise_exception("Didn't expect targets to be None")
    else:
        targets = _TARGETS
    for target in targets:
        rebuild_target(ivy_view, target.name, usr_choice.new_tag)

    # If doing a complete local build, complete the release process
    if "BuildReleaseCandidate" == usr_choice.action:
        publish_tag(ivy_view, usr_choice.new_tag)


""" Current directory when module loaded """
__initWorkingDirectory = os.getcwd()


def retrieve_launch_directory():
    """ Return folder that was the current directory when started """
    return os.path.abspath(__initWorkingDirectory)


def configure_logging():
    """ Configure logging for the application, this will log INFO messages to STDOUT and DEBUG to file """
    # Set the basic configuration
    logging.basicConfig(
        level=logging.DEBUG,
        format='%(asctime)s %(levelname)-8s:%(name)-5s:%(message)s',
        datefmt='%m/%d/%Y %I:%M:%S %p',
        filename=os.path.join(retrieve_launch_directory(), '0executeBuildOrRelease.log'),
        filemode='w')
    logging.captureWarnings(True)
    # define a Handler which writes INFO messages or higher to the sys.stderr
    console = logging.StreamHandler()
    console.setLevel(logging.INFO)
    # choose a simpler format for the screen
    formatter = logging.Formatter('%(message)s')
    console.setFormatter(formatter)
    # add extra handler
    logging.getLogger('').addHandler(console)


def log_and_raise_exception(msg):
    """ Log an error and raise an exception to exit """
    logging.error(msg)
    raise Exception(msg)


def log_and_print_info(msg):
    """
    Print an informational message and log it.
    :param msg: The message to log and display
    """
    # configure_logging() has configured to post to both screen and file
    logging.info(msg)


def exec_cmd(args, directory, purpose=None, may_fail=False):
    """
    Execute command, logging input and output
    :param args: Name of executable, followed by list of arguments
    :param directory: Absolute path of the directory where the command will be executed
    :param may_fail: Set to true if non-zero returncode is acceptable
    :param purpose: Description of purpose of the command, for the log
    :return: Output from STDOUT and STDERR
    """

    # Calculate environment
    des_env = calculate_desired_environment()

    # Log that about to start the command
    if purpose is None:
        log_and_print_info("About to execute {} in '{}'".format(args, directory))
    else:
        log_and_print_info("To {},\nabout to execute {} in '{}'".format(purpose, args, directory))

    # Execute the command, capturing errors
    try:
        output = subprocess.check_output(args, cwd=directory, stderr=subprocess.STDOUT, env=des_env)
        if purpose is None:
            log_and_print_info("Command {} in '{}' completed successfully:\n{}".format(
                args, directory, output)
            )
        else:
            log_and_print_info("Attempt to {} completed successfully:\n{}".format(
                purpose, output)
            )

    except subprocess.CalledProcessError as err:
        if may_fail:
            output = err.output
            if purpose is None:
                log_and_print_info(
                    "Command {} in '{}' returncode was {}, but this is acceptable:\n{}".format(
                        args, directory, err.returncode, output
                    ))
            else:
                log_and_print_info(
                    "Attempt to {} failed, but this is acceptable\nCommand {} in '{}' returncode was {}:\n{}".format(
                        purpose, args, directory, err.returncode, output
                    )
                )
        else:
            if purpose is None:
                log_and_raise_exception("Command {} in '{}' returncode was {}:\n{}".format(
                    args, directory, err.returncode, err.output
                ))
            else:
                log_and_raise_exception(
                    "Attempt to {} failed,\nCommand {} in '{}' returncode was {}:\n{}".format(
                        purpose, args, directory, err.returncode, err.output
                    )
                )

    # Return output
    return output


UserChoices = collections.namedtuple('UserChoices',
                                     ['action', 'target', 'old_tag', 'new_tag'])


def query_user():
    """
    Query the user what to do
    :return: User selections
    """

    # Ask user what they would like to do
    print("Select desired action:")
    print(" 1. Build one target in this view")
    print("     - Reuses this view")
    print("     - Tags lib_simulink and lib_simulink-a with generated tag that shouldn't be pushed")
    print("     - Skips all other releasing steps")
    print("     - Intended for iterative development")
    print(" 2. Build release candidate in new view")
    print("     - Performs work in a new view")
    print("     - Tags lib_simulink and lib_simulink-a with specified tag")
    print("     - Performs local release steps, including push to server")
    print("     - Requires access to all compilers")
    print("     - Intended for release candidate creation")
    print(" 3. Retag release candidate in new view")
    print("     - Performs work in a new view")
    print("     - Tags existing content with a new tag")
    print("     - Pushes result to the server")
    print("     - Intended for final release creation")
    print(" 0. Exit without doing anything")
    choice = raw_input('Enter the number of your choice: ')

    # Validate the choice
    if "0" == choice.strip():
        action = "cancel"
    elif "1" == choice.strip():
        action = "LocallyBuildOneTarget"
    elif "2" == choice.strip():
        action = "BuildReleaseCandidate"
    elif "3" == choice.strip():
        action = "RetagRelease"
    else:
        log_and_raise_exception(
            "Requested user select action to take, and didn't recognize response '{0}'.".format(choice)
        )
    if "cancel" == action:
        log_and_print_info("User chose to cancel the operation")
        return UserChoices('cancel', None, None, None)

    # Ask user what label is being retagged, and to what
    if "RetagRelease" == action:
        old_tag = raw_input("\nEnter the existing git tag: ")
        new_tag = raw_input("Enter the new git tag to apply and publish: ")
        if "" == old_tag.strip() or "" == new_tag.strip():
            log_and_raise_exception(
                "Invalid git tags provided:\nold_tag = '{0}'\nnew_tag = '{1}'".format(old_tag, new_tag)
            )
    elif "BuildReleaseCandidate" == action:
        old_tag = None
        new_tag = raw_input("Enter the new git tag to apply and publish: ")
        if "" == new_tag.strip():
            log_and_raise_exception(
                "Invalid git tag provided:\nnew_tag = '{1}'".format(new_tag)
            )
    elif "LocallyBuildOneTarget" == action:
        old_tag = None
        new_tag = datetime.datetime.fromtimestamp(time.time()).strftime('AUTOMATED_DEVELOPMENT_BUILD_%Y_%m_%d_%H_%M_%S')
    else:
        old_tag = None
        new_tag = None

    # Ask user what target to build
    if "LocallyBuildOneTarget" == action:
        targets = list(_TARGETS)
        print("\nSelect target to build:")
        for idx in range(0, len(targets)):
            print("  {0}. {1}".format(idx + 1, targets[idx].desc))
        print("  0. Exit without doing anything")
        choice = raw_input('Enter the number of your choice: ')

        # Validate the choice
        if "0" == choice.strip():
            action = 'Cancel'
            lcl_target = 'Cancel'
        else:
            lcl_target = None
            for idx in range(0, len(targets)):
                if "{0}".format(idx + 1) == choice.strip():
                    lcl_target = targets[idx].name
            if not lcl_target:
                log_and_raise_exception(
                    "Requested user select action to take, and didn't recognize response '{0}'.".format(choice)
                )
    else:
        lcl_target = None

    # Package and return responses
    return UserChoices(action, lcl_target, old_tag, new_tag)


def calculate_desired_environment(view_dir=None):
    """
    Clones the initial environment, and constructs a minimal path to minimize PC variability
    :param view_dir: Absolute path to the view/lib directory, if not provided python and make aren't on the path
    :return: A dictionary based on the inherited environment that can be passed to subprocess env
    """
    # Determine where git.exe is located
    git_dir = os.path.dirname(retrieve_git_exe())
    # Determine where ivyu.exe is located
    ivyu_dir = os.path.abspath(os.path.join(retrieve_ivy_project_dir(), 'ivyutil'))
    if not os.path.isfile(os.path.join(ivyu_dir, 'ivyu.exe')):
        log_and_raise_exception("Didn't find ivyu.exe in '{0}'".format(ivyu_dir))
    # Construct path
    env = os.environ.copy()
    env['PATH'] = (
        os.path.abspath(os.path.join(env['SYSTEMROOT'], 'system32')) +
        os.pathsep + env['SYSTEMROOT'] +
        os.pathsep + os.path.abspath(os.path.join(env['SYSTEMROOT'], r'system32\Wbem')) +
        os.pathsep + git_dir +
        os.pathsep + ivyu_dir
    )
    if view_dir:
        env['PATH'] = (
            env['PATH']
            + os.pathsep + os.path.abspath(os.path.join(view_dir, r'com.portablepython\oss\portable_python\2.7.6.1'))
            + os.pathsep + os.path.abspath(os.path.join(view_dir, r'com.cat.e\cat\dt\catutils_deps\make\bin'))
        )
    # Attempt to remove DIABLIB from environment, to avoid conflicts between diab versions
    if 'DIABLIB' in env:
        del env['DIABLIB']
    # Return result
    return env


def retrieve_current_view_lib():
    """
    :return: Path to the current view's lib directory
    """

    # Get the %VIEW%\lib_autocode_release\lib_simulink\src\makefiles absolute path
    cur_directory = retrieve_launch_directory()

    # Return the %VIEW% absolute path
    return os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(cur_directory))))


def retrieve_current_view_dir():
    """
    :return: Path to the current view's view directory, containing ivy.xml
    """

    # Get the view's lib directory
    lib_dir = retrieve_current_view_lib()

    # Get the .ivy-view path
    view_file = os.path.join(lib_dir, '.ivy-view')
    if not os.path.isfile(view_file):
        log_and_raise_exception("Expected '{0}' to exist, but it didn't.".format(view_file))

    # Load the .ivy-view
    tree = ET.parse(view_file)
    root_elem = tree.getroot()
    view_elem = None
    for element in root_elem.iter('view-root'):
        view_elem = element
    if view_elem is None:
        log_and_raise_exception("Expected '{0}' to contain a view-root element, but it didn't.".format(view_file))

    # Return the path
    if not view_elem.attrib['path']:
        log_and_raise_exception(("Expected '{0}' to contain one 'view-root' element "
                                 "with a 'path', but it didn't.").format(view_file))
    return os.path.abspath(view_elem.attrib['path'])


def retrieve_ivy_project_dir():
    """
    :return: Absolute path to the Ivyu project directory
    """

    # Get the view's lib directory
    lib_dir = retrieve_current_view_lib()

    # Get the .ivy-view path
    view_file = os.path.join(lib_dir, '.ivy-view')
    if not os.path.isfile(view_file):
        log_and_raise_exception("Expected '{0}' to exist, but it didn't.".format(view_file))

    # Load the .ivy-view
    tree = ET.parse(view_file)
    root_elem = tree.getroot()
    view_elem = None
    for element in root_elem.iter('view-root'):
        view_elem = element
    if view_elem is None:
        log_and_raise_exception("Expected '{0}' to contain a view-root element, but it didn't.".format(view_file))

    # Return the path with the name stripped off
    if not view_elem.attrib['path']:
        log_and_raise_exception(("Expected '{0}' to contain one 'view-root' element "
                                 "with a 'path', but it didn't.").format(view_file))
    view_dir = view_elem.attrib['path']
    if not view_elem.attrib['name']:
        log_and_raise_exception(("Expected '{0}' to contain one 'view-root' element "
                                 "with a 'name', but it didn't.").format(view_file))
    view_name = view_elem.attrib['name']
    return os.path.abspath(view_dir[:(-1 * len(view_name))])


def retrieve_git_exe():
    """
    :return: Returns the absolute path to git.exe, as documented in $IvyProj\.ivy-proj
    """

    # Load the .ivy-proj filename as XML
    filename = os.path.abspath(os.path.join(retrieve_ivy_project_dir(), '.ivy-proj'))
    if not os.path.isfile(filename):
        log_and_raise_exception("File '{0}' doesn't exist".format(filename))
    tree = ET.parse(filename)
    root_elem = tree.getroot()
    git_elem = root_elem.find('git-cmd')
    if git_elem is None:
        log_and_raise_exception("Expected {0} to contain a git-cmd element".format(filename))

    # Check and validate the path
    git_path = git_elem.attrib['path']
    if not git_path:
        log_and_raise_exception("Expected {0} to contain a git-cmd element with a path attribute".format(filename))
    if not os.path.isfile(git_path):
        log_and_raise_exception(
            "File {0} thinks git is at {1}, but that filename doesn't exist".format(filename, git_path)
        )
    return git_path


def retrieve_git_branch():
    """
    :return: git branch of the original repository
    """
    branch = exec_cmd(
        ['git', 'rev-parse', '--abbrev-ref', 'HEAD'],
        retrieve_launch_directory()
    )
    branch = branch.strip()
    if 'HEAD' == branch:
        # Return's HEAD when no branch is checked out
        return None
    else:
        return branch


def remove_lib_simulink_descriptor(revision):
    """
    Remove the lib_simulink Ivy revision from the local ivy-xml directory
    :param revision: Text with the name of the revision to remove
    """

    # Determine the absolute path
    rev_dir = os.path.join(retrieve_ivy_project_dir(), 'ivy-xml', 'ivy-dt', 'com.cat.e', 'cat', 'dt', 'libsl',
                           revision)

    # Take appropriate action
    if os.path.isdir(rev_dir):
        delete_directory(rev_dir)
    else:
        log_and_print_info(
            "Asked to delete lib_simulink revision '{0}', but '{1}' doesn't exist.".format(revision, rev_dir))


def delete_directory(name):
    """
    Attempt to efficiently delete directories on Windows
    :param name: Absolute path of the directory to delete
    """
    if os.path.isdir(name):
        log_and_print_info("About to delete '{}'".format(name))
        exec_cmd(['cmd', '/c', 'DEL', '/f', '/s', '/q', name], os.path.dirname(name))
        exec_cmd(['cmd', '/c', 'RMDIR',     '/s', '/q', name], os.path.dirname(name))
        log_and_print_info("Successfully deleted '{}'".format(name))
    else:
        log_and_print_info("Directory '{}' doesn't exist, won't try to delete".format(name))


def test_git_repo_is_clean(repo):
    """
    :param repo: Absolute path to a directory in the git repository to test
    :return: True if the repository is clean, False otherwise
    """

    # Validate input
    repo_abs = os.path.abspath(repo)
    if not os.path.isdir(repo_abs):
        log_and_raise_exception("'{}' resolved to '{}', which doesn't exist".format(repo, repo_abs))

    # Check git repo status
    output = exec_cmd(['git', 'status', '--porcelain'], repo_abs)
    if output.strip():
        # Non-empty string detected
        log_and_print_info("It appears git repository {} is not clean:\n{}".format(repo_abs, output))
        return False
    else:
        log_and_print_info("It appears git repository {} is clean at this time".format(repo_abs))
        return True


def tag2rev(tag):
    """
    :param tag: Git tag that we wish to depend upon
    :return: Ivy revision with 'LIB_SIMULINK_' prefix removed
    """
    if tag.startswith('LIB_SIMULINK_'):
        return tag[len('LIB_SIMULINK_'):]
    else:
        return tag


def create_new_view(usr_choice):
    """
    This function will create a new view in parallel with the existing view.  When building a release candidate, only
    a dependency on lib_simulink's build configuration is added.  When retagging, a dependency on each of the -a repos
    is added.

    :param usr_choice: User selections
    :return: Path to the new view's lib directory
    """

    if 'BuildReleaseCandidate' == usr_choice.action:
        # Need to ensure that everything is checked in and on a branch, and that the
        # Ivy descriptor for the branch is up to date

        # Check that we're on a branch
        cur_branch = retrieve_git_branch()
        if not cur_branch:
            log_and_raise_exception(
                "Asked to build release candidate, but '{0}' isn't on a branch".format(retrieve_launch_directory())
            )

        # Check that everything is checked in
        output = exec_cmd(['git', 'status', '--porcelain'], retrieve_launch_directory())
        if output.strip():
            # Non-empty string detected
            log_and_raise_exception(
                "Git repository '{0}' is not clean:\n{1}".format(retrieve_launch_directory(), output)
            )
        else:
            log_and_print_info(
                "Git repository '{0}' is clean".format(retrieve_launch_directory())
            )

        # Remove any existing descriptor
        remove_lib_simulink_descriptor(cur_branch)

        # Push branch to server and create a new descriptor
        exec_cmd(['git', 'push', '--set-upstream', 'origin', cur_branch], retrieve_launch_directory())
        exec_cmd(['ivyu', '-lv', '-d', 'cat/dt/libsl', 'TBD', 'pubFR', '--local', '--branch', cur_branch],
                 retrieve_launch_directory())
    else:
        cur_branch = None

    # Determine the name of the new view
    #   'tLibSlXXX'
    new_name = retrieve_unique_view_name(1)

    # Create the new view
    output = exec_cmd(
        ['ivyu', '-lv', 'project', '--view', new_name],
        retrieve_ivy_project_dir(),
        "create the view {}".format(new_name)
    )
    match_output = re.search('View Create:\s*Created\s+view\s+directory\s+-\s+([^\r\n]+)', output)
    if match_output:
        new_view_dir = os.path.abspath(match_output.group(1))
    else:
        log_and_raise_exception(
            "Tried to create view {0}, but didn't find output directory in the result:\n{1}".format(new_name, output))

    # Add the appropriate dependencies
    if 'BuildReleaseCandidate' == usr_choice.action:
        # Need to add a dependency on the build configuration
        exec_cmd(
            ['ivyu', '-lv', 'addDep', '-id', 'ivy-dt', '-dd', 'cat/dt/libsl', cur_branch, '-c', '*->dev'],
            new_view_dir,
            "add dependency on build configuration of {} in '{}'".format(cur_branch, new_view_dir)
        )

    elif 'RetagRelease' == usr_choice.action:
        # Need to add dependencies on the old -a revisions
        for target in _TARGETS:
            module = 'cat/dt/libsl-{0}-a'.format(target.name)
            exec_cmd(
                ['ivyu', '-lv', 'addDep', '-id', 'ivy-dt', '-dd', module, tag2rev(usr_choice.old_tag), '-c', '*->rel'],
                new_view_dir,
                "add dependency on module '{}', revision '{}'".format(module, usr_choice.old_tag)
            )

    else:
        log_and_raise_exception("Didn't expect usr_choice.action to be '{}'".format(usr_choice.action))

    # Populate the view
    exec_cmd(
        ['ivyu', '-lv', 'retrieve', '--sync'],
        new_view_dir,
        "populate view for {}".format(new_view_dir)
    )

    # Return absolute path to the new view
    return os.path.abspath(os.path.join(new_view_dir, 'lib'))


def retrieve_unique_view_name(cur_count, ivy_project=retrieve_ivy_project_dir()):
    """
    :param cur_count: The current count for finding a unique project name
    :param ivy_project: Absolute path of the Ivy project directory
    :return: Name of the new view (not the absolute path)
    """
    tst_name = 'tLibSl{:0>3}'.format(cur_count)
    tst_path = os.path.join(ivy_project, tst_name)
    if os.path.isdir(tst_path):
        return retrieve_unique_view_name(cur_count + 1, ivy_project)
    else:
        return tst_name


def create_target_ivy_xml(ivy_view, target, des_tag, as_orphan):
    """
    Create ivy.xml and git-repo.xml using popFR, and tag the result
    :param ivy_view: Absolute path of the Ivy view's lib directory
    :param target: Name of the target to process
    :param des_tag: Tag to publish
    :param as_orphan: Boolean to indicate if the new commit should be an orphan commit
    """
    # Calculate some data about this target
    target_dir = os.path.abspath(os.path.join(ivy_view, 'lib_autocode_release', 'lib_simulink-a', target))
    if not os.path.isdir(target_dir):
        log_and_raise_exception("Expected {} to exist in {}, but it doesn't.".format(target_dir, ivy_view))
    target_module = "cat/dt/libsl-{0}-a".format(target)
    target_server = "git@git1.corp.cat.com:/cat/dt/libsl-{0}-a".format(target)
    
    # Use ivyu popFR to create a new ivy.xml and git-repo.xml
    ivy_template = os.path.abspath(os.path.join(retrieve_launch_directory(), 'tgt.ivy.xml'))
    exec_cmd(
        ['ivyu', '-lv', '--dom-name', 'ivy-dt', '-d', target_module, 'TBD', 'popFR',
         '--tag-type', 'prefix', '--tag-val', 'LIB_SIMULINK_', '--branch-type', 'match',
         '--server', target_server, '--templateivy', ivy_template],
        target_dir, "recreate ivy.xml and git-repo.xml using popFR in '{}'".format(target_dir)
    )

    # Use ivyu addDep to add appropriate dependencies
    exec_cmd(
        ['ivyu', '-lv', 'addDep', '-id', 'ivy-dt',
         '-dd', "cat/dt/libsl", tag2rev(des_tag)],
        target_dir, "add dependency for lib_simulink revision {} to {}".format(des_tag, target_dir)
    )

    # Commit the new contents with the latest tag, as orphan or child as appropriate
    args = ['git', 'checkout']
    if as_orphan:
        args.append('--orphan')
    else:
        args.append('-B')
    args.append('tmpBranch')
    exec_cmd(
        args, target_dir,
        "create branch 'tmpBranch in '{}'".format(target_dir)
    )
    if as_orphan:
        exec_cmd(['git', 'rm', '--cached', '-rf', '.'], target_dir,
            "unstage files in '{}'".format(target_dir), may_fail=True)
    exec_cmd(
        ['git', 'add', '--all'], target_dir,
        "stage all changes in '{}'".format(target_dir)
    )
    commit_msg_arg = '--message="Automatic build and tag with {}"'.format(des_tag)
    exec_cmd(
        ['git', 'commit', commit_msg_arg], target_dir,
        "commit all changes in '{}'".format(target_dir)
    )
    exec_cmd(
        ['git', 'tag', '--annotate', commit_msg_arg, des_tag], target_dir,
        "tag commit with '{}' in '{}'".format(des_tag, target_dir)
    )
    exec_cmd(
        ['git', 'checkout', des_tag], target_dir,
        "checkout commit '{}' in '{}'".format(des_tag, target_dir)
    )
    exec_cmd(
        ['git', 'branch', '-D', 'tmpBranch'], target_dir,
        "delete branch 'tmpBranch' in '{}'".format(target_dir)
    )


def publish_tag(ivy_view, tag):
    """
    Complete the common steps for publishing
    1. Push the tag to the server and publish the new Ivy descriptor for lib_simulink
    2. Push the tag to the server and publish the new Ivy descriptor for each target
    3. Commit the changes to ivy-xml and push to the server
    :param ivy_view: Absolute path of the Ivy view
    :param tag: Tag to publish
    """

    # Setup
    libsl_dir = os.path.abspath(os.path.join(ivy_view, 'lib_autocode_release', 'lib_simulink'))

    # 1a. Push the new tag to the server for lib_simulink
    if _PUSH_TO_SERVER:
        exec_cmd(
            ['git', 'push', 'origin', 'tag', tag],
            libsl_dir,
            "push tag {} to server for {}".format(tag, libsl_dir)
        )
    else:
        log_and_print_info(('Asked not to push anything to server, must manually run:\n'
                            'cd "{}" && git push origin tag "{}"').format(libsl_dir, tag))

    # 1b. Publish lib_simulink's new Ivy descriptor
    arg_list = ['ivyu', '-lv', '-d', 'cat/dt/libsl', 'TBD', 'pubFR', '--tag', tag]
    if not _PUSH_TO_SERVER:
        arg_list.append('--local')
    exec_cmd(arg_list, libsl_dir, "publish Ivy descriptor '{}' for '{}'".format(tag, libsl_dir))

    # 2. For each -a repository:
    for target in _TARGETS:
        # Calculate some data about this target
        target_dir = os.path.abspath(os.path.join(ivy_view, 'lib_autocode_release', 'lib_simulink-a', target.name))
        if not os.path.isdir(target_dir):
            log_and_raise_exception("Expected {} to exist in {}, but it doesn't.".format(target_dir, ivy_view))
        target_module = "cat/dt/libsl-{0}-a".format(target.name)

        # 2a. Push the new tag to the server for each target
        if _PUSH_TO_SERVER:
            exec_cmd(
                ['git', 'push', 'origin', 'tag', tag],
                target_dir,
                "push tag {} to server for {}".format(tag, target_dir)
            )
        else:
            log_and_print_info(('Asked not to push anything to server, must manually run:\n'
                                'cd "{}" && git push origin tag "{}"').format(target_dir, tag))

        # 2b. Publish each target's new Ivy descriptor
        arg_list = ['ivyu', '-lv', '-d', target_module, 'TBD', 'pubFR', '--tag', tag]
        if not _PUSH_TO_SERVER:
            arg_list.append('--local')
        exec_cmd(arg_list, target_dir, "publish Ivy descriptor '{}' for '{}'".format(tag, target_dir))

    # 3. Commit the changes to ivy-xml and push to the server
    repo = os.path.abspath(os.path.join(retrieve_ivy_project_dir(), 'ivy-xml', 'ivy-dt'))
    if not os.path.isdir(repo):
        log_and_raise_exception("Expected {} to exist".format(repo))
    exec_cmd(
        ['git', 'pull', 'origin'], repo,
        "pull latest changes from server for Ivy descriptor repo '{}'".format(repo)
    )
    exec_cmd(
        ['git', 'add', '--all'], repo,
        "stage all changes in Ivy descriptor repo {}".format(repo)
    )
    exec_cmd(
        ['git', 'commit', '--message="{}"'.format(tag)], repo,
        "commit all changes in Ivy descriptor repo '{}'".format(repo)
    )
    if _PUSH_TO_SERVER:
        exec_cmd(
            ['git', 'push', '--set-upstream', 'origin'], repo,
            "push changes to server for Ivy descriptor repo '{}'".format(repo)
        )
    else:
        log_and_print_info(('Asked not to push anything to server, must manually run:\n'
                            'cd "{}" && git push --set-upstream origin'.format(repo)))


def retag_release(usr_choice, ivy_view):
    """
    Perform the retag operation on a freshly retrieved Ivy view
    1. Tag lib_simulink with the new git tag
    2. For each -a repository:
    2a. Delete the existing ivy.xml and git-repo.xml
    2b. Use ivyu popFR to create a new ivy.xml and git-repo.xml
    2c. Use ivyu addDep to add appropriate dependencies
    2d. Commit the new contents with the latest tag, branching from the existing commit rather than as an orphan
    3. Push the new tag to the server
    4. Publish lib_simulink's new Ivy descriptor
    5. Publish each target's new Ivy descriptor
    6. Push changes in ivy-xml\ivy-dt to the server

    Will not actually push to the server if _PUSH_TO_SERVER is False
    :param usr_choice: User selections provided initially
    :param ivy_view: Absolute path of the freshly retrieved Ivy view
    """

    # Extract the desired tag to use
    des_tag = usr_choice.new_tag

    # Overall commit message argument
    commit_msg_arg = '--message="Automatic retag of {0} with {1}"'.format(usr_choice.old_tag, des_tag)

    # 1. Tag lib_simulink with the new git tag
    libsl_dir = os.path.abspath(os.path.join(ivy_view, 'lib_autocode_release', 'lib_simulink'))
    exec_cmd(
        ['git', 'tag', '--annotate', commit_msg_arg, des_tag],
        libsl_dir, "apply tag {} to {}".format(des_tag, libsl_dir)
    )

    # 2. For each -a repository:
    for target in _TARGETS:
        # Calculate some data about this target
        target_dir = os.path.abspath(os.path.join(ivy_view, 'lib_autocode_release', 'lib_simulink-a', target.name))
        if not os.path.isdir(target_dir):
            log_and_raise_exception("Expected {} to exist in {}, but it doesn't.".format(target_dir, ivy_view))

        # 2a. Delete the existing ivy.xml and git-repo.xml
        filename = os.path.join(target_dir, 'ivy.xml')
        if os.path.isfile(filename):
            os.remove(filename)
            log_and_print_info("Deleted {} before creating a new one".format(filename))
        else:
            log_and_raise_exception("Expected {} to exist, but it doesn't.".format(filename))
        filename = os.path.join(target_dir, 'git-repo.xml')
        if os.path.isfile(filename):
            os.remove(filename)
            log_and_print_info("Deleted {} before creating a new one".format(filename))
        else:
            log_and_raise_exception("Expected {} to exist, but it doesn't.".format(filename))

        # 2b. Use ivyu popFR to create a new ivy.xml and git-repo.xml
        # 2c. Use ivyu addDep to add appropriate dependencies
        # 2d. Commit the new contents with the latest tag, branching from the existing commit rather than as an orphan
        create_target_ivy_xml(ivy_view, target.name, des_tag, False)

    # 3. Push the new tag to the server
    # 4. Publish lib_simulink's new Ivy descriptor
    # 5. Publish each target's new Ivy descriptor
    # 6. Push changes in ivy-xml\ivy-dt to the server
    publish_tag(ivy_view, des_tag)
    log_and_print_info('retag_release() completed')


def delete_lib_simulink_a_contents(view):
    """
    Deletes the contents of lib_simulink-a if it exists
    :param view: Absolute path to view containing lib_autocode_release/lib_simulink-a
    """
    log_and_print_info("Asked to delete contents of {0}'s lib_simulink-a".format(view))

    # Check if lib_simulink-a exists
    sl_dir = os.path.abspath(os.path.join(view, 'lib_autocode_release', 'lib_simulink-a'))
    if not os.path.isdir(sl_dir):
        log_and_print_info("Directory {0} doesn't exist, nothing to do".format(sl_dir))
        return

    # Delete everything in lib_simulink-a
    for name in os.listdir(sl_dir):
        child = os.path.abspath(os.path.join(sl_dir, name))
        if os.path.isdir(child):
            delete_directory(child)
        elif os.path.isfile(child):
            log_and_print_info("About to delete file {0}".format(child))
            os.remove(child)
            log_and_print_info("Successfully deleted {0}".format(child))
        else:
            log_and_raise_exception("{0} is in {1} and isn't a file or directory".format(child, sl_dir))
    log_and_print_info("Successfully deleted contents of {0}".format(sl_dir))


def tag_lib_simulink_at_start(view, tag):
    """
    Ensures lib_simulink is clean, and tags it so it can be published and referenced from lib_simulink-a.
    :param view: Absolute path to view containing lib_simulink
    :param tag: New tag to apply
    """
    log_and_print_info("Asked to tag {}'s lib_simulink".format(view))

    # Check if generate_code.log is out of date
    sl_dir = os.path.abspath(os.path.join(view, 'lib_autocode_release', 'lib_simulink'))

    # Commit changes if any detected
    if not test_git_repo_is_clean(sl_dir):
        log_and_raise_exception("Repository {} is not clean".format(sl_dir))

    # Tag current commit
    exec_cmd(
        ['git', 'tag', '--annotate', '--message="Automatic tag so -a repos can reference this commit"', tag],
        sl_dir, "tag current commit in '{}' with '{}'".format(sl_dir, tag)
    )


def call_make(view, make_dir, targets, single_thread=False):
    """
    Calls gmake for the desired target
    :param view: Absolute path to the view\lib directory
    :param make_dir: Relative path from view to directory in which make will be invoked
    :param targets: List of targets to execute
    :param single_thread: Set to true to keep make single threaded
    """

    # Validate input
    view = os.path.abspath(view)
    if not os.path.isdir(view):
        log_and_raise_exception("Expected '{}' to exist".format(view))
    make_dir = os.path.abspath(os.path.join(view, make_dir))
    if not os.path.isdir(make_dir):
        log_and_raise_exception("Expected '{}' to exist".format(make_dir))

    # Calculate the number of threads if multi-threaded
    if single_thread:
        thread_args = list()
    else:
        num_proc = os.environ.get('NUMBER_OF_PROCESSORS', '2')
        thread_args = ['-j', "{}".format(3 * int(num_proc)), '--output-sync']

    # Calculate path to make.exe
    exe = os.path.abspath(os.path.join(view, r'oss\make\bin\make.exe'))

    # Invoke make
    args = list()
    args.append(exe)
    args.extend(thread_args)
    args.extend(targets)
    exec_cmd(args, make_dir, "execute make target {} in '{}'".format(targets, make_dir))


def retrieve_buildable_targets(target, target_lib):
    """
    In lib_simulink, not all of the targets are buildable.  Some just have too many files, and were built once in
    ClearCase, and are never regularly built again.  This function returns the list of libraries that could be built.
    :param target: Name of the target
    :param target_lib: Absolute path to the target's lib directory
    :return: A list of children that could be built
    """

    # For a couple of targets, the list is really small and it is easier to list what to build than what to exclude
    if r'tgt_cc32r_4.30_M32Rx' == target:
        libs = [
            'ac_map',
            'sl_cal',
            'sl_cdl',
            'sl_csl',
            'sl_dyn_R2009B',
            'sl_pms',
            'sl_rtw_R2007B',
            'sl_rtw_R2009B',
            'sl_rtw_R2011B',
            'sl_rtw_R2012B',
            'sl_SclJ1939'
        ]
    else:
        # Get the list of child directories, the maximal set
        libs = os.listdir(target_lib)

        # Remove libsl_dyn_R2007B from the set, nobody builds this
        if 'sl_dyn_R2007B' in libs:
            libs.remove('sl_dyn_R2007B')

    # Return the result
    return libs


def checkout_unbuildable_targets(target, target_lib):
    """
    In lib_simulink, not all of the targets are buildable.  Some just have too many files, and were built once in
    ClearCase, and are never regularly built again.  This function checks out these files from previous commits.
    :param target: Name of the target
    :param target_lib: Absolute path to the target's lib directory
    """

    # Figure out what to do based on the target
    if r'tgt_ar_diab_5.9.4.0_PPCVLEEF' == target:
        tag = None
        files = None
    elif r'tgt_cc32r_4.30_M32Rx' == target:
        tag = 'LIB_SIMULINK_1.1.3_BETA'
        files = list()
        for idx in range(1, 39):
            files.append("libsl_dyn_R2007B_{:02d}.a".format(idx+1))
    elif r'tgt_diab_4.2b_PPC555EH' == target:
        tag = 'LIB_SIMULINK_1.0.0_BETA'
        files = ['libsl_dyn_R2007B.a']
    elif r'tgt_diab_5.8.0.0_PPCVLEEF' == target:
        tag = 'LIB_SIMULINK_1.0.3_BETA'
        files = ['libsl_dyn_R2007B.a']
    elif r'tgt_sim_gcc_4.8.2_x86-64' == target:
        tag = None
        files = None
    elif r'tgt_rvct_2.1_ARM7TDMI' == target:
        tag = 'LIB_SIMULINK_1.0.0_BETA'
        files = list()
        for idx in range(1, 39):
            files.append("libsl_dyn_R2007B_{:02d}.a".format(idx+1))
    else:
        log_and_raise_exception("Unexpected target '{}'".format(target))

    # Exit if nothing to do
    if tag is None:
        log_and_print_info("No files to checkout from previous commits for {}".format(target))
        return

    # Retrieve previous commit
    exec_cmd(
        ['git', 'fetch', 'origin', 'tag', tag],
        target_lib, "retrieve previous commit {}".format(tag)
    )

    # Checkout each filename
    for filename in files:
        exec_cmd(
            ['git', 'checkout', tag, '--', filename],
            target_lib, "checkout {} from {} in '{}'".format(filename, tag, target_lib)
        )


def rebuild_target(view, target, tag):
    """
    Rebuilds on target in lib_simulink-a
    1. In each sub-directory of tgt\lib, run make all
    2. In tgt\, run make aggregate_libs
    3. Copy tgt.gitignore to target
    4. Populate ivy.xml and git-info.xml
    5. Initialize git repo with orphan commit
    6. Commit all changes to temporary branch
    7. Tag with same tag applied to lib_simulink after regenerating source
    :param view: Absolute path to the view directory
    :param target: Name of the target to rebuild
    """

    # Calculate the path to /lib_simulink-a/target and /lib_simulink-a/target/lib
    target_dir = os.path.abspath(os.path.join(view, 'lib_autocode_release', 'lib_simulink-a', target))
    target_lib = os.path.abspath(os.path.join(target_dir, 'lib'))
    if not os.path.isdir(target_lib):
        log_and_raise_exception("Expected directory {} to exist".format(target_lib))
    server = "git@git1.corp.cat.com:/cat/dt/libsl-{}-a".format(target)

    # 1. In each buildable sub-directory of tgt\lib, run make all
    for child in retrieve_buildable_targets(target, target_lib):
        child_dir = os.path.abspath(os.path.join(target_lib, child))
        call_make(view, child_dir, ['all'])

    # 2. In tgt\, run make aggregate_libs
    has_aggregate = False
    for element in _TARGETS:
        if target == element.name:
            has_aggregate = element.has_aggregate
    if has_aggregate:
        call_make(view, target_dir, ['aggregate_libs'], True)

    # 3. Copy tgt.gitignore to target
    src_file = os.path.abspath(os.path.join(
        view, 'lib_autocode_release', 'lib_simulink', 'src', 'makefiles', 'tgt.gitignore'
    ))
    dst_file = os.path.abspath(os.path.join(target_dir, '.gitignore'))
    shutil.copyfile(src_file, dst_file)
    log_and_print_info("Copied '{}' to '{}'".format(src_file, dst_file))

    # 5. Initialize git repo
    exec_cmd(['git', 'init'], target_dir,
             "initialize git repo in '{}'".format(target_dir))
    exec_cmd(['git', 'remote', 'add', 'origin',  server], target_dir,
             "point origin to '{}' in '{}".format(server, target_dir))

    # Checkout libraries that are not normally rebuilt
    checkout_unbuildable_targets(target, target_lib)

    # 4. Populate ivy.xml and git-info.xml
    # 5. Checkout temporary branch as orphan commit
    # 6. Commit all changes to temporary branch
    # 7. Tag with same tag applied to lib_simulink after regenerating source
    create_target_ivy_xml(view, target, tag, True)
    log_and_print_info("Automated build of {} successfully completed".format(target_dir))


if __name__ == "__main__":
    main()
    logging.shutdown()
