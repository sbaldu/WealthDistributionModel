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

  pybind11::class_<SparseMatrix<bool>>(m, "SparseMatrix")
      .def(pybind11::init<>())
      .def(pybind11::init<int, int>())
      .def(pybind11::init<int>())
      .def(pybind11::init<SparseMatrix<bool> const &>())
      .def("insert", static_cast<void (SparseMatrix<bool>::*)(int, int, bool)>(
                         &SparseMatrix<bool>::insert))
      .def("insert", static_cast<void (SparseMatrix<bool>::*)(int, bool)>(
                         &SparseMatrix<bool>::insert))
      .def("insert_or_assign",
           static_cast<void (SparseMatrix<bool>::*)(int, int, bool)>(
               &SparseMatrix<bool>::insert_or_assign))
      .def("insert_or_assign",
           static_cast<void (SparseMatrix<bool>::*)(int, bool)>(
               &SparseMatrix<bool>::insert_or_assign))
      .def("erase", &SparseMatrix<bool>::erase)
      .def("clear", &SparseMatrix<bool>::clear)
      .def("contains",
           static_cast<bool (SparseMatrix<bool>::*)(int, int) const>(
               &SparseMatrix<bool>::contains))
      .def("contains", static_cast<bool (SparseMatrix<bool>::*)(int) const>(
                           &SparseMatrix<bool>::contains))
      .def("getRow", &SparseMatrix<bool>::getRow)
      .def("getCol", &SparseMatrix<bool>::getCol)
      .def("getRndRowElement", &SparseMatrix<bool>::getRndRowElement)
      .def("getRndColElement", &SparseMatrix<bool>::getRndColElement)
      .def("getNormRows", &SparseMatrix<bool>::getNormRows)
      .def("getNormCols", &SparseMatrix<bool>::getNormCols)
      .def("getRowDim", &SparseMatrix<bool>::getRowDim)
      .def("getColDim", &SparseMatrix<bool>::getColDim)
      .def("size", &SparseMatrix<bool>::size)
      .def("print", &SparseMatrix<bool>::print);

  pybind11::class_<network>(m, "network")
      .def(pybind11::init<uint16_t, uint16_t, uint16_t>())
      .def("getRows", &network::getRows)
      .def("getCols", &network::getCols)
      .def("getPlayers", &network::getPlayers)
      .def("getPoors", &network::getPoors)
      .def("couples", &network::couples)
      .def("playersMoney", &network::playersMoney)
      .def("createLinks", &network::createLinks)
      .def("exists", &network::exists)
      .def("printMatrix", &network::printMatrix)
      .def("evolveUniform", &network::evolveUniform)
      .def("evolvePrefAtt", &network::evolvePrefAtt)
      .def("evolvePrefAttNoTax", &network::evolvePrefAttNoTax)
      .def("evolveFixed", &network::evolveFixed)
      .def("flatTax", &network::flatTax)
      .def("evolveSavings", &network::evolveSavings)
      .def("checkPoor", &network::checkPoor)
      .def("calcProb", &network::calcProb)
      .def("print", &network::print);
}
