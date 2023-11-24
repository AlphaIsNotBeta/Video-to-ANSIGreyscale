#include "opencv-image_header.h"
#define VIDEO_PATH "PATH"
#define ANSI_CODE "\033[48;5;"

#ifndef VIDEO_PATH
    #define VIDEO_PATH NULL
#endif


int main() {

    if (VIDEO_PATH == NULL){
        cerr << "Missing video path.";
        return -1;
    }

    VideoCapture cap(VIDEO_PATH);

    const string grayscaleDensity[24] = {"232","233","234","235","236","237","238","239","240","241","242","243","244","245","246","247","248","249","250","251","252","253","254","255"};
    string ansi_frame;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int height, width;

    for (size_t TIME = 5; TIME > 0; TIME -= 1){
        system("cls");
        cout << "Video start in " << TIME << "\n";
        sleep_for(seconds(1));
    }

    Mat frame, gray_frame, resized_frame;

    system("cls");
    while (true) {

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = csbi.srWindow.Right - csbi.srWindow.Left;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top;

        cap >> frame;

        if(frame.empty()){
            break;
        }
        
        cvtColor(frame, gray_frame, COLOR_BGR2GRAY);

        resize(gray_frame, resized_frame, Size(width, height), 0, 0, INTER_LINEAR);

        ansi_frame = "";
        for (int i = 0; i < height; i += 1) {
            for (int j = 0; j < width; ++j) {
                ansi_frame += ANSI_CODE + grayscaleDensity[resized_frame.at<uchar>(i, j) * 24 / 255] + "m ";
                
            }
            ansi_frame += "\n";
        }
        cout << ansi_frame;
        system("cls");
    }
    cout << "Video over. . .\n";
    system("pause");

    return 0;
}
