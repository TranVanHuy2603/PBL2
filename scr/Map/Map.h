#include "Vector.h"
#include <string>
#include <SFML\Graphics.hpp>

class Map
{
private:
    int height, width; //chieu cao va chieu rong cua ban do
    Vector<Vector<int>> grid;//ma tran chua thong tin cac diem dung cho A*
public:
    Map(int, int);

    int get_height(); //lay chieu cao
    int get_width(); //lay chieu rong
    Vector<Vector<int>> get_grid(); //lay ma tran

    void load_File(const std::string&); //load tu file
    void draw(sf::RenderWindow&); //ve ban do
    bool isWalkable(int, int) const; //xem diem co di duoc hay khong
};