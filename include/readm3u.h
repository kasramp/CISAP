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

#if !defined(_READM3U_H)
#define _READM3U_H


#include<stdio.h>
#include<string.h>

int readM3u(char* strpath,char name[2000][2000])
{
  char* strTemp=NULL;
  int i=0;
  size_t len=0;
  size_t read;
  FILE *fp;
  fp=fopen(strpath,"r");
  if(!fp)
  {
      printf("Error in opening file \n");
      exit(2);
  }
  while(!feof(fp))
  {
   read=getline(&strTemp,&len,fp);
   ++i;
  }
  strcpy(name[0],strpath);
  fclose(fp);
  return i;
}
#endif
