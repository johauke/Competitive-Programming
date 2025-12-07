f = open("input.txt")
sample = f.read().splitlines()

operations = sample[-1].split()
sample.pop()

def task_1():
    table = []
    for line in sample:
        table.append(list(map(int, line.split())))

    total = 0
    for i, op in enumerate(operations):

        if op == "*":
            sum = 1
            for r in range(len(table)):
                sum *= table[r][i]
            total += sum
        else:
            sum = 0
            for r in range(len(table)):
                sum += table[r][i]
            total += sum

    return total


def task_2():
    m = 0
    sum = operations[m] == "*"
    ll = [[] for _ in operations]

    for i in range(len(sample[0])):
        num = ""
        for j in range(len(sample)):
            num += sample[j][i]

        num = num.strip()
        if num == "":
            m += 1
            sum = operations[m] == "*"
        else:
            ll[m].append(int(num))

    total = 0
    for i, op in enumerate(operations):
        sum = op == "*"
        for num in ll[i]:
            if op == "*":
                sum *= num
            else:
                sum += num
        total += sum

    return total


print(f"Solution task 1: {task_1()}")
print(f"Solution task 2: {task_2()}")
f.close()
