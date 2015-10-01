#include "test.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
    // Create black empty images
    Mat image = Mat::zeros( 400, 400, CV_8UC3 );
   
    // Draw a line 
    line( image, Point( 15, 20 ), Point( 270, 300), Scalar( 110, 220, 0 ),  2, 8 );
	circle(image, Point(200, 200), 66, Scalar(255, 255, 0));
    imshow("Image",image);
 
    waitKey( 0 );
    return(0);

    return 0;
}