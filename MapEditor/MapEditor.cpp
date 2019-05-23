#include <fstream>
#include <vector>
#define TILE_SIZE 16
#define SCREEN_WIDTH 312
#define SCREEN_HEIGHT 176
#define CELL_WIDTH 156
#define CELL_HEIGHT 88

void CreateGridFile(int level)
{
	std::ifstream ifile;
	char fileGridName[30];
	sprintf_s(fileGridName, "Resources\\grid%d.txt", level);

	// Nếu không tìm thấy file grid -> Tạo file từ map objects trong level đó
	ifile.open(fileGridName);
	if (ifile.fail())
	{
		ifile.close();

		// Đọc file matrix để lấy size map -> xác định số cell trong grid
		char fileMapName[30];
		sprintf_s(fileMapName, "Resources\\matrix%d.txt", level);
		ifile.open(fileMapName);

		int numTiles, rowTiles, colTiles;
		ifile >> numTiles >> colTiles >> rowTiles;
		ifile.close();

		int colCell = ceil((float)(colTiles * TILE_SIZE) / (SCREEN_WIDTH >> 1));
		int rowCell = ceil((float)(rowTiles * TILE_SIZE) / (SCREEN_HEIGHT >> 1));

		// Tạo mảng cells chứa các object
		struct GameObject
		{
			char type;
			std::vector<int> value;
		};

		std::vector<std::vector<std::vector<GameObject*>>> cells;
		for (int i = 0; i < rowCell; ++i)
		{
			auto row = std::vector<std::vector<GameObject*>>();
			for (int j = 0; j < colCell; ++j)
			{
				auto col = std::vector<GameObject*>();
				row.push_back(col);
			}
			cells.push_back(row);
		}

		// Đọc từng loại object và đẩy vào grid (mỗi loại có thông số cách tính Rect khác nhau)
		char fileObjectsName[30];
		sprintf_s(fileObjectsName, "Resources\\objects%d.txt", level);
		ifile.open(fileObjectsName);

		while (!ifile.eof())
		{
			auto obj = new GameObject();
			Rect* rect = NULL;
			char type;

			ifile >> type;
			obj->type = type;

			switch (type)
			{
			case 'g': //ground: x, y, width, height
			{
				int value;
				for (int i = 0; i < 4; ++i)
				{
					ifile >> value;
					obj->value.push_back(value);
				}

				rect = new Rect(obj->value[0], obj->value[1], obj->value[2], obj->value[3]);
				break;
			}
			}

			// Xác định cell object đó và đẩy vào
			int LeftCell = rect->x / Cell::width;
			int RightCell = (rect->x + rect->width) / Cell::width;
			int TopCell = rect->y / Cell::height;
			int BottomCell = (rect->y - rect->height) / Cell::height;
			delete rect;

			for (int r = BottomCell; r <= TopCell; ++r)
			{
				for (int c = LeftCell; c <= RightCell; ++c)
				{
					cells[r][c].push_back(obj);
				}
			}
		}

		// Viết ra file grid
		std::ofstream ofile;
		ofile.open(fileGridName);
		ofile << colCell << " " << rowCell << "\n";

		for (int r = 0; r < rowCell; ++r)
		{
			for (int c = 0; c < colCell; ++c)
			{
				ofile << r << " " << c << " " << cells[r][c].size() << "\n";
				for (auto obj : cells[r][c])
				{
					ofile << obj->type;
					for (auto v : obj->value)
					{
						ofile << " " << v;
					}
					ofile << "\n";
				}
			}
		}

		//Sau khi có các thông số, xoá GridObject
		for (int r = 0; r < rowCell; ++r)
		{
			for (int c = 0; c < colCell; ++c)
			{
				int n = cells[r][c].size();
				for (int i = 0; i < n; ++i)
				{
					auto obj = cells[r][c][i];
					if (obj->value.size())
						delete obj;
				}
			}
		}

		ifile.close();
		ofile.close();

		ifile.close();
		ofile.close();
	}
	else ifile.close();
}

