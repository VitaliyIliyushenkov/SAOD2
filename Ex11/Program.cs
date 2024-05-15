using System;
using System.Text.RegularExpressions;
using System.IO;
using System.Xml;


namespace RegExpLab
{
    class Program
    {
        static void Main(string[] args)
        {
            string str = " фыидо, fjbld33- 2олт?";
            Console.WriteLine(str);

            // регулярное выражение, которое соответствует любому слову, включающему хотя бы одну цифру.
            //Regex re = new Regex(@"\w*\d+\w*");

            //регулярное выражение, которое находит все слова со сдвоенными символами.
            //Regex re = new Regex(@"\b(\w)+(\1+)+\w*\b");

            //регулярное выражение, которое выберет слова только с латинскими буквами и цифрами. 
            //Regex re = new Regex(@"\b[a-zA-Z0-9]+\b");

            //регулярное выражение, которое выберет слова, имеющие хотя бы одну латинскую букву.
            //Regex re = new Regex(@"\b[a-zA-Z]+\w*\b");

            Regex re = new Regex(@"\b(\w)+(\1+)+\w*\b");

            MatchCollection mc = re.Matches(str);
            foreach (var m in mc)
                Console.WriteLine(m);

            string input = "Привет, как дела? У меня все хорошо!";
            re = new Regex(@"(\W*)(\w+)(\W+)(\w+)(\W+)(\w+)(\W*)");
            Console.WriteLine(re.Replace(input, "$1$4$3$2$5$6$7"));

            string orig;
            try
            {
                using (StreamReader sr = new StreamReader("CreateDB.sql"))
                {
                    orig = sr.ReadToEnd();
                    Console.WriteLine(orig.Length);
                }

            }
            catch (Exception ex)
            {
                Console.WriteLine("Ошибкачтенияфайла: \"CreateDB.sql\"\n{0}", ex);
                return;
            }

            Regex regex = new Regex(@"\(\s*(?!\d+(,\s*\d+)*\s*)\w+(\s*,\s*\w+)*\s*\)");
            MatchCollection matches = regex.Matches(orig);
            Console.WriteLine($"Количество совпадений: {matches.Count}");

            string transformed = orig;
            transformed = Regex.Replace(transformed, @"(GO\r?\n)|(SET.*\r?\n)", "", RegexOptions.Multiline);
            transformed = Regex.Replace(transformed, @"\[.*\]\.\[(.*?)\]", "$1", RegexOptions.Multiline);
            transformed = Regex.Replace(transformed, @"\[(.*?)\]", "$1", RegexOptions.Multiline);
            transformed = Regex.Replace(transformed, @"IDENTITY\(1,1\)", "AUTO_INCREMENT", RegexOptions.Multiline);
            transformed = Regex.Replace(transformed, @"timestamp", "timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP", RegexOptions.Multiline);
            transformed = Regex.Replace(transformed, @"PRIMARY KEY CLUSTERED \((.*?)\) WITH \(.+?\) ON \[PRIMARY\]", "PRIMARY KEY ($1)", RegexOptions.Multiline);
            transformed = Regex.Replace(transformed, @"PRIMARY KEY NONCLUSTERED \((.*?)\) WITH \(.+?\) ON \[PRIMARY\]", "PRIMARY KEY ($1)", RegexOptions.Multiline);
            transformed = Regex.Replace(transformed, @"UNIQUE NONCLUSTERED \((.*?)\) WITH \(.+?\) ON \[PRIMARY\]", "UNIQUE KEY ($1)", RegexOptions.Multiline);
            transformed = Regex.Replace(transformed, @"ON \[PRIMARY\]\s*;?", ";", RegexOptions.Multiline);
            transformed = Regex.Replace(transformed, @"uniqueidentifier", "char(32)", RegexOptions.Multiline);
            transformed = Regex.Replace(transformed, @"xml\s*\(\d+\)", "text", RegexOptions.Multiline);
            transformed = Regex.Replace(transformed, @"ntext", "text", RegexOptions.Multiline);
            transformed = Regex.Replace(transformed, @"nvarchar\(max\)", "text", RegexOptions.Multiline);
            transformed = Regex.Replace(transformed, @"image", "BLOB", RegexOptions.Multiline);
            transformed = Regex.Replace(transformed, @"varbinary\(max\)", "BLOB", RegexOptions.Multiline);
            transformed = Regex.Replace(transformed, @"^\s*$\n", "", RegexOptions.Multiline);

            try
            {
                using (StreamWriter sw = new StreamWriter("CreateDB_MySQL.sql"))
                {
                    sw.Write(transformed);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Ошибка сохранения в файл: \"CreateDB_MySQL.sql\"\n{0}", ex);
                return;
            }

            Console.WriteLine("Файл CreateDB_MySQL.sql успешно создан.");

        }
    }
}
