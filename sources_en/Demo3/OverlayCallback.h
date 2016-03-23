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

#ifndef OVERLAY_CALLBACK_H
#define OVERLAY_CALLBACK_H

#include "tisudshl.h"

namespace Demo3
{
	using namespace DShowLib;
	public class COverlayCallback : public GrabberListener  
	{
	public:
		COverlayCallback();
		virtual ~COverlayCallback();
		virtual void overlayCallback( Grabber& param, smart_ptr<OverlayBitmap> pBitmap, const tsMediaSampleDesc& );

	private:
		int	m_displayCallCount;
	};	
}



#endif//OVERLAY_CALLBACK_H
