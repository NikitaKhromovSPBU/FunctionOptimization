#pragma once
#include "GeneralFunction.h"
class ExpModulatedSin : public GeneralFunction
{
    ExpModulatedSin() : GeneralFunction(2){};

    double evaluate(const std::vector<double> &parameters) const override;

    std::vector<double> get_gradient(const std::vector<double> &parameters) const override;

    ~ExpModulatedSin() override = default;
};
