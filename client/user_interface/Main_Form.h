#pragma once

#include "../tools/transport/CCObjectFactory.h"

namespace UserInterface {

   using namespace System;
   using namespace System::ComponentModel;
   using namespace System::Collections;
   using namespace System::Windows::Forms;
   using namespace System::Data;
   using namespace System::Drawing;

   public ref class Main_Form
      :public System::Windows::Forms::Form
   {
   public:
      Main_Form(void);

   protected:
      ~Main_Form();

   private:
      IObjectFactory::Ptr GetFactoryObjects();

      System::Void smiParametersConnectionMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
      void ReloadInfoHDDToListView(void);
      void InitializeDefaultChanel(void);
      void InitializeComponent(void);

   private:
      System::Windows::Forms::ListView^  lvHDDInfoListView;
      System::Windows::Forms::MenuStrip^  msTopMenuStrip;
      System::Windows::Forms::ToolStripMenuItem^  smiSettingsMenuItem;
      System::Windows::Forms::ToolStripMenuItem^  smiParametersConnectionMenuItem;
      System::Windows::Forms::SplitContainer^  scMainSplitContainer;
      System::Windows::Forms::ListBox^  lbLogListBox;
      System::Windows::Forms::ImageList^  imageList1;
      System::Windows::Forms::ColumnHeader^  chHeader_HddLabel;
      System::Windows::Forms::ColumnHeader^  chHeader_Bootable;
      System::Windows::Forms::ColumnHeader^  chHeader_Size;
      System::Windows::Forms::ColumnHeader^  chHeader_FileSystem;
      System::Windows::Forms::TableLayoutPanel^  tlFullInformationLayot;
      System::ComponentModel::IContainer^  components;

   };
}

