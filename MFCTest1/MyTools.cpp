#include "stdafx.h"
// MyTools.cpp : 实现文件
//

#include "MyTools.h"
#include "VehicleDetector.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

MyTools::MyTools()
{

}

Mat MyTools::getPictureBackground(VideoCapture& capture, int order)
{
	Mat mid,mmid,middle;
	//if (!capture.read(mid)) return mid;
	//cvtColor(mid, mid, COLOR_BGR2GRAY);
	//absdiff(mid, mid, mid);
	
	//capture.set(CV_CAP_PROP_POS_FRAMES, order);
	int value = capture.get(CV_CAP_PROP_FORMAT);
	//mid.create(Size(capture.get(CV_CAP_PROP_FRAME_WIDTH), capture.get(CV_CAP_PROP_FRAME_HEIGHT)), value);
	mid = Mat::zeros(Size(capture.get(CV_CAP_PROP_FRAME_WIDTH), capture.get(CV_CAP_PROP_FRAME_HEIGHT)), value);
	imwrite("first.jpg", mid);
	for (int i = 0; i < 50; i++) {
		if (!capture.read(mmid)) break;
		cvtColor(mmid, mmid, COLOR_BGR2GRAY);
		//medianBlur(mmid, mmid, 3);
		addWeighted(mid, 1, mmid,(float)1/(float)50, 0, mid);
	}
	//mmid = mmid / 30;
	capture.set(CV_CAP_PROP_POS_FRAMES, order);
	return mid;
}
