#pragma once
#include <vector>

class RectangularArea
{
  private:
    /**
     * Space dimensionality.
     */
    size_t _dimensions;

    /**
     * Rectangular area boundary array.
     * 2i-th and 2i+1-st elements are the lower and the upper bounds for the i-th coordinate respectively.
     */
    std::vector<double> _bounds;

  public:
    /**
     * Creates an empty rectangular area with given number of dimensions.
     *
     * @param dimensions Number of dimensions of the RectangularArea object.
     */
    RectangularArea(size_t dimensions) : _dimensions(dimensions), _bounds(std::vector<double>(2 * dimensions)){};

    /**
     * Creates a rectangular area with given bounds.
     *
     * \param dimensions Number of dimensions of the RectangularArea object.
     */
    RectangularArea(const std::vector<double> &bounds)
        : _dimensions(bounds.size() % 2 == 0 ? bounds.size() / 2 : throw std::exception("Odd number of bounds.")),
          _bounds(bounds){};

    void set_bounds(const std::vector<double> &bounds)
    {
        _bounds = bounds;
    };

    std::vector<double> get_bounds() const
    {
        return _bounds;
    };

    size_t get_dimensions() const
    {
        return _dimensions;
    };

    /**
     * Checks whether the RectangularArea object has valid bounds.
     *
     * \return true if the bounds are valid, false otherwise.
     */
    bool is_valid() const;

    /**
     * Checks whether the given point lies within the RectangularArea object.
     *
     * \param point A vector of coordinates of the point in question. Must be of length equal to the number of
     * dimensions of the RectangularArea object.
     * \return true if the point lies within the rectangle, false otherwise.
     */
    bool contains(const std::vector<double> &point) const;
};