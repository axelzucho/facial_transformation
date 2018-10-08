#include "FaceAligner.h"
#include "facial_extractor_tools.h"

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

using cv::Mat;
using cv::Size;

using dlib::point;

#define PI 3.14159265

FaceAligner::FaceAligner(const Size size, const double left_eye_after_x, const double left_eye_after_y) :
        size_(size), left_eye_after_x_(left_eye_after_x), left_eye_after_y_(left_eye_after_y) {}

void FaceAligner::AlignImage(const dlib::full_object_detection &shape, const Mat &image, Mat *template_image) {
    point left_eye = extractor::get_average(shape.part(37), shape.part(40));
    point right_eye = extractor::get_average(shape.part(43), shape.part(46));

    long dx = right_eye.x() - left_eye.x();
    long dy = right_eye.y() - left_eye.y();
    double angle = atan2(dy, dx) * 180 / PI;

    double right_eye_after_x = 1 - left_eye_after_x_;
    double distance_before = sqrt(dx * dx + dy * dy);
    double desired_distance = right_eye_after_x - left_eye_after_x_;
    desired_distance *= size_.width;
    double scale = desired_distance / distance_before;

    point center_between_eyes = extractor::get_average(left_eye, right_eye);
    cv::Point2f center_between_eyes_f(center_between_eyes.x(), center_between_eyes.y());
    Mat rotation_matrix = cv::getRotationMatrix2D(center_between_eyes_f, angle, scale);

    double tx = (float) size_.width / 2;
    double ty = size_.height * left_eye_after_y_;
    rotation_matrix.at<double>(0, 2) += tx - center_between_eyes.x();
    rotation_matrix.at<double>(1, 2) += ty - center_between_eyes.y();
    cv::warpAffine(image, *template_image, rotation_matrix, size_, cv::INTER_CUBIC);
}