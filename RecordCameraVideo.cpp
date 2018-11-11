/*
This file is used to capture image with specified resolution.
Besides, it can record the camera's video in MP42 encoding method and save it by using current time.

author: liqi
contact:lickeymouses@163.com

*/

#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
#include <time.h>
#include <string>

int width = 396;
int height = 396;
int fps = 30;

int main()
{
	time_t tt = time(NULL);
	tm *t = localtime(&tt);
	char filename[64];
	sprintf(filename, "%d-%02d-%02d-%02d-%2d-%2d.avi", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, width);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, height);
	cap.set(CV_CAP_PROP_FPS, fps);

	// MPEG, I263, u263, flv1, pim1 不行
	//VideoWriter writer("shoushu_mjpg.avi", CV_FOURCC('M','J','P','G'), 30, Size(396, 396)); // 13s 6318K
	//VideoWriter writer("shoushu_divx.avi", CV_FOURCC('D', 'I', 'V', 'X'), 30, Size(396, 396)); // 8s 1106K
	//VideoWriter writer("shoushu_div3.avi", CV_FOURCC('D', 'I', 'V', '3'), 30, Size(396, 396)); // 4s 1146K
	VideoWriter writer(string(filename), CV_FOURCC('M', 'P', '4', '2'), fps, Size(width, height)); // 6s 897K, 1h 525.6M
	//VideoWriter writer("shoushu_pim1.avi", CV_FOURCC('P', 'I', 'M', '1'), 30, Size(396, 396));

	namedWindow("image", CV_WINDOW_NORMAL);
	setWindowProperty("image", WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	//resizeWindow("image", 1080, 1080);
	moveWindow("image", 0, 0);
	Mat img;
	printf("Starting capturing image and press 'ESC' or 'q' or 'Q'(while the image window is at the most front) to exit.\n");
	while (1)
	{
		cap.read(img);
		if (img.empty())
			continue;
		writer << img;
		imshow("image", img);
		char key = waitKey(30);
		if (key == 27 || key == 'q' || key == 'Q')
			break;
	}
	return 0;
}
