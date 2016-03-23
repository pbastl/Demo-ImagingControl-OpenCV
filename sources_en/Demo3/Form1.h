//////////////////////////////////////////////////////////////////////////
// Demo example how to work with SDK IC Imaging Control 3.4
// under Visual C++ .NET
// Author: Petr Bastl, DFC Design, 2016
//
// In the example is showed:
// - Open camera device and setup properties of the device.
// - Live preview of camera.
// - Adding filters for rotation of image.
// - Grabbing frame, import image to PictureBox
// - Image processing under grabbed image (by OpenCV)
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

#include "FilterDialog.h"
#include "FilterManager.h"

#include "OverlayDialog.h"
#include "Form_ImageProcessing.h"
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
	/// Summary for Form1
	///
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::Button^  btnSnapAndDraw;		
	private: System::Windows::Forms::PictureBox^  pbLiveVideo;		// in this PictureBox is shown thw live preview
	private: System::Windows::Forms::Panel^  panel1;

	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  toolButtonDevice;	// Button for open dialog with the list of available devices

	private: System::Windows::Forms::ToolStripSplitButton^  toolStripSplitButtonFilters;
	private: System::Windows::Forms::ToolStripMenuItem^  deviceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  displayToolStripMenuItem;

	private: System::Windows::Forms::ToolStripButton^  toolStripButtonCameraLive;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonOberlays;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonImageProc;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonSnapMode;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonProperties;

	private: System::Windows::Forms::PictureBox^  pbSnappedImage;	// In this PicterBox is shown the snapped Image .

	public:
		Form1(void)
		{
			InitializeComponent();
			
			
			// Initialization of the SDK IC Imaging Control
			if( !DShowLib::InitLibrary() )
			{
				exit( 1 );
			}

			// Because the instances of clasess defined in IC ImagingControl is not possible to use in managed code od Windows Form application,
			// we will control the creating and destruction of this object ourself.
			
			// Create instances of classes from SDK
			m_cGrabber = new DShowLib::Grabber();					
			m_pSink = new DShowLib::FrameHandlerSink::tFHSPtr();	
			pListener = new CListener();							
			
			pFilterManagerDevice = new FILTER_MANAGER();
			pFilterManagerDisplay = new FILTER_MANAGER();
			pFilterManagerDevice->SetRotateFilterParams(false, true, FILTER_MANAGER::Rotate0);
			pFilterManagerDisplay->SetRotateFilterParams(false, true, FILTER_MANAGER::Rotate0);
			
			
			// Create a Sink
			*m_pSink = FrameHandlerSink::create( DShowLib::eRGB24, 1 ); // Set format and size of the bufferu - format  
																		// corresponding with the format of bitmap in the PictureBox
			(*m_pSink)->setSnapMode( true );						// The frames are grabbed after the command snapImages.
			m_cGrabber->setSinkType( *m_pSink );					// Register the Sink in the grabber.
			
			m_cGrabber->setDefaultWindowPosition(false);			// Must be set to allow set the size of LivePreview manualy (over OnResize event of PictureBox).
			
			// Register the Listener - event handler of new received frame
			m_cGrabber->addListener(pListener, GrabberListener::eFRAMEREADY);

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				// Relese resources
				delete components;
				delete m_cGrabber;
				delete pFilterManagerDevice;
				delete pFilterManagerDisplay;
				delete m_pSink;
				delete pListener;
			}
			// At the end of the program, the IC Imaging Control Class Library must be cleaned up
			// by a call to ExitLibrary().
			DShowLib::ExitLibrary();
		}
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		// Pinters at objects of IC Imaging Control library
		DShowLib::Grabber *m_cGrabber;					//
		tFrameFilterList *filterList;					// Set filter parameters.
		DShowLib::FrameHandlerSink::tFHSPtr *m_pSink;	//

		// Pointers at FilterManagers objects
		FILTER_MANAGER *pFilterManagerDevice;
		FILTER_MANAGER *pFilterManagerDisplay;

		CListener *pListener;							//

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->btnSnapAndDraw = (gcnew System::Windows::Forms::Button());
			this->pbLiveVideo = (gcnew System::Windows::Forms::PictureBox());
			this->pbSnappedImage = (gcnew System::Windows::Forms::PictureBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolButtonDevice = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonProperties = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonCameraLive = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonSnapMode = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSplitButtonFilters = (gcnew System::Windows::Forms::ToolStripSplitButton());
			this->deviceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->displayToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripButtonOberlays = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonImageProc = (gcnew System::Windows::Forms::ToolStripButton());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbLiveVideo))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbSnappedImage))->BeginInit();
			this->panel1->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnSnapAndDraw
			// 
			this->btnSnapAndDraw->Location = System::Drawing::Point(7, 208);
			this->btnSnapAndDraw->Name = L"btnSnapAndDraw";
			this->btnSnapAndDraw->Size = System::Drawing::Size(90, 33);
			this->btnSnapAndDraw->TabIndex = 6;
			this->btnSnapAndDraw->Text = L"Snap and Draw";
			this->btnSnapAndDraw->UseVisualStyleBackColor = true;
			this->btnSnapAndDraw->Click += gcnew System::EventHandler(this, &Form1::btnSnapAndDraw_Click);
			// 
			// pbLiveVideo
			// 
			this->pbLiveVideo->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->pbLiveVideo->Location = System::Drawing::Point(295, 5);
			this->pbLiveVideo->Name = L"pbLiveVideo";
			this->pbLiveVideo->Size = System::Drawing::Size(625, 473);
			this->pbLiveVideo->TabIndex = 4;
			this->pbLiveVideo->TabStop = false;
			this->pbLiveVideo->Resize += gcnew System::EventHandler(this, &Form1::pbLiveVideo_Resize);
			// 
			// pbSnappedImage
			// 
			this->pbSnappedImage->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->pbSnappedImage->Location = System::Drawing::Point(7, 247);
			this->pbSnappedImage->Name = L"pbSnappedImage";
			this->pbSnappedImage->Size = System::Drawing::Size(282, 230);
			this->pbSnappedImage->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pbSnappedImage->TabIndex = 8;
			this->pbSnappedImage->TabStop = false;
			// 
			// panel1
			// 
			this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel1->Controls->Add(this->pbSnappedImage);
			this->panel1->Controls->Add(this->pbLiveVideo);
			this->panel1->Controls->Add(this->btnSnapAndDraw);
			this->panel1->Location = System::Drawing::Point(-1, 38);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(929, 486);
			this->panel1->TabIndex = 10;
			// 
			// toolStrip1
			// 
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->toolButtonDevice, 
				this->toolStripButtonProperties, this->toolStripButtonCameraLive, this->toolStripButtonSnapMode, this->toolStripSplitButtonFilters, 
				this->toolStripButtonOberlays, this->toolStripButtonImageProc});
			this->toolStrip1->Location = System::Drawing::Point(0, 0);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(929, 25);
			this->toolStrip1->TabIndex = 11;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolButtonDevice
			// 
			this->toolButtonDevice->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolButtonDevice->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolButtonDevice.Image")));
			this->toolButtonDevice->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolButtonDevice->Name = L"toolButtonDevice";
			this->toolButtonDevice->Size = System::Drawing::Size(43, 22);
			this->toolButtonDevice->Text = L"Device";
			this->toolButtonDevice->Click += gcnew System::EventHandler(this, &Form1::toolButtonDevice_Click);
			// 
			// toolStripButtonProperties
			// 
			this->toolStripButtonProperties->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButtonProperties->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonProperties.Image")));
			this->toolStripButtonProperties->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonProperties->Name = L"toolStripButtonProperties";
			this->toolStripButtonProperties->Size = System::Drawing::Size(60, 22);
			this->toolStripButtonProperties->Text = L"Properties";
			this->toolStripButtonProperties->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonProperties_Click);
			// 
			// toolStripButtonCameraLive
			// 
			this->toolStripButtonCameraLive->CheckOnClick = true;
			this->toolStripButtonCameraLive->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButtonCameraLive->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonCameraLive.Image")));
			this->toolStripButtonCameraLive->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonCameraLive->Name = L"toolStripButtonCameraLive";
			this->toolStripButtonCameraLive->Size = System::Drawing::Size(70, 22);
			this->toolStripButtonCameraLive->Text = L"Camera Live";
			this->toolStripButtonCameraLive->CheckedChanged += gcnew System::EventHandler(this, &Form1::toolStripButtonCameraLive_CheckedChanged);
			// 
			// toolStripButtonSnapMode
			// 
			this->toolStripButtonSnapMode->Checked = true;
			this->toolStripButtonSnapMode->CheckOnClick = true;
			this->toolStripButtonSnapMode->CheckState = System::Windows::Forms::CheckState::Checked;
			this->toolStripButtonSnapMode->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButtonSnapMode->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonSnapMode.Image")));
			this->toolStripButtonSnapMode->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonSnapMode->Name = L"toolStripButtonSnapMode";
			this->toolStripButtonSnapMode->Size = System::Drawing::Size(61, 22);
			this->toolStripButtonSnapMode->Text = L"SnapMode";
			this->toolStripButtonSnapMode->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonSnapMode_Click);
			// 
			// toolStripSplitButtonFilters
			// 
			this->toolStripSplitButtonFilters->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripSplitButtonFilters->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->deviceToolStripMenuItem, 
				this->displayToolStripMenuItem});
			this->toolStripSplitButtonFilters->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripSplitButtonFilters.Image")));
			this->toolStripSplitButtonFilters->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripSplitButtonFilters->Name = L"toolStripSplitButtonFilters";
			this->toolStripSplitButtonFilters->Size = System::Drawing::Size(52, 22);
			this->toolStripSplitButtonFilters->Text = L"Filters";
			// 
			// deviceToolStripMenuItem
			// 
			this->deviceToolStripMenuItem->Name = L"deviceToolStripMenuItem";
			this->deviceToolStripMenuItem->Size = System::Drawing::Size(108, 22);
			this->deviceToolStripMenuItem->Text = L"Device";
			this->deviceToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::deviceToolStripMenuItem_Click);
			// 
			// displayToolStripMenuItem
			// 
			this->displayToolStripMenuItem->Name = L"displayToolStripMenuItem";
			this->displayToolStripMenuItem->Size = System::Drawing::Size(108, 22);
			this->displayToolStripMenuItem->Text = L"Display";
			this->displayToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::displayToolStripMenuItem_Click);
			// 
			// toolStripButtonOberlays
			// 
			this->toolStripButtonOberlays->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButtonOberlays->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonOberlays.Image")));
			this->toolStripButtonOberlays->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonOberlays->Name = L"toolStripButtonOberlays";
			this->toolStripButtonOberlays->Size = System::Drawing::Size(54, 22);
			this->toolStripButtonOberlays->Text = L"Overlays";
			this->toolStripButtonOberlays->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonOberlays_Click);
			// 
			// toolStripButtonImageProc
			// 
			this->toolStripButtonImageProc->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButtonImageProc->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonImageProc.Image")));
			this->toolStripButtonImageProc->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonImageProc->Name = L"toolStripButtonImageProc";
			this->toolStripButtonImageProc->Size = System::Drawing::Size(95, 22);
			this->toolStripButtonImageProc->Text = L"Image Processing";
			this->toolStripButtonImageProc->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonImageProc_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(929, 527);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->panel1);
			this->MinimumSize = System::Drawing::Size(371, 242);
			this->Name = L"Form1";
			this->Text = L"Demo3";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbLiveVideo))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbSnappedImage))->EndInit();
			this->panel1->ResumeLayout(false);
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	
	//-----------------------------------------------------------------------
	//	On click button handler: Grab one image and show it in the PictureBox
	//-----------------------------------------------------------------------
	private: System::Void btnSnapAndDraw_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			tFrameHandlerSinkPtr pSink = m_cGrabber->getSinkTypePtr();	// Get pointer at Sink in the Grabber.
			
			Error er;
			if( m_cGrabber->isLive() )				// To grab image must be the device in the Live mode.
			{
				er = pSink->snapImages( 1, 2000 );	// Grab and copy the frame to the MemBufferCollection 
													// (timeout = 2000ms).
			}
			
			// Error handling
			if( er.isError() )
			{
				String^ text = gcnew String(er.c_str());
				MessageBox::Show( text, "Grabbing error",
									MessageBoxButtons::OK, 
									MessageBoxIcon::Exclamation );
			}
			else
			{
				smart_ptr<MemBuffer> pBuff = pSink->getLastAcqMemBuffer();	// get pointer to the buffer with the grabbed frame
				SIZE size = pBuff->getSize();									// get size of image
				int stride = pBuff->getBitsPerPixel()*size.cx/8;				// get bytes count on the row
				// Create bitmap which datapointer point at the memory of buffer:
				Bitmap^ imtmp = gcnew Bitmap(size.cx,size.cy,stride,								//
											 System::Drawing::Imaging::PixelFormat::Format24bppRgb,	//
											 (System::IntPtr) pBuff->getPtr());						//
				pbSnappedImage->Image = imtmp;	// Show the bitmap in the picturebox
				pbSnappedImage->Refresh();		//
			}
		}

	
	//---------------------------------------------------------------------------
	// OnResize pictureBox handler - for change the size of LivePreviw to see 
	// whole image in the properly aspect ratio.
	//---------------------------------------------------------------------------
	private: System::Void pbLiveVideo_Resize(System::Object^  sender, System::EventArgs^  e) 
		{
			// Get size of PictureBox
			System::Windows::Forms::PictureBox^ pb = (System::Windows::Forms::PictureBox^) sender;
			long width  = pb->Size.Width;
			long height = pb->Size.Height;
			// Get the size of camera image and the ratio
			SIZE size = this->m_cGrabber->getVideoFormat().getSize();
			double ratio = (double)size.cx/(double)size.cy;
			
			// If the window is larger than the image, leave size of image
			// Otherwise change the aspect ratio of the window according the ration of image.
			if(width>size.cx && height>size.cy)
			{
				width = size.cx;
				height = size.cy;
			}
			else 
			{
				// If the window is wider than image, change width of window
				if( double(width)/(double)(height) > ratio)
				{
					width = (long)(height * ratio);
				}
				// If the window is higher than image, change the hight of window
				else
				{
					height = (long)(width / ratio);
				}
			}

			// Change of size of live preview
			if( this->m_cGrabber->getDefaultWindowPosition() == false )	// Change size of preview is possible only if the defaultWindowPosition flag is deactivated
			{
				if( this->m_cGrabber->setWindowSize( width, height ) == false )
				{
					String^ text = gcnew String("Unsuccess during changing size of livePreview window");
					MessageBox::Show( text, "Error",
										MessageBoxButtons::OK, 
										MessageBoxIcon::Exclamation );
				}
			}
		}


		 
	//-----------------------------------------------------------------------
	// OnClick button handler to open dialog with list of available devices
	//-----------------------------------------------------------------------
	private: System::Void toolButtonDevice_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			 
			// To change Grabber settings, the Live mode must be off
			if(m_cGrabber->isDevValid() && m_cGrabber->isLive())
			{
				m_cGrabber->stopLive();
				toolStripButtonCameraLive->Checked = false;
			}
			m_cGrabber->closeDev();
			// Open dialog with list of available devices
			m_cGrabber->showDevicePage(0);
			
			// Set window handler for display live preview
			HWND hwnd = (HWND)this->pbLiveVideo->Handle.ToPointer();	// Get the window handler of picture box
			m_cGrabber->setHWND(hwnd);


			
			

			// Set filter to horizontal flip of device stream
			m_cGrabber->setDeviceFrameFilters(pFilterManagerDevice->GetFilterList());
			// Set filter to horizontal flip of display stream
			m_cGrabber->setDisplayFrameFilters (pFilterManagerDisplay->GetFilterList());

			// Set live mode on
			toolStripButtonCameraLive->Checked = true;
			
			// Change the size of the live preview according the size of the picture box
			pbLiveVideo_Resize(this->pbLiveVideo, gcnew System::EventArgs() );



			// ---------------------------------------------------------------------
			// Initialization of the output buffer of image processing result
			//	- dimensions according the video format
			// - Image format 8 bits, 4 channels, bgra
			cv::Mat* pMat = pListener->getOutputImage1();					
			*pMat = cv::Mat(m_cGrabber->getVideoFormat().getSize().cy,
							m_cGrabber->getVideoFormat().getSize().cx,
							CV_8UC4, cv::Scalar(0,0,0,0));	// BGRA	- initialized on transparent black
			
			

		}

