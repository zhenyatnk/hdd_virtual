using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using bridge_csharp;

namespace client_wpf
{
   public partial class MainWindow : Window
   {
      public MainWindow()
      {
         InitializeDefaultChanel();
         InitializeComponent();
         ErrorLog = new List<System.String>();
         if (!ChangeParmsConnection())
            mFactoryObject = new CREFFactoryObject(mParmConnection);
         ReloadInfoHDDToListView();
      }
      private void MenuItem_Click(object sender, RoutedEventArgs e)
      {
         if (ChangeParmsConnection())
         {
            ReloadInfoHDDToListView();
         }
      }
      private bool ChangeParmsConnection()
      {
         ConectSettings.MainWindow lForm = new ConectSettings.MainWindow(mParmConnection);
         bool? lStat = lForm.ShowDialog();
         if (true == lStat)
         {
            mParmConnection = lForm.GetParametersConnection();
            mConfigFile.SetDefaultIP(mParmConnection.mIP);
            mConfigFile.SetDefaultPort(mParmConnection.mPort);
            if (mFactoryObject != null)
               mFactoryObject.CloseChannel();
            mFactoryObject = new CREFFactoryObject(mParmConnection);
         }
         return true == lStat;
      }
      private void InitializeDefaultChanel()
      {
         mConfigFile = new CREFConfigFile();
         mParmConnection = new CREFConectionParms();
         mParmConnection.mIP = mConfigFile.GetDefaultIP();
         mParmConnection.mPort = mConfigFile.GetDefaultPort();
         mParmConnection.mFamily = 2;
      }
      private void ReloadInfoHDDToListView()
      {
         try
         {
            HDDInfo = new List<ListHDDElement>();
            ArrayList lContainerMeta = mFactoryObject.CreatePartitionsMeta();
            uint lNumberDisk = 1;
            foreach (Object lObj in lContainerMeta)
            {
               CREFPartitionMeta lHDDMeta = (CREFPartitionMeta)lObj;
               ListHDDElement lHDD = new ListHDDElement();
               lHDD.Number = lNumberDisk;
               if (lHDDMeta.IsBoot())  lHDD.Bootable = "*";
               else                    lHDD.Bootable = "";
               lHDD.Size = lHDDMeta.GetSizeInSector();
               lHDD.Type = REFConvertTypeSystem.Convert(lHDDMeta.GetTypePart());
               if (lHDDMeta.IsExtend()) lHDD.Extend = "*";
               else                     lHDD.Extend = "";
               HDDInfo.Add(lHDD);
               ++lNumberDisk;
            }
            this.DataContext = this;
         }
         catch (CREFServerException Error)
         {
            ErrorLog.Add(Error.GetMessage());
            lbListError.ItemsSource = new List<System.String>(ErrorLog);
         }
         catch (CREFSocketException Error)
         {
            ErrorLog.Add(Error.GetMessage());
            lbListError.ItemsSource = new List<System.String>(ErrorLog);
         }
      }
      private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
      {
         if (mFactoryObject != null)
            mFactoryObject.CloseChannel();
      }

      private CREFFactoryObject mFactoryObject;
      private CREFConfigFile mConfigFile;
      private CREFConectionParms mParmConnection;

      public class ListHDDElement
      {
         public uint Number { get; set; }
         public string Bootable { get; set; }
         public uint Size { get; set; }
         public string Type { get; set; }
         public string Extend { get; set; }
      }
      public IList<ListHDDElement> HDDInfo { get; set; }
      public IList<System.String> ErrorLog { get; set; }
   }
}
