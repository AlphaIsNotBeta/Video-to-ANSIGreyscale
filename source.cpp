#include "opencv-image_header.h"



string pixelToANSI(int pixel_intensity) {
    // const string ASCII_CHARS = "@$%#&!*+=-_.                ";
    // const string ASCII_CHARS = "@#&!*+=-_.     ";
    // const string ASCII_CHARS = "   ._-=+*!&#%$@";
    const int grayscaleDensity[24] = {232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};
    string s = "\033[48;5;" + to_string(grayscaleDensity[pixel_intensity * 24 / 255 - 1]) + "m ";
    return s;
}

void main() {

    string video_path = "C:\\Users\\Jun\\Documents\\opencv-image&video\\opencv-video\\video1.mp4";
    VideoCapture cap(video_path);

    double fps = cap.get(CAP_PROP_FPS); 
    int frame_duration_ms = 1000 / fps;

    cout << fps;

    while (true) {


        int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
        int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int height, width;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = csbi.srWindow.Right - csbi.srWindow.Left;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top;

        Mat frame, gray_frame, resized_frame;

        cap >> frame;
        if (frame.empty())
            break;

        cvtColor(frame, gray_frame, COLOR_BGR2GRAY);

        resize(gray_frame, resized_frame, Size(width, height), 0, 0, INTER_LINEAR);

        string ansi_frame;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                ansi_frame += pixelToANSI(resized_frame.at<uchar>(i, j));
            }
            ansi_frame += "\n";
        }
        cout << ascii_frame;
        sleep_for(milliseconds(frame_duration_ms));
        system("cls");
    }
    cout << "Video over. . .";
    cin.get();
}