NOTE3	[âãäæëìíñáÜåİçŞéßïüõıùşÂÃÄÆËÌÍÑÁ¢Å¸Ç¹ÉºÏ¼Õ¾Ù¿]
NOTE4	[^âãäæëìíñáÜåİçŞéßïüõıùşÂÃÄÆËÌÍÑÁ¢Å¸Ç¹ÉºÏ¼Õ¾Ù¿]
GRLCASE	[áÜâãäåİæçŞèéßúêëìíîïüğñóôõıûö÷øùş]
GRUCASE	[Á¢ÂÃÄÅ¸ÆÇ¹ÈÉºÚÊËÌÍÎÏ¼ĞÑÓÔÕ¾ÛÖ×ØÙ¿]
NOGREEK	[^áÜâãäåİæçŞèéßúêëìíîïüğñóôõıûö÷øùşÁ¢ÂÃÄÅ¸ÆÇ¹ÈÉºÚÊËÌÍÎÏ¼ĞÑÓÔÕ¾ÛÖ×ØÙ¿]

%{
/* Redefine these values for stressed output */
	char stress_a = 'a';
	char stress_A = 'A';
	char stress_e = 'e';
	char stress_E = 'E';
	char stress_i = 'i';
	char stress_I = 'I';
	char stress_o = 'o';
	char stress_O = 'O';
	char stress_u = 'u';
	char stress_U = 'U';
	char stress_y = 'y';
	char stress_Y = 'Y';

	char diair_i = 'i';
	char diair_I = 'I';
	char diair_y = 'y';
	char diair_Y = 'Y';

#define YY_INPUT(buf,result,max_size) \
{ \
	int i; \
        if ( yy_current_buffer->yy_is_interactive ) \
                { \
                int c = '*', n; \
                for ( n = 0; n < max_size && \
                             (c = getc( yyin )) != EOF && c != '\n'; ++n ) \
                        buf[n] = (char) c; \
                if ( c == '\n' ) \
                        buf[n++] = (char) c; \
                if ( c == EOF && ferror( yyin ) ) \
                        YY_FATAL_ERROR( "input in flex scanner failed" ); \
                result = n; \
                } \
        else if ( ((result = fread( buf, 1, max_size, yyin )) == 0) \
                  && ferror( yyin ) ) \
                YY_FATAL_ERROR( "input in flex scanner failed" ); \
	for (i = 0; i < result; i++) \
		buf[i] = map[(unsigned char)buf[i]]; \
} \

#define yyterminate() return 
#define YY_DECL void lexi843(int *q, int *qlen)
#define nq(x) (q[*qlen] = (x), *qlen++)

%}


%%

á		{ nq('a'); return; }
Ü		{ nq(stress_a); return; }
Á		{ nq('A'); return; }
¢		{ nq(stress_A); return; }

áõ/{NOTE3}	{ nq('a'); nq('v'); return; }
Áõ/{NOTE3}	{ nq('A'); nq('v'); return; }
ÁÕ/{NOTE3}	{ nq('A'); nq('V'); return; }
áÕ/{NOTE3}	{ nq('a'); nq('V'); return; }
áõ/{NOTE4}	{ nq('a'); nq('f'); return; }
Áõ/{NOTE4}	{ nq('A'); nq('f'); return; }
ÁÕ/{NOTE4}	{ nq('A'); nq('F'); return; }
áÕ/{NOTE4}	{ nq('a'); nq('F'); return; }

áı/{NOTE3}	{ nq(stress_a); nq('v'); return; /* Note 10 */ }
Áı/{NOTE3}	{ nq(stress_A); nq('v'); return; }
Á¾/{NOTE3}	{ nq(stress_A); nq('V'); return; }
á¾/{NOTE3}	{ nq(stress_a); nq('V'); return; }
áı/{NOTE4}	{ nq(stress_a); nq('f'); return; }
Áı/{NOTE4}	{ nq(stress_A); nq('f'); return; }
Á¾/{NOTE4}	{ nq(stress_A); nq('F'); return; }
á¾/{NOTE4}	{ nq(stress_a); nq('f'); return; }

