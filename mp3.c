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
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<curses.h>
#include"include/fmod.h"
#include"include/fmod_errors.h"
#include"include/seprator.h"
#include"include/common.h"
#include"include/parser.h"
#include"include/play.h"
#include"include/readm3u.h"
void ERRCHECK(FMOD_RESULT result);
int main(int args,char *argv[])
{
  int y,x,st,ed,i,count=0,lp,ch,pls,counter=0,emptbuf=0,starving=0,mute=0;
  int dsplowpass_active=0,dsphighpass_active,dspecho_active,dspflange_active,dspdistortion_active,dspchorus_active,dspparameq_active;
  float volume=1.0f,pan=0,frequency=44100.00000003f,freqtemp;
  char file[1000];
  char name[2000][2000];
  char remainstr[1000];
  char loopstr[1000];
  char volstr[1000];
//############################
FMOD_SYSTEM *fmod;
FMOD_SOUND *sound;
FMOD_SOUND *playlist;
FMOD_OPENSTATE  openstate;
FMOD_CHANNEL *channel=0;
FMOD_BOOL isplaying = 0;
FMOD_BOOL paused;
FMOD_TAG tag;
FMOD_RESULT result;
FMOD_DSP *dsplowpass=0;
FMOD_DSP *dsphighpass=0;
FMOD_DSP *dspecho=0;
FMOD_DSP *dspflange=0;
FMOD_DSP *dspdistortion=0;
FMOD_DSP *dspchorus=0;
FMOD_DSP *dspparameq=0;
char str[1000];
unsigned int ms,lenms,percent = 0; 
//******************************
  parse(args,argv);
  getloop(&lp);
  getparam(&st,&ed,name,&pls);
//#############################
  result=FMOD_System_Create(&fmod);
  result=FMOD_System_Init(fmod,1,FMOD_INIT_NORMAL,NULL);
  initscr();
  halfdelay(1);
  keypad(stdscr, TRUE);
  noecho();  
  introprint();
 if(pls)
 {
 result=FMOD_System_CreateSound(fmod,name[0], FMOD_DEFAULT, 0, &playlist);
 ERRCHECK(result);   
 st++;
 }
  while(loop!=count)
  {
  for(i=st;i<=ed;i++)
  {
    printw("Buffering...");  
    refresh();
    if(!pls)
    { 
    result = FMOD_System_SetStreamBufferSize(fmod, 64*1024, FMOD_TIMEUNIT_RAWBYTES);
    ERRCHECK(result);
    result=FMOD_System_CreateSound(fmod, name[i],FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &sound);
    ERRCHECK(result);
    seprator(str,name[i]);
    }
    else
    { 
 //    result = FMOD_System_SetStreamBufferSize(fmod, 64*1024, FMOD_TIMEUNIT_RAWBYTES);
      result=FMOD_Sound_GetTag(playlist, "FILE", counter, &tag);
      ERRCHECK(result);
      sprintf(file,"%s", (char *)tag.data);
      result=FMOD_System_CreateSound(fmod,file, FMOD_SOFTWARE | FMOD_2D |FMOD_CREATESTREAM, 0, &sound);
      ERRCHECK(result);
      seprator(str,file); 
    }
    printw(" (99%%)\n\n");
    tracksep();
    printw("FILE NAME = %s\n",str);
    tagget(sound);
    tracksep();
    printw("\n");
    result=FMOD_System_PlaySound(fmod, FMOD_CHANNEL_FREE, sound,0, &channel);
    FMOD_Channel_SetVolume(channel,volume);
    FMOD_Channel_SetMute(channel,mute);
    FMOD_Channel_SetPan(channel,pan);
    FMOD_Channel_GetFrequency(channel,&freqtemp);
    FMOD_Channel_SetFrequency(channel,freqtemp);
    result=FMOD_System_CreateDSPByType(fmod,FMOD_DSP_TYPE_LOWPASS,&dsplowpass);
    ERRCHECK(result);
    result=FMOD_System_CreateDSPByType(fmod,FMOD_DSP_TYPE_HIGHPASS,&dsphighpass);
    ERRCHECK(result);
    result=FMOD_System_CreateDSPByType(fmod,FMOD_DSP_TYPE_ECHO,&dspecho);
    ERRCHECK(result);
    result=FMOD_System_CreateDSPByType(fmod,FMOD_DSP_TYPE_FLANGE,&dspflange);
    ERRCHECK(result);
    result=FMOD_System_CreateDSPByType(fmod,FMOD_DSP_TYPE_DISTORTION,&dspdistortion);
    ERRCHECK(result);
    result=FMOD_System_CreateDSPByType(fmod,FMOD_DSP_TYPE_CHORUS,&dspchorus);
    ERRCHECK(result);
    result=FMOD_System_CreateDSPByType(fmod,FMOD_DSP_TYPE_PARAMEQ,&dspparameq);
    ERRCHECK(result);
    FMOD_System_Update(fmod);
    ERRCHECK(result);
    result=FMOD_Sound_GetLength(sound, &lenms, FMOD_TIMEUNIT_MS);
    ERRCHECK(result);
    while(1)
    {
      ch=getch();
      if(ch=='q')
    {
      printw("\nExiting... (Quit)\n");
      refresh();

      result=FMOD_Sound_Release(sound);
      ERRCHECK(result);
      result=FMOD_System_Close(fmod);
      ERRCHECK(result);
      result=FMOD_System_Release(fmod);
      ERRCHECK(result);
      endwin();
      exit(0);
    }
    if(ch==62)
    {  
      counter++;
      presskey(&ch,sound);
      break;
    }
    if(ch==60)
    {
      if((i-1)>=1)
    {
	i-=2;
	counter--;
      presskey(&ch,sound);
      break;
    }
    }
    if(ch==' '&&(!starving))
    {
      if(channel)
       {
	ch=0;
        FMOD_Channel_GetPaused(channel,&paused);
        FMOD_Channel_SetPaused(channel,!paused);
       }
    }
    if(ch=='+')
    {
      FMOD_Channel_GetVolume(channel, &volume);
      FMOD_Channel_SetVolume(channel,(volume += 0.1f));
      ch=0;
    }
    if(ch=='-')
    {
      FMOD_Channel_GetVolume(channel, &volume);
      FMOD_Channel_SetVolume(channel,(volume-=0.1f));
      ch=0;
    }
    if(ch=='m')
    {
      FMOD_Channel_GetMute(channel,&mute);
      FMOD_Channel_SetMute(channel,!mute);
      ch=0;
    }
    if(ch==']')
    {  
      FMOD_Channel_GetPan(channel,&pan);
      FMOD_Channel_SetPan(channel,(pan += 0.1f));
      ch=0;
    }
    if(ch=='[')
    {
      FMOD_Channel_GetPan(channel,&pan);
      FMOD_Channel_SetPan(channel,(pan -= 0.1f));
      ch=0;
    }
    if(ch=='p')
    {
      FMOD_Channel_SetPan(channel, 0.0f);
      ch=0;
    }
    if(ch=='}')
    {
      FMOD_Channel_GetFrequency(channel,&frequency);
      FMOD_Channel_SetFrequency(channel,(frequency += 500.0f));
      ch=0;
    }
    if(ch=='{')
    {
      FMOD_Channel_GetFrequency(channel, &frequency);
      FMOD_Channel_SetFrequency(channel,(frequency-=500.0f));
      ch=0;
    }
    if(ch=='f')
    {
      FMOD_Channel_SetFrequency(channel,freqtemp);
      ch=0;
    }
    if(ch=='1')
    {
      result = FMOD_DSP_GetActive(dsplowpass,&dsplowpass_active);
      ERRCHECK(result);
      if(dsplowpass_active)
      {
       result = FMOD_DSP_Remove(dsplowpass);
       ERRCHECK(result);
      }
      else
      {
      result = FMOD_System_AddDSP(fmod,dsplowpass,0);
      ERRCHECK(result);
      }
      ch=0;
    }
    if(ch=='2')
    {
      result = FMOD_DSP_GetActive(dsphighpass,&dsphighpass_active);
      ERRCHECK(result);
      if(dsphighpass_active)
      {
       result = FMOD_DSP_Remove(dsphighpass);
       ERRCHECK(result);
      }
      else
      {
       result = FMOD_System_AddDSP(fmod,dsphighpass,0);
       ERRCHECK(result);
      }
      ch=0;
    }
    if(ch=='3')
    {
      result = FMOD_DSP_GetActive(dspecho,&dspecho_active);
      ERRCHECK(result);
      if(dspecho_active)
      {
       result = FMOD_DSP_Remove(dspecho);
       ERRCHECK(result);
      }
      else
      {
       result = FMOD_System_AddDSP(fmod,dspecho,0);
       ERRCHECK(result);
       result = FMOD_DSP_SetParameter(dspecho, FMOD_DSP_ECHO_DELAY,50.0f);
       ERRCHECK(result);
      }
      ch=0;      
      }
      if(ch=='4')
      {
       result = FMOD_DSP_GetActive(dspflange,&dspflange_active);
       ERRCHECK(result);
       if(dspflange_active)
       {
        result = FMOD_DSP_Remove(dspflange);
        ERRCHECK(result);
       }
       else
       {
        result = FMOD_System_AddDSP(fmod,dspflange,0);
        ERRCHECK(result);
       }
       ch=0;       
      }
      if(ch=='5')
      {
       result = FMOD_DSP_GetActive(dspdistortion,&dspdistortion_active);
       ERRCHECK(result);
       if (dspdistortion_active)
       {
        result = FMOD_DSP_Remove(dspdistortion);
        ERRCHECK(result);
       }
       else
       {
        result = FMOD_System_AddDSP(fmod,dspdistortion,0);
        ERRCHECK(result);
        result = FMOD_DSP_SetParameter(dspdistortion, FMOD_DSP_DISTORTION_LEVEL,0.8f);
        ERRCHECK(result);
       }
       ch=0;
      }
      if(ch=='6')
      {
       result = FMOD_DSP_GetActive(dspchorus,&dspchorus_active);
       ERRCHECK(result);
       if(dspchorus_active)
       {
        result = FMOD_DSP_Remove(dspchorus);
        ERRCHECK(result);
       }
       else
       {
        result = FMOD_System_AddDSP(fmod,dspchorus,0);
        ERRCHECK(result);
       }
      ch=0;
     }
     if(ch=='7')
     {
      result = FMOD_DSP_GetActive(dspparameq,&dspparameq_active);
      ERRCHECK(result);
      if(dspparameq_active)
      {
       result = FMOD_DSP_Remove(dspparameq);
       ERRCHECK(result);
      }
      else
      {
       result = FMOD_System_AddDSP(fmod,dspparameq,0);
       ERRCHECK(result);
       result = FMOD_DSP_SetParameter(dspparameq,FMOD_DSP_PARAMEQ_CENTER,5000.0f);
       ERRCHECK(result);
       result = FMOD_DSP_SetParameter(dspparameq,FMOD_DSP_PARAMEQ_GAIN,0.0f);
       ERRCHECK(result);
      }
     ch=0;
    }
    if(ch==KEY_RIGHT)
    {
     ms+=2000;
     FMOD_Channel_SetPosition(channel,ms,FMOD_TIMEUNIT_MS);
     ch=0;
    }
    if(ch==KEY_LEFT)
    {
     ms-=3000;
     FMOD_Channel_SetPosition(channel,ms,FMOD_TIMEUNIT_MS);
     ch=0;
    }
      FMOD_Channel_GetPosition(channel,&ms,FMOD_TIMEUNIT_MS);
      FMOD_Channel_GetPaused(channel,&paused);
      result=FMOD_Sound_GetOpenState(sound,&openstate,&percent,&starving,0);
      ERRCHECK(result);
      FMOD_Channel_GetFrequency(channel,&frequency);
      FMOD_Channel_GetVolume(channel,&volume);
      FMOD_Channel_GetMute(channel,&mute);
      FMOD_Channel_GetPan(channel,&pan);
      FMOD_DSP_GetActive(dsplowpass,&dsplowpass_active);
      FMOD_DSP_GetActive(dsphighpass,&dsphighpass_active);
      FMOD_DSP_GetActive(dspecho,&dspecho_active);
      FMOD_DSP_GetActive(dspflange,&dspflange_active);
      FMOD_DSP_GetActive(dspdistortion,&dspdistortion_active);
      FMOD_DSP_GetActive(dspchorus,&dspchorus_active);
      FMOD_DSP_GetActive(dspparameq,&dspparameq_active);
      FMOD_Channel_IsPlaying(channel, &isplaying);
      getyx(stdscr,y,x);
      sprintf(loopstr,"%d",loop-1);
      sprintf(remainstr,"%d",(loop-count)-1);
      sprintf(volstr,"%.1f",volume);
      printw("Effects : Lowpass[%c] Highpass[%c] Echo[%c] Flange[%c] Dist[%c] Chorus[%c] Parameq[%c]\n\n", 
                    dsplowpass_active ? 'x' : ' ',
                    dsphighpass_active ? 'x' : ' ',
                    dspecho_active ? 'x' : ' ',
                    dspflange_active ? 'x' : ' ',
                    dspdistortion_active ? 'x' : ' ',
                    dspchorus_active ? 'x' : ' ',
                    dspparameq_active ? 'x' : ' ');
     printw("Track number(s) %d : Current Track %d : Loop time(s) %s : Remain loop(s) %s\n\n",ed==0?1:ed,i==0?1:i,loop>0?loopstr:"INF",loop>0?remainstr:"INF");
     printw("Time %02d:%02d:%02d/%02d:%02d:%02d : -%02d:%02d:%02d/%02d:%02d:%02d : %s : (%%%d) %s\n\n", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100,(lenms-ms) / 1000 / 60, (lenms-ms) / 1000 % 60, (lenms-ms) / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100,starving?"Buffering...":paused?"Paused      ":(!isplaying)?"Stop        ":"Playing     " ,percent,starving?"STARVING":"         ");
     printw("Volume %s : Balance %.1f %s : Frequency %.1f(Hz)%s\n\n",mute==0?volstr:"Mute",pan,((unsigned)(pan*1000000)==0)?"Center":((pan*1000000)<=0)?"Left":"Right",frequency,frequency==freqtemp?"Normal play":frequency<freqtemp?"Slow play":"Fast play");
      move(y,x);
      refresh();
      if((!emptbuf)&&(isplaying)&&(starving))
      {
        emptbuf=1;
        FMOD_Channel_SetPaused(channel, !paused);
      } 
      else if((emptbuf)&&(!starving))
      {
        emptbuf=0;
        FMOD_Channel_SetPaused(channel, !paused);
      }
      if(!isplaying)
      {
	counter++;
	comprky();
	break;
      }
    }
    FMOD_System_Update(fmod);
    clear();
  }
  counter=0;
  count++;
}
endwin();
return 0;
}
void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        endwin();
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result)); 
        exit(-1);
    }
}
