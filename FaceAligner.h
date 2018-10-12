#ifndef FACIAL_TRANSFORMATION_FACEALIGNER_H
#define FACIAL_TRANSFORMATION_FACEALIGNER_H

#include <dlib/image_processing/frontal_face_detector.h>
#include <opencv2/opencv.hpp>

class FaceAligner {
public:
    FaceAligner(const cv::Size size, const double left_eye_after_x, const double left_eye_after_y);
    void AlignImage(const dlib::full_object_detection &shape, const cv::Mat &image, cv::Mat *template_image);

private:
    cv::Size size_;
    double left_eye_after_x_;
    double left_eye_after_y_;
};

#endif //FACIAL_TRANSFORMATION_FACEALIGNER_H
