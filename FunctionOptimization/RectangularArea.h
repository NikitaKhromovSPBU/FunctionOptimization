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
    RectangularArea(size_t dimensions) : _dimensions(dimensions), _bounds(std::vector<double>(2 * dimensions)){};

    RectangularArea(size_t dimensions, const std::vector<double> &bounds)
        : _dimensions(dimensions),
          _bounds(bounds.size() == 2 * dimensions ? bounds : throw std::exception("Wrong number of bounds.")){};

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

    bool contains(const std::vector<double> &point) const;
};
