#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

using namespace std;
using namespace cv;
using namespace aruco;

static bool readCameraParameters(string filename, Mat &camMatrix, Mat &distCoeffs);

int main(int argc, const char **argv) {
    /** Display image */
//    Mat image;
//    image = imread("../licorne.jpg", 1 );
//
//    if ( !image.data )
//    {
//        printf("No image data \n");
//        return -1;
//    }
//    namedWindow("Display Image", WINDOW_AUTOSIZE );
//    imshow("Display Image", image);
//    waitKey(0);

    /** WEBCAM */
    VideoCapture inputVideo;
    inputVideo.open(0);
    Ptr<Dictionary> dictionary = getPredefinedDictionary(DICT_6X6_1000);
    float markerSizeMM = 97;

    FileStorage fs("calibration.txt", FileStorage::READ);

    Mat cameraMatrix, distCoeffs;
    readCameraParameters("calibration.txt", cameraMatrix, distCoeffs);

    inputVideo.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
    inputVideo.set(CAP_PROP_FRAME_WIDTH, 1920);
    inputVideo.set(CAP_PROP_FRAME_HEIGHT, 1080);
    inputVideo.set(CAP_PROP_FPS, 60);

    cout << "FPS : " << inputVideo.get(CAP_PROP_FPS) << endl;
    cout << "Width : " << inputVideo.get(CAP_PROP_FRAME_WIDTH) << endl;
    cout << "Height : " << inputVideo.get(CAP_PROP_FRAME_HEIGHT) << endl;

    while (inputVideo.grab()) {
        Mat image, imageCopy;
        inputVideo.retrieve(image);

        image.copyTo(imageCopy);

        vector<int> ids;
        vector<vector<Point2f>> corners, rejected;
        vector<Vec3d> rvec, tvec;

        detectMarkers(image, dictionary, corners, ids);

        // if at least one marker detected
        if (ids.size() > 0) {
            estimatePoseSingleMarkers(corners, markerSizeMM, cameraMatrix, distCoeffs, rvec, tvec);

            drawDetectedMarkers(imageCopy, corners, ids);
            drawAxis(imageCopy, cameraMatrix, distCoeffs, rvec, tvec, markerSizeMM * 0.5);

//            cout << "rvec : " << rvec[0] << endl;
//            cout << "tvec : " << tvec[0] << endl;
        }

        imshow("out", imageCopy);
        char key = (char) waitKey(17);

        if (key == 27)
            break;
    }

    return 0;
}

static bool readCameraParameters(string filename, Mat &camMatrix, Mat &distCoeffs) {
    cout << "camera file : " << filename << endl;
    FileStorage fs(filename, FileStorage::READ);
    if(!fs.isOpened())
        return false;
    fs["camera_matrix"] >> camMatrix;
    fs["distortion_coefficients"] >> distCoeffs;
    return true;
}