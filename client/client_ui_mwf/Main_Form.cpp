#include "stdafx.h"
#include "winsock.h"

#include "Main_Form.h"
#include "Connect_Form.h"
#include "../tools/CConfig.h"
#include "../../common/tools/CExceptions.h"

namespace
{
   TConectionParms gParm;
   std::string gFileNameVM;
   IObjectFactory::Ptr gFactoryObject;
}

namespace UserInterface
{
   Main_Form::Main_Form(void)
   {
      InitializeComponent();
      InitializeDefaultChanel();
      ChangeParmsConnection();
      ReloadInfoHDDToListView();
   }

   Main_Form::~Main_Form()
   {
      if (components)
         delete components;
   }

   IObjectFactory::Ptr Main_Form::GetFactoryObjects()
   {
      if (!gFactoryObject)
         gFactoryObject = CreateClientFactory(gParm, gFileNameVM);
      return gFactoryObject;
   }

   System::Void Main_Form::smiParametersConnectionMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
   {
      if (ChangeParmsConnection())
         ReloadInfoHDDToListView();
   }
   void Main_Form::ReloadInfoHDDToListView()
   {
      try
      {
         lvHDDInfoListView->Items->Clear();
         V_UINT32 lNumberDisk = 1;
         std::vector<CPartitionMeta::Ptr> lHDDMetas = GetFactoryObjects()->CreatePartitionsMeta();
         for (std::vector<CPartitionMeta::Ptr>::iterator lIterator = lHDDMetas.begin(); lIterator != lHDDMetas.end(); ++lIterator)
         {
            ListViewItem ^lHDDInfo = gcnew ListViewItem(System::Convert::ToString((int)lNumberDisk));
            if ((*lIterator)->IsBoot())  lHDDInfo->SubItems->Add(gcnew ListViewItem::ListViewSubItem(lHDDInfo, "*"));
            else                     lHDDInfo->SubItems->Add(gcnew ListViewItem::ListViewSubItem(lHDDInfo, ""));
            lHDDInfo->SubItems->Add(gcnew ListViewItem::ListViewSubItem(lHDDInfo, System::Convert::ToString((int)(*lIterator)->GetSizeInSector())));
            lHDDInfo->SubItems->Add(gcnew ListViewItem::ListViewSubItem(lHDDInfo, gcnew System::String(ConvertTypeSystem((*lIterator)->GetTypePart()).c_str())));
            if ((*lIterator)->IsExtend())  lHDDInfo->SubItems->Add(gcnew ListViewItem::ListViewSubItem(lHDDInfo, "*"));
            else                           lHDDInfo->SubItems->Add(gcnew ListViewItem::ListViewSubItem(lHDDInfo, ""));
            lvHDDInfoListView->Items->Add(lHDDInfo);
            ++lNumberDisk;
         }
      }
      catch (server_exception &e)
      {
         lbLogListBox->Items->Add(gcnew System::String(e.get_message().c_str()));
      }
      catch (socket_exception_w&e)
      {
         lbLogListBox->Items->Add(gcnew System::String(e.get_message().c_str()));
      }
      catch (System::Object^ e)
      {
         this->Close();
      }
   }

   void Main_Form::InitializeDefaultChanel(void)
   {
      gParm.mIP = CConfigForms::GetInstance().GetDefaultIP();
      gParm.mFamily = AF_INET;
      gParm.mPort = CConfigForms::GetInstance().GetDefaultPort();
      gFileNameVM = CConfigForms::GetInstance().GetDefaultFileNameVM();
   }

