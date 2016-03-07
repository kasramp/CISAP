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
# © 2016 Kasra Madadipouya <kasra@madadipouya.com>

NAME = cisap
CPU = x86_64
CONFIG = Release
TARGET =dist/Debug/GNU-Linux/
ifndef CPU
    $(error Specify CPU=[x86|x86_64|arm|armhf])
endif
ifndef CONFIG
    $(error Specify CONFIG=[Debug|Release])
endif

ifeq (${CPU}, armhf)
    FLAGS += -marm -march=armv6 -mfpu=vfp -mfloat-abi=hard
else ifeq (${CPU}, arm)
    FLAGS += -marm -march=armv6 -mfpu=vfp -mfloat-abi=softfp
else ifeq (${CPU}, x86)
    FLAGS += -m32
else
    override CPU = x86_64
    FLAGS += -m64
endif

ifeq (${CONFIG}, Debug)
    FLAGS += -g
    SUFFIX = L
else
    override CONFIG = Release
    FLAGS += -O2
    SUFFIX =
endif

SOURCE_FILES = \
    main.cpp \
    common.cpp \
    common_platform.cpp \
    readm3u.cpp \
    parser.cpp \
    init.cpp

INCLUDE_DIRS = \
    -Iinc

LOWLEVEL_LIB = lib/${CPU}/libfmod${SUFFIX}.so

all:
	g++ --std=c++0x -pthread ${FLAGS} -o ${NAME} ${SOURCE_FILES} -Wl,-rpath=${LOWLEVEL_LIB} ${LOWLEVEL_LIB} ${INCLUDE_DIRS} -lncurses
install:
	cp cisap /usr/bin/
	cp -r lib/${CPU}/* /lib/
	install -g 0 -o 0 -m 0644 man/cisap /usr/share/man/man1/cisap.1
	gzip /usr/share/man/man1/cisap.1
run:
	./cisap
clean:
	rm -f cisap
uninstall:
	rm -rvf cisap
	rm -rvf /usr/bin/cisap
	rm -rvf /lib/libfmod.so
	rm -rvf /lib/libfmod.so.7
	rm -rvf /lib/libfmod.so.7.5
	rm -rvf /lib/libfmodL.so
	rm -rvf /lib/libfmodL.so.7  
	rm -rvf /lib/libfmodL.so.7.5
	rm -rvf /usr/local/man/man1/cisap.1*
	rm -rvf /usr/share/man/man1/cisap.1*
