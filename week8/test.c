#include<stdio.h>
int main()
{
  int a=1;
  unsigned char b=255;
  int c=(int)b;
  char d=(char)b;
  printf("%d \n",c);
  printf("%c \n",d);
  if(d==EOF)
    {
      printf("they are same");
    }
  else
    printf("no");
}
