
#include "stdafx.h"

#pragma once
class MyTools
{
public:
	MyTools();
	~MyTools();
public:
	static Mat getPictureBackground(VideoCapture& capture, int order);
	
};

