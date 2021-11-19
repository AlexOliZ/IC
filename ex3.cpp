#include <iostream>
#include <string>
#include <fstream>
#include <sndfile.h>

using namespace std;

int main(int argc ,char *argv[])
{
    if(argc < 3)
    {
        printf("Missing args\n");
        return -1;
    }
    string filename = argv[1];

    const char* path = "./Wav files-20211025/";
    filename = path + filename;
    path = filename.c_str();

    SF_INFO sfinfo;
    SNDFILE* snd_file,*outfile;

    sfinfo.format = 0;
    snd_file = sf_open(path,SFM_READ,&sfinfo);

    if(snd_file == NULL)
    {
        printf("Failed to open the file\n");
    }    

    int num_channels, num, num_items, *buf, f, sr,c;

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

    path = "./";
    
    filename = argv[2];
    filename = path + filename;
    path = filename.c_str();

    outfile = sf_open(path,SFM_WRITE,&sfinfo);
    num = sf_write_int(outfile,buf,num_items);
    printf("Write %d items\n",num);

    sf_close(outfile);
}