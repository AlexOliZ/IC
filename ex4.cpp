#include <iostream>
#include <string>
#include <fstream>
#include <opencv4>


using namespace std;

int main()
{
    string input_name,output_name;
    FILE* input_f,*output_f;

    cout << "input file: ";
    cin >> output_name;
    cout << "output file: ";
    cin >> input_name;

    input_name = "./" + input_name;
    const char* path = filename.c_str();
    cv::Mat input_image = cv::imread(path);

    output_name = "./" + output_name;
    const char* path = filename.c_str();
    cv::Mat output_image = cv::imread(path);




}