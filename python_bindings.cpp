#include <pybind11/pybind11.h>
#include "paymentProvider.h"

namespace py = pybind11;

PYBIND11_MODULE(paymentlib, module) {
    module.doc() = "Payment utilities exposed from C++";

    py::class_<PaymentProvider>(module, "PaymentProvider")
        .def(py::init<>())
        .def_static(
            "calculate_required_payment",
            &PaymentProvider::calculate_required_payment,
            py::arg("principal"),
            py::arg("annual_rate_percent"),
            py::arg("months"),
            "Calculate required monthly payment for an amortized loan"
        );

    module.def(
        "calculate_required_payment",
        &PaymentProvider::calculate_required_payment,
        py::arg("principal"),
        py::arg("annual_rate_percent"),
        py::arg("months"),
        "Calculate required monthly payment for an amortized loan"
    );
}
