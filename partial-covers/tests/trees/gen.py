import random

random.seed(42)


def line(N):
    return [(i, i + 1) for i in range(1, N)]


def rand(N):
    l = line(N)
    random.shuffle(l)
    return l


def connect_binary(N):
    """ connects elements i, i+2**k then a, i+2**(k-1) and so on """
    x = 1
    while 2 * x <= N:
        x *= 2

    edges = []

    while x > 0:
        for i in range(x):
            if i >= N:
                break
            edges.append((i + 1, i + x + 1))
        x = x // 2

    return edges


def rand_tree(N):
    edges = []
    for i in range(2, N + 1):
        edges.append((i, random.randint(1, i - 1)))
    random.shuffle(edges)
    return edges


def write_test(fname, test):
    print fname
    with open(fname, "w") as f:
        N = len(test) + 1
        f.write("%d\n" % N)
        f.write("\n".join("%d %d" % x for x in test))
        f.write("\n")


write_test("hand1.in", [(1, 2), (3, 5), (4, 3), (1, 3)])

for i in [3, 5, 10, 15, 20, 30, 50, 100, 1000]:
    write_test("line%d.in" % i, line(i))
    write_test("invline%d.in" % i, line(i)[::-1])
    write_test("randline%d.in" % i, rand(i))
    write_test("rand_tree%d.in" % i, rand_tree(i))
    write_test("connect_binary%d.in" % i, connect_binary(i))
