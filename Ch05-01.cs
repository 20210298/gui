using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Ch05
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            MessageBox.Show("바이염");
            Application.Exit();
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            Graphics g = CreateGraphics();
          
            Font drawFont = new Font("FixedSys", 16);
            SolidBrush drawBrush = new SolidBrush(Color.Black);

            float x = 0.0F;
            float y = 0.0F;
            float width = 200.0F;
            float height = 50.0F;
            RectangleF drawRect = new RectangleF(x, y, width, height);

            // 글자가 쓰여지는 부분을 회색으로 채운다
            Color backGray = Color.FromArgb(240, 240, 240);
            SolidBrush backBrush = new SolidBrush(backGray);
            g.FillRectangle(backBrush, drawRect);

            String str = string.Format("{0:d5} {1:d5}", e.X, e.Y);

            g.DrawString(str, drawFont, drawBrush, drawRect);

            g.Dispose();
        }

        private void mybtn1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("버튼 클릭함","알림");
        }

        private void mybtn1_MouseMove(object sender, MouseEventArgs e)
        {
            // g는 Form1의 객체이므로 Form1에서 좌표가 표시된다.
            Graphics g = CreateGraphics();

            /* 버튼에서 표시하고싶다면 아래와 같이
             Graphics g = mybtn1.CreateGraphics();*/

            Font drawFont = new Font("FixedSys", 12);
            SolidBrush drawBrush = new SolidBrush(Color.Red);

            float x = 0.0F;
            float y = 0.0F;
            float width = 200.0F;
            float height = 50.0F;
            RectangleF drawRect = new RectangleF(x, y, width, height);

            // 글자가 쓰여지는 부분을 회색으로 채운다
            Color backGray = Color.FromArgb(240, 240, 240);
            SolidBrush backBrush = new SolidBrush(backGray);
            g.FillRectangle(backBrush, drawRect);

            String str = string.Format("{0:d5} {1:d5}", e.X, e.Y);

            g.DrawString(str, drawFont, drawBrush, drawRect);

            g.Dispose();
        }
    }
}
