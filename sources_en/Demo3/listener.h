//////////////////////////////////////////////////////////////////////////
// Demo example how to work with SDK IC Imaging Control 3.4
// under Visual C++ .NET
// Author: Petr Bastl, DFC Design, 2016
//
// Implementation of the class CListener:
// - CListener inherits the class GrabberListener and modifies method "frameReady()"
//   which use to call method of image processing
// - The method frameReady is called after recived new image (is registred with the param eFRAMEREADY)
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

#ifndef LISTENER_H
#define LISTENER_H

#include "stdafx.h"


#include "FaceDetection.h"

#define MESSAGEDEVICELOST WM_USER+90

using namespace DShowLib;

namespace Demo3
{
	class CListener : public GrabberListener  
	{
	public:		
		virtual void frameReady( Grabber& param, smart_ptr<MemBuffer> pBuffer, DWORD FrameNumber); 		
		void setCannyParams(double thr1, double thr2);
		
		void setRefreshEvent(HANDLE refresh);
		cv::Mat* getOutputImage1(void);
	protected:
		void DoImageProcessing( smart_ptr<MemBuffer> pBuffer);
		void DoImageProcessingFace( smart_ptr<MemBuffer> pBuffer, cv::Mat &outputImage1);

	private:
		double cannyThr1, cannyThr2;
		HANDLE hRefreshingFire;
		cv::Mat outputImage1;

		CFaceDetection FaceDetector;
	};

}


#endif // LISTENER_H
