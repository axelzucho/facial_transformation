#ifndef FACIAL_EXTRACTOR_TOOLS_H
#define FACIAL_EXTRACTOR_TOOLS_H

#include "facial_extractor_tools.cpp"

namespace extractor {
    static point get_average(const point &left, const point &right);

    void show_image(const Mat &image);

    void show_image_with_points(const full_object_detection &shape, const rectangle &face_rectangle, const Mat &image);

    void read_image(int argc, char **argv, string image_path, Mat *image);

    } // namespace extractor

#endif