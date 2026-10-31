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

untranslated_strings = set((
    'kPa', 'psi',
    'lb x 1000', 'klb',
    '%',
    'OK',
    'kWh/h',
    'ECM SN',
    'T', 'Tons',
    'mm/sec', 'in/sec',
    'YYYY/MM/DD', 'DD/MM/YYYY', 'MM/DD/YYYY',
    'pounds', 'lb',
    'lb/ft^3', 'kg/m^3',
    'rpm',
    'tonnes', 't',
    'Deg C', 'Deg F',
    'ID',
    'MID',
    'BEM',
    'kg', 'kilograms',
    'mins', 'Minutes',
    '0', '1', '2',
    'E2126', 'E63028',
    '0x000B', '0x0107', '0x000A', '0x0100', '0x0105', '0x0102', '0x0103',
    '0x0002', '0x0007', '0x0008', '0x0001', '0x0009', '0x0000', '0x107C',
    '0x0005', '0x0106', '0x0004', '0x0101', '0x0006', '0x0003', '0x0104',
    '000-19', '000-00', '000-0',
    '351-8', '248-9', '765-8', '351-13', '364-3',
    '364-4', '458-3', '769-4', '765-3', '351-3',
    '967-14', '458-4', '247-9', '765-4', '350-8',
    '364-8', '351-4', '458-8', '2183-13', '247-14',
    '769-3', '769-8', '350-4', '350-13', '350-3', '248-14',
    '3900-9'
))

if __name__ == '__main__':
    files = glob.glob('../ldpayloadui-a/Web_App_Release_Content/assets/languages/*.json')
    en_file = '../ldpayloadui-a/Web_App_Release_Content/assets/languages/en.json'

    grief = dict()

    en_dict = None
    with open(en_file) as fp:
        en_dict = json.load(fp)
        en_dict = flatten_dict(en_dict)

    for f in files:
        if os.path.basename(f) != 'en.json':
            other_dict = None
            with open(f) as fp:
                other_dict = json.load(fp)
                other_dict = flatten_dict(other_dict)
            if other_dict is not None:
                for (k, en_val) in en_dict.items():
                    other_val = other_dict.get(k)
                    if str(en_val) in untranslated_strings:
                        if str(en_val) != str(other_val):
                            #print('Strings mismatch in %s for %s.  %s != %s' % (os.path.basename(f), k, en_val, other_val))
                            pass
                    else:
                        if str(en_val) == str(other_val):
                            grief.setdefault(k, list()).append(os.path.splitext(os.path.basename(f))[0])
                            #print('Strings match in %s for %s. %s' % (os.path.basename(f), k, other_val))

    grief = collections.OrderedDict(sorted(grief.items()))

    for k, l in grief.items():
        print('%s = "%s": %s' % (k, en_dict[k], l))

