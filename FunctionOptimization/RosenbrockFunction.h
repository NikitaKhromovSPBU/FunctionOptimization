#pragma once
#include "GeneralFunction.h"
class RosenbrockFunction :
    public GeneralFunction
{
public:
    RosenbrockFunction() : GeneralFunction(3) {};

    double evaluate(const std::vector<double>& parameters) const override;

    std::vector<double> get_gradient(const std::vector<double>& parameters) const override;

    ~RosenbrockFunction() override = default;
};

