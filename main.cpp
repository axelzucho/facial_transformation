#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <opencv2/imgproc.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/image_io.h>

using namespace dlib;
using namespace cv;
using namespace std;

void show_image(Mat image){
    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display window", image );                // Show our image inside it.
    waitKey(0); // Wait for a keystroke in the window
}

void show_image_with_face(Mat image, Rect rect, Scalar color){
    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    cv::rectangle(image, rect, color);
    imshow( "Display window", image );                // Show our image inside it.
    waitKey(0); // Wait for a keystroke in the window
}

void face_landmark_detector(string path_to_model, dlib::rectangle face_rectangle, string image_path){
    shape_predictor sp;
    deserialize(path_to_model) >> sp;

    array2d<rgb_pixel> image;
    load_image(image, image_path);

    full_object_detection shape = sp(image, face_rectangle);
    cout << "number of parts: " << shape.num_parts() << endl;
}

void read_image(int argc, char** argv, string image_path){
    if( argc > 1)
    {
        image_path = argv[1];
    }
    Mat image;
    image = imread(image_path.c_str(), IMREAD_COLOR); // Read the file
    if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return;
    }
    show_image_with_face(image, Rect(350,300,300,330), Scalar(100,130,130));
    face_landmark_detector("/home/axel/Documents/Proyecto_Reconocimiento/facial_transformation/shape_predictor_68_face_landmarks.dat", dlib::rectangle(350,300,300,330),image_path);
}


int main( int argc, char** argv )
{
    read_image(argc, argv, "/home/axel/Documents/Proyecto_Reconocimiento/facial_transformation/images/Cara1.jpeg"); // by default
    return 0;
}
