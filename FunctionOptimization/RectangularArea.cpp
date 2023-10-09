#include "RectangularArea.h"

bool RectangularArea::contains(const std::vector<double> &point) const
{
    if (point.size() != _dimensions)
        throw std::exception("Wrong number of dimensions.");

    bool result = true;

    for (size_t i{}; i < _dimensions; ++i)
    {
        if (point[i] < _bounds[2 * i] || point[i] > _bounds[2 * i + 1])
            return false;
    }
    return true;
}
