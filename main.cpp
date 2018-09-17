#include <iostream>
#include <string>
#include <math.h>

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

#define PI 3.14159265

Mat align_image(double size_x, double size_y, point left_eye_before, point right_eye_before, Mat image, Rect face, double left_eye_after_x, double left_eye_after_y);

static cv::Rect dlib_rectangle_to_opencv(dlib::rectangle r)
{
    return cv::Rect(cv::Point2i(r.left(), r.top()), cv::Point2i(r.right() + 1, r.bottom() + 1));
}

point get_average(point left, point right){
    point average((left.x() + right.x())/2, (left.y() + right.y())/2);
    //average.x((left.x() + right.x())/2);
    //average.y((left.y() + right.y())/2);
    return average;
}

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
    //show_image_with_points(shape, face_rectangle, image_before, 960, 1280);
    point left_eye = get_average(shape.part(37), shape.part(40));
    point right_eye = get_average(shape.part(43), shape.part(46));
    Mat new_image = align_image(500,500, left_eye, right_eye, image_before, dlib_rectangle_to_opencv(face_rectangle), 0.3, 0.3);
    show_image(new_image);
}

void read_image(int argc, char** argv, string image_path){
    if(argc > 1){
        image_path = argv[1];
    }
    Mat image;
    image = imread(image_path.c_str(), IMREAD_COLOR); // Read the file
    if(image.empty()){                      // Check for invalid input
        cout <<  "Could not open or find the image" << std::endl;
        return;
    }
    face_landmark_detector("/home/axelzucho/Documents/Github/facial_transformation/shape_predictor_68_face_landmarks.dat", dlib::rectangle(330,320,640,630),image_path, image);
}

Mat align_image(double size_x, double size_y, point left_eye_before, point right_eye_before, Mat image, Rect face, double left_eye_after_x, double left_eye_after_y){
    int dx = right_eye_before.x() - left_eye_before.x();
    int dy = right_eye_before.y() - left_eye_before.y();

    double angle = atan2(dy, dx);

    double right_eye_after_x = 1 - left_eye_after_x;
    double distance_before = sqrt(dx*dx + dy*dy);
    double desired_distance = right_eye_after_x - left_eye_after_x;
    desired_distance *= size_x;
    double scale = desired_distance/distance_before;

    point center_between_eyes = get_average(left_eye_before, right_eye_before);
    cv::Point2f center_between_eyes_f((float)center_between_eyes.x(), (float)center_between_eyes.y());
    Mat rotation_matrix = cv::getRotationMatrix2D(center_between_eyes_f, angle, scale);

    double tx = size_x/2;
    double ty = size_y*left_eye_after_y;

    rotation_matrix.at<double>(0,2) += tx - center_between_eyes.x();
    rotation_matrix.at<double>(1,2) += ty - center_between_eyes.y();

    Mat image_after;
    cv::warpAffine(image, image_after, rotation_matrix, cv::Size(size_x, size_y), cv::INTER_CUBIC);
    return image_after;
}


int main(int argc, char** argv){
    read_image(argc, argv, "/home/axelzucho/Documents/Github/facial_transformation/images/Cara1.jpeg"); // by default
    return 0;
}
