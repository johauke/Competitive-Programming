f = open("input.txt")
sample = f.read().splitlines()


def task_1():
    pos = 50
    count = 0

    for line in sample:
        direction = line[0]
        amount = int(line[1:])
        if direction == "L":
            amount *= -1
        pos = (pos - amount) % 100
        if pos == 0:
            count += 1
    return count


def task_2():
    pos = 50
    count = 0

    for line in sample:
        direction = line[0]
        amount = int(line[1:])
        if amount > 100:
            count += amount // 100
            amount %= 100
        orig = pos
        if direction == "L":
            amount *= -1
        pos += amount
        if (0 > pos or pos > 100) and orig != 0:
            count += 1
        pos %= 100
        if pos == 0:
            count += 1
    return count


print(f"Solution task 1: {task_1()}")
print(f"Solution task 2: {task_2()}")
f.close()
