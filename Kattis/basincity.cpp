#include <bitset>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <vector>

using i64 = int64_t;

std::vector<std::vector<int>> map;
i64 n;
std::bitset<75> S;
std::vector<bool> pick;

bool rec(int k, int i, std::bitset<75> bmask) {

  if (!k)
    return true;

  if (i == n || i + k > n) {
    return false;
  }
  i64 l = 0, s = 0;
  bmask[i] = false;
  std::bitset<75> dpick = bmask;

  for (auto j : map[i]) {
    if (bmask[j]) {
      dpick[j] = false;
      s++;
    }
  }

  if (s <= 1) {
    l = i;
    for (; l < n; ++l) {
      if (dpick[l])
        break;
    }
    return (rec(k - 1, l, dpick));
  }

  l = i;
  for (; l < n; ++l) {
    if (dpick[l])
      break;
  }
  if (rec(k - 1, l, dpick))
    return true;

  i64 z, w;
  std::bitset<75> twoPick;
  for (size_t x = 0; x < map[i].size(); ++x) {
    z = map[i][x];
    if (bmask[z]) {
      for (size_t y = x + 1; y < map[i].size(); ++y) {
        twoPick = bmask;
        w = map[i][y];
        if (bmask[w] && std::ranges::find(map[z], w) == map[z].end()) {
          twoPick[z] = false;
          twoPick[w] = false;
          l = i;
          for (auto v : map[z]) {
            twoPick[v] = false;
          }
          for (auto v : map[w]) {
            twoPick[v] = false;
          }
          for (; l < n; ++l) {
            if (twoPick[l])
              break;
          }
          if (rec(k - 2, l, twoPick))
            return true;
        }
      }
    }
  }
  return false;
}

int main() {
  std::cin.tie(nullptr);
  i64 k, r;

  std::cin >> k >> n;

  if (n > k * 5) {
    std::cout << "possible" << "\n";
    return 0;
  }

  std::bitset<75> bmask;
  S.set();
  std::vector<int> _map;
  _map.reserve(4);
  map = std::vector<std::vector<int>>(n, _map);
  r = n;

  i64 d, x, nei;
  for (i64 i = 0; i < n; ++i) {
    std::cin >> d;
    if (d == 0) {
      k--;
      S[i] = false;
      continue;
    }
    if (d == 1) {
      k--;
      std::cin >> nei;
      S[i] = false;
      S[nei - 1] = false;
      continue;
    }
    for (i64 j = 0; j < d; ++j) {
      std::cin >> x;
      map[i].push_back(x - 1);
    }
  }

  if (k <= 0 || r > 5 * k) {
    std::cout << "possible" << "\n";
    return 0;
  }
  bmask ^= S;
  i64 i = 0;
  for (; i < n; ++i) {
    if (bmask[i])
      break;
  }

  if (rec(k, i, bmask)) {
    std::cout << "possible\n";
  } else {
    std::cout << "impossible\n";
  }
}
