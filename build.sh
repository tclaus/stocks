echo Building stocks
cmake -DCMAKE_BUILD_TYPE=Release -DHAIKU_ENABLE_I18N=ON -S ./ -B build
cmake --build ./build --target Stocks -- -j 2

echo Building package

cd package
cp ../build/Stocks ./apps
package create -v -i ../.PackageInfo ../stocks-0.4-x86_64.hpkg