struct Rect
{
	float x, y;
	float width, height;

	Rect() {}
	Rect(float x, float y, float width, float height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
};

void CreateGridFile(int level)
{
	std::ifstream ifile;
	char fileGridName[30];
	sprintf_s(fileGridName, "Resources\\grid%d.txt", level);

	// Nếu không tìm thấy file grid -> Tạo file từ map objects trong level đó
	ifile.open(fileGridName);
	if (ifile.fail())
	{
		ifile.close();

		// Đọc file matrix để lấy size map -> xác định số cell trong grid
		char fileMapName[30];
		sprintf_s(fileMapName, "Resources\\matrix%d.txt", level);
		ifile.open(fileMapName);

		int numTiles, rowTiles, colTiles;
		ifile >> numTiles >> colTiles >> rowTiles;
		ifile.close();

		int colCell = ceil((float)(colTiles * TILE_SIZE) / (SCREEN_WIDTH >> 1));
		int rowCell = ceil((float)(rowTiles * TILE_SIZE) / (SCREEN_HEIGHT >> 1));

		// Tạo mảng cells chứa các object
		struct GameObject
		{
			char type;
			std::vector<int> value;
		};

		std::vector<std::vector<std::vector<GameObject*>>> cells;
		for (int i = 0; i < rowCell; ++i)
		{
			auto row = std::vector<std::vector<GameObject*>>();
			for (int j = 0; j < colCell; ++j)
			{
				auto col = std::vector<GameObject*>();
				row.push_back(col);
			}
			cells.push_back(row);
		}

		// Đọc từng loại object và đẩy vào grid (mỗi loại có thông số cách tính Rect khác nhau)
		char fileObjectsName[30];
		sprintf_s(fileObjectsName, "Resources\\objects%d.txt", level);
		ifile.open(fileObjectsName);

		while (!ifile.eof())
		{
			auto obj = new GameObject();
			Rect* rect = NULL;
			char type;

			ifile >> type;
			obj->type = type;

			switch (type)
			{
			case 'g': //ground: x, y, width, height
			{
				int value;
				for (int i = 0; i < 4; ++i)
				{
					ifile >> value;
					obj->value.push_back(value);
				}

				rect = new Rect(obj->value[0], obj->value[1], obj->value[2], obj->value[3]);
				break;
			}
			}

			// Xác định cell object đó và đẩy vào
			int LeftCell = rect->x / CELL_WIDTH;
			int RightCell = (rect->x + rect->width) / CELL_WIDTH;
			int TopCell = rect->y / CELL_HEIGHT;
			int BottomCell = (rect->y - rect->height) / CELL_HEIGHT;
			delete rect;

			for (int r = BottomCell; r <= TopCell; ++r)
			{
				for (int c = LeftCell; c <= RightCell; ++c)
				{
					cells[r][c].push_back(obj);
				}
			}
		}

		// Viết ra file grid
		std::ofstream ofile;
		ofile.open(fileGridName);
		ofile << colCell << " " << rowCell << "\n";

		for (int r = 0; r < rowCell; ++r)
		{
			for (int c = 0; c < colCell; ++c)
			{
				ofile << r << " " << c << " " << cells[r][c].size() << "\n";
				for (auto obj : cells[r][c])
				{
					ofile << obj->type;
					for (auto v : obj->value)
					{
						ofile << " " << v;
					}
					ofile << "\n";
				}
			}
		}

		//Sau khi có các thông số, xoá GridObject
		for (int r = 0; r < rowCell; ++r)
		{
			for (int c = 0; c < colCell; ++c)
			{
				int n = cells[r][c].size();
				for (int i = 0; i < n; ++i)
				{
					auto obj = cells[r][c][i];
					if (obj->value.size())
						delete obj;
				}
			}
		}

		ifile.close();
		ofile.close();
	}
	else ifile.close();
}

int main()
{
	CreateGridFile(1);
	return 0;
}