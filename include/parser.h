#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"play.h"
#include"readm3u.h"

#if !defined(_PARSER_H)
#define _PARSER_H

void parse(int args,char *argv[])
{
int i=1,end,begin=1,flag=1,ps;
char strNames[2000][2000];
for(i=1;i<=(args-1);i++)
{
if(!strcmp("--loop",argv[i]))
{
if(!atoi(argv[i+1]))
{
printf("Invalid parameter(s)\n");
exit(1);
}
setloop(atoi(argv[++i]));
}
else if((!strcmp("--playlist",argv[i])&&flag))
{
  ps=1;
  flag=0;
  ++i;
  end=readM3u(argv[i],strNames);
  end-=2;
  begin=0;
}
else if((!strcmp("--stream",argv[i])&&flag))
{
  ps=0;
  flag=0;
  begin=0;
  end=0;
  strcpy(strNames[0],argv[++i]);
}
else if(flag)
{
  ps=0;
  flag=0;
  end=args-1;
  for(begin=i;begin<=end;begin++)
  {
    if(!(strcmp("--loop",argv[begin])))
    {
      end=begin-1;
      break;
    }
    if(!(strcmp("--playlist",argv[begin])))
    {
      end=begin-1;
      break;
    }
    if(!(strcmp("--stream",argv[begin])))
    {
      end=begin-1;
      break;
    }
    else 
    strcpy(strNames[begin],argv[begin]);
  }
  begin=i;
}
}
setparam(begin,end,strNames,ps);
}
#endif
