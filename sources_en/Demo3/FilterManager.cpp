//////////////////////////////////////////////////////////////////////////
// Demo example how to work with SDK IC Imaging Control 3.4
// under Visual C++ .NET
// Author: Petr Bastl, DFC Design, 2016
//
// Filter Managment module
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
#include "FilterManager.h"

namespace Demo3
{
	char* FILTER_MANAGER::GetLastError()
	{
		strcpy_s(LastErrorMessageOut, LastErrorMessage);
		return LastErrorMessageOut;
	}

	tFrameFilterList FILTER_MANAGER::GetFilterList()
	{
		return FilterList;
	}

	bool FILTER_MANAGER::SetRotateFilterParams(bool flipHorizont, bool flipVertical, Rotate rotation)
	{
		IFrameFilter* pFilter = pRotateFilter->get();

		long lAngle = 0;
		long lNewAngle = 0;
		bool bFlipVertical = false;
		bool bFlipHorizontal = false;

		tFilterError retval;

		// Retrieve the current parameter settings.
		pFilter->getParameter("Rotation Angle", lAngle);
		pFilter->getParameter("Flip V", bFlipVertical);
		pFilter->getParameter("Flip H", bFlipHorizontal);

		// Change the parameter
		switch(rotation)
		{
		case Rotate0:   lNewAngle = 0; break;
		case Rotate90:  lNewAngle = 90; break;
		case Rotate180: lNewAngle = 180; break;
		case Rotate270: lNewAngle = 270; break;
		}

		retval = pFilter->setParameter("Rotation Angle", lNewAngle);
		if(retval != eNO_ERROR)
		{
			strcpy_s(LastErrorMessage, "An error was returned by setParameter(). If the resulting video format is changed, new value can only be set while the live video is stopped.");
			return false;
		}
		// The flip parameters do not cause a video format change, so they can be 
		// set regardless of whether the live video is running.
		bFlipHorizontal = flipHorizont;
		bFlipVertical = flipVertical;
		pFilter -> setParameter("Flip H", bFlipHorizontal);
		pFilter -> setParameter("Flip V", bFlipVertical);

		return true;
	}


	void FILTER_MANAGER::GetRotateFilterParams(bool &flipHorizont, bool &flipVertical, Rotate &rotation)
	{
		long lAngle = 0;
		IFrameFilter* pFilter = pRotateFilter->get();

		// Retrieve the current parameter settings.
		pFilter->getParameter("Rotation Angle", lAngle);
		pFilter->getParameter("Flip V", flipVertical);
		pFilter->getParameter("Flip H", flipHorizont);

		switch(lAngle)
		{
		case 0  : rotation = Rotate0  ; break;
		case 90 : rotation = Rotate90 ; break;
		case 180: rotation = Rotate180; break;
		case 270: rotation = Rotate270; break;
		default:  rotation = Rotate0  ; break;
		}

	}
}