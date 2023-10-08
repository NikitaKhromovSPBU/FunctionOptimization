#include "RastriginFunction.h"

double RastriginFunction::evaluate(const std::vector<double> &parameters) const
{
    if (parameters.size() != get_dimensions())
        throw std::exception("Wrong number of parameters");
    return 20 + parameters[0] * parameters[0] + parameters[1] * parameters[1] - 10 * cos(2 * PI * parameters[0]) -
           10 * cos(2 * PI * parameters[1]);
}

std::vector<double> RastriginFunction::get_gradient(const std::vector<double> &parameters) const
{
    if (parameters.size() != get_dimensions())
        throw std::exception("Wrong number of parameters");
    return std::vector<double>{2 * parameters[0] + 20 * PI * sin(2 * PI * parameters[0]),
                               2 * parameters[1] + 20 * PI * sin(2 * PI * parameters[1])};
}
