#pragma once
#include "GeneralFunction.h"
#include <vector>

/**
 * Abstract class for optimization processes stopping criteria.
 */
class GeneralStopCriterion
{
  protected:
    size_t _iterations_number;

  public:
    explicit GeneralStopCriterion(size_t iterations_number = 1000) : _iterations_number(iterations_number){};

    /**
     * Checks whether to stop the optimization process based on the given trajectory.
     *
     * \param trajectory Trajectory of the optimization process.
     * \param function A function being optimized. Is nullptr if not needed.
     * \return true if the optimization process should be stopped, false otherwise.
     */
    bool stop(const std::vector<std::vector<double>> &trajectory, const GeneralFunction *function = nullptr) const
    {
        return (trajectory.size() >= _iterations_number) || stop_criterion(trajectory, function);
    };

    void set_iterations_number(size_t iterations_number)
    {
        _iterations_number = iterations_number;
    };

    size_t get_iterations_number() const { return _iterations_number; };

    virtual ~GeneralStopCriterion() = default;

  protected:
    virtual bool stop_criterion(const std::vector<std::vector<double>> &trajectory,
                                const GeneralFunction *function = nullptr) const = 0;
};
