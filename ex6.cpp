//https://github.com/lava/matplotlib-cpp
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

    int num_channels, num, num_items, *buf, f, sr,c, i , j;

    f = sfinfo.frames;
    sr = sfinfo.samplerate;
    c = sfinfo.channels;

    num_items = f*c;

    printf("frames=%d\n",f);
    printf("samplerate=%d\n",sr);
    printf("channels=%d\n",c);

    buf = (int *) malloc(num_items*sizeof(int));
    num = sf_read_int(snd_file,buf,num_items);
    
    sf_close(snd_file);
    printf("Read %d items\n",num);

    /* Write the data to filedata.out. */
    path = "./";
    
    filename = argv[2];
    filename = path + filename;
    path = filename.c_str();
    map <int, int> histogram_c1;
    map <int, int> histogram;
    map <int, int> histogram_c2;
    map <int, int> histogram_avg;

    for (i = 0; i < num; i += c)
    {
        
        if (histogram.find(buf[i]/100000)!= histogram.end()){ //if the element exists
            histogram[buf[i]/100000]+=1; //increase the number of elements
        }else{
            histogram[buf[i]/100000]+=1;
            //printf("key=%d\n",buf[i+j]);
        }

        if (histogram.find(buf[i+1]/100000)!= histogram.end()){ //if the element exists
            histogram[buf[i+1]/100000]+=1; //increase the number of elements
        }else{
            histogram[buf[i+1]/100000]+=1;
            //printf("key=%d\n",buf[i+j]);
        }

        if (histogram_c1.find(buf[i]/100000)!= histogram_c1.end()){ //if the element exists
            histogram_c1[buf[i]/100000]+=1; //increase the number of elements
            
        }else{
            histogram_c1[buf[i]/100000]=1; //add an element
            //printf("key=%d\n",buf[i+j]);
        }

        if (histogram_c2.find(buf[i+1]/100000)!= histogram_c2.end()){ //if the element exists
            histogram_c2[buf[i+1]/100000]++; //increase the number of elements
        }else{
            histogram_c2[buf[i+1]/100000]=1; //add an element
            //printf("key=%d\n",buf[i+j]);
        }

        if (histogram_avg.find((buf[i]+buf[i+1])/200000)!= histogram_avg.end()){ //if the element exists
            histogram_avg[(buf[i]+buf[i+1])/200000]++; //increase the number of elements
        }else{
            histogram_avg[(buf[i]+buf[i+1])/200000]=1; //add an element
            //printf("key=%d\n",buf[i+j]);
        }
    }
    int key;
    int value;
    // entropy -> para cada simbolo ak sum[(log P(ak))*P(ak)]
    // P(ak) = val/map.size()
    double entropy_c1 = 0, entropy_c2 = 0, entropy = 0, entropy_avg=0 ,pak = 0;
    //std::vector<int> x_c1(n),y_c1(n);
    i=0;
    
    int len = num_items/100000;
    int len_channel = num_items/200000;
    
    out = fopen("./histogram_c1.txt","w");
    for(std::map<int,int>::iterator it = histogram_c1.begin(); it != histogram_c1.end(); ++it) {
        //x_c1.at(i) = it->first;   //key
        //y_c1.at(i) = it->second; // val
        //i++;
        // entropy c1
        fprintf(out,"%d %d\n",it->first,it->second);
        pak = it->second/len_channel;
        printf("%d,%f\n",it->first,pak);
        if(pak > 0)
            entropy_c1 -= (log(pak)/log(histogram_c1.size())) *pak;
    }
    

    //plt::figure_size(1200, 780);
    //plt::plot(x_c1, y_c1);
    //plt::title("Sample figure");
    //std::vector<int> x_c2(n),y_c2(n);
    out = fopen("./histogram_c2.txt","w");
    for(std::map<int,int>::iterator it = histogram_c2.begin(); it != histogram_c2.end(); ++it) {
        //x_c2.at(i) = it->first;   //key
        //y_c2.at(i) = it->second; // val
        // entropy c2
        fprintf(out,"%d %d\n",it->first,it->second);
        pak = it->second/len_channel;
        if(pak > 0)
            entropy_c2 -= (log(pak)/log(histogram_c2.size())) *pak;
    }

    out = fopen("./histogram.txt","w");
    for(std::map<int,int>::iterator it = histogram.begin(); it != histogram.end(); ++it) {
        //x_c2.at(i) = it->first;   //key
        //y_c2.at(i) = it->second; // val
        // entropy avg
        fprintf(out,"%d %d\n",it->first,it->second);
        pak = it->second/len;
        if(pak > 0)
            entropy -= (log(pak)/log(histogram.size())) *pak;
    }

    out = fopen("./histogram_avg.txt","w");
    for(std::map<int,int>::iterator it = histogram_avg.begin(); it != histogram_avg.end(); ++it) {
        //x_c2.at(i) = it->first;   //key
        //y_c2.at(i) = it->second; // val
        // entropy avg
        fprintf(out,"%d %d\n",it->first,it->second);
        pak = it->second/len_channel;
        if(pak > 0)
            entropy_avg -= (log(pak)/log(histogram_avg.size())) *pak;
    }

    printf("entropy c1 -> %f\n",entropy_c1);
    printf("entropy c2 -> %f\n",entropy_c2);
    printf("entropy avg -> %f\n",entropy_avg);
    printf("entropy -> %f\n",entropy);
    //plot::plot(x,y,"r-",x,[](int d) { return d; }, "k-");
}