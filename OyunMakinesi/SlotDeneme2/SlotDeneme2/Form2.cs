using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SlotDeneme2
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }
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
                a = 20 * c;
            else if (a == 6)
                a = 50 * c;
            else if (a == 7)
                a = 100 * c;
            return a;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            label5.Text = "";
            if (Convert.ToInt32(Coin.Text) < 1)
            {
                MessageBox.Show("Yetersiz Bakiye Lütfen Para Atınız!! ");
                btnTurn.Hide();
            }
            else if ((Convert.ToInt32(Coin.Text) - Convert.ToInt32(xCoin.Text)) >= 0)
            {
                timer.Start();
                Coin.Text = (Convert.ToInt32(Coin.Text) - Convert.ToInt32(xCoin.Text)).ToString();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {

            Coin.Text = (Convert.ToInt32(Coin.Text) + 1).ToString();
            if (Convert.ToInt32(Coin.Text) == 1)
            {
                btnTurn.Show();
            }
        }

        private void button5_Click(object sender, EventArgs e)
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

        private void button4_Click(object sender, EventArgs e)
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
        Random rnd = new Random();
        int a; int b; int c;
        int sayac = 0;
        private void timer_Tick(object sender, EventArgs e)
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
            if (sayac <= 25)
            {
                a = rnd.Next(0, 100);
                b = rnd.Next(0, 100);
                c = rnd.Next(0, 100);

                pb1.Image = iList.Images[rnd.Next(1, 7)];
                pb2.Image = iList.Images[rnd.Next(1, 7)];
                pb3.Image = iList.Images[rnd.Next(1, 7)];
                pBox4.Image = iList.Images[rnd.Next(1, 7)];
                pBox5.Image = iList.Images[rnd.Next(1, 7)];
                pBox6.Image = iList.Images[rnd.Next(1, 7)];
                pBox7.Image = iList.Images[rnd.Next(1, 7)];
                pBox8.Image = iList.Images[rnd.Next(1, 7)];
                pBox9.Image = iList.Images[rnd.Next(1, 7)];
            }
            else
            {
                int kart1 = Oran(a);
                int kart2 = Oran(b);
                int kart3 = Oran(c);
                pb1.Image = iList.Images[kart1];//kart1];
                pb2.Image = iList.Images[kart2];//kart2];
                pb3.Image = iList.Images[kart3];//kart3];
                timer.Stop();
                if (kart1 == kart2 && kart2 == kart3)
                {
                    label5.Text = "Tebrikler" + "\n" + Para(kart1, Convert.ToInt32(xCoin.Text)) + "TL Kazandınız";
                    sayac = 0;

                }
                else
                {
                    label5.Text = "Kaybettiniz\nTekrar Deneyin";
                    sayac = 0;
                }

            }
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            Home hm = new Home();
            hm.Show();
            this.Hide();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            YonetimPaneli yonetim = new YonetimPaneli();
            yonetim.Show();
        }
    }
}
