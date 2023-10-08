#pragma once
#include <vector>

class GeneralFunction
{
  private:
    size_t _dimensions;

  public:
    virtual double evaluate(const std::vector<double> &parameters) const = 0;
    virtual std::vector<double> get_gradient(const std::vector<double> &parameters) const = 0;
    size_t get_dimensions() const { return _dimensions; };
    virtual ~GeneralFunction() = default;
};
