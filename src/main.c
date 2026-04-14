#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  if (argc > 1){
    printf("Привет, %s", argv[1]);
  }
  else 
  {
    const char *name = "USERNAME";
    const char *env_p = getenv(name);
    if (env_p)
    {
      printf("Привет, %s", env_p);
    }
    else
    {
      printf("Hello, %s", getenv("USER"));
    }

  }
  return 0;
}
