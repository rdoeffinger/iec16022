#!/bin/bash

FAILED=0
export LD_LIBRARY_PATH="../.libs:$LD_LIBRARY_PATH"

../iec16022 -o testsuite-test.text -f Text -c "Aolash3l dee6Ieke OhBohm1C MengaR9m zaHaoQu2 huW3Uer8 ieg7chaJ haiKua1o"
../iec16022 -o testsuite-test.eps -f EPS -c "Aolash3l dee6Ieke OhBohm1C MengaR9m zaHaoQu2 huW3Uer8 ieg7chaJ haiKua1o"
../iec16022 -o testsuite-test.png -f PNG -c "Aolash3l dee6Ieke OhBohm1C MengaR9m zaHaoQu2 huW3Uer8 ieg7chaJ haiKua1o"
../iec16022 -o testsuite-test.bin -f Bin -c "Aolash3l dee6Ieke OhBohm1C MengaR9m zaHaoQu2 huW3Uer8 ieg7chaJ haiKua1o"
../iec16022 -o testsuite-test.hex -f Hex -c "Aolash3l dee6Ieke OhBohm1C MengaR9m zaHaoQu2 huW3Uer8 ieg7chaJ haiKua1o"
../iec16022 -o testsuite-test.utf8 -f utf8 -c "UEXPLR4-CBR3A3-001-TSK 13471 3216"

diff -b testsuite-test.text testsuite-example.text && echo "Text test passed" || { echo "Text test FAILED" && FAILED=1 ; }
diff -b testsuite-test.eps testsuite-example.eps && echo "EPS test passed" || { echo "EPS test FAILED" && FAILED=1 ; }
diff -b testsuite-test.png testsuite-example.png && echo "PNG test passed" || { echo "PNG test FAILED" && FAILED=1 ; }
diff -b testsuite-test.bin testsuite-example.bin && echo "Bin test passed" || { echo "Bin test FAILED" && FAILED=1 ; }
diff -b testsuite-test.hex testsuite-example.hex && echo "Hex test passed" || { echo "Hex test FAILED" && FAILED=1 ; }
diff -b testsuite-test.utf8 testsuite-example.utf8 && echo "UTF-8 test passed" || { echo "UTF-8 test FAILED" && FAILED=1 ; }

rm testsuite-test.*

exit $FAILED
