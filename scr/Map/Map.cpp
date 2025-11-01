#include "Map.h"
#include <cstdio>  // fopen, fscanf, fprintf
#include "String.h"

Map::Map() : width(0), height(0), grid(nullptr) {}

Map::~Map() {
    if (grid) {
        for (int i = 0; i < height; i++)
            delete[] grid[i];
        delete[] grid;
        grid = nullptr;
    }
}

int Map::get_width() const { return width; }
int Map::get_height() const { return height; }

Tile* Map::get_tile(int x, int y) const {
    if (!grid || x < 0 || y < 0 || x >= width || y >= height)
        return nullptr;
    return &grid[y][x];
}

bool Map::isWalkable(int x, int y) const {
    if (!grid || x < 0 || y < 0 || x >= width || y >= height)
        return false;
    return grid[y][x].isWalkable();
}

void Map::load_File(const char* filename, EntityManager* entityManager) {
    // Xoa du lieu cu neu co
    if (grid) {
        for (int i = 0; i < height; i++)
            delete[] grid[i];
        delete[] grid;
        grid = nullptr;
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Khong the mo file ban do: %s\n", filename);
        return;
    }

    const int MAX_LINE = 1024;
    char line[MAX_LINE];
    int rowCount = 0, colCount = 0;

    // Dem so dong va cot truoc
    while (fgets(line, MAX_LINE, file)) {
        if (line[0] == '#' || line[0] == '\n')
            break;
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

    // Cap phat mang dong 2 chieu
    grid = new Tile*[height];
    for (int i = 0; i < height; i++)
        grid[i] = new Tile[width];

    // Quay lai dau file doc lai map thuc su
    fseek(file, 0, SEEK_SET);
    int y = 0;
    while (fgets(line, MAX_LINE, file)) {
        if (line[0] == '#' || line[0] == '\n')
            break;
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

    // ==== Doc phan entity ====
    while (fgets(line, MAX_LINE, file)) {
        if (line[0] == '\n' || line[0] == '\0') continue;

        char type[32];
        float x, y;
        if (sscanf(line, "%s %f %f", type, &x, &y) == 3) {
            if (entityManager) {
                if (String::strcmp(type, "CASTLE") == 0) {
                    Castle* c = new Castle(x, y, 500, 50);
                    entityManager->add(c);
                    entityManager->set_castle(c);
                    printf("Tao CASTLE tai (%.1f, %.1f)\n", x, y);
                } else if (String::strcmp(type, "PLAYER") == 0) {
                    Character* p = new Character(x, y, 200, 50);
                    entityManager->add(p);
                    entityManager->set_player(p);
                    printf("Tao PLAYER tai (%.1f, %.1f)\n", x, y);
                } else if (String::strcmp(type, "RESOURCE") == 0) {
                    entityManager->create_resource_at(x, y);
                    printf("Tao RESOURCE tai (%.1f, %.1f)\n", x, y);
                } else if (String::strcmp(type, "MONSTER") == 0) {
                    entityManager->create_monster_at(x, y);
                    printf("Tao MONSTER tai (%.1f, %.1f)\n", x, y);
                }
            }
        }
    }

    fclose(file);
    printf("Tai map thanh cong (%d x %d)\n", width, height);
}

void Map::saveToFile(const char* filename, const EntityManager* entityManager) const {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Khong the luu file map: %s\n", filename);
        return;
    }

    // Ghi phan tile
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++)
            fprintf(file, "%d ", (int)grid[y][x].getType());
        fprintf(file, "\n");
    }

    fprintf(file, "#ENTITIES\n");

    // Ghi phan entity
    if (entityManager) {
        Vector<Entity*>& list = const_cast<Vector<Entity*>&>(entityManager->getEntities());
        for (int i = 0; i < list.get_size(); i++) {
            Entity* e = list[i];
            sf::Vector2f pos = e->get_sprite().getPosition();
            fprintf(file, "%s %.1f %.1f\n", e->get_type().c_str(), pos.x, pos.y);
        }
    }

    fclose(file);
    printf("Da luu map vao %s\n", filename);
}
