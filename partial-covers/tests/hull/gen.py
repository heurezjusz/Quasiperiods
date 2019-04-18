import random

random.seed(1342)

MIN_POS = 1
MAX_POS = 200

MAX_HEIGHT = int(1e5)


def write_test(fname, tst):
    with open(fname, "w") as f:
        N, points = tst
        f.write("%d %d\n" % (N, len(points)))
        for x1, y1, x2, dx in points:
            f.write("%d %d %d %d\n" % (x1, x2, y1, dx))


def n_ints(N, minval, maxval):
    return [random.randint(minval, maxval) for _ in range(N)]


def random_segment(N=MAX_POS):
    x1, x2 = 0, 0
    while x1 == x2:
        x1, x2, y1 = n_ints(3, MIN_POS, N)

    if x2 < x1:
        x1, x2 = x2, x1
    dx = random.randint(1, MAX_HEIGHT // (x2 - x1))

    return x1, y1, x2, dx


def line_with_dots(N, num_of_dots):
    res = []
    res.append(random_segment())
    for i in range(num_of_dots):
        x, y = n_ints(2, MIN_POS, MAX_HEIGHT)
        res.append((x, y, x, 0))
    return max(y for _, y, _, _ in res), res


def just_random(N, M):
    return N, [random_segment(N) for i in range(N)]


def same(N):
    s = N // 2
    return N, [(i, i, i + s - 1, 1) for i in range(1, N - s + 2)]


print "hand..."
write_test("hand1.in", (10, [(1, 1, 10, 1), (2, 1, 6, 2), (3, 1, 5, 3)]))
write_test("hand2.in", (20, [(2, 3, 2, 3), (7, 4, 7, 4), (9, 9, 9, 9),
                             (2, 2, 2, 2), (4, 2, 4, 4)]))

print "rand..."
for i in range(20):
    write_test("small_rand%d.in" % i, just_random(10, 3))
for i in range(20):
    write_test("medium_rand%d.in" % i, just_random(100, 10))
for i in range(20):
    write_test("big_rand%d.in" % i, just_random(MAX_POS, 16))

print "ldots..."
for i in range(20):
    write_test("line_with_dots_few%d.in" % i, line_with_dots(10, 3))
for i in range(20):
    write_test("line_with_dots_medium%d.in" % i, line_with_dots(100, 17))
for i in range(20):
    write_test("line_with_dots_alot%d.in" % i, line_with_dots(MAX_POS, 100))

print "same..."
for N in [10, 100, 500, 1000]:
    write_test("same%d.in" % N, same(N))
