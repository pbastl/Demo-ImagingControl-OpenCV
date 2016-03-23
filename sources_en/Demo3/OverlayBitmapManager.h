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

#ifndef OVERLAY_BITMAP_MANAGER_H
#define OVERLAY_BITMAP_MANAGER_H

#include "tisudshl.h"
#include "OverlayCallback.h"
namespace Demo3
{
	class COverlayBitmapManager
	{

	public:
		COverlayBitmapManager(DShowLib::Grabber *m_grabber);
		~COverlayBitmapManager();


	protected:
		DShowLib::Grabber	*m_Grabber;
		Demo3::COverlayCallback	overlayCallback;

	public:
		void drawOverlay(DShowLib::tPathPosition pos);
		void getOverlayBitmapsState(bool &device, bool &sink, bool &display, bool &callback);
		void setOverlayBitmapsState(bool  device, bool  sink, bool  display, bool  callback);

	private:
		void setOverlayBitmapColorMode( DShowLib::OverlayBitmap::tOVBColorMode mode );
	};	
}



#endif//OVERLAY_BITMAP_MANAGER_H
