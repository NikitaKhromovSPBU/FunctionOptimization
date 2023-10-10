#pragma once
#include "GeneralStopCriterion.h"

/**
 * Implements a stopping criterion based on the absolute difference values of the function at last two different points.
 */
class AbsoluteValueDifferenceSC : public GeneralStopCriterion
{
  protected:
    double _precision;

  public:
    explicit AbsoluteValueDifferenceSC(size_t iterations_number = 1000, double precision = 1e-6)
        : GeneralStopCriterion(iterations_number), _precision(precision)
    {
        if (precision <= 0)
            throw std::exception("Precision must be a positive number.");
    };

    void set_precision(double precision)
    {
        if (precision <= 0)
            throw std::exception("Precision must be a positive number.");
        else
            _precision = precision;
    }

    double get_precision() const
    {
        return _precision;
    };

    /**
     * Implements a stopping criterion based on the absolute difference values of the function at last two different points.
     *
     * \param trajectory Trajectory of the optimization process.
     * \param function A function being optimized.
     * \return true if the optimization process should be stopped, false otherwise.
     * \throw std::exception The size of one of the points in trajectory and the number of dimensions are not equal.
     */

    ~AbsoluteValueDifferenceSC() override = default;

  protected:
    bool stop_criterion(const std::vector<std::vector<double>> &trajectory,
                        const GeneralFunction *function) const override;
};
