#include<sys/stat.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int totalcmp=0;
int rot13cmp(const void *s1,const void *s2)
{
  totalcmp++;
  int i = 0;
  char* a =*(char**)s1;
  char* b =*(char**)s2;
  while (1)
    {
      if (a[i] == b[i] && a[i] == '\n') //case when they are all finish
      return 0;
      if (a[i] == '\n') //a finish first
      return -1;
      if (b[i] == '\n') //b finish first 
      return 1;
      if (a[i] != b[i])
      {
	if ((a[i]<='z'&& a[i]>='a')&&(b[i]<='z'&& b[i]>='a')) //all lower case
	  {
	    if((a[i]<='m'&&b[i]<='m')||(a[i]>'m'&&b[i]>'m'))
	      {
		return a[i] - b[i];
	      }
	    else
	      return 0-(a[i]-b[i]);
	  }
	else if((a[i]<='Z'&& a[i]>='A')&&(b[i]<='Z'&&b[i]>='A')) //all upper case
	  {
	    if((a[i]<='M'&&b[i]<='M')||(a[i]>'M'&&b[i]>'M'))
	      return a[i] - b[i];
	    else
	      return 0-(a[i]-b[i]);
	  }
	else  //rest
	  return a[i] - b[i];
      }
      else 
	i++;
    }		      
}
int main(int argc,char** argv)
{
  int size=1024;
  char* arr;
  // arr=(char*) malloc(sizeof(char)*size);
  char tmp;
  int i=0;
  int number=0;
  struct stat fileStats;
  fstat(0,&fileStats);
  if(fileStats.st_size)
    {
    arr=(char*) malloc(sizeof(char)*fileStats.st_size);
    // printf("file size is %d\n",fileStats.st_size);
    }
  else
    arr=(char*) malloc(sizeof(char)*size);
  if(argc>1)
    {
      fprintf(stderr,"wrong input arugment\n");
      exit(1);
    }
  read(0,&tmp,1);
  if(tmp==EOF)
    {
      fprintf(stderr,"empty file or wrong input\n");
      exit(-1);
    }
  arr[0]=tmp;
  i++;
  while(read(0,&tmp,1)>0)
    {
      arr[i]=tmp;
      i=i+1;
      //need more space;
      if (!fileStats.st_size && i-1>=size)
	{
	  size*=2;
	  arr=(char*)realloc(arr,sizeof(char)*size);
	} 
    }
  int j;
  //adding \n to the last word
  if(arr[i-1]!='\n')
    {
      arr[i]='\n';
      i++;
    }
  //count the number
  for(j=0;j<i;j++)
    {
      if(arr[j]!='\n')
	number++;
      while(arr[j]!='\n'&& j<i)
	j++;
    }
  char** arr2;
  //printf("%d",number);
  arr2=(char**)malloc(sizeof(char*)*number);
  int count=0;
  for(j=0;j<i;j++)
    {
      if(arr[j]!='\n')
	{
	      arr2[count]=&arr[j];
	      count++;
        }
      while(arr[j]!='\n'&&j<i)
	j++;
    }
  char word;
  qsort(arr2,number,sizeof(char*),rot13cmp);
  fprintf(stderr,"Number of comparisons: %d \n",totalcmp);
  count=0;
  for(j=0;j<number;j++)
  {
    word=*(arr2[j]);
    while(word!='\n')
      {
        write(1,&word,1);
	word=*(++arr2[j]);
      }
    write(1,&word,1);
  }
  free(arr);
  free(arr2);
  return 0;  
}
