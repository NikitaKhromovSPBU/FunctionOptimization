#pragma once
#include "GeneralOptimizer.h"
class FletcherReevesOptimizer : public GeneralOptimizer
{
  protected:
    double alpha;
    double beta;
    std::vector<double> grad_prev, grad_new, p;

  public:
    FletcherReevesOptimizer(const GeneralFunction *&f, std::vector<double> starting_point, RectangularArea area,
                            const GeneralStopCriterion *&sc);
    FletcherReevesOptimizer(const GeneralFunction*& f, std::vector<double> starting_point,
        RectangularArea area, GeneralStopCriterion*&& sc);
    FletcherReevesOptimizer(GeneralFunction*&& f, std::vector<double> starting_point,
        RectangularArea area, const GeneralStopCriterion*& sc);
    FletcherReevesOptimizer(GeneralFunction*&& f, std::vector<double> starting_point,
        RectangularArea area, GeneralStopCriterion*&& sc);

    ~FletcherReevesOptimizer() override = default;

    static const double golden_ratio;

protected:
    void step() override;
};