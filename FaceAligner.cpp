#include "FaceAligner.h"
#include "facial_extractor_tools.h"

#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_transforms.h>
#include <dlib/array2d.h>
#include <dlib/pixel.h>
#include <dlib/opencv.h>
#include <opencv2/core/core.hpp>

#include "facial_extractor_tools.h"

FaceAligner::FaceAligner(const unsigned int size, const double left_eye_after) :
        size_(size), left_eye_after_(left_eye_after) {}

void FaceAligner::AlignImage(const dlib::full_object_detection &shape, dlib::array2d <dlib::bgr_pixel> &image,
                             cv::Mat *template_image) {
    dlib::array2d <dlib::bgr_pixel> face_chip;
    dlib::extract_image_chip(image, dlib::get_face_chip_details(shape, size_, left_eye_after_), face_chip);
    dlib::image_window window(face_chip);
    window.wait_until_closed();

    *template_image = dlib::toMat(face_chip);
}