#!/usr/bin/perl
#
# Read RFC 1345 and defacto standards
# Produce a set of sorted code set translation tables
#
# (C) Copyright 1996, 2000 D. Spinellis.  All rights reserved.
# 
# Permission to use, copy, and distribute this software and its
# documentation for any purpose and without fee is hereby granted,
# provided that the above copyright notice appear in all copies and that
# both that copyright notice and this permission notice appear in
# supporting documentation.
# 
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
# MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
# $Id: mkc.pl,v 1.4 2000/05/06 20:38:15 dds Exp $
#

$tbl{'greek-ccitt'} = 1;
$tbl{'greek7'} = 1;
$tbl{'greek7-old'} = 1;
$tbl{'latin-greek'} = 1;
$tbl{'ISO_5428:1980'} = 1;
$tbl{'IBM423'} = 1;
$tbl{'IBM869'} = 1;
$tbl{'IBM851'} = 1;
$tbl{'MS737'} = 1;
$tbl{'MS1253'} = 1;
$tbl{'MAC_GR'} = 1;
$tbl{'Latin-greek-1'} = 1;
$tbl{'ISO_8859-7:1987'} = 1;

push(@{$alias{'ISO_8859-7:1987'}}, '928');
push(@{$alias{'ISO_8859-7:1987'}}, 'ELOT928');
push(@{$alias{'ISO10646'}}, 'ISO_10646');
push(@{$alias{'ISO10646'}}, 'ISO-10646');
push(@{$alias{'ISO10646'}}, 'Unicode');

# Read character descriptions
while (<>) {
	next if (/^Simonsen     / || /^\f/ || /^$/ || /^RFC 1345/);
	last if (/^4\.  CHARSETS/);
	chop;
	s/\r//;

	# Read descriptions
	if (/ SP     0020    SPACE/ ..  /4.  CHARSETS/) {
		if ($more = ($_ =~ m/^		(.*)/)) {
			$desc{$two} .= $more;
		} elsif (($two, $uni, $desc) = ($_ =~ m/ (..)     (....)    (.*)/)) {
			next if ($two eq '  ');
			$two =~ s/ $//;
			$desc{$two} = $desc;
			$uni{$two} = $uni;
			$n{'ISO10646'}{$two} = $uni;
			$char{'ISO10646'}{$uni} = $two;
		}
	}
}

$uni{'??'} = 'ffff';

# Read character sets
while  (<>) {
	if (/^  \&charset (.*)/) {
		$charset = $1;
		$n = 0;
	}
	next unless ($tbl{$charset});
	if (/^  \&alias (.*)/) {
		push(@{$alias{$charset}}, $1);
		next;
	}
	next if (/^  \&[a-z]/);
	next if (/^Simonsen     / || /^\f/ || /^$/ || /^RFC 1345/);
	chop;
	@chars = split;
	foreach $char (@chars) {
		$n{$charset}{$char} = sprintf("%02x", $n);
		$char{$charset}{$n} = $char;
		$n++;
	}
}

open(CS, '>charset.cpp') || die;
open(CT, '>chartbl.cpp') || die;
open(CTH, '>chartbl.h') || die;
print CS '
#include "charset.h"
#include "chartbl.h"

struct s_charset charsets[] = {
';
print CT '#include "charset.h"
';
for $charset (keys %char) {
	$count = grep(1, keys %{$n{$charset}});
	$name = $charset;
	$name =~ s/[^a-z0-9A-Z]/_/g;
	print CS "\t{ \"$charset\", $count, $name, false},\n";
	for $alias (@{$alias{$charset}}) {
		print CS "\t{ \"$alias\", $count, $name, true},\t\t// Alias\n";
	}
	print CT "struct s_charentry $name\[\] = {\n";
	print CTH "extern struct s_charentry $name\[\];\n";
	for $two (sort byuni keys %{$n{$charset}}) {
		print CT "\t{ 0x$uni{$two}, 0x$n{$charset}{$two} },\t/* $two: $desc{$two} */\n";
	}
	print CT "};\n\n";
}
print CS "\t{ 0, 0, 0},\n";
print CS "};\n";

sub
byuni
{
	return hex($uni{$a}) <=> hex($uni{$b});
}

