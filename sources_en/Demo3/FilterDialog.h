//////////////////////////////////////////////////////////////////////////
// Demo example how to work with SDK IC Imaging Control 3.4
// under Visual C++ .NET
// Author: Petr Bastl, DFC Design, 2016
//
// Dialog for setup of FilterManager
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

#pragma once

#include "FilterManager.h"
#include <iostream>
#include <string>
namespace Demo3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Demo3;

	/// <summary>
	/// Summary for FilterDialog
	/// </summary>
	public ref class FilterDialog : public System::Windows::Forms::Form
	{
	private: 
		DShowLib::Grabber *m_cGrabber;
	private: System::Windows::Forms::ComboBox^  cBoxRotation;
	private: System::Windows::Forms::Button^  bCancel;
	private: System::Windows::Forms::Label^  label1;
			 FILTER_MANAGER *pFilterManager;
	
	public:
		FilterDialog(DShowLib::Grabber *o1,FILTER_MANAGER *o2, System::String^ name)
		{
			m_cGrabber = o1;
			pFilterManager = o2;
			InitializeComponent();

			this->Text = name;

			UpdateControls();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FilterDialog()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 

	private: System::Windows::Forms::Button^  bDeviceSet;
	private: System::Windows::Forms::CheckBox^  cbFlipH;
	private: System::Windows::Forms::CheckBox^  cbFlipV;



	

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->bDeviceSet = (gcnew System::Windows::Forms::Button());
			this->cbFlipH = (gcnew System::Windows::Forms::CheckBox());
			this->cbFlipV = (gcnew System::Windows::Forms::CheckBox());
			this->cBoxRotation = (gcnew System::Windows::Forms::ComboBox());
			this->bCancel = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// bDeviceSet
			// 
			this->bDeviceSet->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->bDeviceSet->Location = System::Drawing::Point(184, 12);
			this->bDeviceSet->Name = L"bDeviceSet";
			this->bDeviceSet->Size = System::Drawing::Size(75, 23);
			this->bDeviceSet->TabIndex = 2;
			this->bDeviceSet->Text = L"Set";
			this->bDeviceSet->UseVisualStyleBackColor = true;
			this->bDeviceSet->Click += gcnew System::EventHandler(this, &FilterDialog::bDeviceSet_Click);
			// 
			// cbFlipH
			// 
			this->cbFlipH->AutoSize = true;
			this->cbFlipH->Location = System::Drawing::Point(7, 70);
			this->cbFlipH->Name = L"cbFlipH";
			this->cbFlipH->Size = System::Drawing::Size(97, 17);
			this->cbFlipH->TabIndex = 3;
			this->cbFlipH->Text = L"Flip Horizontaly";
			this->cbFlipH->UseVisualStyleBackColor = true;
			// 
			// cbFlipV
			// 
			this->cbFlipV->AutoSize = true;
			this->cbFlipV->Location = System::Drawing::Point(7, 47);
			this->cbFlipV->Name = L"cbFlipV";
			this->cbFlipV->Size = System::Drawing::Size(85, 17);
			this->cbFlipV->TabIndex = 4;
			this->cbFlipV->Text = L"Flip Verticaly";
			this->cbFlipV->UseVisualStyleBackColor = true;
			// 
			// cBoxRotation
			// 
			this->cBoxRotation->FormattingEnabled = true;
			this->cBoxRotation->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"0°", L"90°", L"180°", L"270°"});
			this->cBoxRotation->Location = System::Drawing::Point(98, 12);
			this->cBoxRotation->Name = L"cBoxRotation";
			this->cBoxRotation->Size = System::Drawing::Size(80, 21);
			this->cBoxRotation->TabIndex = 7;
			// 
			// bCancel
			// 
			this->bCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->bCancel->Location = System::Drawing::Point(184, 47);
			this->bCancel->Name = L"bCancel";
			this->bCancel->Size = System::Drawing::Size(75, 23);
			this->bCancel->TabIndex = 8;
			this->bCancel->Text = L"Cancel";
			this->bCancel->UseVisualStyleBackColor = true;
			this->bCancel->Click += gcnew System::EventHandler(this, &FilterDialog::bCancel_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(47, 13);
			this->label1->TabIndex = 9;
			this->label1->Text = L"Rotation";
			// 
			// FilterDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(271, 133);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->bCancel);
			this->Controls->Add(this->cBoxRotation);
			this->Controls->Add(this->cbFlipV);
			this->Controls->Add(this->cbFlipH);
			this->Controls->Add(this->bDeviceSet);
			this->Name = L"FilterDialog";
			this->Text = L"FilterDialog";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: void UpdateControls()
			{
				FILTER_MANAGER::Rotate rotation;
				bool bFlipVertical = false;
				bool bFlipHorizontal = false;

				// Retrieve the current parameter settings.
				pFilterManager->GetRotateFilterParams(bFlipHorizontal, bFlipVertical, rotation);

				
				// Change the parameter
				switch(rotation)
				{
				case FILTER_MANAGER::Rotate0  : cBoxRotation->SelectedIndex = 0; break;
				case FILTER_MANAGER::Rotate90 : cBoxRotation->SelectedIndex = 1; break;
				case FILTER_MANAGER::Rotate180: cBoxRotation->SelectedIndex = 2; break;
				case FILTER_MANAGER::Rotate270: cBoxRotation->SelectedIndex = 3; break;
				}

				cbFlipH->Checked = bFlipHorizontal;
				cbFlipV->Checked = bFlipVertical;
			}

	private: System::Void bDeviceSet_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 FILTER_MANAGER::Rotate rotation;
			     long lAngle = 0;
				 long lNewAngle = 0;
				 bool bFlipVertical = false;
				 bool bFlipHorizontal = false;

				 

				 
				 // Change the parameter
				 switch(cBoxRotation->SelectedIndex)
				 {
					case 0: rotation = FILTER_MANAGER::Rotate0; break;
					case 1: rotation = FILTER_MANAGER::Rotate90; break;
					case 2: rotation = FILTER_MANAGER::Rotate180; break;
					case 3: rotation = FILTER_MANAGER::Rotate270; break;
				 }
				 
				 // The flip parameters do not cause a video format change, so they can be 
				 // set regardless of whether the live video is running.
				 bFlipHorizontal = cbFlipH->Checked;
				 bFlipVertical = cbFlipV->Checked;
				 

				 if(!pFilterManager->SetRotateFilterParams(bFlipHorizontal, bFlipVertical, rotation))
				 {
					 String^ msg = gcnew String(reinterpret_cast<const char*>(pFilterManager->GetLastError()));
					 MessageBox::Show( msg, "Chyba",
						 MessageBoxButtons::OK, 
						 MessageBoxIcon::Exclamation );
				 }

			 }
	private: System::Void bCancel_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
			 }
};
}
