#include <vector>

using namespace std;

class SegmentTree // dung voi mang 1 chieu
{
private:
    vector<int> tree;
    int n;
    void build(vector<int> &, int, int, int);
    int query(int, int, int, int, int);
    void update(int, int, int, int, int);

public:
    void Segmenttree(vector<int> &);
    int query(int, int);
    void update(int, int);
};