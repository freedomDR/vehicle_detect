#include "stdafx.h"
#include "PeopleDetector.h"
#include <string.h>
#include <ctype.h>
#include "MFCTest1Dlg.h"



PeopleDetector::PeopleDetector()
{
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
		HOGDescriptor hog;  //HOG特征描述子
		hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());  //得到SVM检测算子----用于对hog特征进行分类的svm模型的系数赋值

/*char _filename[1024]; //图像文件名
	   for (;;)
		{
			char* filename = _filename;
			if (f)
			{
				if (!fgets(filename, (int)sizeof(_filename) - 2, f))  //从文件指针中读取n-1个字符，存到以s为起始地址的空间里，直到读完一行，如果成功则返回s的指针，否则返回NULL。
					break;
				//while(*filename && isspace(*filename))
				//	++filename;
				if (filename[0] == '#') //如果第一个字符是“#”，则表示注释
					continue;
				int l = strlen(filename);
				while (l > 0 && isspace(filename[l - 1]))
					--l;
				filename[l] = '\0';
				img = imread(filename);
			}
			printf("%s:\n", filename);
			if (!img.data)
				continue;

			fflush(stdout);  //清楚缓冲区
			*/



			vector<Rect> found, found_filtered;
			double t = (double)getTickCount();  //从操作系统启动到现在所经过的毫秒数
			int can = img.channels();  //获取通道数

		   /*函数：HOGDescriptor::detectMultiScale(const GpuMat& img, vector<Rect>& found_locations, double hit_threshold=0,
		    Size win_stride=Size(), Size padding=Size(), double scale0=1.05, int group_threshold=2)
            功能：对输入的图片img进行多尺度的行人检测.
			参数说明：
			img：待输入检测的图片
			found_locations：检测到的目标区域列表
			hit_threshold：程序内部为计算行人目标的阈值，也就是检测到的特征到SVM分类超平面的距离
            win_stride：滑动窗口每次移动的距离（必须是块移动的整数倍） padding：图像扩充的大小
			scale0：比例系数，即滑动窗口每次增加的比例
			group_threshold：校正系数，当一个目标被多个窗口检测出来时，起调节作用.设置为0是不调节*/

			hog.detectMultiScale(img, found, 0, Size(8, 8), Size(32, 32), 1.05, 2);

			t = (double)getTickCount() - t;  //检测所耗费的时间
			printf("tdetection time = %gms\n", t*1000. / cv::getTickFrequency()); //在程序段的开始和结束时两次使用cvGetTickCount()，然后将两次的差除以
																				  //cvGetTickFrequency()后就可以获得程序段的以微秒us为单位的运行时间
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
				// 因为HOG detector返回的事比目标大的矩形框，因此应缩小矩形框
				r.x += cvRound(r.width*0.1);
				r.width = cvRound(r.width*0.8);
				r.y += cvRound(r.height*0.07);
				r.height = cvRound(r.height*0.8);
				rectangle(img, r.tl(), r.br(), cv::Scalar(0, 255, 0), 2);  //img-图片，tl----the top-left corner，br----the top-left corner，Scalar()-矩形框颜色，config6-线宽
				
			}
			resize(img, img, Size(this_back->picture_y, this_back->picture_x));
			line(img,Point(150,180),Point(150,200),Scalar(99,100,33),2);
			line(img, Point(280, 180), Point(280, 200), Scalar(99, 100, 33),2);
			imshow("vehicle", img);
			int c = waitKey(1);  
		} 
		




