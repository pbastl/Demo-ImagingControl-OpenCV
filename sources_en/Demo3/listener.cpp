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

#include "stdafx.h"
#include "listener.h"


#ifdef OPENCV
using namespace cv;
#endif

namespace Demo3
{
	//------------------------------------------------------------------------
	// Method called after receive new image
	//------------------------------------------------------------------------
	void CListener::frameReady( Grabber& param, smart_ptr<MemBuffer> pBuffer, DWORD FrameNumber)
	{

		pBuffer->lock();				// Prevent memory overwriting

		DoImageProcessing( pBuffer );	// Work with the image
	
		pBuffer->unlock();				// Release memory for new image

		SetEvent(hRefreshingFire);

	}

	void CListener::setRefreshEvent(HANDLE refresh)
	{
		hRefreshingFire = refresh;
	}


	//------------------------------------------------------------------------
	// Function for simly operation ander data - invertion
	// NOT USED
	//------------------------------------------------------------------------
	void DoImageProcessingInvertion( smart_ptr<MemBuffer> pBuffer)
	{
		// Get the bitmap header of image in the buffer. The header contains number of bits per pixel, hight and width of the image
		smart_ptr<BITMAPINFOHEADER> pInf = pBuffer->getBitmapInfoHeader();
    
		// get pointer to image data
		BYTE* pImageData = pBuffer->getPtr();
    
		// calsulation of size of image in bytes
		int iImageSize = pInf->biWidth * pInf->biHeight * pInf->biBitCount / 8 ;
		// invertion of image
		for( int i = 0; i < iImageSize; i++)
		{
			pImageData[i] = 255 - pImageData[i];
		}
	}
	
	//------------------------------------------------------------------------
	// Function for simple image processing - Canny filter over OpenCV
	// NOT USED
	//------------------------------------------------------------------------
	void DoImageProcessingCanny( smart_ptr<MemBuffer> pBuffer, double cannyThr1, double cannyThr2, cv::Mat &outputImage1)
	{
		
		int ysize = pBuffer->getFrameType().dim.cx;				// get size of image
		int xsize = pBuffer->getFrameType().dim.cy;				//
		BYTE* pImageData = pBuffer->getPtr();					// get pointer to the image data

		Mat matImageData(xsize, ysize, CV_8UC3, pImageData );	// Create opencv matrix (image) with data points to the buffer
																// The format of data must be set acording the format for ringBuffer in the FrameHandlerSink
		Mat imGray(xsize, ysize, CV_8UC1);						// temporary matrix for grayscale data
		Mat imEdges(xsize, ysize, CV_8UC1);						// temporary matrix for edge image
		
		cvtColor(matImageData, imGray, CV_RGB2GRAY);	// convertion to the grayscale
		Canny(imGray, imEdges, cannyThr1, cannyThr2);	// canny filter
		

		// Demonstration how to work with the image data - convertion to the 4-channel output image (RGBA)
		Mat alpha( imEdges.rows, imEdges.cols, CV_8UC1, cv::Scalar(255) );	// create the data for alpha channel - initialization to nontransparent (255)
		Mat inp[] = { imEdges, alpha };										// input for method mixChannels([GrayValue, Alpha])
		int from_to[] = { 0,0,  0,1,  0,2,  1,3 };				// Definition of key for channel mixing
																// imEdges[0] -> outputImage1[0], imEdges[0] -> outputImage1[1],
																// imEdges[0] -> outputImage1[2], alpha[0] -> outputImage1[3]
		mixChannels( inp, 2, &outputImage1, 1, from_to, 4 );	// Do convertion
																// - input array of matrix : inp
																// - count of matrixes in the input : 2
																// - output array of matrix : &outputImage1
																// - count of matrixes in the output : 1
																// - key : from_to
																// - count of channels : 4
																
																
	}


	//------------------------------------------------------------------------
	// Function for simple face detection using opencv functions
	//------------------------------------------------------------------------
	void CListener::DoImageProcessingFace( smart_ptr<MemBuffer> pBuffer, cv::Mat &outputImage1)
	{

		int ysize = pBuffer->getFrameType().dim.cx;				// get size of image
		int xsize = pBuffer->getFrameType().dim.cy;				//
		BYTE* pImageData = pBuffer->getPtr();					// get pointer to the image data

		Mat matImageData(xsize, ysize, CV_8UC3, pImageData );	// Create opencv matrix (image) with data points to the buffer
																// The format of data must be set acording the format for ringBuffer in the FrameHandlerSink

		
		Mat workImage;									// pomocná matice s kopií dat z bufferu - aby nebyl buffer modifikován
		matImageData.copyTo(workImage);					// provedení kopie bufferu

		FaceDetector.detect(workImage);

		// Demonstration how to work with the image data - convertion to the 4-channel output image (RGBA)
		Mat alpha( workImage.rows, workImage.cols, CV_8UC1, cv::Scalar(255) );	// create the data for alpha channel - initialization to nontransparent (255)
		Mat inp[] = { workImage, alpha };										// input for method mixChannels([GrayValue, Alpha])
		int from_to[] = { 0,0,  1,1,  2,2,  3,3 };				// Definition of key for channel mixing
																// imEdges[0] -> outputImage1[0], imEdges[0] -> outputImage1[1],
																// imEdges[0] -> outputImage1[2], alpha[0] -> outputImage1[3]
		mixChannels( inp, 2, &outputImage1, 1, from_to, 4 );	// Do convertion 
		// - input array of matrix : inp
		// - count of matrixes in the input : 2
		// - output array of matrix : &outputImage1
		// - count of matrixes in the output : 1
		// - key : from_to
		// - count of channels : 4


	}

	void CListener::DoImageProcessing( smart_ptr<MemBuffer> pBuffer)
	{
		//DoImageProcessingInvertion(pBuffer);
		//DoImageProcessingCanny(pBuffer, cannyThr1, cannyThr2, outputImage1);
		DoImageProcessingFace(pBuffer, outputImage1);
	}
	cv::Mat* CListener::getOutputImage1(void)
	{
		return &outputImage1;							
	}
	
	void CListener::setCannyParams(double thr1, double thr2)
	{
		cannyThr1 = thr1;
		cannyThr2 = thr2;
	}
	
}