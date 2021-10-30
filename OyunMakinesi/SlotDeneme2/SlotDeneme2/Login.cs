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
    public partial class Login : Form
    {
        public Login()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (txtUID.Text == "multigames")
            {
                if (txtPWD.Text == "mg17")
                {
                    // Giriş Yapacak
                    YonetimPaneli yp = new YonetimPaneli();
                    int  sonuc = OtelYukle();
                    yp.label11.Text = yp.listView1.Items.Count.ToString();

                    if (sonuc == Convert.ToInt32(yp.label8.Text))
                    {
                        MessageBox.Show("Oyun Sınırınız Dolmuştur");
                        this.Close();
                    }
                    else
                    {
                        Home home = new Home();
                        home.Show();
                        this.Hide();
                    }
                 
                }
                else
                {
                    label3.Text = "Geçersiz Giriş";
                }
            }
            else if (txtUID.Text == "superadmin")
            {

                if (txtPWD.Text == "mg17")
                {

                }
                else
                {

                }
           }
            else
            {
                label3.Text = "Geçersiz Giriş";
            }
        }
        string path = "../../App_Data/Otel.txt";
        #region Otel Yükle
        private int  OtelYukle()
        {
            YonetimPaneli yon = new YonetimPaneli();
            yon.listView1.Items.Clear();
            foreach (var item in HotelLoad())
            {
                string[] otel = item.ToString().Split('&');
                ListViewItem lvi = new ListViewItem();
                lvi.Text = otel[0];
                lvi.Tag = item;
                yon.listView1.Items.Add(lvi);
            }
            return yon.listView1.Items.Count;
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
        private void Login_Load(object sender, EventArgs e)
        {
            
        }
    }
}
