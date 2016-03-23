//////////////////////////////////////////////////////////////////////////
// Demo example how to work with SDK IC Imaging Control 3.4
// under Visual C++ .NET
// Author: Petr Bastl, DFC Design, 2016
//
// FaceDetection.cpp: implementation of the face detection inspirated by:
// http://stackoverflow.com/questions/13155298/face-detection-sample-with-opencv-2-4-2-visual-studio-2012-windows-7-64-bit
// 
//////////////////////////////////////////////////////////////////////////
// Copyright 2016 DFC Design, s.r.o.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//////////////////////////////////////////////////////////////////////////

#ifndef FACE_DETECTION_H
#define FACE_DETECTION_H

#include "stdafx.h"

#undef min
#undef max
#include "opencv2/objdetect/objdetect.hpp"

namespace Demo3
{
	class CFaceDetection
	{
	public:
		// Constructor
		CFaceDetection(void);

		// Destructor
		~CFaceDetection(void);

		// Declaration of globals variables
	private:
		cv::CascadeClassifier *face_cascade;
		//cv::CascadeClassifier *eyes_cascade;

		// Declaration of function
	private:
		int Init();
	public:
		cv::Mat detect( cv::Mat frame );
	
	};
}


#endif // FACE_DETECTION_H