#include <iostream>
#include <string>
#include <fstream>
#include <sndfile.h>

using namespace std;

template <class T>
void func(T x)
{
    cout << "**" << sizeof(x) << " " << x << endl;
}

void readFile(string s)
{
    ifstream myfile;
    string line;

    myfile.open(s);
    ofstream ofs("./out_text.txt");

    while(getline(myfile,line))
    {     
        cout << line << endl;
        ofs << line << endl;
        //if(!myfile.good())
        //    break;
    }

    //int x;
    //ofs >> x;
    //ofs << x << endl;

    ofs.close();
}

void copyAudio(const char *path)
{
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
    out = fopen("/home/zedleague/Desktop/IC/wave_copy.txt","w");
    for (i = 0; i < num; i += c)
    {
        for (j = 0; j < c; ++j)
            fprintf(out,"%d ",buf[i+j]);
        fprintf(out,"\n");
    }

    fclose(out);
}

void readJPG(string s)
{
    
}


int main()
{

    //string s;
    //cout << "texto? ";
    //cin >> s;
    //cout << s << endl;
    
    
    readFile("./input.txt");
    copyAudio("/home/zedleague/Desktop/IC/Wav files-20211025/sample02.wav");
    /*
    func(static_cast<char>(64));
    func('x');
    func(1000);
    func(5.5);
    */
}