â		{ nq('b'); return; }
Â		{ nq('B'); return; }

ã		{ nq('g'); return; }
Ã		{ nq('G'); return; }

ãã		{ nq('n'); nq('g'); return; }
ãÃ		{ nq('n'); nq('G'); return; }
Ãã		{ nq('N'); nq('g'); return; }
ÃÃ		{ nq('N'); nq('G'); return; }

ãî		{ nq('n'); nq('x'); return; }
ãÎ		{ nq('n'); nq('X'); return; }
Ãî		{ nq('N'); nq('x'); return; }
ÃÎ		{ nq('N'); nq('X'); return; }

ã÷		{ nq('n'); nq('c'); nq('h'); return; }
ã×		{ nq('n'); nq('C'); nq('H'); return; }
Ã÷		{ nq('N'); nq('c'); nq('h'); return; }
Ã×		{ nq('N'); nq('C'); nq('H'); return; }

ä		{ nq('d'); return; }
Ä		{ nq('D'); return; }

å		{ nq('e'); return; }
Å		{ nq('E'); return; }
İ		{ nq(stress_e); return; }
¸		{ nq(stress_E); return; }

åõ/{NOTE3}	{ nq('e'); nq('v'); return; }
Åõ/{NOTE3}	{ nq('E'); nq('v'); return; }
ÅÕ/{NOTE3}	{ nq('E'); nq('V'); return; }
åÕ/{NOTE3}	{ nq('e'); nq('V'); return; }
åõ/{NOTE4}	{ nq('e'); nq('f'); return; }
Åõ/{NOTE4}	{ nq('E'); nq('f'); return; }
ÅÕ/{NOTE4}	{ nq('E'); nq('F'); return; }
åÕ/{NOTE4}	{ nq('e'); nq('F'); return; }

åı/{NOTE3}	{ nq(stress_e); nq('v'); return; /* Note 10 */ }
Åı/{NOTE3}	{ nq(stress_E); nq('v'); return; }
Å¾/{NOTE3}	{ nq(stress_E); nq('V'); return; }
å¾/{NOTE3}	{ nq(stress_e); nq('V'); return; }
åı/{NOTE4}	{ nq(stress_e); nq('f'); return; }
Åı/{NOTE4}	{ nq(stress_E); nq('f'); return; }
Å¾/{NOTE4}	{ nq(stress_E); nq('F'); return; }
å¾/{NOTE4}	{ nq(stress_e); nq('f'); return; }

æ		{ nq('z'); return; }
Æ		{ nq('Z'); return; }

ç		{ nq('i'); return; }
Ç		{ nq('I'); return; }
Ş		{ nq(stress_i); return; }
¹		{ nq(stress_I); return; }

çõ/{NOTE3}	{ nq('i'); nq('v'); return; }
Çõ/{NOTE3}	{ nq('E'); nq('v'); return; }
ÇÕ/{NOTE3}	{ nq('E'); nq('V'); return; }
çÕ/{NOTE3}	{ nq('i'); nq('V'); return; }
çõ/{NOTE4}	{ nq('i'); nq('f'); return; }
Çõ/{NOTE4}	{ nq('E'); nq('f'); return; }
ÇÕ/{NOTE4}	{ nq('E'); nq('F'); return; }
çÕ/{NOTE4}	{ nq('i'); nq('F'); return; }

çı/{NOTE3}	{ nq(stress_i); nq('v'); return; /* Note 10 */ }
Çı/{NOTE3}	{ nq(stress_I); nq('v'); return; }
Ç¾/{NOTE3}	{ nq(stress_I); nq('V'); return; }
ç¾/{NOTE3}	{ nq(stress_i); nq('V'); return; }
çı/{NOTE4}	{ nq(stress_i); nq('f'); return; }
Çı/{NOTE4}	{ nq(stress_I); nq('f'); return; }
Ç¾/{NOTE4}	{ nq(stress_I); nq('F'); return; }
ç¾/{NOTE4}	{ nq(stress_i); nq('f'); return; }

