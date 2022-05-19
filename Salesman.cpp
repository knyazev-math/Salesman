#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <string>
#include <numeric>
#include <random>

using namespace std;

random_device rd;
mt19937 mersenne(rd());
vector <int> ind;
vector <pair <long long, long long>> point;


vector <int> randomPermutation(vector <int> a, int size) {
    for (int i = 0; i < size - 1; i++) {
        int j = mersenne() % (size - i);
        swap(a[i], a[i + j]);

    }
    return a;
}


long double d(int l1, int l2) {
    return sqrt(pow(point[l1].first - point[l2].first, 2) + pow(point[l1].second - point[l2].second, 2));
}


long double score(vector <int> p, int size) {
    long double sc = 0;
    for (int i = 1; i < size; i++) {
        sc += d(p[i], p[i - 1]);
    }
    return sc;
}


long double diff_score(vector <int> p, int size, int x, int y) {
    if (y == size - 1) {
        if (x != 0)
            return d(p[y], p[x - 1]) - d(p[x], p[x - 1]);
        return 0;
    }
    else {
        if (x == 0) {
            return d(p[x], p[y + 1]) - d(p[y], p[y + 1]);
        }
    }
    return d(p[y], p[x - 1]) - d(p[x], p[x - 1]) + d(p[x], p[y + 1]) - d(p[y], p[y + 1]);
}


pair <vector <int>, long double> sol(int n) {
    vector <int> s = randomPermutation(ind, n);
    vector <int> sbest = s;
    long double fbest = score(s, n);
    long double scDelta = fbest / (n - 1);


    long double tmax = scDelta, tmin = 0.001 * scDelta, tmult = 0.9999;
    for (long double t = tmax; t >= tmin; t *= tmult) {



        int a = mersenne() % n;
        int b = mersenne() % n;
        if (a > b) {
            swap(a, b);
        }

        long double c = (long double)mersenne() / (pow(2, 32) - 1);
        long double dif = (-1) * diff_score(s, n, a, b);
        if (c < exp(dif / t)) {
            for (int j = a; j < (a + b) / 2 + 1; j++) {
                swap(s[j], s[a + b - j]);
            }
            fbest -= dif;
        }
    }
    return { s, fbest };
}



int main() {
    int m;
    cin >> m;
    ind = vector <int>(m);
    point = vector <pair <long long, long long>>(m);
    long double res = 0;
    for (int i = 0; i < m; i++) {
        cin >> point[i].first >> point[i].second;
        ind[i] = i;
    }
    vector <int> ans;
    for (int i = 0; i < 30; i++) {
        pair <vector <int>, long double> sltn = sol(m);
        if ((sltn.second < res) || (i == 0)) {
            res = sltn.second;
            ans = sltn.first;
        }
    }
    for (int i = 0; i < m; i++) {
        cout << 1 + ans[i] << " ";
    }
    return 0;
}
