#include <cstdint>
#include <iostream>
#include <vector>

using u64 = uint64_t;
using i64 = int64_t;

struct plength {
  i64 distance, nei;
};

plength rec(i64 v, std::vector<std::vector<i64>> &g,
            std::vector<plength> &dist) {
  if (g[v].size() == 0) {
    dist[v] = {1, v};
    return {1, v};
  }

  plength longest = {-1, -1};
  i64 best;
  plength tmp;
  for (auto u : g[v]) {
    if (dist[v].distance != -1) {
        tmp = dist[v];
    } else {
      tmp = rec(u, g, dist);
    }
    if (tmp.distance > longest.distance) {
      longest = tmp;
      best = u;
    }
  }
  dist[v] = {longest.distance + 1, best};

  return {longest.distance + 1, v};
}

int main() {
  u64 n, m;
  std::cin >> n >> m;

  std::vector<std::vector<i64>> g(n);
  std::vector<plength> dist(n, {-1, -1});
  std::vector<char> sources(n, true);

  i64 a, b;
  for (u64 i = 0; i < m; i++) {
    std::cin >> a >> b;
    g[a - 1].push_back(--b);
    sources[b] = false;
  }

  plength current = {-1, -1};
  for (i64 v = 0; v < n; v++) {
    if (sources[v]) {
      auto tmp = rec(v, g, dist);
      if (tmp.distance > current.distance)
        current = tmp;
    }
  }

  std::cout << current.distance << "\n";

  while (current.nei != dist[current.nei].nei) {
    std::cout << current.nei + 1 << " ";
    current = dist[current.nei];
  }
  std::cout << current.nei + 1 << "\n";
}
