#pragma once
class VehicleDetector
{
public:
	VehicleDetector();
	Mat pictureBackground;
	~VehicleDetector();
	void process(VideoCapture &capture,LPVOID params);
};

