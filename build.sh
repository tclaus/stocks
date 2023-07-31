echo Building stocks
cmake -DCMAKE_BUILD_TYPE=Release -S ./ -B build
cmake --build ./build --target Stocks -- -j 4

echo building package
mkdir -p package/apps
cd package
cp ../build/Stocks ./apps
package create -v -i ../.PackageInfo ../Stocks-0.1-x86.hpkg