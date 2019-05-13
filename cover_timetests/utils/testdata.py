def _get_test_size_from_name(testname):
    fname = str(testname)
    N = fname.split("_")[1]
    return int(N)


def get_test_size(part, testname):
    if part in ["random", "recursive"]:
        return _get_test_size_from_name(testname)
    else:
        raise NotImplementedError
