#include "FletcherReevesOptimizer.h"

const double FletcherReevesOptimizer::golden_ratio{ 1.618033988749894848 };

FletcherReevesOptimizer::FletcherReevesOptimizer(const GeneralFunction *&f, std::vector<double> starting_point,
                                                 RectangularArea area, const GeneralStopCriterion *&sc)
    : GeneralOptimizer(f, std::move(starting_point), area, sc), grad_new(f->get_gradient(starting_point)), p(grad_new)
{
    for (auto &x : p)
    {
        x = -x;
    }
}

FletcherReevesOptimizer::FletcherReevesOptimizer(const GeneralFunction *&f, std::vector<double> starting_point,
                                                 RectangularArea area, GeneralStopCriterion *&&sc)
    : GeneralOptimizer(f, std::move(starting_point), area, std::move(sc)), grad_new(f->get_gradient(starting_point)),
      p(grad_new)
{
    for (auto &x : p)
    {
        x = -x;
    }
}

FletcherReevesOptimizer::FletcherReevesOptimizer(GeneralFunction *&&f, std::vector<double> starting_point,
                                                 RectangularArea area, const GeneralStopCriterion *&sc)
    : GeneralOptimizer(std::move(f), std::move(starting_point), area, sc), grad_new(f->get_gradient(starting_point)),
      p(grad_new)
{
    for (auto &x : p)
    {
        x = -x;
    }
}

FletcherReevesOptimizer::FletcherReevesOptimizer(GeneralFunction *&&f, std::vector<double> starting_point,
                                                 RectangularArea area, GeneralStopCriterion *&&sc)
    : GeneralOptimizer(std::move(f), std::move(starting_point), area, std::move(sc)),
      grad_new(f->get_gradient(starting_point)), p(grad_new)
{
    for (auto &x : p)
    {
        x = -x;
    }
}

double find_interception(const std::vector<double> &v, const std::vector<double> &start_point, const RectangularArea &rect)
{
    if (v.size() != rect.get_dimensions())
        throw std::exception("Number of dimensions of vector and rectangle are not equal.");

    double res = std::min(abs((start_point[0] - rect[0]) / v[0]), abs((start_point[0] - rect[1]) / v[0]));
    for (size_t i{1}; i < v.size(); ++i)
    {
        res = std::min(abs((start_point[i] - rect[2 * i]) / v[i]), res);
        res = std::min(abs((start_point[i] - rect[2 * i + 1]) / v[i]), res);
    }
    return res;
}

void FletcherReevesOptimizer::step()
{
    const double precision{ 1e-8 };

    const std::vector<double> &starting_point{*_trajectory.rbegin()};
    const size_t dimensions{starting_point.size()};
    std::vector<double> p_moved(dimensions);
    for (size_t i{}; i < dimensions; ++i)
    {
        p_moved[i] = starting_point[i] + p[i];
    }

    double max_alpha = find_interception(p_moved, starting_point, _area);

    double left_alpha{}, right_alpha{max_alpha},
        left_alpha_temp{right_alpha - (right_alpha - left_alpha) / golden_ratio},
        right_alpha_temp{left_alpha + (right_alpha - left_alpha) / golden_ratio};
    double left_function_value{}, right_function_value{};
    bool left_known;
    std::vector<double> short_vec_temp(dimensions), long_vec_temp(dimensions);

    for (size_t i{}; i < dimensions; ++i)
    {
        short_vec_temp[i] = starting_point[i] + left_alpha_temp * p[i];
        long_vec_temp[i] = starting_point[i] + right_alpha_temp * p[i];
    }

    left_function_value = _function->evaluate(short_vec_temp);
    right_function_value = _function->evaluate(long_vec_temp);
    if (left_function_value < right_function_value)
    {
        right_alpha = right_alpha_temp;
        right_function_value = left_function_value;
        left_known = false;
    }
    else
    {
        left_alpha = left_alpha_temp;
        left_function_value = right_function_value;
        left_known = true;
    }

    while (right_alpha - left_alpha > precision)
    {
        left_alpha_temp = right_alpha - (right_alpha - left_alpha) / golden_ratio;
        right_alpha_temp = left_alpha + (right_alpha - left_alpha) / golden_ratio;

        if (left_known)
        {
            for (size_t i{}; i < dimensions; ++i)
            {
                long_vec_temp[i] = starting_point[i] + right_alpha_temp * p[i];
            }
            right_function_value = _function->evaluate(long_vec_temp);
        }
        else
        {

            for (size_t i{}; i < dimensions; ++i)
            {
                short_vec_temp[i] = starting_point[i] + left_alpha_temp * p[i];
            }
            left_function_value = _function->evaluate(short_vec_temp);
        }

        if (left_function_value < right_function_value)
        {
            right_alpha = right_alpha_temp;
            right_function_value = left_function_value;
            left_known = false;
        }
        else
        {
            left_alpha = left_alpha_temp;
            left_function_value = right_function_value;
            left_known = true;
        }
    }

    alpha = (left_alpha + right_alpha) / 2;

    std::vector<double> new_point(dimensions);

    for (size_t i{}; i < dimensions; ++i)
    {
        new_point[i] = starting_point[i] + alpha * p[i];
    }

    if (_function->evaluate(new_point) < _function->evaluate(starting_point))
        _trajectory.push_back(new_point);
    else
        _trajectory.push_back(starting_point);

    grad_prev = grad_new;
    grad_new = _function->get_gradient(new_point);

    double numerator{}, denominator{};
    for (size_t i{}; i < dimensions; ++i)
    {
        numerator += grad_new[i] * grad_new[i];
        denominator += grad_prev[i] * grad_prev[i];
    }

    beta = numerator / denominator;

    for (size_t i{}; i < dimensions; ++i)
    {
        p[i] = -grad_new[i] + beta * p[i];
    }
}
