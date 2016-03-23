//////////////////////////////////////////////////////////////////////////
// Demo example how to work with SDK IC Imaging Control 3.4
// under Visual C++ .NET
// Author: Petr Bastl, DFC Design, 2016
//
// Form to control enable/disable state of overlays
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

#include "StdAfx.h"
#include "OverlayDialog.h"

namespace Demo3
{
	void OverlayDialog::UpdateData(bool ToDialog)
	{
		bool device = false, sink = false, display = false, callback = false;
		if(ToDialog)
		{
			bitmapManager->getOverlayBitmapsState(device, sink, display, callback);

			cbDeviceOverlay->Checked = device;
			cbSinkOverlay->Checked = sink;
			cbDisplayOverlay->Checked = display;
			cbCallbackOverlay->Checked = callback;
		}
		else
		{
			device	 = cbDeviceOverlay->Checked  ;
			sink	 = cbSinkOverlay->Checked    ;
			display  = cbDisplayOverlay->Checked ;
			callback = cbCallbackOverlay->Checked;

			bitmapManager->setOverlayBitmapsState(device, sink, display, callback);
		}
	}
}