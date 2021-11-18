//g++ ex10.cpp -lsndfile
// ./a.out sample01.wav

#include <iostream>
#include <string>
#include <fstream>
#include <sndfile.h>
#include <map>
#include <vector>
//#include "matplotlibcpp.h"
#include <cmath>
#include <math.h>
#include <cstring>

//using namespace plt = matplotlibcpp;
using namespace std;

int main(int argc ,char *argv[])
{
    if(argc != 2){
        std::cout << "USE IS: ./ex8 <samplename.wav>"<< std::endl;
        return 1;
    }
    char *inFileName = (char*)malloc(sizeof(char*));
    std::cout << argv[1] << std::endl;
    strcpy(inFileName,argv[1]);

    double *buf,*buf_r;
    int num_items,num;
    double sum_r=0,sum=0;
    double SNR;
    SNDFILE *inFile,*outFile;
    SF_INFO inFileInfo;
    string filename = argv[1];

    const char* path = "./Wav files-20211025/";
    filename = path + filename;
    path = filename.c_str();

    inFile = sf_open(path, SFM_READ, &inFileInfo);
    int channels = inFileInfo.channels;

    num_items = inFileInfo.frames*channels;

    /* Allocate space for the data to be read, then read it. */
    buf = (double *) malloc(num_items*sizeof(double));
    num = sf_read_double(inFile,buf,num_items);
    buf_r = (double *) malloc(num_items*sizeof(double));
    double max_abs_error = 0;
    //Δ=|t−s|/(λ−1) 
    //4bits => 2 / (2⁴-1) = 0,1333
    for (int i = 0; i < num; i += channels)
    {
        for (int j = 0; j < channels; ++j){
            buf_r[i+j] = 0.1333*floor(buf[i+j]/0.1333+0.5);
            sum += pow(buf_r[i+j],2);
            sum_r += pow(buf[i+j]-buf_r[i+j],2);
            if(pow(buf[i+j]-buf_r[i+j],2) > max_abs_error)
                max_abs_error = pow(buf[i+j]-buf_r[i+j],2);
        }
    }
    SNR = 10*log(sum/sum_r);

    printf("SUM: %f\n",sum);
    printf("SUM_R: %f\n",sum_r);
    printf("SNR: %f\n",SNR);
    printf("MAX ABS ERROR: %f\n",max_abs_error);



}
