import random


N = [6, 6, 6, 6, 6, 10, 20, 50, 100, 200, 400, 1000, 1, 2, 3, 4, 5]

for i, n in enumerate(N):
    with open('random%d.in' % i, 'w') as f:
        random.seed(100 + i)
        l = range(n)
        random.shuffle(l)

        f.write(str(n) + '\n')
        f.write(" ".join([str(x) for x in l]) + "\n")
