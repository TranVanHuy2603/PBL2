#include "Vector.cpp"
#include <iostream>

using namespace std;

int main()
{
    Vector<int> num;
    for (int i = 0; i <= 20; i++)
    {
        num.push_back(i);
    }
    for (int i = 0; i <= 20; i++)
    {
        cout << num[i] << " ";
    }
    cout << endl;
    return 0;
}