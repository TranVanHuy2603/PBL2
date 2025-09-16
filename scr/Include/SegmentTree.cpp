#include "SegmentTree.h"
// node la so thu tu cua node tren cay ohan d
void SegmentTree::build(vector<int> &arr, int node, int l, int r)
{
    if (l == r)
    {
        tree[node] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(arr, 2 * node, l, mid);
    build(arr, 2 * node + 1, mid + 1, r);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int SegmentTree::query(int node, int L, int R, int l, int r /*L, R la can tren va van duoi cua node ma ta truy van*/)
{
    if (l > r)
        return 0;
    if (r < L || l > R)
        return 0;
    if (L == l && R == r)
        return tree[node];
    int mid = (L + R) / 2;
    int s1 = query(2 * node, L, mid, l, min(r, mid));
    int s2 = query(2 * node + 1, mid + 1, R, max(l, mid + 1), r);
    return s1;
}

void SegmentTree::update(int node, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
        update(2 * node, l, mid, pos, val);
    else
        update(2 * node + 1, mid + 1, r, pos, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void SegmentTree::Segmenttree(vector<int> &arr)
{
    n = arr.size();
    tree.resize(4 * n);
    build(arr, 1, 0, n - 1);
}

int SegmentTree::query(int l, int r) { return query(1, 0, n - 1, l, r); }
void SegmentTree::update(int idx, int val) { update(1, 0, n - 1, idx, val); }