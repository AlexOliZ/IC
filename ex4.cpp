// g++ ex4.cpp -o app `pkg-config --cflags --libs opencv`
// ./app sheeesh.jpg copy.jpg

#include <iostream>
#include <string>
#include <fstream>

#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"


using namespace std;
using namespace cv;

int main(int argc,char *argv[])
{

    if(argc < 2)
    {
        printf("missing arguments");
        return EXIT_FAILURE;
    } 

    string input_name,output_name;
    FILE* input_f,*output_f;
    const char* path = "/home/zedleague/Desktop/IC/";

    input_name = argv[1];
    output_name = argv[2];

    cout<<input_name;

    input_name = "./" + input_name;
    path = input_name.c_str();
    
    Mat input_image = imread(samples::findFile(path));

    if(input_image.empty())
    {
        printf("read input file error");
        return EXIT_FAILURE;
    } 

    Mat output_image = Mat::zeros(input_image.size(),input_image.type());


    for (int i=0;i<input_image.size().height;++i)
    {
        for(int j=0;j<input_image.size().width;++j)
        {
            output_image.at<Vec3b>(i,j) = input_image.at<Vec3b>(i,j);
        }
    }

    imshow("Input image",input_image);
    waitKey(0);
    printf("%s lol \n", path);

    output_name = "./" + output_name;
    path = output_name.c_str();
    imwrite(path,input_image); 

    imshow("copy",output_image);
    waitKey(0);
}