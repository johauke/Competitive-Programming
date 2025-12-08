from math import sqrt, prod
from heapq import nlargest

f = open("input.txt")
sample = f.read().splitlines()

distances = []
points = []


def dist(p1, p2):
    return sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2 + (p1[2] - p2[2]) ** 2)


for i, line in enumerate(sample):
    p1 = tuple(map(int, line.split(",")))
    for j, p2 in enumerate(points):
        distances.append((dist(p1, p2), i, j))
    points.append(p1)

comp = [1] * len(points)
parent = list(range(len(points)))


def find(u):
    if parent[u] != u:
        parent[u] = find(parent[u])
    return parent[u]


def unionf(u, v):
    r1 = find(u)
    r2 = find(v)
    if r1 == r2:
        return
    if comp[r1] < comp[r2]:
        r1, r2 = r2, r1
    comp[r1] += comp[r2]
    comp[r2] = 0
    parent[r2] = r1


distances.sort()


def task_1():
    for edge in distances[:1000]:
        _, u, v = edge
        if find(u) != find(v):
            unionf(u, v)

    return prod(nlargest(3, comp))


def task_2():
    lu, lv = 0, 0
    for edge in distances[1000:]:
        _, u, v = edge
        if find(u) != find(v):
            lu, lv = u, v
            unionf(u, v)

    return points[lu][0] * points[lv][0]


print(f"Solution task 1: {task_1()}")
print(f"Solution task 2: {task_2()}")
f.close()
