#include "FaceTransformer.h"

#include <dlib/image_processing/frontal_face_detector.h>

FaceTransformer::FaceTransformer(const string& path_to_model, const cv::Size& size, const double left_eye_after_x, const double left_eye_after_y){
    face_detector_ = new FaceDetector(path_to_model);
    face_aligner_ = new FaceAligner(size, left_eye_after_x, left_eye_after_y);
}
void FaceTransformer::DetectAndAlign(const cv::Mat &image, const dlib::rectangle &face, cv::Mat* template_image){
    dlib::full_object_detection shape;
    face_detector_->GetFaceLandmark(image, face, &shape);
    face_aligner_->AlignImage(shape, image, template_image);
}

//
// Created by axelzucho on 15/10/18.
//

