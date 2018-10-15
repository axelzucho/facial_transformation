#include "facial_extractor_tools.h"
#include "FaceAligner.h"
#include "FaceDetector.h"
#include "FaceTransformer.h"

using cv::Mat;
using std::string;
using dlib::full_object_detection;
using cv::Size;
using dlib::rectangle;

void
example(int argc, char **argv, const string &path_to_image, const string &path_to_model, const dlib::rectangle &face,
        const cv::Size &template_size, const float &left_eye_x, const float &left_eye_y) {
    Mat image;
    extractor::read_image(argc, argv, path_to_image,
                          &image); // by default

    FaceTransformer face_transformer(path_to_model, template_size, left_eye_x, left_eye_y);
    Mat template_image;
    face_transformer.DetectAndAlign(image, face, &template_image);
    extractor::show_image(template_image);
}

int main(int argc, char **argv) {
    string path_to_image = "/home/axelzucho/Documents/Github/facial_transformation/images/Cara1.jpeg";
    string path_to_model = "/home/axelzucho/Documents/Github/facial_transformation/shape_predictor_68_face_landmarks.dat";
    rectangle face(330, 320, 640, 630);
    Size template_size(500, 500);
    float left_eye_x = 0.3, left_eye_y = 0.3;
    example(argc, argv, path_to_image, path_to_model, face, template_size, left_eye_x, left_eye_y);
    return 0;
}
