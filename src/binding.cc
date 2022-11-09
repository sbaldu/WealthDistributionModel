#include "network.cc"
#include "network.h"
#include <functional>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdint.h>

PYBIND11_MODULE(network, m) {
  m.doc() = "Boltzmann";

  pybind11::class_<network>(m, "network")
      .def(pybind11::init<uint16_t, uint16_t, uint16_t>())
      .def("getPlayers", &network::getPlayers)
      .def("filterByLinks", &network::filterByLinks)
      .def("playersMoney", &network::playersMoney)
      .def("couples", &network::couples)
      .def("createBusinessMen", &network::createBusinessMen)
      .def("distributeBusinessMen", &network::distributeBusinessMen)
      .def("evolveUniform", &network::evolveUniform)
      .def("evolvePrefAtt", &network::evolvePrefAtt)
      .def("flatTax", &network::flatTax)
      .def("print", &network::print);
}
