//
//  main.cpp
//  opencv3
//
//  Created by hakim on 23/02/2015.
//  Copyright (c) 2015 hakim. All rights reserved.
//
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "Histogramme.h"


#define NOMIMAGE "dame.png"

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    
    IplImage * pInpImg = 0;
    Mat src, src_gray;
    cout << "init" << endl;
    
    
    // Load an image from file - change this based on your image name
    pInpImg = cvLoadImage(NOMIMAGE, CV_LOAD_IMAGE_UNCHANGED);
    
    if(!pInpImg){
        
        fprintf(stderr, "failed to load input image\n");
        return -1;
    }
    if( !cvSaveImage(NOMIMAGE, pInpImg) ){
        fprintf(stderr, "failed to write image file\n");
    }
    
    src = imread(NOMIMAGE);
    if( !src.data ){ return -1; }
    
    
    cvtColor( src, src_gray, CV_BGR2GRAY );
    
    /// Reduce the noise so we avoid false circle detection
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );
    
    vector<Vec3f> circles;
    
    /// Apply the Hough Transform to find the circles
    HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 100, 10, 4, 22 );
    
    for( size_t i = 0; i < circles.size(); i++ ){
        
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // circle center
        circle( src, center, 1, Scalar(0,255,0), -1, 8, 0 );
        // circle outline
        circle( src, center, radius, Scalar(0,0,255), 2, 8, 0 );
    }
    
    /// Show your results
    namedWindow( "Jeux de dames detection", CV_WINDOW_AUTOSIZE );
    imshow( "jeux de dames detection", src );
    
  //  cvNamedWindow(NOMIMAGE,1);
  //  cvShowImage(NOMIMAGE, pInpImg);
    Histogramme::getHistogramme(src);
    Histogramme::getHistogrammeEgalise(src);
    
    
    cvWaitKey();
    if (pInpImg) cvReleaseImage (&pInpImg);
    
    
    return 0;
}
