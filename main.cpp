#include <iostream>
#include <string>

#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/opencv/cv_image.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace dlib;
using namespace std;

using cv::Mat;
using cv::Scalar;
using cv::Rect;
using cv::WINDOW_AUTOSIZE;
using cv::namedWindow;
using cv::waitKey;
using cv::imread;
using cv::IMREAD_COLOR;

void show_image(Mat image){
    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display window", image );                // Show our image inside it.
    waitKey(0); // Wait for a keystroke in the window
}

void show_image_with_points(full_object_detection shape, dlib::rectangle face_rectangle, Mat image, int size_x, int size_y){
    std::vector<image_window::overlay_circle> points;
    image_window win;
    win.set_size(size_x,size_y);
    win.set_title("Detector");

    while(!win.is_closed()){
        for(unsigned int n = 0; n < shape.num_parts(); n++){
            point pt = shape.part(n);
            points.push_back(image_window::overlay_circle(pt, 2, rgb_pixel(255, 255, 0)));
            cout << "Point " << n << ": " << pt.x() << " " << pt.y() << endl;
        }

        win.clear_overlay();
        win.set_image(cv_image<bgr_pixel>(image));
        win.add_overlay(points);
        win.add_overlay(face_rectangle);
    }
}

void face_landmark_detector(string path_to_model, dlib::rectangle face_rectangle, string image_path, Mat image_before){
    shape_predictor sp;
    deserialize(path_to_model) >> sp;
    array2d<rgb_pixel> image;
    load_image(image, image_path);

    full_object_detection shape = sp(image, face_rectangle);
    show_image_with_points(shape, face_rectangle, image_before, 960, 1280);
}

void read_image(int argc, char** argv, string image_path){
    if(argc > 1){
        image_path = argv[1];
    }
    Mat image;
    image = imread(image_path.c_str(), IMREAD_COLOR); // Read the file
    if(image.empty()){                      // Check for invalid input
        cout <<  "Could not open or find the image" << std::endl ;
        return;
    }
    face_landmark_detector("/home/axel/Documents/Proyecto_Reconocimiento/facial_transformation/shape_predictor_68_face_landmarks.dat", dlib::rectangle(330,320,640,630),image_path, image);
}


int main(int argc, char** argv){
    read_image(argc, argv, "/home/axel/Documents/Proyecto_Reconocimiento/facial_transformation/images/Cara1.jpeg"); // by default
    return 0;
}
