#pragma once
#include "GeneralStopCriterion.h"

/**
* Implements a stopping criterion based on the number of iterations.
*/
class IterationsNumberSC :
    public GeneralStopCriterion
{
protected:
    size_t _iterations_number;
public:
    IterationsNumberSC(size_t iterations_number = 1000) : _iterations_number(iterations_number) {};

    void set_iterations_number(size_t iterations_number) { _iterations_number = iterations_number; };

    size_t get_iterations_number() const { return _iterations_number };

    /**
     * Implements a stopping criterion based on the number of iterations.
     *
     * \param trajectory Trajectory of the optimization process.
     * \param function Is not used in this criterion.
     * \return true if the optimization process should be stopped, false otherwise.
     */
    bool stop(const std::vector<std::vector<double>>& trajectory, const GeneralFunction* function = nullptr) const override;

    ~IterationsNumberSC() override = default;
};

