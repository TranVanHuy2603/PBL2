#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define MAP_SIZE 1000

int generate_map_main() {
    // Tạo thư mục assets (trên Windows cần dùng "mkdir assets" thay vì -p)
#ifdef _WIN32
    system("mkdir assets");
#else
    system("mkdir -p assets");
#endif

    std::ofstream outFile("assets/mapdata.txt");
    if (!outFile.is_open()) {
        std::cerr << "Không thể tạo file assets/mapdata.txt\n";
        return 1;
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            int dist = std::abs(i - MAP_SIZE / 2) + std::abs(j - MAP_SIZE / 2);
            int type;

            if (dist > 400) type = 4;                  // Water
            else if (dist > 300) type = (std::rand() % 2 ? 7 : 0); // Sand hoặc Grass
            else if (dist > 200) type = std::rand() % 3;           // Grass–Forest–Hill
            else if (dist > 100) type = 6 + std::rand() % 3;       // Stone–Sand–Coal
            else if (dist > 50)  type = 8 + std::rand() % 3;       // Coal–Iron–Gold
            else                 type = 10 + std::rand() % 3;      // Gold–Diamond–Emerald

            outFile << type << " ";
        }
        outFile << "\n";
    }

    outFile.close();
    std::cout << "✅ Đã sinh thành công map " << MAP_SIZE << "x" << MAP_SIZE 
              << " trong assets/mapdata.txt\n";

    return 0;
}
