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

using dlib::rectangle;
using dlib::point;
using dlib::load_image;
using dlib::image_window;
using dlib::bgr_pixel;
using dlib::rgb_pixel;
using dlib::full_object_detection;
using dlib::assign_image;
using dlib::cv_image;

#define PI 3.14159265

namespace extractor {


    static cv::Rect dlib_rectangle_to_opencv(rectangle r) {
        return Rect(cv::Point2i(r.left(), r.top()), cv::Point2i(r.right() + 1, r.bottom() + 1));
    }

    static point get_average(point left, point right) {
        point average((left.x() + right.x()) / 2, (left.y() + right.y()) / 2);
        return average;
    }

    void show_image(Mat image) {
        namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
        imshow("Display window", image);                // Show our image inside it.
        waitKey(0); // Wait for a keystroke in the window
    }

    void show_image_with_points(dlib::full_object_detection shape, rectangle face_rectangle, Mat image, int size_x,
                                int size_y) {
        std::vector <image_window::overlay_circle> points;
        image_window win;
        win.set_size(size_x, size_y);
        win.set_title("Detector");

        while (!win.is_closed()) {
            for (unsigned int n = 0; n < shape.num_parts(); n++) {
                point pt = shape.part(n);
                points.push_back(image_window::overlay_circle(pt, 2, dlib::rgb_pixel(255, 255, 0)));
            }

            win.clear_overlay();
            win.set_image(dlib::cv_image<bgr_pixel>(image));
            win.add_overlay(points);
            win.add_overlay(face_rectangle);
        }
    }

    void face_landmark_detector(string path_to_model, rectangle face_rectangle, Mat mat_image,
                                full_object_detection *shape) {
        dlib::shape_predictor sp;
        dlib::deserialize(path_to_model) >> sp;
        dlib::array2d <rgb_pixel> dlib_image;
        assign_image(dlib_image, cv_image<rgb_pixel>(mat_image));

        *shape = sp(dlib_image, face_rectangle);
        show_image_with_points(*shape, face_rectangle, mat_image, 960, 1280);
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

    void align_image(double size_x, double size_y, point left_eye_before, point right_eye_before, Mat image,
                     double left_eye_after_x, double left_eye_after_y, Mat *template_image) {
        int dx = right_eye_before.x() - left_eye_before.x();
        int dy = right_eye_before.y() - left_eye_before.y();
        double angle = atan2(dy, dx) * 180 / PI;

        double right_eye_after_x = 1 - left_eye_after_x;
        double distance_before = sqrt(dx * dx + dy * dy);
        double desired_distance = right_eye_after_x - left_eye_after_x;
        desired_distance *= size_x;
        double scale = desired_distance / distance_before;

        point center_between_eyes = get_average(left_eye_before, right_eye_before);
        cv::Point2f center_between_eyes_f((float) center_between_eyes.x(), (float) center_between_eyes.y());
        Mat rotation_matrix = cv::getRotationMatrix2D(center_between_eyes_f, angle, scale);

        double tx = size_x / 2;
        double ty = size_y * left_eye_after_y;
        rotation_matrix.at<double>(0, 2) += tx - center_between_eyes.x();
        rotation_matrix.at<double>(1, 2) += ty - center_between_eyes.y();
        cv::warpAffine(image, *template_image, rotation_matrix, cv::Size(size_x, size_y), cv::INTER_CUBIC);
    }


    void example(int argc, char **argv) {
        Mat image;
        read_image(argc, argv, "/home/axelzucho/Documents/Github/facial_transformation/images/Cara1.jpeg",
                   &image); // by default
        full_object_detection shape;
        rectangle face(330, 320, 640, 630);
        face_landmark_detector(
                "/home/axelzucho/Documents/Github/facial_transformation/shape_predictor_68_face_landmarks.dat", face,
                image, &shape);
        Mat template_image;
        point left_eye = get_average(shape.part(37), shape.part(40));
        point right_eye = get_average(shape.part(43), shape.part(46));
        align_image(500, 500, left_eye, right_eye, image, 0.3, 0.3, &template_image);
        show_image(template_image);
    }

} // namespace extractor