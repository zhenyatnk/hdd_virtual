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
using bridge_csharp;

namespace ConectSettings
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow(CREFConectionParms aParm)
        {
            InitializeComponent();
            System.String[] lIP = aParm.mIP.Split('.');
            if (lIP.Length == 4)
            {
                IP1.Value = Convert.ToUInt16(lIP[0]);
                IP2.Value = Convert.ToUInt16(lIP[1]);
                IP3.Value = Convert.ToUInt16(lIP[2]);
                IP4.Value = Convert.ToUInt16(lIP[3]);
            }
            Port.Value = aParm.mPort;
        }
        public CREFConectionParms GetParametersConnection()
        {
            CREFConectionParms lParms = new CREFConectionParms();
            lParms.mIP = IP1.Value.ToString() + ".";
            lParms.mIP += IP2.Value.ToString() + ".";
            lParms.mIP += IP3.Value.ToString() + ".";
            lParms.mIP += IP4.Value.ToString();
            lParms.mPort = (int)Port.Value;
            lParms.mFamily = 2;
            return lParms;
        }

        private void button_OK_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = true;
            this.Close();
        }
        private void button_Cancel_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = false;
            this.Close();
        }
    }
}
