#include <iostream>
#include <string>
#include <math.h>

#include <dlib/image_processing/render_face_detections.h>
#include <dlib/opencv/cv_image.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>

#include "facial_extractor_tools.h"

using namespace std;

using cv::Mat;
using cv::Scalar;
using cv::Rect;
using cv::Size;
using cv::WINDOW_AUTOSIZE;
using cv::namedWindow;
using cv::waitKey;
using cv::imread;
using cv::IMREAD_COLOR;

using dlib::rectangle;
using dlib::point;
using dlib::load_image;
using dlib::image_window;
using dlib::full_object_detection;
using dlib::assign_image;
using dlib::cv_image;

#define PI 3.14159265

namespace extractor {

    dlib::rectangle opencv_rect_to_dlib(cv::Rect r){
        return dlib::rectangle((long)r.tl().x, (long)r.tl().y, (long)r.br().x - 1, (long)r.br().y - 1);
    }

    dlib::point get_average(const dlib::point &left, const dlib::point &right) {
        point average((left.x() + right.x()) / 2, (left.y() + right.y()) / 2);
        return average;
    }

    void show_image(const Mat &image) {
        namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
        imshow("Display window", image);                // Show our image inside it.
        waitKey(0); // Wait for a keystroke in the window
    }

    void show_image_with_points(const dlib::full_object_detection &shape, const rectangle &face_rectangle,
                                const Mat &image) {
        std::vector<image_window::overlay_circle> points;
        image_window win;
        win.set_size(image.cols, image.rows);
        win.set_title("Detector");

        while (!win.is_closed()) {
            for (unsigned int n = 0; n < shape.num_parts(); n++) {
                const point &pt = shape.part(n);
                points.emplace_back(image_window::overlay_circle(pt, 2, dlib::rgb_pixel(255, 255, 0)));
            }

            win.clear_overlay();
            win.set_image(dlib::cv_image<dlib::bgr_pixel>(image));
            win.add_overlay(points);
            win.add_overlay(face_rectangle);
        }
    }

    void read_image(int argc, char **argv, string image_path, Mat *image) {
        if (argc > 1) {
            image_path = argv[1];
        }
        *image = imread(image_path.c_str(), IMREAD_COLOR); // Read the file
        if (image->empty()) {                      // Check for invalid input
            cout << "Could not open or find the image" << std::endl;
            return;
        }
    }

} // namespace extractor