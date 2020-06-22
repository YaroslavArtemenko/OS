using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace WindowsFormsApp2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            var fl = string.Empty;
            Stream myStream;
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            if (openFileDialog1.ShowDialog()==DialogResult.OK)
            {
                fl = openFileDialog1.FileName;
                richTextBox1.Clear();
                richTextBox1.Text = File.ReadAllText(fl);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var fl = string.Empty;
            Stream myStream;
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();

            saveFileDialog1.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            saveFileDialog1.FilterIndex = 2;
            saveFileDialog1.RestoreDirectory = true;
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                fl = saveFileDialog1.FileName;
                File.WriteAllText(fl, richTextBox1.Text);
                MessageBox.Show("Файл сохранен успешно.");
            }
            richTextBox1.Clear();
        }
    }
}
