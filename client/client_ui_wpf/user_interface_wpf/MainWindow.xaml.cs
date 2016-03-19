using System;
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

namespace client_wpf
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            bridge_csharp.CREFConectionParms lParms = new bridge_csharp.CREFConectionParms();
            lParms.mPort = 25000;
            lParms.mIP = "127.0.0.1";
            lParms.mFamily = 2;
            bridge_csharp.CREFFactoryObject lFactor = new bridge_csharp.CREFFactoryObject(lParms);
            bridge_csharp.CREFPartitionMeta lPartMeta = lFactor.CreatePartitionMeta(1);
            lFactor.CloseChannel();
        }
        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            ConectSettings.MainWindow lForms = new ConectSettings.MainWindow();
            lForms.ShowDialog();
        }
    }
}
