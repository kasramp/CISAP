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
#if !defined(_SEPRATOR_H)
#define _SEPRATOR_H

#include<string.h>
#include<malloc.h>
#include<stdio.h>
void seprator(char *strDest,char *strSrc)
{
char *strTemp=malloc(1000);
int i,tool,len;
len=strlen(strSrc);
--len;
strcpy(strTemp,strSrc);
for(i=len;i>=0;i--)
{
if(strTemp[i]=='/')
  break;
}
tool=len-i;
tool++;
strncpy(strTemp,strTemp+(strlen(strTemp)-(tool-1)),tool);
strcpy(strDest,strTemp);
}
void nseprator(char ch,char *strDest,char *strSrc)
{
char *strTemp=malloc(1000);
int i,tool,len;
len=strlen(strSrc);
--len;
strcpy(strTemp,strSrc);
for(i=len;i>=0;i--)
{
if(strTemp[i]==ch)
  break;
}
tool=len-i;
tool++;
strncpy(strTemp,strTemp+(strlen(strTemp)-(tool-1)),tool);
strcpy(strDest,strTemp);
}
#endif
