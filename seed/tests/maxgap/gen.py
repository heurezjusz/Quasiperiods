import random


N = [1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 8, 9, 10, 11, 12, 20, 50, 100, 200, 400, 1000]

for i, n in enumerate(N):
    with open('random%d.in' % i, 'w') as f:
        random.seed(100 + i)
        l = range(n)
        random.shuffle(l)

        f.write(str(n) + '\n')
        f.write(" ".join([str(x) for x in l]) + "\n")
