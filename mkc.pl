#!/usr/bin/perl
#
# Read RFC 1345 and defacto standards
# Produce a set of sorted code set translation tables
#
# (C) Copyright 1996, 2000 D. Spinellis.  All rights reserved.
# This program may be freely used and reproduced as long  as this notice
# is retained and modified copies are clearly marked as such.
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
$tbl{'MS928'} = 1;
$tbl{'MAC_GR'} = 1;
$tbl{'Latin-greek-1'} = 1;
$tbl{$target = 'ISO_8859-7:1987'} = 1;

# Read character descriptions
while (<>) {
	next if (/^Simonsen     / || /^\f/ || /^$/ || /^RFC 1345/);
	last if (/^4\.  CHARSETS/);
	chop;

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

print '
struct s_charentry {
	int unicode;
	int charval;
};

struct s_charset {
	char *name;			// Character set name
	int count;
	struct s_charentry ce[1500];	// Sorted by Unicode value
} charsets[] = {

';

for $charset (keys %char) {
	$count = grep(1, keys %{$n{$charset}});
	print "\t{ \"$charset\", $count, {\n";
	for $two (sort byuni keys %{$n{$charset}}) {
		print "\t\t{ 0x$uni{$two}, 0x$n{$charset}{$two} },\t/* $two: $desc{$two} */\n";
	}
	print "\t} },\n";
}
print "};\n";

sub
byuni
{
	return hex($uni{$a}) <=> hex($uni{$b});
}

