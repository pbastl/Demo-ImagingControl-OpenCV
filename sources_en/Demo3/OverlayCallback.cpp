//////////////////////////////////////////////////////////////////////////
// Demo example how to work with SDK IC Imaging Control 3.4
// under Visual C++ .NET
// Author: Petr Bastl, DFC Design, 2016
//
// Implementation of the class COverlayCallback:
// - COverlayCallback inherits the class GrabberListener and modifies method "overlayCallback()"
// - The overlayCallback method is called for every image in the imagestream (registeres with the parameter eOVERLAYCALLBACK)
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
#include "OverlayCallback.h"
#include <string.h>
#include <sstream>
namespace Demo3
{
	
	COverlayCallback::COverlayCallback()
	:	m_displayCallCount( 0 )
	{
	}

	COverlayCallback::~COverlayCallback()
	{

	}

	///////////////////////////////////////////////////////////////////////////////
	/*! The overlayCallback method is called, after the video capture device has
		delivered a new frame. In this method drawing operations can be performed.
	*/
	void COverlayCallback::overlayCallback( Grabber& param, smart_ptr<OverlayBitmap> pBitmap, const tsMediaSampleDesc &MediaSample )
	{
		std::ostringstream stringStream;

		switch( pBitmap->getPathPosition() )
		{
		case ePP_DEVICE:
			stringStream << "Device: Frame " << MediaSample.FrameNumber;
			pBitmap->drawText(RGB(255,255,0), 20, 100, stringStream.str().c_str() );
			break;
		case ePP_SINK:
			stringStream << "Sink: Frame " << MediaSample.FrameNumber;
			pBitmap->drawText(RGB(255,255,0), 20, 120, stringStream.str().c_str() );
			break;
		case ePP_DISPLAY:
			stringStream << "Display: No Frame Number Available, called " << m_displayCallCount++ << " times";
			pBitmap->drawText(RGB(255,255,0), 20, 140, stringStream.str().c_str() );
			break;
		}
	}
}