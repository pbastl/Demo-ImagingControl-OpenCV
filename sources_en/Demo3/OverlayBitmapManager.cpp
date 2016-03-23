//////////////////////////////////////////////////////////////////////////
// Demo example how to work with SDK IC Imaging Control 3.4
// under Visual C++ .NET
// Author: Petr Bastl, DFC Design, 2016
//
// Implementation of the class COverlayBitmapManager:
// - COverlayBitmapManager controls overlays of the grabber
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
#include "OverlayBitmapManager.h"
#include <string.h>
	
namespace Demo3
{
	COverlayBitmapManager::COverlayBitmapManager(DShowLib::Grabber *m_grabber)
		: m_Grabber(m_grabber)
	{
		setOverlayBitmapColorMode( OverlayBitmap::eBESTFIT );
		
		m_Grabber->setOverlayBitmapPathPosition( ePP_DEVICE );
		drawOverlay( ePP_DEVICE );
	}

	COverlayBitmapManager::~COverlayBitmapManager()
	{
		bool bLive = m_Grabber->isLive();
		m_Grabber->stopLive();
		m_Grabber->removeListener(&overlayCallback, GrabberListener::eOVERLAYCALLBACK);
		if(bLive) m_Grabber->startLive();
	}

	//------------------------------------------------------------------
	// Printed text in the overlays
	void COverlayBitmapManager::drawOverlay(DShowLib::tPathPosition pos)
	{
		smart_ptr<OverlayBitmap> ob = m_Grabber->getOverlay(pos);

		ob->setEnable(true);
		ob->setFont("Courier",14);	
		ob->drawText( RGB(255,0,0),  0, 0, "IC Imaging Control 3.2" );	

		switch( pos )
		{
		case ePP_DEVICE:
			ob->drawText( RGB(0,255,0),  20, 20,  "Device Overlay Active" );
			return;
		case ePP_SINK:
			ob->drawText( RGB(0,255,0),  20, 40,  "Sink Overlay Active" );
			return;
		case ePP_DISPLAY:
			ob->drawText( RGB(0,255,0),  20, 60,  "Display Overlay Active" );
			return;
		}
	}
			 
	//------------------------------------------------------------------
	// Get enable state of overlays
	void COverlayBitmapManager::getOverlayBitmapsState(bool &device, bool &sink, bool &display, bool &callback)
	{
		DWORD pos = m_Grabber->getOverlayBitmapPathPosition();

		device = (pos & ePP_DEVICE)!=0;
		sink = (pos & ePP_SINK)!=0;
		display = (pos & ePP_DISPLAY)!=0;

		callback = m_Grabber->isListenerRegistered(&overlayCallback);
	}

	//------------------------------------------------------------------
	// Set enable state of overlays
	void COverlayBitmapManager::setOverlayBitmapsState(bool  device, bool  sink, bool  display, bool  callback)
	{
		DWORD pos = 0;
		if(device)  pos = pos | ePP_DEVICE ;
		if(sink)    pos = pos | ePP_SINK   ;
		if(display) pos = pos | ePP_DISPLAY;

		bool bLive = m_Grabber->isLive();
		m_Grabber->stopLive();

		m_Grabber->setOverlayBitmapPathPosition(pos);

		
		if(callback) 
			m_Grabber->addListener(&overlayCallback, GrabberListener::eOVERLAYCALLBACK);
		else
			m_Grabber->removeListener(&overlayCallback, GrabberListener::eOVERLAYCALLBACK);

		if( bLive )	m_Grabber->startLive();
	}



	//------------------------------------------------------------------
	// Instrumental method for set ColorMode for all overlays
	void COverlayBitmapManager::setOverlayBitmapColorMode( DShowLib::OverlayBitmap::tOVBColorMode mode )
	{
		bool bLive = m_Grabber->isLive();
		m_Grabber->stopLive();

		m_Grabber->getOverlay(ePP_DEVICE)->setColorMode(mode);
		m_Grabber->getOverlay(ePP_SINK)->setColorMode(mode);
		m_Grabber->getOverlay(ePP_DISPLAY)->setColorMode(mode);

		if( bLive )	m_Grabber->startLive();
	}
	


}