   bool Main_Form::ChangeParmsConnection()
   {
      UserInterface::Connect_Form lFormConnect(gParm, gFileNameVM);
      if (Windows::Forms::DialogResult::OK == lFormConnect.ShowDialog())
      {
         gParm = lFormConnect.GetParametersConnection();
         gFileNameVM = lFormConnect.GetFileNameVM();
         CConfigForms::GetInstance().SetDefaultIP(gParm.mIP);
         CConfigForms::GetInstance().SetDefaultPort(gParm.mPort);
         CConfigForms::GetInstance().SetDefaultFileNameVM(gFileNameVM);
         gFactoryObject = NULL;
         return true;
      }
      return false;
   }

#pragma region Windows Form Designer generated code
   void Main_Form::InitializeComponent(void)
   {
      this->components = (gcnew System::ComponentModel::Container());
      System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Main_Form::typeid));
      this->lvHDDInfoListView = (gcnew System::Windows::Forms::ListView());
      this->chHeader_HddNum = (gcnew System::Windows::Forms::ColumnHeader());
      this->chHeader_Bootable = (gcnew System::Windows::Forms::ColumnHeader());
      this->chHeader_Size = (gcnew System::Windows::Forms::ColumnHeader());
      this->chHeader_FileSystem = (gcnew System::Windows::Forms::ColumnHeader());
      this->chHeader_Extend = (gcnew System::Windows::Forms::ColumnHeader());
      this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
      this->msTopMenuStrip = (gcnew System::Windows::Forms::MenuStrip());
      this->smiSettingsMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->smiParametersConnectionMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->scMainSplitContainer = (gcnew System::Windows::Forms::SplitContainer());
      this->lbLogListBox = (gcnew System::Windows::Forms::ListBox());
      this->tlFullInformationLayot = (gcnew System::Windows::Forms::TableLayoutPanel());
      this->msTopMenuStrip->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->scMainSplitContainer))->BeginInit();
      this->scMainSplitContainer->Panel1->SuspendLayout();
      this->scMainSplitContainer->Panel2->SuspendLayout();
      this->scMainSplitContainer->SuspendLayout();
      this->tlFullInformationLayot->SuspendLayout();
      this->SuspendLayout();
      // 
      // lvHDDInfoListView
      // 
      this->lvHDDInfoListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {
         this->chHeader_HddNum,
            this->chHeader_Bootable, this->chHeader_Size, this->chHeader_FileSystem, this->chHeader_Extend
      });
      this->lvHDDInfoListView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->lvHDDInfoListView->LargeImageList = this->imageList1;
      this->lvHDDInfoListView->Location = System::Drawing::Point(0, 0);
      this->lvHDDInfoListView->Name = L"lvHDDInfoListView";
      this->lvHDDInfoListView->Size = System::Drawing::Size(516, 162);
      this->lvHDDInfoListView->TabIndex = 0;
      this->lvHDDInfoListView->UseCompatibleStateImageBehavior = false;
      this->lvHDDInfoListView->View = System::Windows::Forms::View::Details;
      // 
      // chHeader_HddNum
      // 
      this->chHeader_HddNum->Text = L"�";
      this->chHeader_HddNum->Width = 27;
      // 
      // chHeader_Bootable
      // 
      this->chHeader_Bootable->Text = L"�����������";
      this->chHeader_Bootable->Width = 56;
      // 
      // chHeader_Size
      // 
      this->chHeader_Size->Text = L"������ (��)";
      this->chHeader_Size->Width = 91;
      // 
      // chHeader_FileSystem
      // 
      this->chHeader_FileSystem->Text = L"�������� �������";
      this->chHeader_FileSystem->Width = 113;
      // 
      // chHeader_Extend
      // 
      this->chHeader_Extend->Text = L"�����������";
      // 
      // imageList1
      // 
      this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList1.ImageStream")));
      this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
      this->imageList1->Images->SetKeyName(0, L"hdd_icon.png");
      // 
      // msTopMenuStrip
      // 
      this->msTopMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->smiSettingsMenuItem });
      this->msTopMenuStrip->Location = System::Drawing::Point(0, 0);
      this->msTopMenuStrip->Name = L"msTopMenuStrip";
      this->msTopMenuStrip->Size = System::Drawing::Size(522, 24);
      this->msTopMenuStrip->TabIndex = 2;
      this->msTopMenuStrip->Text = L"menuStrip1";
      // 
      // smiSettingsMenuItem
      // 
      this->smiSettingsMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->smiParametersConnectionMenuItem });
      this->smiSettingsMenuItem->Name = L"smiSettingsMenuItem";
      this->smiSettingsMenuItem->Size = System::Drawing::Size(79, 20);
      this->smiSettingsMenuItem->Text = L"���������";
      // 
      // smiParametersConnectionMenuItem
      // 
      this->smiParametersConnectionMenuItem->Name = L"smiParametersConnectionMenuItem";
      this->smiParametersConnectionMenuItem->Size = System::Drawing::Size(206, 22);
      this->smiParametersConnectionMenuItem->Text = L"��������� ����������";
      this->smiParametersConnectionMenuItem->Click += gcnew System::EventHandler(this, &Main_Form::smiParametersConnectionMenuItem_Click);
      // 
      // scMainSplitContainer
      // 
      this->scMainSplitContainer->Dock = System::Windows::Forms::DockStyle::Fill;
      this->scMainSplitContainer->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
      this->scMainSplitContainer->Location = System::Drawing::Point(3, 3);
      this->scMainSplitContainer->Name = L"scMainSplitContainer";
      this->scMainSplitContainer->Orientation = System::Windows::Forms::Orientation::Horizontal;
      // 
      // scMainSplitContainer.Panel1
      // 
      this->scMainSplitContainer->Panel1->Controls->Add(this->lvHDDInfoListView);
      // 
      // scMainSplitContainer.Panel2
      // 
      this->scMainSplitContainer->Panel2->Controls->Add(this->lbLogListBox);
      this->scMainSplitContainer->Size = System::Drawing::Size(516, 231);
      this->scMainSplitContainer->SplitterDistance = 162;
      this->scMainSplitContainer->TabIndex = 3;
      // 
      // lbLogListBox
      // 
      this->lbLogListBox->Dock = System::Windows::Forms::DockStyle::Fill;
      this->lbLogListBox->FormattingEnabled = true;
      this->lbLogListBox->Location = System::Drawing::Point(0, 0);
      this->lbLogListBox->Name = L"lbLogListBox";
      this->lbLogListBox->Size = System::Drawing::Size(516, 65);
      this->lbLogListBox->TabIndex = 0;
      // 
      // tlFullInformationLayot
      // 
      this->tlFullInformationLayot->ColumnCount = 1;
      this->tlFullInformationLayot->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
         100)));
      this->tlFullInformationLayot->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
         20)));
      this->tlFullInformationLayot->Controls->Add(this->scMainSplitContainer, 0, 0);
      this->tlFullInformationLayot->Dock = System::Windows::Forms::DockStyle::Fill;
      this->tlFullInformationLayot->Location = System::Drawing::Point(0, 24);
      this->tlFullInformationLayot->Name = L"tlFullInformationLayot";
      this->tlFullInformationLayot->RowCount = 1;
      this->tlFullInformationLayot->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
         100)));
      this->tlFullInformationLayot->Size = System::Drawing::Size(522, 237);
      this->tlFullInformationLayot->TabIndex = 4;
      // 
      // Main_Form
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(522, 261);
      this->Controls->Add(this->tlFullInformationLayot);
      this->Controls->Add(this->msTopMenuStrip);
      this->MainMenuStrip = this->msTopMenuStrip;
      this->Name = L"Main_Form";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->Text = L"���������� � ������ � �������� VM";
      this->msTopMenuStrip->ResumeLayout(false);
      this->msTopMenuStrip->PerformLayout();
      this->scMainSplitContainer->Panel1->ResumeLayout(false);
      this->scMainSplitContainer->Panel2->ResumeLayout(false);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->scMainSplitContainer))->EndInit();
      this->scMainSplitContainer->ResumeLayout(false);
      this->tlFullInformationLayot->ResumeLayout(false);
      this->ResumeLayout(false);
      this->PerformLayout();

   }
#pragma endregion

}
