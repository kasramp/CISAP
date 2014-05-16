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
