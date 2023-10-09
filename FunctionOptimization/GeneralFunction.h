#pragma once
#include <vector>

/**
 * Abstract class for different functions.
 */
class GeneralFunction
{
  private:
    /**
     * Dimensionality of the function.
     */
    size_t _dimensions;

  public:
    /**
     * Evaluates the function in the given point.
     * 
     * \param parameters Coordinates in which the function is evaluated.
     * \return Value of the function on the given parameters.
     */
    virtual double evaluate(const std::vector<double> &parameters) const = 0;

    /**
     * Evaluates the gradient of the function.
     * 
     * \param parameters Coordinates in which the gradient is evaluated
     * \return Gradient vector on the given parameters.
     */
    virtual std::vector<double> get_gradient(const std::vector<double> &parameters) const = 0;

    size_t get_dimensions() const
    {
        return _dimensions;
    };

    virtual ~GeneralFunction() = default;

  protected:
    GeneralFunction(size_t d)
    {
        _dimensions = d;
    };
};
