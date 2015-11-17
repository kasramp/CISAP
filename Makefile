# CISAP is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3
# as published by the Free Software Foundation.
#
# CISAP is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.  <http://www.gnu.org/licenses/>
#
# Author(s):
#
# © 2012 Kasra Madadipouya <kasra@madadipouya.com>

mp3:	mp3.c
	gcc -O3 -o cisap mp3.c -Llib -l :libfmodex64.so -pthread -lncurses
make install:
	cp cisap /usr/bin/
	cp -r lib/* /lib/
	install -g 0 -o 0 -m 0644 man/cisap /usr/share/man/man1/cisap.1
	gzip /usr/share/man/man1/cisap.1
run:
	./cisap
clean:
	rm -f cisap
make uninstall:
	rm -rvf cisap
	rm -rvf /usr/bin/cisap
	rm -rvf /lib/libfmodex-4.44.52.so
	rm -rvf /lib/libfmodex64.so         
	rm -rvf /lib/libfmodexL64-4.44.52.so  
	rm -rvf /lib/libfmodexL.so
	rm -rvf /lib/libfmodex64-4.44.52.so  
	rm -rvf /lib/libfmodexL-4.44.52.so  
	rm -rvf /lib/libfmodexL64.so          
	rm -rvf /lib/libfmodex.so
	rm -rvf /usr/local/man/man1/cisap.1*
	rm -rvf /usr/share/man/man1/cisap.1*
