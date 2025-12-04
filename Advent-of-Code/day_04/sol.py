f = open("input.txt")
sample = f.read().splitlines()

table = []
for line in sample:
    tmp = []
    for c in line:
        tmp.append(c)
    table.append(tmp)


pos = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]


def can_remove(i, j):
    count = 4
    for p in pos:
        if (
            (0 <= i + p[0] < len(table))
            and (0 <= j + p[1] < len(table[i]))
            and table[i + p[0]][j + p[1]] == "@"
        ):
            count -= 1
            if count <= 0:
                continue
    return count > 0


def task_1():
    sum = 0
    for i in range(len(table)):
        for j in range(len(table[i])):
            if table[i][j] == "@" and can_remove(i, j):
                sum += 1
    return sum


def task_2():

    sum = 0
    while True:
        toRemove = []
        for i in range(len(table)):
            for j in range(len(table[i])):
                if table[i][j] == "@" and can_remove(i, j):
                    toRemove.append((i, j))
                    sum += 1

        if len(toRemove) == 0:
            break

        for p in toRemove:
            table[p[0]][p[1]] = "."

    return sum


print(f"Solution task 1: {task_1()}")
print(f"Solution task 2: {task_2()}")
f.close()
