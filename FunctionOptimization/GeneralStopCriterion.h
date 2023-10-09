#pragma once
#include <vector>
#include "GeneralFunction.h"

/**
 * Abstract class for optimization processes stopping criteria.
 */
class GeneralStopCriterion
{
public:
    /**
     * Checks whether to stop the optimization process based on the given trajectory.
     *
     * \param trajectory Trajectory of the optimization process.
     * \param function A function being optimized. Is nullptr if not needed.
     * \return true if the optimization process should be stopped, false otherwise.
     */
    virtual bool stop(const std::vector<std::vector<double>>& trajectory, const GeneralFunction *function = nullptr) const = 0;

	virtual ~GeneralStopCriterion() = default;
};

