#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include "CameraCapture.h"
#include "ImageProcess.h"
#include <Windows.h>

float tsum = 0;
int count = 0;

// total mapx of final image
cv::Mat mapx = cv::Mat::zeros(1080, 1920, CV_32FC1);
cv::Mat lmapx = mapx.colRange(0, 960);
cv::Mat rmapx = mapx.colRange(960, 1920);
// total mapy of final image
cv::Mat mapy = cv::Mat::zeros(1080, 1920, CV_32FC1);
cv::Mat lmapy = mapy.colRange(0, 960);
cv::Mat rmapy = mapy.colRange(960, 1920);
// short and uchar
cv::Mat Smapx, Umapy;

cv::Mat TestSmapx, TestUmapy;
cv::Mat TestMapImg;

// original image
cv::Mat oriImg = cv::Mat(1080, 3840, CV_8UC3);
cv::Mat oriLImg = oriImg.colRange(0, 1920);
cv::Mat oriRImg = oriImg.colRange(1920, 3840);

// mapped image from original image
cv::Mat mapImg = cv::Mat::zeros(1080, 1920, CV_8UC3);
cv::Mat mapLeftImg = mapImg.colRange(0, 960);
cv::Mat mapRightImg = mapImg.colRange(960, 1920);

void Init1080pCameraParams(){
	cv::Mat A1, A2;
	A1 = cv::Mat(3, 3, CV_32F);
	A2 = cv::Mat(3, 3, CV_32F);
	cv::Mat D1, D2;
	D1 = cv::Mat(5, 1, CV_32F);
	D2 = cv::Mat(5, 1, CV_32F);
	cv::Mat R1, R2;
	R1 = cv::Mat(3, 3, CV_32F);
	R2 = cv::Mat(3, 3, CV_32F);

	A1.at<float>(0, 0) = 1154.2f; A1.at<float>(0, 1) = 0.f; A1.at<float>(0, 2) = 866.5341f;
	A1.at<float>(1, 0) = 0.f; A1.at<float>(1, 1) = 1157.9f; A1.at<float>(1, 2) = 569.0965f;
	A1.at<float>(2, 0) = 0.f; A1.at<float>(2, 1) = 0.f; A1.at<float>(2, 2) = 1.f;
	D1.at<float>(0, 0) = -0.2009f; D1.at<float>(1, 0) = 0.0610f; D1.at<float>(2, 0) = 0.f;
	D1.at<float>(3, 0) = -0.0025f; D1.at<float>(4, 0) = 0.0013f;

	A2.at<float>(0, 0) = 1161.5f; A2.at<float>(0, 1) = 0.f; A2.at<float>(0, 2) = 841.5507f;
	A2.at<float>(1, 0) = 0.f; A2.at<float>(1, 1) = 1165.5f; A2.at<float>(1, 2) = 596.2143f;
	A2.at<float>(2, 0) = 0.f; A2.at<float>(2, 1) = 0.f; A2.at<float>(2, 2) = 1.f;
	D2.at<float>(0, 0) = -0.1999f; D2.at<float>(1, 0) = 0.0574f; D2.at<float>(2, 0) = 0.f;
	D2.at<float>(3, 0) = -0.0030f; D2.at<float>(4, 0) = 0.0039f;

	R1.at<float>(0, 0) = 0.9994f; R1.at<float>(0, 1) = 0.03361f; R1.at<float>(0, 2) = -2.02e-3f;
	R1.at<float>(1, 0) = -0.03361f; R1.at<float>(1, 1) = 0.9994f; R1.at<float>(1, 2) = 1.38e-3f;
	R1.at<float>(2, 0) = 2.07e-3f; R1.at<float>(2, 1) = -1.31e-3f; R1.at<float>(2, 2) = 1.f;

	R2.at<float>(0, 0) = 0.9987f; R2.at<float>(0, 1) = 0.05059f; R2.at<float>(0, 2) = -3.6e-3f;
	R2.at<float>(1, 0) = -0.0506f; R2.at<float>(1, 1) = 0.9987f; R2.at<float>(1, 2) = -1.26e-3f;
	R2.at<float>(2, 0) = 3.53e-3f; R2.at<float>(2, 1) = 1.44e-3f; R2.at<float>(2, 2) = 1.f;

	cv::Mat A = (A1 + A2) / 2;

	float fx1, fy1, cx1, cy1, k11, k12, k13, p11, p12;
	fx1 = A1.at<float>(0, 0); fy1 = A1.at<float>(1, 1);
	cx1 = A1.at<float>(0, 2); cy1 = A1.at<float>(1, 2);
	k11 = D1.at<float>(0, 0); k12 = D1.at<float>(1, 0); k13 = D1.at<float>(2, 0);
	p11 = D1.at<float>(3, 0); p12 = D1.at<float>(4, 0);
	float fx2, fy2, cx2, cy2, k21, k22, k23, p21, p22;
	fx2 = A2.at<float>(0, 0); fy2 = A2.at<float>(1, 1);
	cx2 = A2.at<float>(0, 2); cy2 = A2.at<float>(1, 2);
	k21 = D2.at<float>(0, 0); k22 = D2.at<float>(1, 0); k23 = D2.at<float>(2, 0);
	p21 = D2.at<float>(3, 0); p22 = D2.at<float>(4, 0);

	float fx = (fx1 + fx2) / 2;
	float fy = (fy1 + fy2) / 2;
	float cx = (cx2 + cx1);
	float cy = (cy1 + cy2);
	int width = 1920 * 2;
	int height = 1080 * 2;

	cv::Mat Tmapx = cv::Mat(height, width, CV_32F);
	cv::Mat Tmapy = cv::Mat(height, width, CV_32F);

	printf("left is calculate.\n");
	// for left image
	for (int y = 0; y < height; ++y)
	{
		cv::Mat pos = cv::Mat::ones(3, 1, CV_32F);
		float* mapx_row = Tmapx.ptr<float>(y);
		float* mapy_row = Tmapy.ptr<float>(y);
		for (int x = 0; x < width; ++x)
		{
			float yy = (y - cy) / fy;
			float xx = (x - cx) / fx;
			pos.at<float>(0, 0) = xx;
			pos.at<float>(1, 0) = yy;
			pos.at<float>(2, 0) = 1;
			pos = R1 * pos;
			xx = pos.at<float>(0, 0) / pos.at<float>(2, 0);
			yy = pos.at<float>(1, 0) / pos.at<float>(2, 0);

			float r2 = xx*xx + yy*yy;
			float _2xy = 2 * xx*yy;
			float xxx = xx*(1 + r2*(k11 + r2*(k12 + r2*k13))) + p11*_2xy + p12*(r2 + 2 * xx*xx);
			float yyy = yy*(1 + r2*(k11 + r2*(k12 + r2*k13))) + p12*_2xy + p11*(r2 + 2 * yy*yy);
			float xxxx = xxx*fx1 + cx1;
			float yyyy = yyy*fy1 + cy1;
			mapx_row[x] = xxxx;
			mapy_row[x] = yyyy;
		}
	}
	printf("left calculation finished.\n");
	cv::Rect left = cv::Rect(880, 590, 1920, 1080); // 880, for regular 3D display; 680 for goovis 3D display
	cv::Mat Tlmapx = Tmapx(left).clone();
	cv::Mat Tlmapy = Tmapy(left).clone();

	printf("right is calculate.\n");
	// for right image
	for (int y = 0; y < height; ++y)
	{
		cv::Mat pos = cv::Mat::ones(3, 1, CV_32F);
		float* mapx_row = Tmapx.ptr<float>(y);
		float* mapy_row = Tmapy.ptr<float>(y);
		for (int x = 0; x < width; ++x)
		{
			float yy = (y - cy) / fy;
			float xx = (x - cx) / fx;
			pos.at<float>(0, 0) = xx;
			pos.at<float>(1, 0) = yy;
			pos.at<float>(2, 0) = 1;
			pos = R2 * pos;
			xx = pos.at<float>(0, 0) / pos.at<float>(2, 0);
			yy = pos.at<float>(1, 0) / pos.at<float>(2, 0);

			float r2 = xx*xx + yy*yy;
			float _2xy = 2 * xx*yy;
			float xxx = xx*(1 + r2*(k21 + r2*(k22 + r2*k23))) + p21*_2xy + p22*(r2 + 2 * xx*xx);
			float yyy = yy*(1 + r2*(k21 + r2*(k22 + r2*k23))) + p22*_2xy + p21*(r2 + 2 * yy*yy);
			float xxxx = xxx*fx2 + cx2;
			float yyyy = yyy*fy2 + cy2;
			mapx_row[x] = xxxx;
			mapy_row[x] = yyyy;
		}
	}
	printf("right calculation finished.\n");

	cv::Rect right = cv::Rect(800, 590, 1920, 1080);
	cv::Mat Trmapx = Tmapx(right).clone();
	cv::Mat Trmapy = Tmapy(right).clone();

	cv::resize(Tlmapx, lmapx, cv::Size(960, 1080));
	cv::resize(Trmapx, rmapx, cv::Size(960, 1080));
	rmapx += 1920;
	cv::resize(Tlmapy, lmapy, cv::Size(960, 1080));
	cv::resize(Trmapy, rmapy, cv::Size(960, 1080));

	cv::convertMaps(mapx, mapy, Smapx, Umapy, CV_16SC2);

	cv::resize(Smapx, TestSmapx, cv::Size(1280, 720));
	cv::resize(Umapy, TestUmapy, cv::Size(1280, 720));
}


