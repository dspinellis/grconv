Summary: universal Greek character code converter
Name: grconv
Version: X.X
Release: X
Copyright: BSD
Group: Utilities/Text
Source: grconv.tar.gz
%description
Grconv converts between a large number of character sets, transcription,
and transliteration methods that are used to represent Greek text.
In addition, it supports a number of encodings used to represent
those character sets in different environments.

%prep
%setup
%build
make RPM_OPT_FLAGS="$RPM_OPT_FLAGS"

%install
install -m 755 -o 0 -g 0 grconv /usr/bin/grconv
install -m 644 -o 0 -g 0 grconv.1 /usr/share/man/man1

%files
%doc README COPYING ChangeLog
/usr/bin/grconv
/usr/share/man/man1/grconv.1

