#include "SparseMatrix.hpp"
#include "network.cc"
#include "network.h"
#include <cstdint>
#include <functional>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdint.h>
#include <vector>

PYBIND11_MODULE(network, m) {
  m.doc() = "Boltzmann";

  pybind11::class_<network>(m, "network")
      .def(pybind11::init<uint16_t, uint16_t, uint16_t>())
      .def("getRows", &network::getRows)
      .def("getCols", &network::getCols)
      .def("players", &network::players)
      .def("getPoors", &network::getPoors)
      .def("couples", &network::couples)
      .def("createLinks", &network::createLinks)
      .def("exists", &network::exists)
      .def("printMatrix", &network::printMatrix)
      .def("evolveUniform", &network::evolveUniform)
      .def("evolvePrefAtt", &network::evolvePrefAtt)
      .def("evolvePrefAttNoTax", &network::evolvePrefAttNoTax)
      .def("evolveFixed", &network::evolveFixed)
      .def("evolvebyLink", &network::evolvebyLink)
      .def("flatTax", &network::flatTax)
      .def("checkPoor", &network::checkPoor)
      .def("calcProb", &network::calcProb)
      .def("print", &network::print);
}
