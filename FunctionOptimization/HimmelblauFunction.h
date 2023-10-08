#pragma once
#include "GeneralFunction.h"
class HimmelblauFunction : public GeneralFunction
{
  public:
    HimmelblauFunction() : GeneralFunction(2){};

    double evaluate(const std::vector<double> &parameters) const override;

    std::vector<double> get_gradient(const std::vector<double> &parameters) const override;

    ~HimmelblauFunction() override = default;
};
