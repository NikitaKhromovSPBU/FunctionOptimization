#include "IterationsNumberSC.h"

bool IterationsNumberSC::stop(const std::vector<std::vector<double>>& trajectory, const GeneralFunction* function) const
{
    return trajectory.size() >= _iterations_number;
}
