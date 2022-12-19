var filePath = args.FirstOrDefault();

Console.WriteLine($" *** Build Pico C using file {filePath} *** ");

filePath = filePath?.Trim('"');

if (!File.Exists(filePath))
{
    Console.Write("Enter *.c file to build: ");
    filePath = Console.ReadLine();
    filePath = filePath?.Trim('"');
    if (!File.Exists(filePath))
        return 1;
}

var content = File.ReadAllText(filePath);

const string startTerm = "// Copy script from here\r\n";

var index = content.IndexOf(startTerm, StringComparison.Ordinal);

content = content.Remove(0, index + startTerm.Length);

content = content.Replace("// Delete main\r\nint main() {\r\n// Delete main\r\n", "", StringComparison.Ordinal);
content = content.Replace("// Delete main end\r\n}\r\n// Delete main end", "", StringComparison.Ordinal);
content = content.Trim('\r', '\n');

var outputPath = Path.Combine(Path.GetDirectoryName(filePath) ?? throw new InvalidOperationException(), Path.GetFileNameWithoutExtension(filePath) + ".picoc");

File.WriteAllText(outputPath, content);

return 0;