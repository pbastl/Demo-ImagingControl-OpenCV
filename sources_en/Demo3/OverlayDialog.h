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

#pragma once

#include "OverlayBitmapManager.h"

namespace Demo3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for OverlayDialog
	/// </summary>
	public ref class OverlayDialog : public System::Windows::Forms::Form
	{
	public:
		OverlayDialog(DShowLib::Grabber* m_cgrabber)
		{
			InitializeComponent();
			
			m_cGrabber = m_cgrabber;
			bitmapManager = new COverlayBitmapManager(m_cgrabber);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~OverlayDialog()
		{
			if (components)
			{
				delete components;
			}
			delete bitmapManager;
		}
	private: System::Windows::Forms::CheckBox^  cbEnable;
	protected: 
	private: System::Windows::Forms::GroupBox^  gbOvelaysSetttings;
	private: System::Windows::Forms::CheckBox^  cbCallbackOverlay;

	private: System::Windows::Forms::CheckBox^  cbDisplayOverlay;

	private: System::Windows::Forms::CheckBox^  cbSinkOverlay;

	private: System::Windows::Forms::CheckBox^  cbDeviceOverlay;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		DShowLib::Grabber* m_cGrabber;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
			 COverlayBitmapManager* bitmapManager;


		void UpdateData(bool ToDialog);

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->cbEnable = (gcnew System::Windows::Forms::CheckBox());
			this->gbOvelaysSetttings = (gcnew System::Windows::Forms::GroupBox());
			this->cbCallbackOverlay = (gcnew System::Windows::Forms::CheckBox());
			this->cbDisplayOverlay = (gcnew System::Windows::Forms::CheckBox());
			this->cbSinkOverlay = (gcnew System::Windows::Forms::CheckBox());
			this->cbDeviceOverlay = (gcnew System::Windows::Forms::CheckBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->gbOvelaysSetttings->SuspendLayout();
			this->SuspendLayout();
			// 
			// cbEnable
			// 
			this->cbEnable->AutoSize = true;
			this->cbEnable->Location = System::Drawing::Point(18, 11);
			this->cbEnable->Name = L"cbEnable";
			this->cbEnable->Size = System::Drawing::Size(59, 17);
			this->cbEnable->TabIndex = 0;
			this->cbEnable->Text = L"Enable";
			this->cbEnable->UseVisualStyleBackColor = true;
			// 
			// gbOvelaysSetttings
			// 
			this->gbOvelaysSetttings->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->gbOvelaysSetttings->Controls->Add(this->cbCallbackOverlay);
			this->gbOvelaysSetttings->Controls->Add(this->cbDisplayOverlay);
			this->gbOvelaysSetttings->Controls->Add(this->cbSinkOverlay);
			this->gbOvelaysSetttings->Controls->Add(this->cbDeviceOverlay);
			this->gbOvelaysSetttings->Location = System::Drawing::Point(12, 34);
			this->gbOvelaysSetttings->Name = L"gbOvelaysSetttings";
			this->gbOvelaysSetttings->Size = System::Drawing::Size(229, 117);
			this->gbOvelaysSetttings->TabIndex = 1;
			this->gbOvelaysSetttings->TabStop = false;
			this->gbOvelaysSetttings->Text = L"Overlays Setting";
			// 
			// cbCallbackOverlay
			// 
			this->cbCallbackOverlay->AutoSize = true;
			this->cbCallbackOverlay->Location = System::Drawing::Point(6, 88);
			this->cbCallbackOverlay->Name = L"cbCallbackOverlay";
			this->cbCallbackOverlay->Size = System::Drawing::Size(106, 17);
			this->cbCallbackOverlay->TabIndex = 4;
			this->cbCallbackOverlay->Text = L"Overlay Callback";
			this->cbCallbackOverlay->UseVisualStyleBackColor = true;
			this->cbCallbackOverlay->CheckedChanged += gcnew System::EventHandler(this, &OverlayDialog::cbOverlay_CheckedChanged);
			// 
			// cbDisplayOverlay
			// 
			this->cbDisplayOverlay->AutoSize = true;
			this->cbDisplayOverlay->Location = System::Drawing::Point(6, 65);
			this->cbDisplayOverlay->Name = L"cbDisplayOverlay";
			this->cbDisplayOverlay->Size = System::Drawing::Size(97, 17);
			this->cbDisplayOverlay->TabIndex = 3;
			this->cbDisplayOverlay->Text = L"Display overlay";
			this->cbDisplayOverlay->UseVisualStyleBackColor = true;
			this->cbDisplayOverlay->CheckedChanged += gcnew System::EventHandler(this, &OverlayDialog::cbOverlay_CheckedChanged);
			// 
			// cbSinkOverlay
			// 
			this->cbSinkOverlay->AutoSize = true;
			this->cbSinkOverlay->Location = System::Drawing::Point(6, 42);
			this->cbSinkOverlay->Name = L"cbSinkOverlay";
			this->cbSinkOverlay->Size = System::Drawing::Size(84, 17);
			this->cbSinkOverlay->TabIndex = 2;
			this->cbSinkOverlay->Text = L"Sink overlay";
			this->cbSinkOverlay->UseVisualStyleBackColor = true;
			this->cbSinkOverlay->CheckedChanged += gcnew System::EventHandler(this, &OverlayDialog::cbOverlay_CheckedChanged);
			// 
			// cbDeviceOverlay
			// 
			this->cbDeviceOverlay->AutoSize = true;
			this->cbDeviceOverlay->Location = System::Drawing::Point(6, 19);
			this->cbDeviceOverlay->Name = L"cbDeviceOverlay";
			this->cbDeviceOverlay->Size = System::Drawing::Size(97, 17);
			this->cbDeviceOverlay->TabIndex = 1;
			this->cbDeviceOverlay->Text = L"Device overlay";
			this->cbDeviceOverlay->UseVisualStyleBackColor = true;
			this->cbDeviceOverlay->CheckedChanged += gcnew System::EventHandler(this, &OverlayDialog::cbOverlay_CheckedChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(83, 7);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Update";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &OverlayDialog::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(166, 7);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Draw";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &OverlayDialog::button2_Click);
			// 
			// OverlayDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(253, 155);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->gbOvelaysSetttings);
			this->Controls->Add(this->cbEnable);
			this->Name = L"OverlayDialog";
			this->Text = L"OverlayDialog";
			this->gbOvelaysSetttings->ResumeLayout(false);
			this->gbOvelaysSetttings->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void cbOverlay_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			UpdateData(false);
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 UpdateData(true);
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 bitmapManager->drawOverlay( ePP_DEVICE );
			 bitmapManager->drawOverlay( ePP_SINK );
			 bitmapManager->drawOverlay( ePP_DISPLAY );
		 }
};
}
