#

g++ -O3 -Wall -shared -std=c++20 -fPIC $(python3 -m pybind11 --includes) ./src/bindingNew.cc -o newModel$(python3-config --extension-suffix)
mv *.so ~/.local/lib/python*/site-packages/
