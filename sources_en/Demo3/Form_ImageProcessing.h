//////////////////////////////////////////////////////////////////////////
// Demo example how to work with SDK IC Imaging Control 3.4
// under Visual C++ .NET
// Author: Petr Bastl, DFC Design, 2016
//
// Window used to show result of image processing
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

#include "listener.h"

#pragma once

namespace Demo3 {

	using namespace System;
	using namespace System::Threading;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	/// <summary>
	/// Summary for Form_ImageProcessing
	/// </summary>
	public ref class Form_ImageProcessing : public System::Windows::Forms::Form
	{
	private: DShowLib::Grabber *m_cGrabber;
		
	private: delegate void PictureBoxRefreshing(System::Object ^obj); // delegate of function for refreshing of picturebox
			 EventWaitHandle^ RefreshingFire;						  // sync. object for control the thread
			 volatile bool stopThreadRefreshing;					  // flag for end of thread
		
	public:
		Form_ImageProcessing(DShowLib::Grabber *o1, CListener *o2)
		{
			bool retval;

			m_cGrabber = o1;

			InitializeComponent();
			
			pListener = o2;

			// Bound image data from image processing with the bitmap in the picturebox
			cv::Mat* pMat = pListener->getOutputImage1(); // Get outputImage from the image processing
			System::Drawing::Bitmap^ imtmp = gcnew    // replacement of cvShowImage
								System::Drawing::Bitmap(pMat->size().width,pMat->size().height,pMat->step,
														System::Drawing::Imaging::PixelFormat::Format32bppArgb,
														(System::IntPtr) pMat->data);
			pictureBox1->Image = imtmp;

			retval = m_cGrabber->addListener(pListener, GrabberListener::eFRAMEREADY);
			startRefreshingThread();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form_ImageProcessing()
		{
			if (components)
			{
				delete components;

				delete pListener;
			}
			
			stopThreadRefreshing = true;
			RefreshingFire->Set();
		}


	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		CListener *pListener;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(615, 470);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// Form_ImageProcessing
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(615, 470);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Form_ImageProcessing";
			this->Text = L"Form_ImageProcessing";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	
	//-----------------------------------------------------------------------
	// Start new thread, which refresh the picture box after new image is processed
	//-----------------------------------------------------------------------
	private: void Form_ImageProcessing::startRefreshingThread(void)
		{
			stopThreadRefreshing = false;
			RefreshingFire  = gcnew EventWaitHandle( false,EventResetMode::AutoReset ); // create sync. object
			pListener->setRefreshEvent((void*)RefreshingFire->Handle);					// pass the sync. object to the listener
			// Create thread
			Thread^ oThread = gcnew Thread( gcnew ParameterizedThreadStart( this, &Form_ImageProcessing::threadRefreshingFunction ) );
			// spuštìní vlákna
			oThread->Start(this);
		}
	
	//-----------------------------------------------------------------------
	//	Body of thread - waiting for the sync. object and refresh the picturebox
	//-----------------------------------------------------------------------
	private: void Form_ImageProcessing::threadRefreshingFunction(System::Object ^obj) 
	{
		while(!stopThreadRefreshing)
		{	
			RefreshingFire->WaitOne(10000);
			safeRefreshingFunction(obj);
		}
	}

	//-----------------------------------------------------------------------
	//	Function for refresh the picturebox (thread safe)
	//-----------------------------------------------------------------------
	private: void Form_ImageProcessing::safeRefreshingFunction(System::Object ^obj)
		{
			Form_ImageProcessing ^pForm = (Form_ImageProcessing^) obj;

			if(pForm->InvokeRequired)
			{
				PictureBoxRefreshing ^d = gcnew PictureBoxRefreshing(this, &Form_ImageProcessing::safeRefreshingFunction);
				try
				{
					pForm->Invoke(d, gcnew array<System::Object^>{pForm});
				}
				catch( ObjectDisposedException^ e )
				{
					Diagnostics::Debug::WriteLine("Caught: " + e->Message);
				}
				catch( Exception^ e )
				{
					Diagnostics::Debug::WriteLine("Caught: " + e->Message);
				}
			}
			else
			{
				pForm->pictureBox1->Refresh();
			}
		}
	};
}
