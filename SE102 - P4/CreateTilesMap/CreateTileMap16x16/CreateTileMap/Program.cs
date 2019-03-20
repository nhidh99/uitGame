using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Security.Cryptography;

namespace CreateTileMap
{
    class Program
    {
        // Kiểm tra 2 Bitmap có giống nhau (dùng cho HashSet và so sánh)
        class TileComparer : IEqualityComparer<Bitmap>
        {
            public bool Equals(Bitmap bmp1, Bitmap bmp2)
            {
                ImageConverter converter = new ImageConverter();

                var bmpBytes1 = new byte[1];
                var bmpBytes2 = new byte[1];

                bmpBytes1 = (byte[])converter.ConvertTo(bmp1, bmpBytes1.GetType());
                bmpBytes2 = (byte[])converter.ConvertTo(bmp2, bmpBytes2.GetType());

                SHA256Managed sha = new SHA256Managed();
                byte[] bmpHash1 = sha.ComputeHash(bmpBytes1);
                byte[] bmpHash2 = sha.ComputeHash(bmpBytes2);
                return bmpHash1.SequenceEqual(bmpHash2);
            }

            public int GetHashCode(Bitmap bmp)
            {
                return bmp.ToString().ToLower().GetHashCode();
            }
        }

        // Tạo Ma trận gồm các Tile 16x16
        static List<List<Bitmap>> CreateMap16x16Tile(string fileName)
        {
            var result = new List<List<Bitmap>>();
            Bitmap MapTiles = new Bitmap(fileName);

            var cols = MapTiles.Width >> 4;
            var rows = MapTiles.Height >> 4;

            for (var i = 0; i < rows; ++i)
            {
                var RowTiles = new List<Bitmap>();
                for (var j = 0; j < cols; ++j)
                {
                    var rect = new Rectangle(j << 4, i << 4, 16, 16);
                    var tile = MapTiles.Clone(rect, MapTiles.PixelFormat);
                    RowTiles.Add(tile);
                }
                result.Add(RowTiles);
            }
            return result;
        }

        // Tạo Set các Tile 16x16
        static HashSet<Bitmap> CreateSet16x16Tile(List<List<Bitmap>> MapTiles)
        {
            var Tiles = MapTiles.SelectMany(x => x).ToList();
            return new HashSet<Bitmap>(Tiles, new TileComparer());
        }

        // Tạo ma trận file text các Tile 16x16 được đánh số theo SetTiles
        static List<List<int>> CreateMatrix16x16Tile(List<List<Bitmap>> MapTiles)
        {
            var MatrixTiles = new List<List<int>>();
            var SetTiles = CreateSet16x16Tile(MapTiles).ToList();
            var TileComparer = new TileComparer();

            foreach (var RowTiles in MapTiles)
            {
                var Row = new List<int>();
                foreach (var Tile in RowTiles)
                {
                    foreach (var TypeTile in SetTiles)
                    {
                        if (TileComparer.Equals(TypeTile, Tile))
                        {
                            Row.Add(SetTiles.IndexOf(TypeTile));
                            break;
                        }
                    }
                }
                MatrixTiles.Add(Row);
            }
            return MatrixTiles;
        }

        // Tạo Tiles Bitmap bằng cách thêm các Bitmap từ SetTiless
        static Bitmap CreateTilesBitmap(HashSet<Bitmap> SetTiles)
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
            var ImagePath = Path.GetFullPath("lv1.png");
            var TextPath = Path.GetFullPath("matrix.txt");
            var TilesPath = Path.GetFullPath("tiles.png");
            var MapTiles = CreateMap16x16Tile(ImagePath);
            var SetTiles = CreateSet16x16Tile(MapTiles);

            using (var sw = new StreamWriter(TextPath))
            {
                var MatrixTiles = CreateMatrix16x16Tile(MapTiles);

                sw.WriteLine("{0} {1} {2}", SetTiles.Count, MapTiles[0].Count, MapTiles.Count);
                foreach (var RowTiles in MatrixTiles)
                {
                    sw.WriteLine(string.Join(" ", RowTiles));
                }
            }

            var TilesBitmap = CreateTilesBitmap(SetTiles);
            TilesBitmap.Save(TilesPath);

            Console.WriteLine("Success");
            Console.ReadKey();
        }
    }
}