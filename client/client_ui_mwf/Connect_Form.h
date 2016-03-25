#pragma once
#include "./../../common/tools/ISocket.h"

namespace UserInterface
{

   using namespace System;
   using namespace System::ComponentModel;
   using namespace System::Collections;
   using namespace System::Windows::Forms;
   using namespace System::Data;
   using namespace System::Drawing;

   public ref class Connect_Form
      :public System::Windows::Forms::Form
   {
   public:
      Connect_Form(TConectionParms aParmConnection, std::string aFileNameVM);
      TConectionParms GetParametersConnection();
      std::string GetFileNameVM();

   protected:
      ~Connect_Form();

   private:
      void InitValueControls(TConectionParms aParmConnection);
      void InitFileNameControls(std::string aFileNameVM);
      void InitializeComponent(void);

   private:
      System::Windows::Forms::TableLayoutPanel^  tlMainTableLayot;
      System::Windows::Forms::TableLayoutPanel^  tlBottomTableLayout;
      System::Windows::Forms::Button^  bOk;
      System::Windows::Forms::Button^  bCancel;
      System::Windows::Forms::Panel^  pnPanelParameters;
      System::Windows::Forms::GroupBox^  gbPort;
      System::Windows::Forms::GroupBox^  gbIP;
      System::Windows::Forms::NumericUpDown^  nudIP1;
   private: System::Windows::Forms::NumericUpDown^  nudNumberPort;

   private: System::Windows::Forms::NumericUpDown^  nudIP2;
   private: System::Windows::Forms::NumericUpDown^  nudIP3;
   private: System::Windows::Forms::NumericUpDown^  nudIP4;





      System::Windows::Forms::Label^  lDot1;
      System::Windows::Forms::Label^  lDot2;
      System::Windows::Forms::Label^  lDot3;
   private: System::Windows::Forms::GroupBox^  groupBox1;
   private: System::Windows::Forms::TextBox^  tbFilenameVM;

            System::ComponentModel::Container ^components;
   };
}
