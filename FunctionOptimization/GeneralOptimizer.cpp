#include "GeneralOptimizer.h"

GeneralOptimizer::GeneralOptimizer(const GeneralFunction *&f, const std::vector<double> &starting_point,
                                   RectangularArea area, const GeneralStopCriterion *&sc)
    : _area(std::move(area)), _trajectory({starting_point}),
      _result_function_value(std::numeric_limits<double>::quiet_NaN())
{
    if (!_area.contains(starting_point))
        throw std::exception("Starting point must be within the given rectangular area.");

    switch (f->get_type())
    {
    case GeneralFunction::FunctionType::ExpSin:
        _function = new ExpModulatedSin();
        break;
    case GeneralFunction::FunctionType::Himmelblau:
        _function = new HimmelblauFunction();
        break;
    case GeneralFunction::FunctionType::Levi:
        _function = new LeviFunction();
        break;
    case GeneralFunction::FunctionType::Rosenbrock:
    default:
        _function = new RosenbrockFunction();
        break;
    }

    switch (sc->get_stop_criterion_type())
    {
    case GeneralStopCriterion::StopCriterionType::AbsoluteValueDifference:
        _sc = new AbsoluteValueDifferenceSC(*dynamic_cast<const AbsoluteValueDifferenceSC *>(sc));
        break;
    case GeneralStopCriterion::StopCriterionType::IterationsNumber:
    default:
        _sc = new IterationsNumberSC(*dynamic_cast<const IterationsNumberSC *>(sc));
        break;
    }
}

GeneralOptimizer::GeneralOptimizer(const GeneralFunction *&f, const std::vector<double> &starting_point,
                                   RectangularArea area, GeneralStopCriterion *&&sc)
    : _area(std::move(area)), _sc(sc), _trajectory({starting_point}),
      _result_function_value(std::numeric_limits<double>::quiet_NaN())
{
    if (!_area.contains(starting_point))
        throw std::exception("Starting point must be within the given rectangular area.");

    switch (f->get_type())
    {
    case GeneralFunction::FunctionType::ExpSin:
        _function = new ExpModulatedSin();
        break;
    case GeneralFunction::FunctionType::Himmelblau:
        _function = new HimmelblauFunction();
        break;
    case GeneralFunction::FunctionType::Levi:
        _function = new LeviFunction();
        break;
    case GeneralFunction::FunctionType::Rosenbrock:
    default:
        _function = new RosenbrockFunction();
        break;
    }

    sc = nullptr;
}

GeneralOptimizer::GeneralOptimizer(GeneralFunction *&&f, const std::vector<double> &starting_point,
                                   RectangularArea area, const GeneralStopCriterion *&sc)
    : _area(std::move(area)), _function(f), _trajectory({starting_point}),
      _result_function_value(std::numeric_limits<double>::quiet_NaN())
{
    if (!_area.contains(starting_point))
        throw std::exception("Starting point must be within the given rectangular area.");

    f = nullptr;

    switch (sc->get_stop_criterion_type())
    {
    case GeneralStopCriterion::StopCriterionType::AbsoluteValueDifference:
        _sc = new AbsoluteValueDifferenceSC(*dynamic_cast<const AbsoluteValueDifferenceSC *>(sc));
        break;
    case GeneralStopCriterion::StopCriterionType::IterationsNumber:
    default:
        _sc = new IterationsNumberSC(*dynamic_cast<const IterationsNumberSC *>(sc));
        break;
    }
}

GeneralOptimizer::GeneralOptimizer(GeneralFunction *&&f, const std::vector<double> &starting_point,
                                   RectangularArea area, GeneralStopCriterion *&&sc)
    : _area(std::move(area)), _function(f), _sc(sc), _trajectory({starting_point}),
      _result_function_value(std::numeric_limits<double>::quiet_NaN())
{
    if (!_area.contains(starting_point))
        throw std::exception("Starting point must be within the given rectangular area.");

    f = nullptr;

    sc = nullptr;
}

double GeneralOptimizer::optimize()
{
    while (!_sc->stop(_trajectory, _function))
    {
        step();
    }
    return _result_function_value = _function->evaluate(*_trajectory.rbegin());
}