private: System::Void deviceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 Form^ filterDialog = gcnew FilterDialog(m_cGrabber, pFilterManagerDevice, "Device Filters");
			 filterDialog->Show();
		 }
private: System::Void displayToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 Form^ filterDialog = gcnew FilterDialog(m_cGrabber, pFilterManagerDisplay, "Display Filters");
			 filterDialog->Show();
		 }
private: System::Void toolStripButtonCameraLive_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(!toolStripButtonCameraLive->Checked)
			 {
				m_cGrabber->stopLive();
			 }
			 else
			 {
				 if(m_cGrabber->isDevValid())
				 {
					 // Set window handler for display live preview
					 HWND hwnd = (HWND)this->pbLiveVideo->Handle.ToPointer();	// Get the window handler of picture box
					 m_cGrabber->setHWND(hwnd);

					 if(!m_cGrabber->getDev().isValid()) // if no device choosed
					 {
						 return;							// end
					 }
					 if( m_cGrabber->startLive(true) == false) // switch the grabber to live mode and switch the preview on
					 {
					 	toolStripButtonCameraLive->Checked = false;
					 	//	It is possible use method getLastError:
					 	Error er = m_cGrabber->getLastError();
					 	String^ ertext = gcnew String(er.c_str());
					 	MessageBox::Show( ertext, "Error",
					 		MessageBoxButtons::OK, 
					 		MessageBoxIcon::Exclamation );
					 }
				 }		
			 }
		 }
private: System::Void toolStripButtonOberlays_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 Form^ overlayDialog = gcnew OverlayDialog(m_cGrabber);
			 overlayDialog->Show();
		 }
private: System::Void toolStripButtonImageProc_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 Form^ imageProcDialog = gcnew Form_ImageProcessing(m_cGrabber, pListener);
			 imageProcDialog->Show();
		 }
	private: System::Void toolStripButtonSnapMode_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			(*m_pSink)->setSnapMode( toolStripButtonSnapMode->Checked );
		}
private: System::Void toolStripButtonProperties_Click(System::Object^  sender, System::EventArgs^  e) {
			 m_cGrabber->showVCDPropertyPage(); 
		 }
};// Form1

}// namespace Demo1

