#ifndef FACIAL_EXTRACTOR_TOOLS_H
#define FACIAL_EXTRACTOR_TOOLS_H

#include "facial_extractor_tools.cpp"

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

using namespace std;

using cv::Mat;
using cv::Scalar;
using cv::Rect;
using cv::WINDOW_AUTOSIZE;
using cv::namedWindow;
using cv::waitKey;
using cv::imread;
using cv::IMREAD_COLOR;

using dlib::point;
using dlib::full_object_detection;

#define PI 3.14159265

namespace extractor {
    static Rect dlib_rectangle_to_opencv(rectangle r);
    static point get_average(point left, point right);
    void show_image(Mat image);
    void show_image_with_points(full_object_detection shape, rectangle face_rectangle, Mat image, int size_x, int size_y);
    void face_landmark_detector(string path_to_model, rectangle face_rectangle, Mat mat_image, full_object_detection* shape);
    void read_image(int argc, char** argv, string image_path, Mat* image);
    void align_image(double size_x, double size_y, point left_eye_before, point right_eye_before, Mat image, double left_eye_after_x, double left_eye_after_y, Mat* template_image);
    void example(int argc, char** argv);
} // namespace extractor








#endif