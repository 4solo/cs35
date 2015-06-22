#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char** argv)
{
  char buffer;
  char arr[128];
  char same[128];
  if(argc>1)
  {
  int length1=strlen(argv[1]);
  int length2=strlen(argv[2]);
  char err1[]="an error from and to are not the same length \n";
  char err2[]="this char is dupilicate bytes \n";
  int err1length=strlen(err1);
  int err2length=strlen(err2);
  if(length1!=length2)
  {
    write(2,&err1,err1length);
    exit(-1);
  }
  int i;
  for(i=0;i<128;i++)
    {
      same[i]=0;
      arr[i]=i;
    }
  char ch;
  for(i=0;i<length1;i++)
    {
      ch=argv[1][i];
      if(same[ch]==1)
	{
	  write(2,&err2,err2length);
	  exit(-1);
	}
      else
	{
	  same[ch]=1;
	  arr[ch]=argv[2][i];
	}
    }
  while(read(0,&buffer,1)>0)
    {
      write(1,&arr[buffer],1);
    }
  }
  else
    while(read(0,&buffer,1)>0)
    {
      write(1,&buffer,1);
    }
}
