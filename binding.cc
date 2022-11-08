#include "src/network.cc"
#include "src/network.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdint.h>

PYBIND11_MODULE(network, m) {
  m.doc() = "Boltzmann";

  pybind11::class_<network>(m, "network")
      .def(pybind11::init<uint16_t, uint16_t, uint16_t>())
      .def("getPlayers", &network::getPlayers)
      .def("couples", &network::couples)
      .def("evolveUniform", &network::evolveUniform)
      .def("evolvePrefAtt", &network::evolvePrefAtt)
      .def("flatTax", &network::flatTax)
      .def("print", &network::print);
}
