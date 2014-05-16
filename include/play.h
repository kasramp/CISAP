#include<stdio.h>

#if !defined(_PLAY_H)
#define _PLAY_H

static int loop=1;
static int begin;
static int fin;
static int ps;
static char namefiles[2000][2000];
int getloop()
{
return loop;
}
void setloop(int x)
{
if(x>0)
  loop=++x;
else
loop=x;
}

void setparam(int start,int end,char names[2000][2000],int pOs)
{
  int i;
  begin=start;
  fin=end;
  ps=pOs;
  for(i=begin;i<=fin;i++)
   strcpy(namefiles[i],names[i]);
}
void getparam(int *start,int *end,char names[2000][2000],int *pOs)
{ 
  int i;
  (*start)=begin;
  (*end)=fin;
  (*pOs)=ps;
  for(i=begin;i<=fin;i++)
    strcpy(names[i],namefiles[i]);
}
#endif
