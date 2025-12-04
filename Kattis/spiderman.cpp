#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <vector>

using u64 = uint64_t;
using i64 = int64_t;

const i64 bigNum = i64{1} << 32;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  i64 n, m, tmp;
  std::cin >> n;

  std::array<i64, 40> distances;
  std::array<char, 40> path;

  for (u64 _ = 0; _ < n; _++) {
    std::cin >> m;
    u64 num = 0;

    for (u64 i = 0; i < m; i++) {
      std::cin >> tmp;
      distances[i] = tmp;
      num += tmp;
    }
    num /= 2;
    num++;

    auto opt = std::vector(m + 1, std::vector(num, bigNum));
    opt[0][0] = 0;

    for (i64 i = 0; i < m; i++) {
      for (i64 j = 0; j < num; j++) {
        i64 up = bigNum, down = bigNum;
        if (j - distances[i] >= 0) {
          down = opt[i][j - distances[i]];
        }
        if (j + distances[i] < num) {
          up = opt[i][j + distances[i]];
        }
        opt[i + 1][j] = std::max(std::min(up, down), j);
      }
    }

    if (opt[m][0] < i64{1} << 32) {
      i64 j = 0;
      for (i64 i = m; i-- > 0;) {
        i64 up = bigNum, down = bigNum;
        if (j - distances[i] >= 0) {
          up = opt[i][j - distances[i]];
        }
        if (j + distances[i] < num) {
          down = opt[i][j + distances[i]];
        }
        if (up <= down) {
          path[i] = 'U';
          j = j - distances[i];
        } else {
          j = j + distances[i];
          path[i] = 'D';
        }
      }

      for (u64 i = 0; i < m; i++)
        std::cout << path[i];
      std::cout << "\n";

    } else
      std::cout << "IMPOSSIBLE\n";
  }
}
