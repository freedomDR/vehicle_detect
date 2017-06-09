#pragma once
class PeopleDetector
{
public:
	 PeopleDetector();
	 ~PeopleDetector();
	 void process2(VideoCapture &caputure, LPVOID params);
	 static void onMouseAction(int event, int x, int y,int flags, void *ustc);
	 int initBegin, initEnd;
	 int finaBegin, finaEnd;
     bool flag;
	 int lines[11];
	 HOGDescriptor hog;  //HOGÌØÕ÷ÃèÊö×Ó
	 static UINT DealPeople(LPVOID pParam);
	 vector<Rect> found_filtered;
	 Mat img;
	 BOOL found_filtered_flag;
	 
};
typedef struct P
{
	Mat image;
	vector<Rect>& found, found_filtered;
}*Params;

