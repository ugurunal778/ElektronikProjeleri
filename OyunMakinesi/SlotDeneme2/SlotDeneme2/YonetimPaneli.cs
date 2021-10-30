using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SlotDeneme2
{
    public partial class YonetimPaneli : Form
    {
        public YonetimPaneli()
        {
            InitializeComponent();
        }

        private void YonetimPaneli_Load(object sender, EventArgs e)
        {
            OtelYukle();
            CoinYukle();
            label11.Text = listView1.Items.Count.ToString();
            label6.Text = listView2.Items.Count.ToString();

        }
        #region Otel Yükle
        private void OtelYukle()
        {
            listView1.Items.Clear();
            foreach (var item in HotelLoad())
            {
                string[] otel = item.ToString().Split('&');
                ListViewItem lvi = new ListViewItem();
                lvi.Text = otel[0];
                lvi.Tag = item;
                listView1.Items.Add(lvi);
            }
        }
        #endregion

        #region Hotel Load
        private ArrayList HotelLoad()
        {
            ArrayList okunanlar = new ArrayList();
            if (File.Exists(path))
            {
                using (StreamReader sr = new StreamReader(path))
                {
                    while (sr.Peek() >= 0)
                    {
                        okunanlar.Add(sr.ReadLine());
                    }
                }
            }
            return okunanlar;
        }
        #endregion
        #region CoinLoad
        private ArrayList CoinLoad()
        {
            ArrayList okunanlar1 = new ArrayList();
            if (File.Exists(path1))
            {
                using (StreamReader sr1 = new StreamReader(path1))
                {
                    while (sr1.Peek() >= 0)
                    {
                        okunanlar1.Add(sr1.ReadLine());
                    }
                }
            }
            return okunanlar1;
        }
#endregion
        #region CoinYukle
        private void CoinYukle()
        {
            listView2.Items.Clear();
            foreach (var item1 in CoinLoad())
            {
                string[] otel1 = item1.ToString().Split('&');
                ListViewItem lvi1 = new ListViewItem();
                lvi1.Text = otel1[0];
                lvi1.Tag = item1;
                listView2.Items.Add(lvi1);
            }
        }
        #endregion
        #region Temizle
        //void Temizle()
        //{
        //    foreach (Control item in groupBox1.Controls)
        //    {
        //        if (item is TextBox)
        //        {
        //            item.Text = "";
        //        }
        //    }
        //}
        #endregion

        string path = "../../App_Data/Otel.txt";
        string path1 = "../../App_Data/Otel1.txt";
        string path2 = "../../App_Data/Otel2.txt";

        private void btnKaydet_Click(object sender, EventArgs e)
        {
            label8.Text = textBox1.Text;
        //    ArrayList okunanlar = HotelLoad();

        //    using (StreamWriter sw = new StreamWriter(path))
        //    {

        //        if (okunanlar.Count > 0)
        //        {
        //            foreach (string otel in okunanlar)
        //            {
        //                sw.WriteLine(otel);
        //            }
        //        }

        //        sw.WriteLine(string.Format("{0}", DateTime.Now));
        //        sw.Close();
        //    }
        //    OtelYukle();
        }
    }
}
