#include <cmath>
#include <cstdint>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>

using u64 = uint64_t;

struct point {
  double x, y;
};

double distance(point &a, point &b) {
  return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double totalDistance(std::vector<point> &points, point &p) {
  double sum = 0;
  for (auto pt : points) {
    sum += distance(p, pt);
  }
  return sum;
}

point distanceSum(std::vector<point> &points, point &p) {
  point sum = {0, 0};
  double tmp, tmp2 = 0;
  for (auto pt : points) {
    tmp = distance(p, pt);
    sum.x += pt.x / tmp;
    sum.y += pt.y / tmp;
    tmp2 += 1 / tmp;
  }
  sum.x /= tmp2;
  sum.y /= tmp2;
  return sum;
}

double calculateMedian(std::vector<point> &points, double eps) {

  point curPoint{0, 0};
  for (auto pt : points) {
    curPoint.x += pt.x;
    curPoint.y += pt.y;
  }

  curPoint.x /= points.size();
  curPoint.y /= points.size();

  point tmp = distanceSum(points, curPoint);

  while (distance(tmp, curPoint) > eps) {
    curPoint = tmp;
    tmp = distanceSum(points, curPoint);
  }
  return totalDistance(points, curPoint);
}

int main() {
  u64 n;
  std::cin >> n;

  std::vector<point> points;
  points.reserve(n);

  double x, y;
  for (u64 i = 0; i < n; i++) {
    std::cin >> x >> y;
    points.push_back({x, y});
  }

  std::cout << std::setprecision(100000) << calculateMedian(points, 0.00001)
            << "\n";
}
