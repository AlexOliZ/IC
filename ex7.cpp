////g++ ex7.cpp -o ex7 -std=c++11 `pkg-config --cflags --libs opencv`
//Histograms
//https://agostinhobritojr.github.io/tutorial/pdi/ 
//https://docs.opencv.org/4.x/d8/dbc/tutorial_histogram_calculation.html?fbclid=IwAR1ZW9fgVW7tJA62hZ9byJCtnsFgTH4hN7QwpRUpUrzxaLYsST44DuA4DIg
//https://stackoverflow.com/questions/15771512/compare-histograms-of-grayscale-images-in-opencv/15773817 
//https://github.com/samidalati/OpenCV-Entropy/blob/master/histColor.cpp -> entropy calculation
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

//calculate entropy
float entropy(Mat hist, Size size, int histSize) //histogram, image size, histogram size
{  
  int cnt = 0;
  float entr = 0;
  float total_size = size.height * size.width; //total size of all symbols in an image

  for(int i=0;i<hist.rows;i++)
  {
    float sym_occur = hist.at<float>(i, 0); //the number of times a sybmol has occured
    //we want column 1 for all rows
    if(sym_occur>0) //log of zero goes to infinity
      {
        cnt++;
        entr += (sym_occur/total_size)*(log(total_size/sym_occur)); 
      }
  }
 
  return entr;

}


int main(int argc, char** argv)
{
    if(argc < 2){
        cout << "Error: Should write <input filename>" << endl;
        return 0; 
    }
    string filename = argv[1];
    const char* path = "./imagensPPM/";
    filename = path + filename;
    path = filename.c_str();

    Mat src = imread(filename ,IMREAD_COLOR);

    if(! src.data ) { //if you did not find the image
        std::cout <<  "Image not found or unable to open" << std::endl ;
        return -1;
    }
    
    //Separate the image in its three R,G and B planes
    vector<Mat> bgr_planes;
    split( src, bgr_planes );

    //configuring the histograms
    int histSize = 256; //values will range in the interval [0,255]
    int histSize1[] = {histSize};
    int const hist_height = 256;
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange[] = { range };
    // bins to have the same size (uniform) and to clear the histograms in the beginning
    bool uniform = true, accumulate = false;

    //calculation of colour histograms
    Mat b_hist, g_hist, r_hist;
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate ); //b plane
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate ); //g plane
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate ); //r plane
    
    // calculate entropy for colour image
    cout<<"entropy B: "<<entropy(b_hist,src.size(), histSize)<<endl;
    cout<<"entropy G: "<<entropy(g_hist,src.size(), histSize)<<endl;
    cout<<"entropy R: "<<entropy(r_hist,src.size(), histSize)<<endl;


    //Create an image to display the histograms
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    

    //histograma de grayscale

    //procedure the calculation of grayscale histogram
    Mat image1_gray; 
    cvtColor(src, image1_gray, COLOR_BGR2GRAY); //turn the colour image into black and white
    Mat grayscale_hist; //create matrix for histogram
    Mat3b hist_image = Mat3b::zeros(histSize,histSize);//create matrix for histogram visualization
    
    //calculation of grayscale histogram
    calcHist(&image1_gray, 1, 0, Mat(), grayscale_hist, 1, histSize1, histRange, true, false);
    double max_val=0;
    minMaxLoc(grayscale_hist, 0, &max_val);
    //entropy calculation for gray image
    cout<<"entropy grayscale: "<<entropy(grayscale_hist,image1_gray.size(), histSize)<<endl;
    

    //to access the bin (in this case in this 1D-Histogram)
    // we use the expression: b_hist.at<float>(i) when i = dimension
    //If it were a 2D-histogram we would use something like b_hist.at<float>( i, j )
    for( int i = 1; i < histSize; i++ )
    {
        //colour histograms
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
              Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
              Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
              Scalar( 0, 0, 255), 2, 8, 0  );
        
        //grayscale histogram
        line( hist_image, Point(i-1, hist_height- cvRound(grayscale_hist.at<float>(i-1)*hist_height/max_val)),
              Point(i-1, hist_height),Scalar::all(255));
   
    }
   
    //display our histograms and wait for the user to exit
    imshow("Source image", src );
    imshow("Colour histogram", histImage);
    imshow("Source image gray", image1_gray);
    imshow("Grayscale histogram", hist_image);
    waitKey();

    return 0;
}