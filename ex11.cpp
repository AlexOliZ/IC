//g++ ex9.cpp -o ex9 -std=c++11 `pkg-config --cflags --libs opencv`
//./ex9 <input filename> <output filename> (por ex ./ex9 lena.ppm  lena7.ppm)

#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <math.h>
using namespace std;
using namespace cv;


int main(int argc, char** argv) 
{
    if(argc < 3){
        cout << "Error: Should write <input filename> <output filename>" << endl;
        return 0; 
    }
    string filename = argv[1];
    const char* path = "./imagensPPM/";
    filename = path + filename;
    path = filename.c_str();

    Mat image = imread(filename ,IMREAD_COLOR);
    //create final image
    Mat Final_image = Mat::zeros(image.size(),image.type()); 
    imshow("Initial image",image);

    if(! image.data ) { //if you did not find the image
        std::cout <<  "Image not found or unable to open" << std::endl ;
        return -1;
    }
    
    //read the image pixel by pixel
    uint8_t* pixelPtr = (uint8_t*)image.data;

    uint64_t original,transformed;
    uint64_t sum_x = 0;
    uint64_t sum = 0;
    uint8_t max =0;
    
    int cn = image.channels(); //gives us the colour channels (which colours they are)
    
    for(int i=0; i<image.rows; i++){
        for(int j=0; j<image.cols; j++){
            //get pixel
            Vec3b & val = Final_image.at<Vec3b>(i,j);
            //store original value of pixel
            original = pixelPtr[i*image.cols*cn + j*cn + 0] + pixelPtr[i*image.cols*cn + j*cn + 1] + pixelPtr[i*image.cols*cn + j*cn + 2];
            //color
            val[0] = (((pixelPtr[i*image.cols*cn + j*cn + 0])>>7)<<7);     //B
            val[1] = (((pixelPtr[i*image.cols*cn + j*cn + 1])>>7)<<7);     //G
            val[2] = (((pixelPtr[i*image.cols*cn + j*cn + 2])>>7)<<7);     //R
            //store transformed value of pixel
            transformed = val[0] + val[1] + val[2]; 
            //avaliação valor maximo
            if(max < original - transformed){
                max = original - transformed;
            }
            //calculo er
            sum+=pow(original - transformed,2); 
            //calculo ex
            sum_x+=pow(original,2);

            // set pixel (Can now access the pixel value with cv::Vec3b)
            Final_image.at<Vec3b>((i,j)) = val;
        }
    }

    //snr = 10log(ex/er)
    uint64_t snr = 10*log(sum_x/sum);   
    printf("SNR: %lu\n",snr);
    printf("MAX ABSOLUTE ERROR: %d\n",max);


    imshow("Final image",Final_image); // show image
    waitKey();   

    return 0;
}