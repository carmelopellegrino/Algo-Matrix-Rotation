#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

template<typename T>
T min(T const& a, T const& b)
{
    return a < b ? a : b;
}

template<typename T>
T max(T const& a, T const& b)
{
    return a < b ? b : a;
}

inline
int layer(int i, int j, int m, int n)
{
    if (i >= m / 2) {
        i = m - i - 1;
    }
    if (j >= n / 2) {
        j = n - j - 1;
    }

    return min(j, i);
}

std::pair<int, int> destination(int i, int j, int i_max, int i_min, int j_max, int j_min, int r)
{
  r = r % (2 * (i_max - i_min + j_max - j_min));
  if (r == 0) {
    return std::make_pair(i, j);
  }

  int i_dest = i;
  int j_dest = j;

  if (i == i_min) {
     if (j == j_min) {
       if (i + r <= i_max) {
         i_dest = i + r;
         // j_dest = j;
       } else {
         int const step = r - (i_max - i_dest);
         i_dest = i_max;
         std::pair<int, int> const d = destination(i_dest, j_dest, i_max, i_min, j_max, j_min, step);
         i_dest = d.first;
         j_dest = d.second;
       }
     } else {
       if (j - r >= j_min) {
         // i_dest = i;
         j_dest = j - r;
       } else {
         int const step = r - (j_dest - j_min);
         j_dest = j_min;
         std::pair<int, int> const d = destination(i_dest, j_dest, i_max, i_min, j_max, j_min, step);
         i_dest = d.first;
         j_dest = d.second;
       }
     }
  } else if (i == i_max) {
     if (j == j_max) {
       if (i - r >= i_min) {
         i_dest = i - r;
         // j_dest = j;
       } else {
         int const step = r - (i_dest - i_min);
         i_dest = i_min;
         std::pair<int, int> const d = destination(i_dest, j_dest, i_max, i_min, j_max, j_min, step);
         i_dest = d.first;
         j_dest = d.second;
       }
     } else {
       if (j + r <= j_max) {
         // i_dest = i;
         j_dest = j + r;
       } else {
         int const step = r - (j_max - j_dest);
         j_dest = j_max;
         std::pair<int, int> const d = destination(i_dest, j_dest, i_max, i_min, j_max, j_min, step);
         i_dest = d.first;
         j_dest = d.second;
       }
     }
  } else {
     if (j == j_min) {
       if (i + r <= i_max) {
         i_dest = i + r;
         // j_dest = j;
       } else {
         int const step = r - (i_max - i_dest);
         i_dest = i_max;
         std::pair<int, int> const d = destination(i_dest, j_dest, i_max, i_min, j_max, j_min, step);
         i_dest = d.first;
         j_dest = d.second;
       }
     } else {
       if (i - r >= i_min) {
         i_dest = i - r;
         // j_dest = j;
       } else {
         int const step = r - (i_dest - i_min);
         i_dest = i_min;
         std::pair<int, int> const d = destination(i_dest, j_dest, i_max, i_min, j_max, j_min, step);
         i_dest = d.first;
         j_dest = d.second;
       }
     }
  }

  return std::make_pair(i_dest, j_dest);
}


void rotate(std::vector< std::vector<int> > const& a, std::vector< std::vector<int> > & b, int r)
{
    int const m = a.size();
    int const n = a[0].size();

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
          int const l = layer(i, j, m, n);
          int const i_min = l;
          int const i_max = m - l - 1;
          int const j_min = l;
          int const j_max = n - l - 1;

          std::pair<int, int> const d = destination(i, j, i_max, i_min, j_max, j_min, r);

          b[d.first][d.second] = a[i][j];
        }
    }
}

int main() {
    int m, n, r;
    std::cin >> m >> n >> r;
    std::vector< std::vector<int> > a(m, std::vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> a[i][j];
        }
    }

    std::vector< std::vector<int> > b(a.size(), std::vector<int>(a[0].size()));

    rotate(a, b, r);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << b[i][j];
            std::cout << (j != n - 1 ? ' ' : '\n');
        }
    }
}
