#

g++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) ./src/binding.cc -o network$(python3-config --extension-suffix)
mv *.so ~/.local/lib/python*/site-packages/
