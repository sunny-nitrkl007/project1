#!/usr/bin/env python3

import os
import glob
import json
import collections

def _flatten_list_gen(l, parent_key, sep):
    for idx, x in enumerate(l):
        new_key = parent_key + sep + str(idx) if parent_key else str(idx)
        if isinstance(x, collections.MutableMapping):
            yield from flatten_dict(x, new_key, sep=sep).items()
        elif isinstance(x, list):
            yield from flatten_list(x, new_key, sep=sep).items()
        else:
            yield new_key, x

def _flatten_dict_gen(d, parent_key, sep):
    for k, v in d.items():
        new_key = parent_key + sep + k if parent_key else k
        if isinstance(v, collections.MutableMapping):
            yield from flatten_dict(v, new_key, sep=sep).items()
        elif isinstance(v, list):
            yield from flatten_list(v, new_key, sep=sep).items()
        else:
            yield new_key, v

def flatten_list(l: list, parent_key: str = '', sep: str = '.'):
    return dict(_flatten_list_gen(l, parent_key, sep))

def flatten_dict(d: collections.MutableMapping, parent_key: str = '', sep: str = '.'):
    return dict(_flatten_dict_gen(d, parent_key, sep))

if __name__ == '__main__':

    existing_file = './en_7.13.json'
    existing_dict = None
    with open(existing_file) as fp:
        existing_dict = json.load(fp)
        existing_dict = flatten_dict(existing_dict)

    new_file = './en_7.14.2.json'    
    new_dict = None
    with open(new_file) as fp:
        new_dict = json.load(fp)
        new_dict = flatten_dict(new_dict)

    missing = {}
    for (k, v) in existing_dict.items():
        if k not in new_dict:
            missing[k] = v

    print('Missing:')
    for k in sorted(missing.keys()):
        print('%s = %s' % (k,missing[k]))

    extra = {}
    for (k, v) in new_dict.items():
        if k not in existing_dict:
            extra[k] = v

    print('Extra:')
    for k in sorted(extra.keys()):
        print('%s = %s' % (k,extra[k]))

