#include <iostream>
#include <string>
#include <fstream>
#include <sndfile.h>
#include <map>
#include <vector>
//#include "matplotlibcpp.h"
#include <cmath>
#include <math.h>

//using namespace plt = matplotlibcpp;
using namespace std;

int main(int argc ,char *argv[])
{
    if(argc < 2)
    {
        printf("Missing args\n");
        return -1;
    }
    string filename = argv[1];

    //cout << "input filename: ";
    //cin >> filename;

    const char* path = "./Wav files-20211025/";
    filename = path + filename;
    path = filename.c_str();

    SF_INFO sfinfo;
    SNDFILE* snd_file;
    FILE *out;

    sfinfo.format = 0;
    snd_file = sf_open(path,SFM_READ,&sfinfo);

    if(snd_file == NULL)
    {
        printf("Failed to open the file\n");
    }    

    int num_channels, num, num_items, f, sr,c, i , j;
    double *buf;
    f = sfinfo.frames;
    sr = sfinfo.samplerate;
    c = sfinfo.channels;

    num_items = f*c;

    printf("frames=%d\n",f);
    printf("samplerate=%d\n",sr);
    printf("channels=%d\n",c);

    buf = (double *) malloc(num_items*sizeof(double));
    num = sf_read_double(snd_file,buf,num_items);

}

void make_copy(char* filename){
    audioFile.load ("sample01.wav");
    std::ofstream ofs ("output.txt");

    std::map <double, int> histogram;

    int channels = audioFile.getNumChannels();
    int numSamples = audioFile.getNumSamplesPerChannel();
    double x;
    //Δ=|t−s|/(λ−1) 
    for(int channel = 0; channel < channels; channel++){
        for (int i = 0; i < numSamples; i++)
        {
        double currentSample = audioFile.samples[channel][i];
        audioFile.samples[channel][i] = 0.25*floor(currentSample/0.25+0.5);
        //ofs << currentSample << "<-->" << audioFile.samples[channel][i] << "<-->" << currentSample - audioFile.samples[channel][i] <<endl;
        }
    }
    //audioFile.setBitDepth (8);

    audioFile.save ("output.wav");

    return 0;