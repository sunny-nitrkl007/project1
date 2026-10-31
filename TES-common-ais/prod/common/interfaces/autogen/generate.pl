#!/usr/bin/perl
use strict;
use warnings;
use IPC::System::Simple qw(system);

system($^X, "../../../../../eta-ais/prod/coretech/ais_interfaces/autogen/generate.pl", @ARGV);