È		{ nq('T'); nq('H'); return; }
è		{ nq('t'); nq('h'); return; }
È/{GRLCASE}	{ nq('T'); nq('h'); return; /* Note 11 */}

é		{ nq('i'); return; }
É		{ nq('I'); return; }
ß		{ nq(stress_i); return; }
º		{ nq(stress_I); return; }
ú		{ nq(diair_i); return; }
Ú		{ nq(diair_I); return; }

ê		{ nq('k'); return; }
Ê		{ nq('K'); return; }

ë		{ nq('l'); return; }
Ë		{ nq('L'); return; }

ì		{ nq('m'); return; }
Ì		{ nq('M'); return; }

{NOGREEK}ìğ	{ nq(*yytext); nq('b'); return; /* Note 5 */ }
{NOGREEK}Ìğ	{ nq(*yytext); nq('B'); return; }
{NOGREEK}ìĞ	{ nq(*yytext); nq('b'); return; }
{NOGREEK}ÌĞ	{ nq(*yytext); nq('B'); return; }
^ìğ		{ nq('b'); return; }
^Ìğ		{ nq('B'); return; }
^ìĞ		{ nq('b'); return; }
^ÌĞ		{ nq('B'); return; }

ìğ/{NOGREEK}	{ nq('b'); return; /* Note 7 */ }
Ìğ/{NOGREEK}	{ nq('B'); return; }
ìĞ/{NOGREEK}	{ nq('b'); return; }
ÌĞ/{NOGREEK}	{ nq('B'); return; }

í		{ nq('n'); return; }
Í		{ nq('N'); return; }

Î		{ nq('X'); return; }
î		{ nq('x'); return; }


ï		{ nq('o'); return; }
Ï		{ nq('O'); return; }
ü		{ nq(stress_o); return; }
¼		{ nq(stress_O); return; }

ïõ		{ nq('o'); nq('u'); return; }
Ïõ		{ nq('O'); nq('u'); return; }
ïÕ		{ nq('o'); nq('U'); return; }
ÏÕ		{ nq('O'); nq('U'); return; }

ïı		{ nq('o'); nq(stress_u); return; }
Ïı		{ nq('O'); nq(stress_u); return; }
ï¾		{ nq('o'); nq(stress_U); return; }
Ï¾		{ nq('O'); nq(stress_U); return; }

ğ		{ nq('p'); return; }
Ğ		{ nq('P'); return; }

ñ		{ nq('r'); return; }
Ñ		{ nq('R'); return; }

ó		{ nq('s'); return; }
ò		{ nq('s'); return; }
Ó		{ nq('S'); return; }

ô		{ nq('t'); return; }
Ô		{ nq('T'); return; }

õ		{ nq('y'); return; }
Õ		{ nq('Y'); return; }
ı		{ nq(stress_y); return; }
¾		{ nq(stress_Y); return; }

ö		{ nq('f'); return; }
Ö		{ nq('F'); return; }

÷		{ nq('c'); nq('h'); return; }
×		{ nq('C'); nq('H'); return; }
×/{GRLCASE}	{ nq('C'); nq('h'); return; /* Note 11 */}

ø		{ nq('p'); nq('s'); return; }
Ø		{ nq('P'); nq('S'); return; }
Ø/{GRLCASE}	{ nq('P'); nq('s'); return; /* Note 11 */}

ù		{ nq('o'); return; }
Ù		{ nq('O'); return; }
ş		{ nq(stress_o); return; }
¿		{ nq(stress_O); return; }

%%

main()
{
	yylex();
}

yywrap()
{
	return (1);
}
