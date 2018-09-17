#ifndef FACIAL_EXTRACTOR_TOOLS_H
#define FACIAL_EXTRACTOR_TOOLS_H

#include "facial_extractor_tools.cpp"

namespace extractor {
    static point get_average(const point &left, const point &right);

    void show_image(const Mat &image);

    void show_image_with_points(const full_object_detection &shape, const rectangle &face_rectangle, const Mat &image);

    void face_landmark_detector(const string &path_to_model, const rectangle &face_rectangle, const Mat &mat_image,
                                full_object_detection *shape);

    void read_image(int argc, char **argv, string image_path, Mat *image);

    void align_image(const Size &size, const point &left_eye_before, const point &right_eye_before, const Mat &image,
                     const double &left_eye_after_x, const double &left_eye_after_y, Mat *template_image);

    void example(int argc, char **argv, const string &path_to_image, const string &path_to_model, const rectangle &face,
                 const Size &template_size, const float &left_eye_x, const float &left_eye_y);
} // namespace extractor

#endif