#
# Read C code for the transliteration and produce lex code to do the
# reverse
#
# $Id: lit2ulit.pl,v 1.1 2000/03/18 18:03:27 dds Exp $
#
open(STDIN, "translit.cpp") || die;
while (<>) {
	if (/case '(.)'\: (.*)break/) {
		$in = $1;
		$out = $2;
		$out =~ s/nq\(\'//g;
		$out =~ s/\'\); //g;
		$out =~ s/\\\'/'/g;
		print "$out\t\t{ l->nq('$in'); return; }\n";
	}
}
