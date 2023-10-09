#pragma once
#include "GeneralFunction.h"

/**
 * Implements the function \f$ f(x, y) = e^x\sin(y)\f$.
 */
class ExpModulatedSin : public GeneralFunction
{
    ExpModulatedSin() : GeneralFunction(2){};

    double evaluate(const std::vector<double> &parameters) const override;

    std::vector<double> get_gradient(const std::vector<double> &parameters) const override;

    ~ExpModulatedSin() override = default;
};
