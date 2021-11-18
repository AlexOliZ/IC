// g++ ex6.cpp -lsndfile
// ./a.out sample01.wav
// #include "gnuplot.h"
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
    if(argc < 1)
    {
        printf("Missing args\n");
        return -1;
    }
    string filename = argv[1];

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

    double* buf;
    f = sfinfo.frames;
    sr = sfinfo.samplerate;
    c = sfinfo.channels;
    num_items = f*c;

    printf("frames=%d\n",f);
    printf("samplerate=%d\n",sr);
    printf("channels=%d\n",c);
    
    buf = (double *) malloc(num_items*sizeof(double));
    num = sf_read_double(snd_file,buf,num_items);
    
    sf_close(snd_file);
    printf("Read %d items\n",num);

    /* Write the data to filedata.out. */
    path = "./";
    
    map <double, int> histogram_c1;
    map <double, int> histogram;
    map <double, int> histogram_c2;
    map <double, int> histogram_avg;

    int precision = 1;
    
    for (i = 0; i < num; i += c)
    {
        
        if (histogram.find(buf[i]*precision)!= histogram.end()){ //if the element exists
            histogram[(buf[i]*precision)]++; //increase the number of elements
        }else{
            histogram[(buf[i]*precision)]=1;
        }

        if (histogram.find((buf[i+1]*precision))!= histogram.end()){ //if the element exists
            histogram[(buf[i+1]*precision)]++; //increase the number of elements
        }else{
            histogram[(buf[i+1]*precision)]=1;
        }

        if (histogram_c1.find((buf[i]*precision))!= histogram_c1.end()){ //if the element exists
            histogram_c1[(buf[i]*precision)]++; //increase the number of elements
            
        }else{
            histogram_c1[(buf[i]*precision)]=1; //add an element
        }

        if (histogram_c2.find((buf[i+1]*precision))!= histogram_c2.end()){ //if the element exists
            histogram_c2[(buf[i+1]*precision)]++; //increase the number of elements
        }else{
            histogram_c2[(buf[i+1]*precision)]=1; //add an element
        }

        if (histogram_avg.find((((buf[i]+buf[i+1])*precision)/2))!= histogram_avg.end()){ //if the element exists
            histogram_avg[((buf[i]+buf[i+1])*precision)/2]++; //increase the number of elements
        }else{
            histogram_avg[((buf[i]+buf[i+1])*precision)/2]=1; //add an element
        }
        
    }
    int key;
    int value;
    double entropy_c1 = 0, entropy_c2 = 0, entropy = 0, entropy_avg=0 ,pak = 0;
    
    i=0;
    
    int len = num_items;
    int len_channel = num_items/2;
    
    out = fopen("./histogram_c1.txt","w");
    for(std::map<double,int>::iterator it = histogram_c1.begin(); it != histogram_c1.end(); ++it) {
        // entropy c1
        fprintf(out,"%f %d\n",it->first,it->second);
        pak = (double)it->second/len_channel;
        if(pak > 0)
            entropy_c1 -= (log(pak)/log(16)) *pak;
    }
    fclose(out);
    

    out = fopen("./histogram_c2.txt","w");
    for(std::map<double,int>::iterator it = histogram_c2.begin(); it != histogram_c2.end(); ++it) {
        // entropy c2
        fprintf(out,"%f %d\n",it->first,it->second);
        pak = (double)it->second/len_channel;
        if(pak > 0)
            entropy_c2 -= (log(pak)/log(16)) *pak;
    }
    fclose(out);

    out = fopen("./histogram.txt","w");
    for(std::map<double,int>::iterator it = histogram.begin(); it != histogram.end(); ++it) {
        // entropy avg
        fprintf(out,"%f %d\n",it->first,it->second);
        pak = (double)it->second/len;
        if(pak > 0)
            entropy -= (log(pak)/log(16)) *pak;
    }
    fclose(out);

    out = fopen("./histogram_avg.txt","w");
    for(std::map<double,int>::iterator it = histogram_avg.begin(); it != histogram_avg.end(); ++it) {
        // entropy avg
        fprintf(out,"%f %d\n",it->first,it->second);
        pak = (double)it->second/len_channel;
        if(pak > 0)
            entropy_avg -= (log(pak)/log(16)) *pak;
    }
    fclose(out);    
    printf("entropy c1 -> %f\n",entropy_c1);
    printf("entropy c2 -> %f\n",entropy_c2);
    printf("entropy avg -> %f\n",entropy_avg);
    printf("entropy -> %f\n",entropy);
}