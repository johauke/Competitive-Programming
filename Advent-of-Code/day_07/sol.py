from functools import cache

f = open("input.txt")
sample = f.read().splitlines()


def find_start():
    start = 0
    for i, e in enumerate(sample[0]):
        if e == "S":
            start = i
            break
    return start


def task_1():
    count = 0
    searching = {find_start()}
    toSearch = set()
    for line in sample[2::2]:
        for s in searching:
            if line[s] == "^":
                toSearch.add(s - 1)
                toSearch.add(s + 1)
                count += 1
            else:
                toSearch.add(s)
        searching = toSearch
        toSearch = set()

    return count


def task_2():
    @cache
    def rec(row, col):
        if row >= len(sample) - 1:
            return 1

        if sample[row][col] == "^":
            return rec(row + 2, col - 1) + rec(row + 2, col + 1)

        return rec(row + 2, col)

    return rec(2, find_start())


print(f"Solution task 1: {task_1()}")
print(f"Solution task 2: {task_2()}")
f.close()
