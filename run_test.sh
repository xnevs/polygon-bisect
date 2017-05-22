#!/usr/bin/bash

ns=$(seq 100 100 900)
ns="$ns
$(seq 1000 1000 9000)"
ns="$ns
$(seq 10000 10000 90000)"
ns="$ns
$(seq 100000 20000 1000000)"

for n in $ns
do
    ./test-polygon-bisect $n 2>&1 1>/dev/null
done
