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
	gcc -O3 -o mp3 mp3.c lib/libfmodex64.so -pthread -lncurses

run:
	./mp3

clean:
	rm -f mp3
