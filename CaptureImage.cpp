/*This file is used to catch the video from camera robustly
 in case sometimes it cannot read the image from the camera*/
#include <opencv2/opencv/opencv.hpp>
#include <opencv2/highgui/higugui.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;

int main()
{
	VideoCapture cap(0);
	Mat img;
	while (1){
		cap.read(img);
		try{
			if (img.empty()){
				throw double(0);
			}
			else{
				imshow("image",img);
				waitKey(10);
				img.release();
			}
		}
		catch (double){
			cap.release();
			cap.open(0);
		}
	}
}