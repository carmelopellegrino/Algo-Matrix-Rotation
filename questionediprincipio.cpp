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

std::pair<int, int> destination(int i, int j, int i_max, int i_min, int j_max, int j_min)
{
  int i_dest = i;
  int j_dest = j;

  if (i == i_min) {
     if (j == j_min) {
         i_dest = i + 1;
         // j_dest = j;
     } else {
         // i_dest = i;
         j_dest = j - 1;
     }
  } else if (i == i_max) {
     if (j == j_max) {
         i_dest = i - 1;
         // j_dest = j;
     } else {
         // i_dest = i;
         j_dest = j + 1;
     }
  } else {
     if (j == j_min) {
         i_dest = i + 1;
         // j_dest = j;
     } else {
         i_dest = i - 1;
         // j_dest = j;
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

          std::pair<int, int> d = std::make_pair(i, j);

          for (int k = 0; k < r; ++k) {
            std::pair<int, int> const d1 = destination(d.first, d.second, i_max, i_min, j_max, j_min);
            d = d1;
          }

          b[d.first][d.second] = a[i][j];
        }
    }
}

std::vector< std::vector<int> > rotate(std::vector< std::vector<int> > const& a, int r)
{
    std::vector< std::vector<int> > b(a);

    rotate(a, b, r);
    return b;
    //std::vector< std::vector<int> > b1(a);
    //std::vector< std::vector<int> > b2(a);

    //for (int i = 0; i < r; ++i) {
    //    rotate(b1, b2);
    //    b1.swap(b2);
    //}
    //return b1;
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

    std::vector< std::vector<int> > const b = rotate(a, r);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << b[i][j];
            if (j != n -1) std::cout << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}

