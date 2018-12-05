with open('report.out', 'r') as f:
    lines = f.read().split()


def prettyprint(a, b, c):
    print "%s \t| %s \t | %s" % (a, b, c)


prettyprint("test name", "time lin", "time nlogn")
for i in range(0, len(lines), 3):
    prettyprint(lines[i], lines[i + 1], lines[i + 2])
