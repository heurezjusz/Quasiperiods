rm report.out -f

for i in *.in
do
    >&2 echo "test $i"
    echo "$i" >> report.out
    \time -f "%e" ./seed_lin.e < $i > lin.out 2>> report.out
    \time -f "%e" ./seed_nlogn.e < $i > nlogn.out 2>> report.out
done

python parse_report.py
