#pragma once
class VehicleDetector
{
public:
	VehicleDetector();
	Mat pictureBackground;
	~VehicleDetector();
	void process(VideoCapture &capture,LPVOID params);
	static void onMouseAction(int event,int x,int y,int flags,void*ustc);
	 int initBegin, initEnd;
	 int finaBegin, finaEnd;
    Mat  frame_mid;
	bool flag;
	int lines[11];
};

