#include "stdafx.h"
// MyTools.cpp : 实现文件
//

#include "MyTools.h"


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
	//imwrite("first.jpg", mid);
	//capture.set(CV_CAP_PROP_POS_FRAMES, order);
	mid.create(Size(capture.get(CV_CAP_PROP_FRAME_WIDTH), capture.get(CV_CAP_PROP_FRAME_HEIGHT)), CV_8UC3);
	for (int i = 0; i < 25; i++) {
		if (!capture.read(mmid)) break;
		cvtColor(mmid, mmid, COLOR_BGR2GRAY);
		//medianBlur(mmid, mmid, 3);
		addWeighted(mid, 1, mmid, 0.04, 0, mid);
	}
	//mmid = mmid / 30;
	capture.set(CV_CAP_PROP_POS_FRAMES, order);
	return mid;
}
