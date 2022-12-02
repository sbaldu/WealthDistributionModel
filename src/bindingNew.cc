#include "newModel.cc"
#include "newModel.h"
#include <cstdint>
#include <functional>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdint.h>
#include <vector>

PYBIND11_MODULE(network, m) {
  m.doc() = "Boltzmann";

  pybind11::class_<newModel>(m, "newModel")
      .def(pybind11::init<float, uint16_t, uint16_t>())
      .def("getRows", &newModel::getRows)
      .def("getCols", &newModel::getCols)
      .def("getPlayers", &newModel::getPlayers)
      .def("couples", &newModel::couples)
      .def("evolveUniform", &newModel::evolveUniform)
      .def("evolveSavings", &newModel::evolveSavings);
}
