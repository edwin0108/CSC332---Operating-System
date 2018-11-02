#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
  int x = 10;
  int y = 4;
  FILE *inpf;
  inpf = fopen("input_file.txt", "w");
  for (int i=0; i<x; i++){
    for (int j=0; j<y; j++){
      fprintf(inpf,"%*d ",3, rand()%100);
    }
	fprintf(inpf,"\n");
  }
  fclose(inpf);
}
