/* 
 * This file is part of CISAP.
 * CISAP is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
 *
 * CISAP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.  <http://www.gnu.org/licenses/>
 *
 * Author(s):
 * © 2012 Kasra Madadipouya <kasra@madadipouya.com>
 */
#if !defined(_INIT_H)
#define _INIT_H

#include<stdio.h>
#include<curses.h>
#include"fmod.h"
int tagexist=1;
void introprint();
void tracksep();
void printtag(char *name,char *data,int datalen);
void tagget(FMOD_SOUND *sound);
void presskey(int *ch,FMOD_SOUND *sound);
void comprky();
void checktag(FMOD_TAG);

void introprint()
{
	int y,x,i,xx,yy;
	getmaxyx(stdscr,y,x);
	move(y/2-3,0);
	for(i=1;i<=x;i++)
		printw("=");
	getyx(stdscr,yy,xx);
	move(yy,((x-57)/2));
	printw("CISAP Copyleft Written By Kasra Madadipouya May-2015.\n");
	getyx(stdscr,yy,xx);
	move(yy,((x-42)/2));
	printw("The program uses FMOD API version %08x\n",(FMOD_VERSION));
	for(i=1;i<=x;i++)
		printw("=");
	printw("Loading...");
	refresh();
	sleep(1);
	clear();
	refresh();
}
void tracksep()
{
	int y,x,i;
	getmaxyx(stdscr,y,x);
	for(i=1;i<=x;i++)
		printw("#");
}
void printtag(char *name,char *data,int datalen)
{
	printw("%s = %s (%d bytes)\n", name,data, datalen);
	refresh();
}
void tagget(FMOD_SOUND *sound)
{
	FMOD_TAG tag;
	tagexist=1;
	if(FMOD_Sound_GetTag(sound,0,-1,&tag)!=FMOD_OK)
	{
		printw("TITLE = Unknown (? bytes)\n");
		printw("ARTIST = Unknown (? bytes)\n");
		printw("ALBUM = Unknown (? bytes)\n");
		printw("YEAR = Unknown (? bytes)\n");
		printw("COMMENT = Unknown (? bytes)\n");
		printw("GENERE = Unknown (? bytes)\n");
		refresh();
		tagexist=0;
	}
	checktag(tag);
	FMOD_Sound_GetTag(sound, "ARTIST", 0, &tag);
	checktag(tag);
	FMOD_Sound_GetTag(sound, 0, 2, &tag);
	checktag(tag);
	FMOD_Sound_GetTag(sound, 0, 3, &tag);
	checktag(tag);
	FMOD_Sound_GetTag(sound, 0, 4, &tag);
	checktag(tag);
	FMOD_Sound_GetTag(sound, 0,6, &tag);
	checktag(tag);
}
void presskey(int *ch,FMOD_SOUND *sound)
{
	FMOD_Sound_Release(sound);
	(*ch)=0;
	comprky();
}
void comprky()
{
	sleep(1);
	printw("\n");
}
void checktag(FMOD_TAG tag)
{
	if(tagexist)
	{
		if (tag.datatype == FMOD_TAGDATATYPE_STRING)
		{
			printtag(tag.name,(char*)tag.data,tag.datalen);
		}
		else
		{
			printw("%s = Unknown (%d bytes)\n", tag.name, tag.datalen);
			refresh();
		}
	}
}
void print_help()
{
	printf("Usage:\tcisap [options] [url|path/]filename\n");
	printf("\n");
	printf("Basic options:\n");
	printf(" --playlist <.m3u>\tplaying from list\n");
	printf(" --stream <url>\t\tplaying from stream\n");
	printf(" --loop <number>\tloop playback <number> times.  -1 means forever\n");
	printf(" --help\t\t\tshow help page\n");
	printf("\n");
	printf("Basic keys:\n");
	printf(" < or >\t\t\tstep backward/forward in playlist\n");
	printf(" + or -\t\t\tincrease or decrease PCM volume\n");
	printf(" m \t\t\tmute or unmute\n");
	printf(" [ or ]\t\t\tleft/right speaker adjustment\n");
	printf(" p\t\t\tbalance speaker channel\n");
	printf(" { or }\t\t\tincrease/decrease audio delay\n");
	printf(" f\t\t\treset audio deplay\n");
	printf(" <- or ->\t\tseek backward/forward 5 seconds\n");
	printf(" SPACE\t\t\tpause song\n");
	printf(" q\t\t\tstop playing and quit program\n");
	printf(" 1\t\t\tactivate/diactivate 'Lowpass' sound effect\n");
	printf(" 2\t\t\tactivate/diactivate 'Highpass' sound effect\n");
	printf(" 3\t\t\tactivate/diactivate 'Echo' sound effect\n");
	printf(" 4\t\t\tactivate/diactivate 'Flange' sound effect\n");
	printf(" 5\t\t\tactivate/diactivate 'Dist' sound effect\n");
	printf(" 6\t\t\tactivate/diactivate 'Chorous' sound effect\n");
	printf(" 7\t\t\tactivate/diactivate 'Parameq' sound effect\n");
	printf("\n");
	printf("CISAP v0.1 2012-2015 Kasra Madadipouya\n");
}
#endif
