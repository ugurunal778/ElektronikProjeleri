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
//using static System.Convert;

namespace SlotDeneme2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        string path = "../../App_Data/Otel.txt";
        string path1 = "../../App_Data/Otel1.txt";
        string path2 = "../../App_Data/Otel2.txt";
        #region Otel Yükle
        private void OtelYukle()
        {
            yp.listView1.Items.Clear();
            foreach (var item in HotelLoad())
            {
                string[] otel = item.ToString().Split('&');
                ListViewItem lvi = new ListViewItem();
                lvi.Text = otel[0];
                lvi.Tag = item;
                yp.listView1.Items.Add(lvi);
            }
        }
        private void CoinYukle()
        {
            yp.listView2.Items.Clear();
            foreach (var item1 in CoinLoad())
            {
                string[] otel1 = item1.ToString().Split('&');
                ListViewItem lvi1 = new ListViewItem();
                lvi1.Text = otel1[0];
                lvi1.Tag = item1;
                yp.listView2.Items.Add(lvi1);
            }
        }
        #endregion

        #region Hotel Load
        private ArrayList HotelLoad()
        {
            ArrayList okunanlar = new ArrayList();
            if (File.Exists(path))
            {
                using (StreamReader sr1 = new StreamReader(path))
                {
                    while (sr1.Peek() >= 0)
                    {
                        okunanlar.Add(sr1.ReadLine());
                    }
                }
            }
            return okunanlar;
        }
        private ArrayList  CoinLoad()
        {
            ArrayList okunanlar = new ArrayList();
            if (File.Exists(path1))
            {
                using (StreamReader sr = new StreamReader(path1))
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

        #region Oranlar
        public int Oran(int a)
        {
            a = rnd.Next(0, 100);
            if (a < 54) //                0 - 53      54
                a = 1;
            else if (a > 53 && a < 79) //     54 - 78      25
                a = 2;
            else if (a > 78 && a < 94) //      79 - 93     15 
                a = 3;
            else if (a > 93 && a < 97) //      94 - 96      3
                a = 4;
            else if (a > 96 && a < 99) //      97 - 98      2
                a = 5;
            else if (a == 99)  //                 99        1
                a = 6;
            return a;
        }
        public int Oran1(int a)
        {
            a = rnd.Next(0, 100);
            if (a < 61) //                0 - 53      54
                a = 1;
            else if (a > 60 && a < 81) //     54 - 78      25
                a = 2;
            else if (a > 80 && a < 100) //      79 - 93     15 
                a = 3;
            return a;
        }
        public int Oran2(int a)
        {
            a = rnd.Next(0, 100);
            if (a < 61) //                0 - 53      54
                a = 1;
            else if (a > 60 && a < 81) //     54 - 78      25
                a = 2;
            else if (a > 80 && a < 100) //      79 - 93     15 
                a = 3;
            return a;
        }
        public int Oran3(int a)
        {
            a = rnd.Next(0, 100);
            if (a < 61) //                0 - 53      54
                a = 1;
            else if (a > 60 && a < 81) //     54 - 78      25
                a = 2;
            else if (a > 80 && a < 100) //      79 - 93     15 
                a = 3;
            return a;
        }

        public int Para(int a, int c)
        {
            if (a == 1)
                a = 1 * c;
            else if (a == 2)
                a = 2 * c;
            else if (a == 3)
                a = 5 * c;
            else if (a == 4)
                a = 10 * c;
            else if (a == 5)
                a = 50 * c;
            else if (a == 6)
                a = 100 * c;
            return a;
        }
        #endregion

        Random rnd = new Random();
        private void Form1_Load(object sender, EventArgs e)
        {
            timer.Stop();
            timer1.Start();
            serialPort1.Open();
        }
        YonetimPaneli yp = new YonetimPaneli();
        private void button1_Click(object sender, EventArgs e)
        {


            if (Convert.ToInt32(Coin.Text) < 1)
            {
                MessageBox.Show("Yetersiz Bakiye Lütfen Para Atınız!! ");
                btnTurn.Hide();
            }
            else if ((Convert.ToInt32(Coin.Text) - Convert.ToInt32(xCoin.Text)) >= 0)
            {
                timer.Start();
                Coin.Text = (Convert.ToInt32(Coin.Text) - Convert.ToInt32(xCoin.Text)).ToString();
                //
                ArrayList okunanlar = HotelLoad();

                using (StreamWriter sw = new StreamWriter(path))
                {

                    if (okunanlar.Count > 0)
                    {
                        foreach (string otel in okunanlar)
                        {
                            sw.WriteLine(otel);
                        }
                    }
                    for (int i = 0; i < Convert.ToInt32(xCoin.Text); i++)
                    {
                        sw.WriteLine(string.Format("{0}", DateTime.Now));
                    }
                    
                    sw.Close();
                }
                OtelYukle();
                //

            }


        }
        int sayac = 0;
        int a;
        int b;
        int c;
        private void timer1_Tick(object sender, EventArgs e)
        {
            /*
            //Oran//
            rmd(0,100)
            1.   50  (0,50)
            2.   30  (50,80)
            3.   10  (80,90)
            4.   4   (90,94)
            5.   3   (94,97)
            6.   2   (97,99)
            7.   1   (99,100)
           */
            sayac++;
            if (sayac <= 26)
            {
                a = rnd.Next(0, 100);
                b = rnd.Next(0, 100);
                c = rnd.Next(0, 100);
                pb1.Image = iList.Images[rnd.Next(1, 7)];
                pBox4.Image = iList.Images[rnd.Next(1, 7)];
                pBox7.Image = iList.Images[rnd.Next(1, 7)];
                pb2.Image = iList.Images[rnd.Next(1, 7)];
                pBox5.Image = iList.Images[rnd.Next(1, 7)];
                pBox8.Image = iList.Images[rnd.Next(1, 7)];
                pb3.Image = iList.Images[rnd.Next(1, 7)];
               pBox6.Image = iList.Images[rnd.Next(1, 7)];
               pBox9.Image = iList.Images[rnd.Next(1, 7)];
            }
            else
            {
                int kart1 =  Oran(a);
                int kart2 =  Oran(b);
                int kart3 =  Oran(c);
                pb1.Image = iList.Images[kart1];//kart1];
                pb2.Image = iList.Images[kart2];//kart2];
                pb3.Image = iList.Images[kart3];//kart3];
                timer.Stop();
                if (kart1 == kart2 && kart2 == kart3)
                {
                    label5.Text = "Tebrikler" + "\n" + Para(kart1, Convert.ToInt32(xCoin.Text)) + "TL Kazandınız";
                    sayac = 0;

                    ArrayList okunanlar1 = CoinLoad();
                    using (StreamWriter sw1 = new StreamWriter(path1))
                    {
                       if (okunanlar1.Count > 0)
                       {
                            foreach (string otel1 in okunanlar1)
                           {
                               sw1.WriteLine(otel1);
                           }
                        }
                        for (int i = 0; i < Para(kart1, Convert.ToInt32(xCoin.Text)); i++)
                        {
                            sw1.WriteLine(string.Format("{0}", Para(kart1, Convert.ToInt32(xCoin.Text))));
                        }
                        
                        sw1.Close();
                    }
                    CoinYukle();
                    

                }
                else
                {
                    label5.Text = "Kaybettiniz\nTekrar Deneyin";
                    sayac = 0;

                }
            }
            //else
            //{
            //    kart1 = Oran(a);
            //    pb1.Image = iList.Images[kart1];//kart1];
            //    timer.Stop();
            //    sayac = 0;
            //}


        }

        private void addCoin_Click(object sender, EventArgs e)
        {//
            Coin.Text = (Convert.ToInt32(Coin.Text) + 1).ToString();
            if (Convert.ToInt32(Coin.Text) == 1)
            {
                btnTurn.Show();
            }
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            if (Convert.ToInt32(xCoin.Text) == 3)
            {
                xCoin.Text = 3.ToString();
            }
            else
            {
                xCoin.Text = (Convert.ToInt32(xCoin.Text) + 1).ToString();
            }
        }
        private void button2_Click(object sender, EventArgs e)
        {

            if (Convert.ToInt32(xCoin.Text) == 1)
            {
                xCoin.Text = 1.ToString();
            }
            else
            {
                xCoin.Text = (Convert.ToInt32(xCoin.Text) - 1).ToString();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Home hm = new Home();
            hm.Show();
            this.Hide();
        }

        private void btnYonetim_Click(object sender, EventArgs e)
        {
            YonetimPaneli yonetim = new YonetimPaneli();
                yonetim.Show();


        }

        private void timer1_Tick_1(object sender, EventArgs e)
        {
            try
            {
                string oku = serialPort1.ReadLine();
                if (oku == "C\r")
                {
                    Coin.Text = (Convert.ToInt32(Coin.Text) + 1).ToString();
                }
            }
            catch (Exception)
            {
                MessageBox.Show("Arduino PortBağlı Değil");
            }
        }
    }
        }
    

//{
//    int kart1 = Oran(a);
//    int kart2 = Oran(b);
//    int kart3 = Oran(c);
//    pb1.Image = iList.Images[kart1];//kart1];
//    pb2.Image = iList.Images[kart2];//kart2];
//    pb3.Image = iList.Images[kart3];//kart3];
//    timer.Stop();
//    if (kart1 == kart2 && kart2 == kart3)
//    {
//        label5.Text = "Tebrikler" + "\n" + Para(kart1, Convert.ToInt32(xCoin.Text)) + "TL Kazandınız";
//        sayac = 0;
//        //
//        ArrayList okunanlar = HotelLoad();

//        using (StreamWriter sw = new StreamWriter(path1))
//        {

//            if (okunanlar.Count > 0)
//            {
//                foreach (string otel in okunanlar)
//                {
//                    sw.WriteLine(otel);
//                }
//            }

//            sw.WriteLine(string.Format("{0}", Convert.ToInt32(xCoin.Text)) + "TL" );
//            sw.Close();
//        }
//        OtelYukle();
//        //

//    }
//    else
//    {
//        label5.Text = "Kaybettiniz\nTekrar Deneyin";
//        sayac = 0;

//    }

//}