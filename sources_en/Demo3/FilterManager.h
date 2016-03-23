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

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string.h>

namespace Demo3
{
	class FILTER_MANAGER
	{


		// Declaration of types and constants
	public: enum Rotate {Rotate0, Rotate90, Rotate180, Rotate270};
	
		// Constructor
	public:
		FILTER_MANAGER()
		{
			pRotateFilter = new smart_com<IFrameFilter>();

			
			*pRotateFilter = FilterLoader::createFilter( "Rotate Flip",   // Filter name.
				"stdfilters.ftf" ); // Module file.

			FilterList.push_back(pRotateFilter->get());
		}
		// Destructor
	public:
		~FILTER_MANAGER()
		{
			delete pRotateFilter;
		}

		// Declaration of globals variables
	private:
		tFrameFilterList FilterList;

		char LastErrorMessage[255];
		char LastErrorMessageOut[255];

		smart_com<IFrameFilter> *pRotateFilter;


	
		// Declaration of function
	public: 
		char* FILTER_MANAGER::GetLastError();
		
		tFrameFilterList FILTER_MANAGER::GetFilterList();
		
		bool FILTER_MANAGER::SetRotateFilterParams(bool flipHorizont, bool flipVertical, Rotate rotation);
		
		void FILTER_MANAGER::GetRotateFilterParams(bool &flipHorizont, bool &flipVertical, Rotate &rotation);
		
	};
}


#endif//FILE_MANAGER_H
