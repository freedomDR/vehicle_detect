#pragma once
class PeopleDetector
{
public:
	PeopleDetector();
	~PeopleDetector();
	void process2(VideoCapture &caputure, LPVOID params);
	//static void process(VideoCapture caputure, LPVOID params);
};

