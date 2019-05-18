using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;

namespace CreateTileMap
{
    class Program
    {
        // Kiểm tra 2 Bitmap có giống nhau (dùng cho HashSet và so sánh)
        public static bool IsEqualBitmap(Bitmap bmp1, Bitmap bmp2)
        {
            if (object.Equals(bmp1, bmp2))
                return true;

            int bytes = bmp1.Width * bmp1.Height * (Image.GetPixelFormatSize(bmp1.PixelFormat) / 8) - 1;

            bool result = true;
            var b1bytes = new byte[bytes];
            var b2bytes = new byte[bytes];

            var bitmapData1 = bmp1.LockBits(new Rectangle(0, 0, bmp1.Width, bmp1.Height), ImageLockMode.ReadOnly, bmp1.PixelFormat);
            var bitmapData2 = bmp2.LockBits(new Rectangle(0, 0, bmp2.Width, bmp2.Height), ImageLockMode.ReadOnly, bmp2.PixelFormat);

            Marshal.Copy(bitmapData1.Scan0, b1bytes, 0, bytes);
            Marshal.Copy(bitmapData2.Scan0, b2bytes, 0, bytes);

            for (int n = 0; n < bytes; ++n)
            {
                if (b1bytes[n] != b2bytes[n])
                {
                    result = false;
                    break;
                }
            }

            bmp1.UnlockBits(bitmapData1);
            bmp2.UnlockBits(bitmapData2);

            return result;
        }

        // Tạo Set các Tile 16x16 (đồng thời lưu ma trận số các tiles)
        static List<List<int>> MapTiles = new List<List<int>>();
        static List<Bitmap> CreateSet16x16Tiles(string fileName)
        {
            var result = new List<Bitmap>();
            var bmp = new Bitmap(fileName);
            var cols = bmp.Width >> 4;
            var rows = bmp.Height >> 4;

            for (var i = 0; i < rows; ++i)
            {
                var RowTiles = new List<int>();

                for (var j = 0; j < cols; ++j)
                {
                    var rect = new Rectangle(j << 4, i << 4, 16, 16);
                    var tile = new Bitmap(16, 16);

                    using (var g = Graphics.FromImage(tile))
                    {
                        g.DrawImage(bmp, new Rectangle(0, 0, 16, 16), rect, GraphicsUnit.Pixel);
                    }

                    bool isContainTile = false;
                    foreach (var t in result)
                    {
                        if (IsEqualBitmap(t, tile))
                        {
                            isContainTile = true;
                            RowTiles.Add(result.IndexOf(t));
                            break;
                        }
                    }

                    if (!isContainTile)
                    {
                        RowTiles.Add(result.Count);
                        result.Add(tile);
                    }
                }
                MapTiles.Add(RowTiles);
            }
            return result;
        }

        // Tạo bitmap các Tile
        static Bitmap CreateTilesBitmap(List<Bitmap> SetTiles)
        {
            var bmp = new Bitmap(SetTiles.Count << 4, 16);

            using (Graphics g = Graphics.FromImage(bmp))
            {
                for (int i = 0; i < SetTiles.Count; ++i)
                {
                    g.DrawImage(SetTiles.ElementAt(i), i << 4, 0);
                }
            }
            return bmp;
        }

        // Thực thi
        static void Main(string[] args)
        {
            var bmpPath = Path.GetFullPath("lv1.png");
            var TextPath = Path.GetFullPath("matrix.txt");
            var TilesPath = Path.GetFullPath("tiles.png");
            var SetTiles = CreateSet16x16Tiles(bmpPath);

            using (var sw = new StreamWriter(TextPath))
            {
                sw.WriteLine("{0} {1} {2}", SetTiles.Count, MapTiles[0].Count, MapTiles.Count);
                foreach (var RowTiles in MapTiles)
                {
                    sw.WriteLine(string.Join(" ", RowTiles));
                }
            }

            var TilesBitmap = CreateTilesBitmap(SetTiles);
            TilesBitmap.Save(TilesPath);
        }
    }
}