#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

using i64 = int64_t;

constexpr i64 maxVal = i64{1} << 61;

i64 r, c;
std::vector<std::unordered_map<i64, i64>> g;
std::vector<std::vector<i64>> adj;

std::vector<i64> getPath(std::vector<i64> &p, i64 s, i64 t) {
  std::vector<i64> path;
  path.push_back(t);
  while (t != s) {
    t = p[t];
    path.push_back(t);
  }
  std::ranges::reverse(path);
  return path;
}

std::optional<std::vector<i64>> bfs(i64 s, i64 t) {

  size_t p = 0;
  std::vector<i64> q;
  std::vector<i64> parent(g.size(), -1);
  parent[s] = s;
  q.push_back(s);

  while (p < q.size()) {
    i64 v = q[p++];
    for (auto u : adj[v]) {
      if (parent[u] != -1) {
        continue;
      }
      if (g[v][u] <= 0)
        continue;
      parent[u] = v;
      q.push_back(u);
      if (u == t) {
        return getPath(parent, s, t);
      }
    }
  }
  return std::nullopt;
}

std::vector<std::pair<i64, i64>> getEdges(std::vector<i64> &l, i64 &cap) {
  std::vector<std::pair<i64, i64>> path;
  cap = maxVal;

  for (size_t i = 0; i < l.size() - 1; ++i) {
    path.push_back({l[i], l[i + 1]});
    cap = std::min(g[l[i]][l[i + 1]], cap);
  }
  return path;
}

i64 maxFlow(i64 s, i64 t) {
  i64 flow = 0;
  i64 b;
  while (auto P = bfs(s, t)) {
    std::vector<std::pair<i64, i64>> edges = getEdges(*P, b);
    for (auto e : edges) {
      g[e.first][e.second] -= b;
      g[e.second][e.first] += b;
    }
    flow += b;
  }
  return flow;
}

i64 calcIdx(i64 i, i64 j) { return i * c + j; }
i64 calcIdxOff(i64 i, i64 j) { return i * c + j + (r * c); }

int main() {
  i64 pr, pc, t, s;
  std::cin >> r >> c;

  std::vector<i64> map(r * c);
  std::vector<i64> tmp(2 * (r * c) + 1, 0);
  g = std::vector<std::unordered_map<i64, i64>>(2 * r * c + 1);
  adj.resize(2 * r * c + 1);

  s = 2 * r * c;

  i64 val;
  for (i64 i = 0; i < r; ++i) {
    for (i64 j = 0; j < c; ++j) {
      std::cin >> val;
      map[calcIdx(i, j)] = val;
      if (val <= 0) {
        continue;
      }
      adj[calcIdx(i, j)].push_back(calcIdxOff(i, j));
      adj[calcIdxOff(i, j)].push_back(calcIdx(i, j));
      g[calcIdx(i, j)][calcIdxOff(i, j)] = val;

      if (i - 1 >= 0) {
        adj[calcIdxOff(i, j)].push_back(calcIdx(i - 1, j));
        adj[calcIdx(i - 1, j)].push_back(calcIdxOff(i, j));
        g[calcIdxOff(i, j)][calcIdx(i - 1, j)] = val;
      }
      if (i + 1 < r) {
        adj[calcIdxOff(i, j)].push_back(calcIdx(i + 1, j));
        adj[calcIdx(i + 1, j)].push_back(calcIdxOff(i, j));
        g[calcIdxOff(i, j)][calcIdx(i + 1, j)] = val;
      }
      if (j - 1 >= 0) {
        adj[calcIdxOff(i, j)].push_back(calcIdx(i, j - 1));
        adj[calcIdx(i, j - 1)].push_back(calcIdxOff(i, j));
        g[calcIdxOff(i, j)][calcIdx(i, j - 1)] = val;
      }
      if (j + 1 < c) {
        adj[calcIdxOff(i, j)].push_back(calcIdx(i, j + 1));
        adj[calcIdx(i, j + 1)].push_back(calcIdxOff(i, j));
        g[calcIdxOff(i, j)][calcIdx(i, j + 1)] = val;
      }
    }
  }

  std::cin >> pr >> pc;
  t = calcIdxOff(pr, pc);

  for (i64 j = 0; j < c; ++j) {
    if (map[calcIdx(0, j)] > 0) {
      adj[j].push_back(s);
      adj[s].push_back(j);
      g[s][j] = map[calcIdx(0, j)];
    }

    if (map[calcIdx(r - 1, j)] > 0) {
      adj[calcIdx(r - 1, j)].push_back(s);
      adj[s].push_back(calcIdx(r - 1, j));
      g[s][calcIdx(r - 1, j)] = map[calcIdx(r - 1, j)];
    }
  }

  for (i64 i = 1; i < r - 1; ++i) {
    if (map[calcIdx(i, 0)] > 0) {
      adj[calcIdx(i, 0)].push_back(s);
      adj[s].push_back(calcIdx(i, 0));
      g[s][i] = map[calcIdx(i, 0)];
    }

    if (map[calcIdx(i, c - 1)] > 0) {
      adj[calcIdx(i, c - 1)].push_back(s);
      adj[s].push_back(calcIdx(i, c - 1));
      g[s][calcIdx(i, c - 1)] = map[calcIdx(i, c - 1)];
    }
  }

  std::cout << maxFlow(s, t) << "\n";
}
