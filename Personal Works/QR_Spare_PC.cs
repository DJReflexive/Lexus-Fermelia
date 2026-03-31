/*
    Custom QR Code/.png Generator 

    Generates QR Codes with provided URLs, and in this example, 
    adds a logo to the center of the QR code. 

    It then composites the QR code with text information (name, serial, LSM code) 
    and instructions on how to use the QR code. 
    
    Finally, it saves each composite image as a .png file.
*/


using QRCoder;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Text;

class Program
{
    private static bool printOnlyOne = false;

    static void Main()
    {
        (string name, string serial, int lsmCode)[] spares =
        [
            ("CRSpare01", "MXL9161ZPK", 14678),
            ("CRSpare04", "MXL1284JGH", 14681),
            ("CRSpare05", "MXL1284JGF", 14680),
            ("CRSpare08", "MXL1284JGG", 14711),
            ("CRSpare10", "MXL01558JC", 14907),
            ("CRSpare11", "MXL01558JH", 14677),
            ("CRSpare12", "MXL01558JG", 14679),
            ("CRSpare13", "MXL01558H7", 14676),
            ("CRSpare14", "MXL208380N", 14817),
            ("CRSpare15", "MXL208380L", 14908),
            ("CRSpare16", "MXL0162C3P", 14906),
            ("CRSpare17", "MXL3213FML", 14909),
            ("CRSpare18", "MZ002X9Q",   15848),
            ("CRSpare19", "MZ00PPJV",   15849),
            ("CRSpare20", "MZ00PPJT",   15850),
            ("CRSpare21", "MXL2083804", 15761),
        ];

        string lsmUrl = "https://uwyo.talem3.com/lsm/item/main?code=";
        string instructions =
            "Instructions for moving Spare PC to New Location:\n" +
            " 1. Scan the QR Code\n" +
            " 2. Login with Credentials\n" +
            " 3. Update in the Editor the Location the PC is going to\n" +
            " 4. Press Save\n" +
            " 5. Finally, install or store the Spare PC in that Location\n" +
            "\nDo NOT skip these steps!";


        // For every spare pc, make a QR Code
        foreach (var spare in spares)
        {
            string fullUrl = lsmUrl + spare.lsmCode;

            // Output Folder
            string folder = "QR Codes";
            Directory.CreateDirectory(folder);

            // Output file path
            string filePath = Path.Combine(folder, spare.name + ".png");

            // Generate QR code
            QRCodeGenerator qrGenerator = new QRCodeGenerator();
            QRCodeData qrCodeData = qrGenerator.CreateQrCode(fullUrl, QRCodeGenerator.ECCLevel.Q);
            QRCode qrCode = new QRCode(qrCodeData);
            Bitmap qrImage = qrCode.GetGraphic(20);


            // ---------------------------
            // Add logo to center of QR
            // ---------------------------
            string logoPath = "logo.png";
            if (File.Exists(logoPath))
            {
                using (Bitmap logo = new Bitmap(logoPath))
                {
                    int logoSize = qrImage.Width / 4;   // adjust this number to taste

                    Bitmap resizedLogo = new Bitmap(logo, new Size(logoSize, logoSize));

                    using (Graphics g = Graphics.FromImage(qrImage))
                    {
                        g.CompositingQuality = System.Drawing.Drawing2D.CompositingQuality.HighQuality;
                        g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
                        g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

                        // Center position
                        int x = (qrImage.Width - logoSize) / 2;
                        int y = (qrImage.Height - logoSize) / 2;

                        // Draw white background square (slightly larger than logo)
                        int paddingAroundLogo = 1; // adjust for thicker/thinner border
                        g.FillRectangle(
                            Brushes.White,
                            x - paddingAroundLogo,
                            y - paddingAroundLogo,
                            logoSize + paddingAroundLogo * 2,
                            logoSize + paddingAroundLogo * 2
                        );

                        // Draw the logo on top
                        g.DrawImage(resizedLogo, x, y, logoSize, logoSize);
                    }

                    resizedLogo.Dispose();
                }
            }
            else
            {
                Console.WriteLine("WARNING: logo.png not found — QR codes generated without logo.");
            }


            // ---------------------------
            // Composite Image Layout
            // ---------------------------

            string nameText = $"{spare.name}";
            string serialText = $"Serial: {spare.serial}";
            string lsmText = $"LSM Code: {spare.lsmCode}";

            int padding = 20;

            // Left column width
            int leftColumnWidth = qrImage.Width + 40;

            // Right column width
            int rightColumnWidth = 1500;

            // Fonts
            Font bodyFont = new Font("Arial", 36, FontStyle.Regular);
            Font boldFont = new Font("Arial", 36, FontStyle.Bold);


            // Measure instructions height
            int instructionsHeight;
            using (Bitmap temp = new Bitmap(1, 1))
            using (Graphics g = Graphics.FromImage(temp))
            {
                SizeF size = g.MeasureString(instructions, bodyFont, rightColumnWidth);
                instructionsHeight = (int)Math.Ceiling(size.Height);
            }

            // Base height from left column content
            int leftColumnHeight =
                padding +
                qrImage.Height +
                padding +
                60 + // name
                60 + // serial
                60 + // lsm
                padding;

            int totalHeight = Math.Max(leftColumnHeight, instructionsHeight + padding * 2);

            // Create final bitmap
            Bitmap finalImage = new Bitmap(leftColumnWidth + rightColumnWidth, totalHeight);

            using (Graphics g = Graphics.FromImage(finalImage))
            {
                g.Clear(Color.White);
                g.TextRenderingHint = TextRenderingHint.AntiAlias;

                // Draw QR
                g.DrawImage(qrImage, padding, padding);


                // Center Serial + LSM horizontally
                int centerX = padding + (qrImage.Width / 2);

                // Name
                SizeF nameSize = g.MeasureString(nameText, bodyFont);
                g.DrawString(
                    nameText,
                    boldFont,
                    Brushes.Black,
                    centerX - nameSize.Width / 2,
                    padding + qrImage.Height + 20
                );

                // Serial
                SizeF serialSize = g.MeasureString(serialText, bodyFont);
                g.DrawString(
                    serialText,
                    bodyFont,
                    Brushes.Black,
                    centerX - serialSize.Width / 2,
                    padding + qrImage.Height + 20 + nameSize.Height + 10
                );

                // LSM Code
                SizeF lsmSize = g.MeasureString(lsmText, bodyFont);
                g.DrawString(
                    lsmText,
                    bodyFont,
                    Brushes.Black,
                    centerX - lsmSize.Width / 2,
                    padding + qrImage.Height + 20 + nameSize.Height + 10 + serialSize.Height + 10
                );


                // Center instructions vertically
                float instructionsY = (totalHeight - instructionsHeight) / 2f;

                RectangleF instructionsRect = new RectangleF(
                    leftColumnWidth,
                    instructionsY,
                    rightColumnWidth - padding,
                    instructionsHeight
                );

                g.DrawString(instructions, bodyFont, Brushes.Black, instructionsRect);
            }

            // Save final composite image
            finalImage.Save(filePath, ImageFormat.Png);

            // Cleanup
            qrImage.Dispose();
            finalImage.Dispose();

            Console.WriteLine($"{spare.name} saved as {spare.name}.png in ./{folder}/");

            if (printOnlyOne) break;
        }
    }
}