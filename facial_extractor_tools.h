#ifndef FACIAL_EXTRACTOR_TOOLS_H
#define FACIAL_EXTRACTOR_TOOLS_H

#include "facial_extractor_tools.cpp"

namespace extractor {
    static point get_average(point left, point right);
    void show_image(Mat image);
    void show_image_with_points(full_object_detection shape, rectangle face_rectangle, Mat image, int size_x, int size_y);
    void face_landmark_detector(string path_to_model, rectangle face_rectangle, Mat mat_image, full_object_detection* shape);
    void read_image(int argc, char** argv, string image_path, Mat* image);
    void align_image(double size_x, double size_y, point left_eye_before, point right_eye_before, Mat image, double left_eye_after_x, double left_eye_after_y, Mat* template_image);
    void example(int argc, char** argv);
} // namespace extractor

#endif