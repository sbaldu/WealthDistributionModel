#include "network.cc"
#include "network.h"
#include <functional>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdint.h>
#include <vector>

PYBIND11_MODULE(network, m) {
  m.doc() = "Boltzmann";

  pybind11::class_<network>(m, "network")
      .def(pybind11::init<uint16_t, uint16_t, uint16_t>())
      .def("getPlayers", &network::getPlayers)
      .def("filterByLinks", &network::filterByLinks)
      .def("playersMoney",
           static_cast<std::vector<uint16_t> const (network::*)()>(
               &network::playersMoney))
      .def("playersMoney",
           static_cast<std::vector<uint16_t> const (network::*)(
               std::vector<Player> const &)>(&network::playersMoney))
      .def("couples", &network::couples)
      .def("createBusinessMen", &network::createBusinessMen)
      .def("distributeBusinessMen", &network::distributeBusinessMen)
      .def("evolveUniform", &network::evolveUniform)
      .def("evolvePrefAtt", &network::evolvePrefAtt)
      .def("flatTax", &network::flatTax)
      .def("print", &network::print);
  pybind11::class_<Player>(m, "Player")
      .def(pybind11::init<>())
      .def(pybind11::init<uint16_t, uint8_t>())
      .def(pybind11::init<const Player &>())
      .def("operator++", &Player::operator++)
      .def("operator--", &Player::operator--)
      .def("operator=", &Player::operator=)
      .def("operator+", &Player::operator+)
      .def("operator-", &Player::operator-);
}
