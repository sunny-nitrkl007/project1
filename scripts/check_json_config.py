#!/usr/bin/env python3

import fnmatch
import os
import json

if __name__ == '__main__':
    dirs_to_check = [
        '../TES-common-ais/config',
        '../CPM-Loader-ais/config'
    ]

    grief = list()

    for d in dirs_to_check:
        for root, dirnames, filenames in os.walk(d):
            for f in fnmatch.filter(filenames, '*.json'):
                p = os.path.join(root, f)
                print('Checking %s' % (p, ), end = ': ')
                with open(p) as fp:
                    try:
                        json.load(fp)
                        print('ok.')
                    except Exception as e:
                        grief.append(p)
                        print('ERROR - %s' % (e, ))

    print('')
    if len(grief) > 0:
        print('ERRORS FOUND in %s file(s)' % (len(grief), ))
        for p in grief:
            print('    %s' % (p, ))
        print('')
        exit(-1)
    else:
        print('OK.')
        print('')
        exit(0)
