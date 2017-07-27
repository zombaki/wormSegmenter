#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/core/matx.hpp"
#include <string>
#include <iostream>
#include "wormSegmenter.h"
wormSegmenter::Arguments cla = {"Proj","data/","output.txt",7,1000,".jpg",640,480,200,400,100,3,25,0.9,"wormSeg.log",true};
std::string wormSegmenter::NumberToString(int pNumber) {
    std::ostringstream oOStrStream;
    oOStrStream << pNumber;

    return oOStrStream.str();
}
std::string wormSegmenter::intToFileName(std::string fileNameFormat, int fileNumber) {
    std::string temp = NumberToString(fileNumber);

    return fileNameFormat.replace(fileNameFormat.size() - temp.size(), temp.size(), temp);
}
int wormSegmenter::findCentroidFromImage(wormSegmenter::Arguments &cla,cv::Mat src, int *pX, int *pY, int *pArea) {
    // Smoothing the image.
    cv::blur(src, src, cv::Size(cla.blur_radius, cla.blur_radius));     //Blur radius 3 in original java worm segmenter.

    // Convert the image into binary image.
    cv::threshold(src, src, int(cla.threshold_ratio * 255), 255, cv::THRESH_BINARY_INV);

    // Vector for storing contour
    std::vector<std::vector <cv::Point> > contours;

    std::vector<cv::Vec4i> hierarchy;

    // Find contours in the image.
    cv::findContours(src, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    if (contours.size() > 0) {
        int largest_contour_index = 0;
        int largest_area = 0;

        // Iterate through each contour.
        for(int i = 0; i < contours.size(); i ++) {
            //  Find the area of contour
            double a = cv::contourArea(contours[i], false);

            if(a > largest_area) {
                largest_area = a;

                // Store the index of largest contour
                largest_contour_index = i;
            }
        }

        cv::Rect bRect = boundingRect(contours[largest_contour_index]);

        *pX = bRect.x + (bRect.width / 2);
        *pY = bRect.y + (bRect.height / 2);
        *pArea = largest_area;
    }
    else {
        *pX = -1;
        *pY = -1;
        *pArea = -1;
    }

    return 0;
}
int wormSegmenter::wormSegmenterF(int fileNumber) {

    static int result[3];
    int adjustX = 0, adjustY = 0,x=-1,y=-1,area=-1;
        std::cout<<"File Number : \t"<<fileNumber<<std::endl;

        // File name of each file including the path.
        std::string fileName = cla.input + intToFileName("0000000", fileNumber) + cla.extension;

        // Read and convert the image into gray scale and copy into the matrix.
        cv::Mat src = cv::imread(fileName, CV_LOAD_IMAGE_GRAYSCALE);

        // Exit.
        if (!src.data) {
            std::cout << std::endl << "Exited." << std::endl;
            exit(1);
        }

        if((x == -1) && (y == -1)) {
            findCentroidFromImage(cla,src, &x, &y, &area);
            src = cv::imread(fileName, CV_LOAD_IMAGE_GRAYSCALE);
            adjustX = x - (cla.search_win_size / 2);
            adjustY = y - (cla.search_win_size / 2);
        }
        else {
            src = src(cv::Rect(x - (cla.search_win_size / 2), y - (cla.search_win_size / 2), cla.search_win_size, cla.search_win_size));

            findCentroidFromImage(cla,src, &x, &y, &area);

            if((x > 0) && (y > 0)) {
                x += adjustX;
                y += adjustY;
                adjustX = x - (cla.search_win_size / 2);
                adjustY = y - (cla.search_win_size / 2);
            }
        }
        result[0]=x;
        result[1]=y;
        result[2]=area;

    return result[0];
}




