using System;
using System.IO;
using System.Collections;
using System.Text.RegularExpressions;


namespace font2png
{
	/// <summary>
	/// Simple class to read an ini file, in the following format:
	/// [section]
	/// name=value ; Comment
	/// </summary>
	public class IniFile
	{
		Hashtable sections = new Hashtable();

		private string trimSpaces(string str)
		{
			string s = Regex.Replace(str, "^ *", "");
			s = Regex.Replace(s, " *$", "");
			return s;
		}
		
		public void assertKeyExists(string section, string id)
		{
			if(!sections.ContainsKey(section))
			{
				throw new Exception("Section not found in ini file: " + section); 
			}

			Hashtable sectionHash = (Hashtable)sections[section];
			if(!sectionHash.ContainsKey(id))
			{
				throw new Exception("Key not found in ini file: " + section + ":" + id); 
			}
		}

		public string getValue(string section, string id)
		{
			string ret = null;
			if(sections.ContainsKey(section))
			{
				Hashtable sectionHash = (Hashtable)sections[section];
				if(sectionHash.ContainsKey(id))
				{
					ret = (string)sectionHash[id];
				}
			}
			return ret;
		}

		public IniFile(string fname)
		{
			using (StreamReader sr = new StreamReader(fname))
			{
				string file = sr.ReadToEnd();
				file = file.Replace("\r\n", "\n");
				file = file.Replace("\t", " ");
				string []lines = file.Split('\n');

				// Remove comments
				for (int i = 0; i < lines.Length; i++)
				{
					int index = lines[i].IndexOf(";");
					if(index != -1)
					{
						lines[i] = lines[i].Substring(0, index - 1);
					}
				}

                
				Hashtable curSection = new Hashtable();
				sections[""] = curSection;

				// Read values
				for (int i = 0; i < lines.Length; i++)
				{
					if (lines[i].Length == 0) continue;

					if (lines[i][0] == '[')
					{
						int index = lines[i].IndexOf("]");
						if (index != -1)
						{
							// This is a section identifier
							string curSectionName = lines[i].Substring(1, index - 1);
							curSection = new Hashtable();
							sections[curSectionName] = curSection;
							
						}
						else
						{
							throw new Exception("Bad section identifier at line " + i.ToString());
						}
					}
					else if (lines[i].IndexOf("=") != -1)
					{
						int index = lines[i].IndexOf("=");
						string id = lines[i].Substring(0, index);
						id = trimSpaces(id);
						string val = lines[i].Substring(index + 1);
						val = trimSpaces(val);
						curSection[id] = val;
					}
				}
			}
		}
	}
}
