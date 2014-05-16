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
printw("CISAP Copyleft Written By Kasra Madadipouya Feb-2012.\n");
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
#endif
