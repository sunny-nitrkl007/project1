% This file creates and compiles an S-Function from the wrapper for the
% Python-generated tipoff_assist.c mass_and_dist function.
%
% Requires:
%   tipoff_assist.c and tipoff_assist.h

% Initialize data structure to specify use of external C code in MATLAB
def = legacy_code('initialize');

% Provide specifics about the C code we want to use in MATLAB
dir_listing_c = dir('./c_src/*.c');
filenames_c = {dir_listing_c.name};
def.SourceFiles = filenames_c;

dir_listing_h = dir('./c_src/*.h');
filenames_h = {dir_listing_h.name};
def.HeaderFiles = filenames_h;

def.SrcPaths = {'./c_src'};
def.IncPaths = {'./c_src'};
def.SFunctionName = 'toa_mass_and_dist_by_id_sfunc';
def.OutputFcnSpec = 'void toa_mass_and_dist_by_id(uint32 u1, double u2, double u3, double u4, double u5, double u6, double u7, double u8, double y1[1], double y2[1])';

% Generate an S-function .c file with name from def.SFunctionName
legacy_code('sfcn_cmex_generate', def);

% Generate .mexw64 file (referenceable S-Func block in model?)
% Depends upon S-function .c file
legacy_code('compile', def);

% Generate .tlc file
% Only depends on def
legacy_code('sfcn_tlc_generate', def);
