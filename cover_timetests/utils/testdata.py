def _get_test_size_random(testname):
    fname = str(testname)
    N = fname.split("_")[1]
    return int(N)


def get_test_size(part, testname):
    if part == "random":
        return _get_test_size_random(testname)
    else:
        raise NotImplementedError