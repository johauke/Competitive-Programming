f = open("input.txt")
sample = f.read().split(",")


def task_1():
    count = 0

    for line in sample:
        l, r = map(int, line.split("-"))
        for e in range(l, r + 1):
            e = str(e)
            if len(e) % 2 == 1:
                continue
            s = len(e) // 2
            if e[0:s] == e[s:]:
                count += int(e)

    return count


def task_2():
    count = 0

    for line in sample:
        l, r = map(int, line.split("-"))
        for e in range(l, r + 1):
            e = str(e)
            s = len(e)
            for i in range(1, s):
                if s % i != 0:
                    continue
                for j in range(0, s - i, i):
                    if e[j : j + i] != e[j + i : j + i + i]:
                        break
                else:
                    count += int(e)
                    break
    return count


print(task_1())
print(task_2())
