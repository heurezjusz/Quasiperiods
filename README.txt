======== Quasiperiods ========
Experimental Evaluation of Algorithms for Computing Quasiperiods



=== Implementations ===


** Directory cover **
Directory "cover/prog" contains implementations if algorithms computing shortest cover of the string.

  filename                | algorithm
 -------------------------|----------------------------------------------------------
  cover_afi.cpp           | Apostolico
  cover_breslauer.cpp     | Breslauer
  cover_folk.cpp          | folklore O(nlog(n))
  cover_ms.cpp            | Moore and Smyth
  cover_ms_static_mem.cpp | Moore and Smyth with static array instead of std::vector

To compile all programs run "make -C cover/prog". Input of all executable files is a single string, output
is the length of the cover.


** Directory seed **
Directory "seed/" contains implementations if algorithms computing shortest seed of the string. Command make -C seed builds following executable files:

  filename         | algorithm                                  | input type
 ------------------|--------------------------------------------|------------
  seed_imp.e       | Iliopoulos                                 | string
  seed_imp_int.e   | Iliopoulos                                 | integers
  seed_lin.e       | Kociumaka                                  | string
  seed_lin_int.e   | Kociumaka                                  | integers
  seed_nlogn.e     | simplified O(nlog(n)) version of Kociumaka | string
  seed_nlogn_int.e | simplified O(nlog(n)) version of Kociumaka | integers

If input type is "string", the executable reads single string from stdin. For "integers" it expects N integers in format:
N
a1 a2 a3... aN

This input format allows us to test algorithms on tests with huge alphabets.
Output format of all executables is a list if packages.


** Directory partial-covers **
Directory "partial-covers" contains implementations if algorithms computing partial covers of the string. Command make -C partial-covers builds following executable files:

  filename                | description
 -------------------------|-
  partial_covers_single.e | Solution for Partial Covers problem. It reads from input a string and a float,
                          | representing input string T and value Alpha in percents. On output prints two lines.
                          | In the first one prints the length of the shortest partial cover covering at least
                          | Alpha positions. On the second line there are starting positions of occurrences of resulting
                          | partial covers. Each partial cover is listed once.
                          |
  partial_covers_all.e    | Solution for All Partial Covers problem. Input is a single string T.
                          | On output print |T| lines in format i:x_i, where x_i is the length of the shortest partial cover
                          | which covers at least i positions.
                          |
  slow_*                  | Brute force solutions of above problems, used in correctness tests.



=== Performance testing tools ===

In directories "cover_timetests" and "seed_timetests" are testing tools allowing to run experiments we made in our paper. Usage:

- "make" prepares executable files
- "python3 run.py part"  measures execution times on tests from chosen part and saves it in report_part.txt.
        List of parts is available by running python3 run.py help. Tests are chosen in random order.
- "python3 plot.py part plot-type" plots results saved in report_part.txt. Plot type defines values on x-axis.
        Possible types are: "size" (default), "period", "alphabet" and "cover/seed".



=== Unit tests ===

In seed and partial-covers directories there is test subdirectory containing Python script for running all unit tests.
Usage: "python test.py all".

To run tests in "cover" directory execute "make run_all". To run tests only on solution cover_XXX.cpp execute "make run_XXX".