void TestCaptureOnethread()
{
	Init1080pCameraParams();
	//cv::VideoCapture capLeft("PC Camera");

	cv::VideoCapture capLeft(1);
	capLeft.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
	capLeft.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
	capLeft.set(CV_CAP_PROP_BUFFERSIZE, 1);
	cv::VideoCapture capRight(0);
	capRight.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
	capRight.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
	capRight.set(CV_CAP_PROP_BUFFERSIZE, 1);
	string winName = "newimage";
	cv::namedWindow(winName, cv::WINDOW_NORMAL);
	cv::moveWindow(winName, 0, 0);
	cv::setWindowProperty(winName, cv::WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	double t1, t2, t3, t4, t5;
	while (1){
		static int count = 0;
		t1 = cv::getTickCount();
		capLeft.read(oriLImg);
		capRight.read(oriRImg);
		t2 = cv::getTickCount();
		if (count % 50 == 0){
			printf("time in capture is %fms.\n", (t2 - t1) * 1000 / cv::getTickFrequency());
		}

		t1 = cv::getTickCount();
		cv::remap(oriImg, mapImg, Smapx, Umapy, CV_INTER_LINEAR);
		t2 = cv::getTickCount();

		//t4 = cv::getTickCount();
		//cv::remap(oriImg, TestMapImg, TestSmapx, TestUmapy, CV_INTER_LINEAR);
		//t5 = cv::getTickCount();

		cv::imshow(winName, mapImg);
		cv::waitKey(20);
		t3 = cv::getTickCount();
		count++;
		if (count % 50 == 0){
			count = 0;
			printf("remap time is %fms. imshow time is %fms\n", (t2 - t1) * 1000 / cv::getTickFrequency(), (t3 - t2) * 1000 / cv::getTickFrequency());
			//printf("remap time is %fms and %fms. imshow time is %fms\n", (t2 - t1) * 1000 / cv::getTickFrequency(), (t5 - t4) * 1000 / cv::getTickFrequency(), (t3 - t2) * 1000 / cv::getTickFrequency());
		}
	}
}

int main(){

	TestCaptureOnethread();


	ImageProcess *imgProcess = NULL;
	CameraCapture *capleft = NULL;
	CameraCapture *capright = NULL;

	imgProcess = new ImageProcess();
	imgProcess->StartProcess();
	capleft = new CameraCapture(0);
	capright = new CameraCapture(1);
	capleft->StartCapture();
	capright->StartCapture();

	while (1){
		Sleep(1000);
	}

	if (capleft){
		delete capleft;
	}
	if (capright){
		delete capright;
	}
	if (imgProcess){
		delete imgProcess;
	}
}



// single thread capture image from camera
//int main(){
//	cv::VideoCapture cap;
//	int deviceID = 0;
//	int apiID = cv::CAP_DSHOW;
//	//int apiID = cv::CAP_FFMPEG;
//	cap.open(apiID + deviceID);
//	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
//	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
//	cap.set(CV_CAP_PROP_BUFFERSIZE, 1);
//	int buf = cap.get(CAP_PROP_BUFFERSIZE);
//	cap.set(CAP_PROP_BUFFERSIZE, 1);
//	buf = cap.get(CAP_PROP_BUFFERSIZE);
//	int fps = cap.get(CV_CAP_PROP_FPS);
//	namedWindow("image", WINDOW_NORMAL);
//	setWindowProperty("image", WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
//	//uchar data[1920 * 1080 * 3];
//	//cv::Mat img = cv::Mat(1080, 1920, CV_8UC3, data);
//	cv::Mat img;
//	double t1, t2 = 0;
//	int count = 0;
//	while (1){
//		//cap >> img;
//		t1 = getTickCount();
//		//printf("Time is %fms.\n", (t1 - t2)*1000/getTickFrequency());
//		cap.grab();
//		cap.retrieve(img);
//		//printf("size: %d %d %d.\n",img.cols,img.rows,img.channels());
//		imshow("image",img);
//		waitKey(1);
//		t2 = getTickCount();
//		tsum += t2 - t1;
//		count++;
//		if ((count % 100) == 0){
//			tsum = tsum / 100 * 1000 / getTickFrequency();
//			float fps = 1000 / tsum;
//			printf("Time is %fms, fps is %f\n", tsum,fps);
//			tsum = 0;
//		}
//	}
//}
