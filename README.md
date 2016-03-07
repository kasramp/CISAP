
				========================================================================
					   CISAP(CISAP Is Simple Audio Player) (v0.2).
					   Copyright © Written By Kasra Madadipouya 2012-2016.
					   The program uses FMOD API version 00010705
				========================================================================

This program will be distributed under GNU/GPL V3 License as soon as the writer of program acheive to stable version of this player.


In order to install and use this software follow below instruction
> Be sure that "g++ version 11" compiler were installed suceessfully installed on your computer.
> Be sure "ncurses" libaray has installed on your system(For displaying).
> Go to terminal.
> cd "Path and folder".
> make
> sudo make install

To uninstall CISAP just run this command in terminal.
> sudo make uninstall

The implicated tasks  that cisap can do are:
> Play most common Audio formats such as Ogg,Mp3,Wav,...(Unfortunately Wma <Microsoft Windows Meda Audio> extesion is not supported in this program).
> Play Audio files from STANDARD playlist which has "m3u" extesnion.
> If non STANDARD "m3u" file is given to software, player returns error that can't support the file. In order to convert none STANDARD playlist file to STANDARD one a program has been written by the programmer of this software as tool that is able to solve this problem and it is distrubuted with the software package.
> Play Audio files (except WMA extension) from online streams(Network,Internet).
> Increse/Decrease volume of the song(s).
> Mute music.
> Change L/R balance of the music.
> Change frequency of song(s).
> Add/Remove effects to song(s)(Lowpass, Highpass, Echo, Flange, Dist, Chorous, Parameq).
> Pause/Play supported audio file.
> Go to next/previous song easily.
> Change the position of audio file(s).
> Repeat favourite song(s) or playlist.
> Shows the tags of the song(For unknown tag names and byte shows in order 'Unknown' and '?' sign.

The options and key which are used in this program are:
> In order to go to previous song press "<" key and for going to next song ">" key.
> For playing and pause the song press "Space".
> For quiting from program press "q".
> For increasing and decreasing press "+" and "-".
> To 'Mute' or 'Unmute' press "m";
> To change balance to left side press "[".
> To change balance to right side press "]".
> To set balance to center press "p".
> To increase frequence of song press "}".
> To decrease frequence of song press "{".
> To reset frequence press "f".
> In order to active/diactive 'Lowpass' effect press "1".
> In order to active/diactive 'Highpass' effect press "2".
> In order to active/diactive 'Echo' effect press "3".
> In order to active/diactive 'Flange' effect press "4".
> In order to active/diactive 'Dist' effect press "5" [Deprecated].
> In order to active/diactive 'Chorous' effect press "6" [Deprecated].
> In order to active/diactive 'Parameq' effect press "7" [Deprecated].
> For seek forward 10 seconds press "Right arrow key".
> For seek backward 10 seconds press "Left arrow key".
> For seek forward 1 minute press "Up arrow key".
> For seek backward 1 minute press "Down arrow key".
> For seek forward 10 minutes press "Page up".
> For seek backward 10 minutes press "Page down".
> "--playlist PATH" argument is used to call playlist.
> "--stream <url>" argument is used to play a song from network or internet.
> "--loop NUMBER" argument is used to repeat song or playlist which was called before or will be called next.
	>0 means ERROR.
	> greater than zero such as 1,2,... means repeating it 1,2,... times.
	> less than zero such as -1,-2,... mean repeating for INFINTE times.


TO DO
> Moving cisap to new FMOD lib & change language from C to C++ [Done]
> Saving favourited song(s) from online streams to hard disk (Live stream downloader). [Delayed/Canceled]
> Add play song(s) from Audio CD
> Writing complete "man" page for program.
> Making GUI.
> Writing documention for it.
> Distribute it widely in the net.

Contact
if you want to report bug(s) or contribute to develop this software you can contact me in one of the these ways.
> Sending mail: "kasra@madadipouya.com" OR "kasra_mp@live.com".

License 
=======
CISAP is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3
as published by the Free Software Foundation.

CISAP is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.  <http://www.gnu.org/licenses/>

Author(s):

© 2012-2016 Kasra Madadipouya <kasra@madadipouya.com>
