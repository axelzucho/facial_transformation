//
// Created by axelzucho on 15/10/18.
//

#ifndef FACIAL_TRANSFORMATION_FACETRANSFORMER_H
#define FACIAL_TRANSFORMATION_FACETRANSFORMER_H

#include "FaceAligner.h"
#include "FaceDetector.h"

#include <dlib/gui_widgets.h>
#include <dlib/image_processing.h>
#include <opencv2/core/core.hpp>

class FaceTransformer {
public:
    FaceTransformer(const string& path_to_model, const unsigned int size, const double left_eye_after);
    void DetectAndAlign(const cv::Mat &image, const dlib::rectangle &face, cv::Mat* template_image);
private:
    FaceDetector* face_detector_;
    FaceAligner* face_aligner_;
};

#endif //FACIAL_TRANSFORMATION_FACETRANSFORMER_H
