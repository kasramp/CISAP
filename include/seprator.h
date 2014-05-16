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
