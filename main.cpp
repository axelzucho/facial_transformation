#include "facial_extractor_tools.h"

int main(int argc, char **argv) {
    string path_to_image = "/home/axelzucho/Documents/Github/facial_transformation/images/Cara1.jpeg";
    string path_to_model = "/home/axelzucho/Documents/Github/facial_transformation/shape_predictor_68_face_landmarks.dat";
    rectangle face(330, 320, 640, 630);
    Size template_size(500, 500);
    float left_eye_x = 0.3, left_eye_y = 0.3;
    extractor::example(argc, argv, path_to_image, path_to_model, face, template_size, left_eye_x, left_eye_y);
    extractor::hardcoded_example(argc, argv, "/home/axelzucho/Documents/Github/facial_transformation/images/Cara2.jpg",
                                 template_size, left_eye_x, left_eye_y);
    return 0;
}
