#include "Map.h"
#include <SFML/System/FileInputStream.hpp>
#include <SFML/System/FileOutputStream.hpp>
#include <cstdio> // dùng cho fopen, fscanf, fprintf

Map::Map() {
    width = 0;
    height = 0;
    grid = nullptr;
}

Map::~Map() {
    if (grid) {
        for (int i = 0; i < height; i++)
            delete[] grid[i];
        delete[] grid;
    }
}

int Map::get_width() const { return width; }
int Map::get_height() const { return height; }
Tile* Map::get_tile(int x, int y) const {
    if (!grid || x < 0 || y < 0 || x >= width || y >= height)
        return nullptr;
    return &grid[y][x];
}

void Map::load_File(const char* filename, EntityManager* entityManager) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Cannot open map file: %s\n", filename);
        return;
    }

    // đọc dữ liệu tile
    const int MAX_LINE = 1024;
    char line[MAX_LINE];
    int rowCount = 0;
    int colCount = 0;

    // đếm số hàng và cột trước
    while (fgets(line, MAX_LINE, file)) {
        if (line[0] == '#' || line[0] == '\n') break; // đến phần #ENTITIES
        int count = 0;
        const char* p = line;
        while (*p) {
            int val;
            if (sscanf(p, "%d", &val) == 1) count++;
            while (*p && *p != ' ') p++;
            while (*p == ' ') p++;
        }
        if (count > 0) {
            rowCount++;
            colCount = count;
        }
    }

    width = colCount;
    height = rowCount;

    // cấp phát mảng động
    grid = new Tile*[height];
    for (int i = 0; i < height; i++)
        grid[i] = new Tile[width];

    // quay lại đầu file để đọc lại thật sự
    fseek(file, 0, SEEK_SET);
    int y = 0;
    while (fgets(line, MAX_LINE, file)) {
        if (line[0] == '#' || line[0] == '\n') break;

        int x = 0;
        const char* p = line;
        while (*p && x < width) {
            int val;
            if (sscanf(p, "%d", &val) == 1) {
                grid[y][x].setType(static_cast<TileType>(val));
                x++;
            }
            while (*p && *p != ' ') p++;
            while (*p == ' ') p++;
        }
        y++;
    }

    // đọc phần entity
    while (fgets(line, MAX_LINE, file)) {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char type[32];
        float x, y;
        if (sscanf(line, "%s %f %f", type, &x, &y) == 3) {
            if (entityManager) {
                if (strcmp(type, "CASTLE") == 0) {
                    Castle* c = new Castle(x, y, 500, 50);
                    entityManager->add(c);
                    entityManager->set_castle(c);
                } else if (strcmp(type, "PLAYER") == 0) {
                    Character* p = new Character(x, y, 200, 50);
                    entityManager->add(p);
                    entityManager->set_player(p);
                } else if (strcmp(type, "RESOURCE") == 0) {
                    entityManager->create_resource_at(x, y);
                } else if (strcmp(type, "MONSTER") == 0) {
                    entityManager->create_monster_at(x, y);
                }
            }
        }
    }

    fclose(file);
    printf("Map loaded successfully (%d x %d)\n", width, height);
}

void Map::saveToFile(const char* filename, const EntityManager* entityManager) const {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Cannot save map file: %s\n", filename);
        return;
    }

    // ghi phần tile
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            fprintf(file, "%d ", (int)grid[y][x].getType());
        }
        fprintf(file, "\n");
    }

    fprintf(file, "#ENTITIES\n");

    if (entityManager) {
        auto list = entityManager->get_all_entities();
        for (int i = 0; i < list.size(); i++) { // nếu bạn không được dùng vector thì cần sửa hàm get_all_entities trả về mảng thuần
            Entity* e = list[i];
            sf::Vector2f pos = e->get_position();
            fprintf(file, "%s %.1f %.1f\n", e->get_type_name(), pos.x, pos.y);
        }
    }

    fclose(file);
    printf("Map saved to file %s\n", filename);
}

bool Map::isWalkable(int x, int y) const {
    if (!grid || x < 0 || y < 0 || x >= width || y >= height)
        return false;
    return grid[y][x].isWalkable();
}
