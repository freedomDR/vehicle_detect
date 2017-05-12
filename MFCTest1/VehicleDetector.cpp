#include "stdafx.h"
#include "VehicleDetector.h"
#include "MFCTest1Dlg.h"
#include "MyTools.h"
#include "resource.h"


VehicleDetector::VehicleDetector()
{
}


VehicleDetector::~VehicleDetector()
{
}

void VehicleDetector::process(VideoCapture &capture, LPVOID params)
{
	int frame_order = capture.get(CV_CAP_PROP_POS_FRAMES);
	Mat frame;
	CMFCTest1Dlg* this_back = (CMFCTest1Dlg*)params;
	//Mat pictureBackground;
	if (frame_order % 1000 == 0)
	{
		pictureBackground = MyTools::getPictureBackground(capture, frame_order);
		medianBlur(pictureBackground, pictureBackground, 3);
		Mat mid_three;
		resize(pictureBackground, mid_three, Size(this_back->picture_y, this_back->picture_x));
	}

	if (!capture.read(frame)) return;
	Mat mid, frame_mid;
	frame.copyTo(frame_mid);
	cvtColor(frame, frame, COLOR_BGR2GRAY);
	medianBlur(frame, frame, 3);

	Mat mid_one, mid_two;
	resize(frame, mid_one, Size(this_back->picture_y, this_back->picture_x));
	//imshow("frame_median.jpg", mid_one);
	absdiff(frame, pictureBackground, frame);
	resize(frame, mid_two, Size(this_back->picture_y, this_back->picture_x));
	imshow("差分图", mid_two);

	//重置大小，满足需求
	Mat des = Mat::zeros(this_back->picture_x, this_back->picture_y, CV_8UC3);
	resize(frame, des, des.size());


	Mat dst;
	double thres_value;
	thres_value = threshold(des, dst, 0, 255, CV_THRESH_OTSU);
	//imwrite("D:\\dst.jpg", dst);
	imshow("二值化图", dst);

	Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));
	Mat element_dilate = getStructuringElement(MORPH_RECT, Size(3, 3));
	erode(dst, dst, element);
	imshow("腐蚀图", dst);
	dilate(dst, dst, element_dilate);
	imshow("膨胀图", dst);


	


	//morphologyEx()

	resize(frame_mid, frame_mid, Size(this_back->picture_y, this_back->picture_x));

	vector<vector<Point>> countours, deal_contours;
	vector<Point> approx;
	findContours(dst, countours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (size_t i = 0; i < countours.size(); i++)
	{
		//approxPolyDP(Mat(countours[i]), approx, arcLength(Mat(countours[i]), true)*0.02, true);
		approxPolyDP(Mat(countours[i]), approx, 0.5, true);

		if (approx.size() >= 3 && contourArea(Mat(countours[i])) > 50 && contourArea(Mat(countours[i])) < 2000)
		{
			deal_contours.push_back(countours[i]);
			Rect rect = boundingRect(countours[i]);
			Blob mid;
			mid.rect = rect;
			mid.id = this_back->blobs.size() + 1;
			Moments m;
			m = moments(approx);
			mid.xx = m.m10 / m.m00;
			mid.yy = m.m01 / m.m00;
			this_back->blobs.push_back(mid);
			circle(frame_mid, Point(mid.xx, mid.yy), 5, Scalar(0.234, 243));
			if (mid.yy<=230&& mid.yy>=120 && mid.xx > 97&& mid.xx<103) this_back->count++;
			
		}
	}
	for (size_t i = 0; i < deal_contours.size(); i++)
	{
		//const Point* p = &deal_contours[i][0];
		Rect rect = boundingRect(deal_contours[i]);
		rectangle(frame_mid, rect, Scalar(0, 255, 255), 1, 8);
	}
	
	line(frame_mid, Point(100, 120), Point(100, 230), Scalar(0, 0, 255), 2);
	CString mid_value;
	mid_value.Format(L"%d", this_back->count);
	this_back->show_text.SetWindowTextW(mid_value);
	imshow("view", frame_mid);
}
