#include<stdio.h>
#include<dlfcn.h>
int main(int argc, char* argv[])
{
  int i=10;
  void(*myfunc)(int*);
  void *dl_handle;
  char *error;
  dl_handle=dlopen("libmymath.so",RTLD_LAZY);
  if(!dl_handle)
    {
      printf("dlopen() error - %s \n",dlerror());
      return 1;
    }
  myfunc=dlsym(dl_handle,"mul5");
  error=dlerror();
  if(error!=NULL)
    {
      printf("dlsym mul5 error - %s \n",error);
    }
  myfunc(&i);
  printf("i=%d\n",i);
  dlclose(dl_handle);
  return 0;
}
