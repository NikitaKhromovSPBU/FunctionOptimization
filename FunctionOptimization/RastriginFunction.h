#pragma once
#include "GeneralFunction.h"
class RastriginFunction :
    public GeneralFunction
{
public:
    RastriginFunction() : GeneralFunction(2) {};

    double evaluate(const std::vector<double>& parameters) const override;

    std::vector<double> get_gradient(const std::vector<double>& parameters) const override;

    ~RastriginFunction() override = default;

protected:
    const double PI = acos(-1);
};

