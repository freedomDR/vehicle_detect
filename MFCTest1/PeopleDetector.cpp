#include "stdafx.h"
#include "PeopleDetector.h"
#include <string.h>
#include <ctype.h>
#include "MFCTest1Dlg.h"



PeopleDetector::PeopleDetector()
{
	found_filtered_flag = true;
}


PeopleDetector::~PeopleDetector()
{
}

void PeopleDetector::process2(VideoCapture &caputure, LPVOID params)
 
{
	    CMFCTest1Dlg* this_back = (CMFCTest1Dlg*)params;
        Mat img;  //存储图像数据
		//FILE* f = 0;


		if (!caputure.read(img)) return;
		Mat img_copy;
		img.copyTo(img_copy);
		
		cvtColor(img_copy, img_copy, CV_BGR2GRAY);

		/*Size win_stride=Size(), Size padding=Size(), double scale0=1.05, int group_threshold=2)
        功能：对输入的图片img进行多尺度的行人检测.
		参数说明：
		img：待输入检测的图片
		found_locations：检测到的目标区域列表
		hit_threshold：程序内部为计算行人目标的阈值，也就是检测到的特征到SVM分类超平面的距离
        win_stride：滑动窗口每次移动的距离（必须是块移动的整数倍） padding：图像扩充的大小
		scale0：比例系数，即滑动窗口每次增加的比例
		group_threshold：校正系数，当一个目标被多个窗口检测出来时，起调节作用.设置为0是不调节*/

		
		this->img = img_copy;
		if (this_back->frame_order % 10 == 0)
		{
			//found_filtered_flag = false;
			//found.clear();
			//found_filtered.clear();
			AfxBeginThread(DealPeople, this, 0, 0, 0, 0);
			
		}

		
		

		//画矩形框
		if (found_filtered_flag == true)
		{
			int i;
			BOOL flag_mid = flag;
			for (i = 0; i < found_filtered.size(); i++)
			{
				Rect r = found_filtered[i];
				// 因为HOG detector返回的事比目标大的矩形框，因此应缩小矩形框
				r.x += cvRound(r.width*0.1);
				r.width = cvRound(r.width*0.8);
				r.y += cvRound(r.height*0.07);
				r.height = cvRound(r.height*0.8);
				rectangle(img, r.tl(), r.br(), cv::Scalar(0, 255, 0), 2);  //img-图片，tl----the top-left corner，br----the top-left corner，Scalar()-矩形框颜色，config6-线宽
				if (r.y+r.height >= initBegin && flag_mid == true && this_back->frame_order%30 == 0)
				{
					//flag_mid = false;
					//AfxBeginThread(NotifyPeople, this, 0, 0, 0, 0);
					//MessageBeep(MB_OK);
					//Beep(5000, 500);
					MessageBeep(MB_NOFOCUS);
					//Sleep(1000);
					
				}
			}
		}
		resize(img, img, Size(this_back->picture_y, this_back->picture_x));
	    if(this_back->peopleDetector.flag==true)
		line(img,Point(this_back->peopleDetector.initBegin, this_back->peopleDetector.initEnd),Point(this_back->peopleDetector.finaBegin, this_back->peopleDetector.finaEnd),Scalar(0,0,255),2);
		//line(img, Point(280, 180), Point(280, 200), Scalar(99, 100, 33),2);
		imshow("vehicle", img);
			  
}

void PeopleDetector::onMouseAction(int event, int x, int y, int flags, void * ustc)
{
	    PeopleDetector *this_flag = (PeopleDetector *)ustc;
		int base_i;
		if (event == CV_EVENT_MOUSEMOVE)
		{
			cout << "触发鼠标移动事件" << endl;
		}
		if (event == CV_EVENT_LBUTTONDOWN)
		{
			this_flag->initBegin = x;
			this_flag->initEnd = y;
			this_flag->flag = false;
		}
		if (event == CV_EVENT_LBUTTONUP)
		{
			this_flag->finaBegin = x;
			this_flag->finaEnd = y;
			this_flag->flag = true;
			
		}
	}

UINT PeopleDetector::DealPeople(LPVOID pParam)
{
	PeopleDetector* p = (PeopleDetector*)pParam;
	HOGDescriptor hog;  //HOG特征描述子
	vector<Rect> found, found_filtered;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());  //得到SVM检测算子----用于对hog特征进行分类的svm模型的系数赋值
	hog.detectMultiScale(p->img, found, 0, Size(8, 8), Size(0, 0), 1.35, 2);
	
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
	p->found_filtered = found_filtered;
	p->found_filtered_flag = true;
	return 0;
}

UINT PeopleDetector::NotifyPeople(LPVOID pParam)
{
	PeopleDetector* this_back = (PeopleDetector*)pParam;
	int i = 0;
	
	MessageBeep(MB_OK);
	//Sleep(250);
	
	//this_back->flag = true;
	return 0;
}




