#include <bitset>
#include <iostream>
#include <string>
#include <vector>

using u8 = u_int8_t;
using u32 = u_int32_t;

int main() {

  u32 n, k, a;

  std::cin >> n >> k;
  std::string tmp;

  std::vector<u32> toSearch = {};
  std::vector<u32> searching = {};
  std::vector<u8> dist = std::vector<u8>(1 << k, 0);

  searching.reserve(n);

  for (u32 i = 0; i < n; i++) {
    std::cin >> tmp;
    a = std::stoi(tmp, nullptr, 2);
    searching.push_back(a);
    dist[a] = 1;
  }
  u32 last = searching.back();

  while (!searching.empty()) {

    for (u32 v : searching) {
      for (u32 i = 0; i < k; i++) {
        auto b = v ^ (1 << i);
        if (!dist[b]) {
          dist[b] = 1;
          toSearch.push_back(b);
          last = b;
        }
      }
    }

    searching.clear();
    std::swap(searching, toSearch);
  }

  auto t = std::bitset<20>(last);
  for (int i = k - 1; i >= 0; i--) {
    std::cout << t[i];
  }
  std::cout << "\n";
}
