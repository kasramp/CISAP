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
