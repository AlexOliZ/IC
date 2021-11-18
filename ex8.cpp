#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <string.h>
#include <iostream>
#include <math.h>      

int main(int argc, char *argv[])
{

  if(argc != 2){
    std::cout << "USE IS: ./ex8 <samplename.wav>"<< std::endl;
    return 1;
  }
  char *inFileName = (char*)malloc(sizeof(char*));
  std::cout << argv[1] << std::endl;
  strcpy(inFileName,argv[1]);

  double *buf;
  int num_items,num;
  double x;
  SNDFILE *inFile,*outFile;
  SF_INFO inFileInfo;

  inFile = sf_open(inFileName, SFM_READ, &inFileInfo);
  int channels = inFileInfo.channels;

  num_items = inFileInfo.frames*channels;

  /* Allocate space for the data to be read, then read it. */
  buf = (double *) malloc(num_items*sizeof(double));
  num = sf_read_double(inFile,buf,num_items);
  
  //Δ=|t−s|/(λ−1) 
  //4bits => 2 / (2⁴-1) = 0,1333
  for (int i = 0; i < num; i += channels)
  {
    for (int j = 0; j < channels; ++j){
        buf[i+j] = 0.1333*floor(buf[i+j]/0.1333+0.5);
        x = buf[i+j];
    }
  }
  const char* outfilename = "output.wav";
  outFile = sf_open (outfilename, SFM_WRITE, &inFileInfo);

  sf_write_double (outFile, buf, num_items) ;
  sf_close(inFile);
  sf_close(outFile) ;
  return 0;
}