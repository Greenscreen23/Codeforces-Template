#include <bits/stdc++.h>
using ll = long long;

// gcd, lcm
ll gcd(ll x, ll y) { return y == 0 ? x : gcd(y, x % y); }
ll lcm(ll x, ll y) { return x / gcd(x, y) * y; }

// Fenwick
int getSum(vector<int> &BITree, int index)
{
    int sum = 0;
    index = index + 1;

    while (index > 0)
    {
        sum += BITree[index - 1];
        index -= index & (-index);
    }
    return sum;
}

// Updates a node in Binary Index Tree (BITree) at given index
// in BITree. The given value is added to the index
void updateBIT(vector<int> &BITree, int n, int index, int val)
{
    index = index + 1;
    while (index <= n)
    {
        BITree[index - 1] += val;
        index += index & (-index);
    }
}

// Constructs and returns a Binary Indexed Tree for given
// array of size n.
void constructBITree(vector<int> arr, int n, vector<int> &BITree)
{
    BITree = vector<int>(n);

    for (int i = 0; i < n; i++)
        updateBIT(BITree, n, i, arr[i]);
    return BITree;
}

// Power Mod
unsigned long long power(unsigned long long x,
                         int y, int p)
{
    unsigned long long res = 1;
    x = x % p;

    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res * x) % p;

        // y must be even now
        y = y >> 1; // y = y/2
        x = (x * x) % p;
    }
    return res;
}

// Returns n^(-1) mod p
unsigned long long modInverse(unsigned long long n,
                              int p)
{
    return power(n, p - 2, p);
}

// Returns nCr % p using Fermat's little theorem.
unsigned long long nCrModPFermat(unsigned long long n,
                                 int r, int p)
{
    if (n < r)
        return 0;
    if (r == 0)
        return 1;

    // Fill factorial array so that we
    // can find all factorial of r, n
    // and n-r
    unsigned long long fac[n + 1];
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % p;

    return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) % p;
}
