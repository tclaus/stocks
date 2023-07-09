echo Building stocks
cmake -DCMAKE_BUILD_TYPE=Release -S ./ -B build
cmake --build ./build --target Stocks -- -j 4

echo building package
cd package
cp ../build/Stocks ./
package create -i ../.PackageInfo Stocks-x86