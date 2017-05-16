#include "stdafx.h"
#include "PeopleDetector.h"
#include <string.h>
#include <ctype.h>
#include "MFCTest1Dlg.h"



PeopleDetector::PeopleDetector()
{
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
}
PeopleDetector::~PeopleDetector()
{
}
void PeopleDetector::onMouseAction(int event, int x, int y, int flags, void * ustc)
{
	PeopleDetector *this_flag = (PeopleDetector *)ustc;
	int base_i;
	if (this_flag->lines[5] == false) base_i = 1;
	else if (this_flag->lines[10] == false) base_i = 6;
	else return;
	if (event == CV_EVENT_MOUSEMOVE)
	{
		cout << "触发鼠标移动事件" << endl;
	}
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		this_flag->initBegin = x;
		this_flag->initEnd = y;
		this_flag->flag = false;
		this_flag->lines[base_i + 0] = x;
		this_flag->lines[base_i + 1] = y;
		this_flag->lines[base_i + 4] = 0;
	}
	if (event == CV_EVENT_LBUTTONUP)
	{
		this_flag->finaBegin = x;
		this_flag->finaEnd = y;
		//line(this_flag->frame_mid, Point(this_flag->initBegin, this_flag->initEnd), Point(this_flag->finaBegin, this_flag->finaEnd), Scalar(0, 0, 255), 2);
		this_flag->flag = true;
		this_flag->lines[base_i + 2] = x;
		this_flag->lines[base_i + 3] = y;
		this_flag->lines[base_i + 4] = 1;
	}

}
void PeopleDetector::process2(VideoCapture &caputure, LPVOID params)
 
{
	    CMFCTest1Dlg* this_back = (CMFCTest1Dlg*)params;
        Mat img; 
		if (!caputure.read(img)) return;
		hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());//得到SVM检测算子----用于对hog特征进行分类的svm模型的系数赋值

	    vector<Rect> found, found_filtered;
		int can = img.channels();  
			hog.detectMultiScale(img, found, 0, Size(8, 8), Size(25, 25), 1.05, 2);
			size_t i, j;
			//找出没有嵌套的矩形框r，如果有嵌套的话，保留大的矩形框
			for (i = 0; i < found.size(); i++)
			{
				Rect r = found[i];
				for (j = 0; j < found.size(); j++)
					if (j != i && (r & found[j]) == r)
						break;
				if (j == found.size())
					found_filtered.push_back(r);
			}

			//画矩形框
			for (i = 0; i < found_filtered.size(); i++)
			{
				Rect r = found_filtered[i];
				// 因为HOG detector返回的是比目标大的矩形框，因此应缩小矩形框
				r.x += cvRound(r.width*0.1);
				r.width = cvRound(r.width*0.8);
				r.y += cvRound(r.height*0.07);
				r.height = cvRound(r.height*0.8);
				rectangle(img, r.tl(), r.br(), cv::Scalar(0, 0, 255), 2);  //img-图片，tl----the top-left corner，br----the top-left corner，Scalar()-矩形框颜色，config6-线宽
				
			}
			resize(img, img, Size(this_back->picture_y, this_back->picture_x));
			if (lines[5] == 1) {
				line(img, Point(lines[1], lines[2]), Point(lines[3], lines[4]), Scalar(12, 2, 200), 2);

			}
			if (lines[10] == 1) {
				line(img, Point(lines[1], lines[2]), Point(lines[3], lines[4]), Scalar(12, 2, 200), 2);
			}
			
			imshow("vehicle", img);
			  
		} 
		




