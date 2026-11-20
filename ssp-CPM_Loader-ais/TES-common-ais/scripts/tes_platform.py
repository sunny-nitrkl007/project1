#!/usr/bin/python
##############################################################################
## @attention COPYRIGHT (C) 2019 CATERPILLAR INC. ALL RIGHTS RESERVED.
## @file    tes_platform.py
## @brief   Functions to import lib and include paths from platform.
##############################################################################

import os

# update common CPPPATH and LIBPATH based on platform
def importCommonLibs( baseEnv ):
    tesPlatformDir = baseEnv[ 'TES_PLATFORM_DIR' ]

    # add all generic and PLATFORM specific CPPPATH and LIBPATH
    baseEnv.Append( CPPPATH = baseEnv.getPathsFromFile( os.path.join(   tesPlatformDir,
                                                                        'common',
                                                                        'includes-list.txt' )) )

    baseEnv.Append( LIBPATH = baseEnv.getPathsFromFile( os.path.join(   tesPlatformDir,
                                                                        'common',
                                                                        'libpaths-list.txt' )) )

    baseEnv.Append( CPPPATH = baseEnv.getPathsFromFile( os.path.join(   tesPlatformDir,
                                                                        baseEnv[ 'PLATFORM' ],
                                                                        'includes-list.txt' )) )

    baseEnv.Append( LIBPATH = baseEnv.getPathsFromFile( os.path.join(   tesPlatformDir,
                                                                        baseEnv[ 'PLATFORM' ],
                                                                        'libpaths-list.txt' )) )

    # add A6NX common libraries and includes
    if ( baseEnv[ 'PLATFORM' ] in ['A6N1', 'A6N2', ]):
        # add common
        baseEnv.Append( CPPPATH = baseEnv.getPathsFromFile( os.path.join(   tesPlatformDir,
                                                                            'A6NX',
                                                                            'includes-list.txt' ) ) )
        baseEnv.Append( LIBPATH = baseEnv.getPathsFromFile( os.path.join(   tesPlatformDir,
                                                                            'A6NX',
                                                                            'libpaths-list.txt' ) ) )

    # install needed generic and PLATFORM libraries to lib/
    baseEnv.InstallLibrariesFromList( os.path.join( tesPlatformDir,
                                                    'common',
                                                    'libs-list.txt' ))

    baseEnv.InstallLibrariesFromList( os.path.join( tesPlatformDir,
                                                    baseEnv[ 'PLATFORM' ],
                                                    'libs-list.txt' ) )

    # install A6NX libraries
    if ( baseEnv[ 'PLATFORM' ] in ['A6N1', 'A6N2',]):
        baseEnv.InstallLibrariesFromList( os.path.join( tesPlatformDir,
                                                        'A6NX',
                                                        'libs-list.txt' ) )

# update CPM project specific CPPPATH and LIBPATH based on platform
def importCpmLibs( baseEnv ):
    # add all generic and PLATFORM specific CPPPATH and LIBPATH
    baseEnv.Append( CPPPATH = baseEnv.getPathsFromFile( os.path.join(  'platform',
                                                                       'common',
                                                                       'includes-list.txt' )) )
    baseEnv.Append( LIBPATH = baseEnv.getPathsFromFile( os.path.join(  'platform',
                                                                       'common',
                                                                       'libpaths-list.txt' )) )

    baseEnv.Append( CPPPATH = baseEnv.getPathsFromFile( os.path.join(  'platform',
                                                                        baseEnv[ 'PLATFORM' ],
                                                                       'includes-list.txt' )) )
    baseEnv.Append( LIBPATH = baseEnv.getPathsFromFile( os.path.join(  'platform',
                                                                        baseEnv[ 'PLATFORM' ],
                                                                       'libpaths-list.txt' )) )

    # add A6NX common libraries and includes
    if ( baseEnv[ 'PLATFORM' ] in ['A6N1', 'A6N2',]):
        baseEnv.Append( CPPPATH = baseEnv.getPathsFromFile( os.path.join(   'platform',
                                                                            'A6NX',
                                                                            'includes-list.txt' )) )
        baseEnv.Append( LIBPATH = baseEnv.getPathsFromFile( os.path.join(   'platform',
                                                                            'A6NX',
                                                                            'libpaths-list.txt' )) )

    # install needed generic and PLATFORM libraries to lib/
    baseEnv.InstallLibrariesFromList( os.path.join( 'platform',
                                                    'common',
                                                    'libs-list.txt' ))

    baseEnv.InstallLibrariesFromList( os.path.join( 'platform',
                                                    baseEnv[ 'PLATFORM' ],
                                                    'libs-list.txt' ))

    # install A6NX libraries
    if ( baseEnv[ 'PLATFORM' ] in ['A6N1', 'A6N2',]):
        baseEnv.InstallLibrariesFromList( os.path.join( 'platform',
                                                        'A6NX',
                                                        'libs-list.txt' ))
