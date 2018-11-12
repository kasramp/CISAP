# CISAP Is Simple Audio Player
CISAP is a simple command audio player that with online streaming and pulling lyric facilities. CISAP previously developed with C programming language (GCC) and used FMOD library version 4.40 to decode audio files. The code re-factored in 2016 and released as v0.2. The entire codebase moved to C++ 11 with updated version of FMOD lib (1.07).

## Dependencies
To compile and deploy CISAP you are required to install following dependencies:
* C++ 11 (g++)
* Make
* Ncurses library
* Curl library 

You can install the above packages in Ubuntu using these commands:

	$ sudo apt-get install g++-4.8
	$ sudo apt-get install build-essential
	$ sudo apt-get install libncurses-dev
	$ sudo apt-get install libcurl4-gnutls-dev

## How to use
To install and use CISAP you need to run below commands:

	$ cd CISAP
	$ make
	$ sudo make install

To uninstall CISAP from your compile simply run:

	$ sudo make uninstall
For getting list of hotkeys and user manual please refer to CISAP man page.

## TODO
- [X] Make it publicly available and distributable
- [X] Moving CISAP to new FMOD lib and code refactoring
- [X] Writing complete "man" page for program
- [X] Lyric display feature [DONE]
- [X] Adding accoustic identification and suggestion to fix the tags
- [ ] Add an option to read songs from sub directories
- [ ] Add play song(s) from Audio CD
- [ ] Making GUI

## Screenshot
<p align="center">
<img src="https://user-images.githubusercontent.com/4501120/47316270-046bdd00-d647-11e8-8bfb-491ac37cdb91.png" alt="CISAP"/>
</p>

## Contact
* kasra@madadipouya.com

## License
CISAP is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3
as published by the Free Software Foundation.

CISAP is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.  <http://www.gnu.org/licenses/>

Author(s):

© 2012-2018 Kasra Madadipouya <kasra@madadipouya.com>
