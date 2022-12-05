#include "newModel.cc"
#include "newModel.h"
#include <cstdint>
#include <functional>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdint.h>
#include <vector>

PYBIND11_MODULE(newModel, m) {
  m.doc() = "New model";

  pybind11::class_<newModel>(m, "newModel")
      .def(pybind11::init<double, int>())
      .def("getPlayers", &newModel::getPlayers)
      .def("getLambdas", &newModel::getLambdas)
      .def("couples", &newModel::couples)
      .def("evolveUniform", &newModel::evolveUniform)
      .def("evolveSavings", &newModel::evolveSavings);
}
