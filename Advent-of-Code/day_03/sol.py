f = open("input.txt")
sample = f.read().splitlines()

table = []
for line in sample:
    tmp = []
    for i in range(len(line)):
        tmp.append(int(line[i]))
    table.append(tmp)


def task_1():
    sum = 0
    for row in table:
        idx = max(range(len(row) - 1), key=row.__getitem__)
        fst = row[idx]

        idx = max(range(idx + 1, len(row)), key=row.__getitem__)
        snd = row[idx]

        sum += int(str(fst) + str(snd))

    return sum


def task_2():
    sum = 0
    for row in table:
        numbers = []
        l, r = 0, len(row) - 12
        for i in range(12):
            idx = max(range(l, r), key=row.__getitem__)
            numbers.append(str(row[idx]))
            l = idx + 1
            r = len(row) - 10 + i

        sum += int("".join(numbers))

    return sum


print(f"Solution task 1: {task_1()}")
print(f"Solution task 2: {task_2()}")
f.close()
