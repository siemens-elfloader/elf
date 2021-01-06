using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;
using System.Drawing.Text;

namespace font2png
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class font2png
	{
		string iniFileName = "font.ini";
		IniFile iniFile;

		// Font parameters
		int width, height;
		string fontFace;
		int fontSize;
		TextRenderingHint antiAlias;
		string fileName;
		bool alpha;
		Bitmap bmpFont;
		Color foreColor;
		Color backColor;

		bool isUnicode = false;
		int startChar = 0;
		int endChar = 256;
		int cols = 16;

		public font2png()
		{
		}

		private string ToPSPHex(Color c)
		{
			// RGB of Color are 8 bits, we want 5
			int r = c.R >> 3;
			int g = c.G >> 3;
			int b = c.B >> 3;
			
			// Color ordering is x-B-G-R 1555
			int color = r | (g << 5) | (b << 10);
			return "0x" + color.ToString("X");
		}

		private void saveFont()
		{
			bmpFont.Save(fileName, System.Drawing.Imaging.ImageFormat.Png);
		}

		private void makeFont()
		{
			bmpFont = new Bitmap(width * cols, height * ((endChar - startChar) / cols));
	
			Graphics bmpG = Graphics.FromImage(bmpFont);
			Font fnt = new Font(fontFace, fontSize);
			bmpG.TextRenderingHint = antiAlias;
			Brush fntBrush = new SolidBrush(foreColor);

			if(alpha)
			{
				bmpG.Clear(Color.Transparent);
			}
			else
			{
				bmpG.Clear(backColor);
			}
			
			
			byte[] bytArray = new byte[8];
			for (int i = startChar; i < endChar; i++)
			{
				string s = null;
				if(!isUnicode)
				{
					bytArray[0] = (byte)i;
					s = System.Text.ASCIIEncoding.ASCII.GetString(bytArray, 0, 1);
				}
				else
				{
					int blen = 0;
					int tempi = i;
					while(tempi != 0)
					{
						tempi /= 256;
						blen += 1;
					}
					tempi = i;
					for(int j = 0; j < blen; j++)
					{
						bytArray[j] = (byte)(tempi & 0xFF);
						tempi = tempi >> 8;
					}
					s = System.Text.UnicodeEncoding.Unicode.GetString(bytArray, 0, blen);
				}
			
				int bmpX = (i % cols) * width;
				int bmpY = (i / cols) * height;

				bmpG.DrawString(s, fnt, fntBrush, bmpX, bmpY);
			}
		}

		private void assertIniFile()
		{
			iniFile.assertKeyExists("font", "width"); 
			iniFile.assertKeyExists("font", "height");
			iniFile.assertKeyExists("font", "fontName");
			iniFile.assertKeyExists("font", "fontSize");
			iniFile.assertKeyExists("font", "antiAlias");
			iniFile.assertKeyExists("font", "outputFile");
			iniFile.assertKeyExists("font", "alpha");
			iniFile.assertKeyExists("font", "backColor");
			iniFile.assertKeyExists("font", "foreColor");
		}
		
		private Color stringToColor(string str)
		{
			int iVal = int.Parse(str, System.Globalization.NumberStyles.HexNumber);
			return Color.FromArgb(iVal);
		}

		private void parseIniSettings()
		{
			width = int.Parse(iniFile.getValue("font", "width"));
			height = int.Parse(iniFile.getValue("font", "height"));
			fontSize = int.Parse(iniFile.getValue("font", "fontSize"));
			fontFace = iniFile.getValue("font", "fontName");
            fileName = iniFile.getValue("font", "outputFile");
			alpha = bool.Parse(iniFile.getValue("font", "alpha"));
            
			string smoothStr = iniFile.getValue("font", "antiAlias");
			if(smoothStr == "none")
			{
				antiAlias = TextRenderingHint.SingleBitPerPixelGridFit;
			}
			else if(smoothStr == "simple")
			{
				antiAlias = TextRenderingHint.AntiAliasGridFit;
			}
			else if(smoothStr == "subpixel")
			{
				antiAlias = TextRenderingHint.ClearTypeGridFit;
			}
			else
			{
				throw new Exception("Invalid antiAlias setting");
			}
			
			backColor = stringToColor(iniFile.getValue("font", "backColor"));
			foreColor = stringToColor(iniFile.getValue("font", "foreColor"));
			

			string unicodeStart = iniFile.getValue("unicode", "startChar");
			if(unicodeStart != null)
			{
				startChar = int.Parse(unicodeStart, System.Globalization.NumberStyles.HexNumber);
				isUnicode = true;
			}

			iniFile.assertKeyExists("unicode", "endChar");
			endChar = int.Parse(iniFile.getValue("unicode", "endChar"), System.Globalization.NumberStyles.HexNumber);
			
			string colsStr = iniFile.getValue("unicode", "cols");

			if(colsStr != null)
			{
				cols = int.Parse(colsStr);
			}

		}

		private void displayUsage()
		{
			System.Console.Out.WriteLine("font2png [font]");
			System.Console.Out.WriteLine(" font is the name of the ini file used to make the font.");
			System.Console.Out.WriteLine(" If font is not specified, font.ini will be used.");
		}

		private void processCommandLine(string [] args)
		{
			if(args.Length == 0)
			{
				iniFile = new IniFile("font.ini");
			}
			else if(args.Length == 1)
			{
				if(args[0] == "-?")
				{
					displayUsage();
					return;
				}
				iniFile = new IniFile(iniFileName);
			}
			else
			{
				displayUsage();
				return;
			}
		}

		private void run(string[] args)
		{
			processCommandLine(args);
			assertIniFile();
			parseIniSettings();	
			makeFont();
			saveFont();
		}

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args) 
		{
			try
			{
				new font2png().run(args);
			}
			catch(Exception e)
			{
				System.Console.Out.WriteLine("־רטבךא: " + e.Message);
                System.Console.In.Read();
				return;
			}
			System.Console.Out.WriteLine("״נטפע סמחהאם!");
		}


	}
}

