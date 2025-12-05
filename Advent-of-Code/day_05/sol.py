f = open("input.txt")
sample = f.read().splitlines()

i = 0
ranges = []
for i in range(len(sample)):
    if sample[i] == "":
        break
    a, b = sample[i].split("-")
    ranges.append((int(a), int(b)))

dates = []
for j in range(i+1, len(sample)):
    dates.append(int(sample[j]))

def remove_overlapping():
    ranges.sort(key=lambda x: (x[0], -1*x[0]))

    new_ranges = [ranges[0]]
    for a, b in ranges[1:]:
        l, r = new_ranges[-1]
        if l <= a <= r:
            new_ranges[-1] = (l, max(r, b))
        else:
            new_ranges.append((a, b))
    return new_ranges

ranges = remove_overlapping()

def task_1():
    sum = 0
    for date in dates:
        for l, r in ranges:
            if l <= date <= r:
                sum += 1
                break
    return sum

def task_2():
    sum = 0
    for a, b in ranges:
        sum += b - a + 1

    return sum

print(f"Solution task 1: {task_1()}")
print(f"Solution task 2: {task_2()}")
f.close()
