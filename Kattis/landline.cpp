#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <ranges>

using i64 = int64_t;

i64 mstFind(i64 u, std::vector<i64> &comp) {
  if (comp[u] == u) {
    return u;
  } else {
    i64 parent = mstFind(comp[u], comp);
    comp[u] = parent;
    return parent;
  }
}

void mstUnion(i64 u, i64 v, std::vector<i64> &comp) {
  i64 r1 = mstFind(u, comp);
  i64 r2 = mstFind(v, comp);

  comp[r1] = r2;
}

void kruskai64(std::vector<i64> &comp,
               std::vector<std::tuple<i64, i64, i64>> &edges,
               std::unordered_map<i64, std::vector<std::pair<i64, i64>>> &mst) {

  for (auto edge : edges) {
    i64 u = get<1>(edge), v = get<2>(edge), e = get<0>(edge);
    if (mstFind(u, comp) != mstFind(v, comp)) {
      mst[u].push_back({e, v});
      mst[v].push_back({e, u});
      mstUnion(u, v, comp);
    }
  }
}

int main() {

  i64 n, m, p;
  std::cin >> n >> m >> p;

  std::vector<std::tuple<i64, i64, i64>> edges;
  std::unordered_map<i64, std::tuple<i64, i64, i64>> insecureEdges;
  bool insecure[1000] = {false};
  std::unordered_map<i64, std::vector<std::pair<i64, i64>>> mst;
  i64 total = 0;

  i64 ins;
  for (i64 i = 0; i < p; ++i) {
    std::cin >> ins;
    insecure[ins - 1] = true;
  }
  if (n == 1) {
    std::cout << "0\n";
    return 0;
  }

  if (n == p) {
    // check if the graph is a qlicue
    if ((n*n - n) / 2 == m) {
      i64 x, y, l;
      for (i64 i = 0; i < m; ++i) {
        std::cin >> x >> y >> l;
        total += l;
      }

      std::cout << total << "\n";
      return 0;
    }
    std::cout << "impossible\n";
    return 0;
  }

  i64 x, y, l;
  for (i64 i = 0; i < m; ++i) {
    std::cin >> x >> y >> l;
    bool insX = insecure[--x];
    bool insY = insecure[--y];

    if (insX && insY) {
      continue;
    }
    if (insX) {
      if (insecureEdges.find(x) == insecureEdges.end()) {
        insecureEdges[x] = {l, x, y};
      } else {
        if (get<0>(insecureEdges[x]) > l) {
          insecureEdges[x] ={l, x, y};
        }
      }
      continue;
    }
    if (insY) {
      if (insecureEdges.find(y) == insecureEdges.end()) {
        insecureEdges[y] = {l, x, y};
      } else {
        if (get<0>(insecureEdges[y]) > l) {
          insecureEdges[y] = {l, x, y};
        }
      }
      continue;
    }

    edges.push_back({l, x, y});
  }

  for (const auto &e : insecureEdges) {
    edges.push_back(e.second);
  }

    std::ranges::sort(edges);

  std::unordered_set<i64> visisted;
  std::vector<i64> comp(n);

  for (i64 i = 0; i < n; ++i) {
    comp[i] = i;
  }

  kruskai64(comp, edges, mst);

  std::queue<i64> toSearch;

  toSearch.push(0);

  while (!toSearch.empty()) {
    i64 v = toSearch.front();
    toSearch.pop();
    visisted.insert(v);

    for (auto neighbour : mst[v]) {
      if (!visisted.count(neighbour.second)) {
        total += neighbour.first;
        toSearch.push(neighbour.second);
      }
    }
  }

  if (visisted.size() == n) {
    std::cout << total << "\n";

  } else {
    std::cout << "impossible\n";
  }
}
