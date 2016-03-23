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

#include "stdafx.h"
#include "FaceDetection.h"

using namespace cv;
namespace Demo3
{

	CFaceDetection::CFaceDetection()
	{
		int retval;
		face_cascade = new CascadeClassifier();
		//eyes_cascade = new CascadeClassifier();
		retval = Init();
	}

	CFaceDetection::~CFaceDetection()
	{
		delete face_cascade;
		//delete eyes_cascade;
	}

	int CFaceDetection::Init()
	{
		String face_cascade_name = "lbpcascade_frontalface.xml";
		String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";

		//-- 1. Load the cascade
		if( !face_cascade->load( face_cascade_name ) ){ /*printf("--(!)Error loading\n");*/ return -1; };
		//if( !eyes_cascade->load( eyes_cascade_name ) ){ /*printf("--(!)Error loading\n");*/ return -1; };

	
		return 0;
	}


	/**
	 * @function detect
	 */
	Mat CFaceDetection::detect( Mat frame )
	{
		std::vector<Rect> faces;
		Mat frame_gray;

		cvtColor( frame, frame_gray, CV_BGR2GRAY );
		equalizeHist( frame_gray, frame_gray );

		//-- Detect faces
		face_cascade->detectMultiScale( frame_gray, faces, 1.1, 2, 0, Size(80, 80) );

		for( unsigned int i = 0; i < faces.size(); i++ )
			{
				Mat faceROI = frame_gray( faces[i] );
				std::vector<Rect> eyes;

				int halfOfWidth = (int)(faces[i].width*0.5 + 0.5);
				int halfOfHeight = (int)(faces[i].height*0.5 + 0.5);

				//-- Draw the face
				Point center( faces[i].x + halfOfWidth, faces[i].y + halfOfHeight );
				ellipse( frame, center, Size( halfOfWidth, halfOfHeight), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );

				continue;

				////-- In each face, detect eyes
				//eyes_cascade->detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
				//if( eyes.size() == 2)
				//{
				//	//-- Draw the face
				//	Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
				//	ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );
				//
				//	for( int j = 0; j < eyes.size(); j++ )
				//	{ //-- Draw the eyes
				//		Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 ); 
				//		int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
				//		circle( frame, center, radius, Scalar( 255, 0, 255 ), 3, 8, 0 );
				//	}
				//}

			} 
		return frame;
	}

} // Namespace Demo3