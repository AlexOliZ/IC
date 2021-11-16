// g++ ex4.cpp -o ex4 `pkg-config --cflags --libs opencv`
// ./ex4 <input filename> <output filename> (por ex ./ex4 lena.ppm copy.ppm)

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

    if(argc < 3)
    {
        cout << "Error: Should write <input filename> <output filename>" << endl;
        return EXIT_FAILURE;
    } 

    string input_name,output_name;
    FILE* input_f,*output_f;
    const char* path = "./imagensPPM/";

    input_name = argv[1];
    output_name = argv[2];

    cout<<input_name;

    input_name = path + input_name;
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
     
    imwrite(output_name,output_image); 

    imshow("copy",output_image);
    waitKey();
}