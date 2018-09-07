#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

void show_image(Mat image){
    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display window", image );                // Show our image inside it.
    waitKey(0); // Wait for a keystroke in the window
}

void read_image(int argc, char** argv, string image_name){
    if( argc > 1)
    {
        image_name = argv[1];
    }
    Mat image;
    image = imread(image_name.c_str(), IMREAD_COLOR); // Read the file
    if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return;
    }
    show_image(image);
}


int main( int argc, char** argv )
{
    read_image(argc, argv, "/home/axel/Documents/Proyecto_Reconocimiento/facial_transformation/images/Cara1.jpeg"); // by default
    return 0;
}
