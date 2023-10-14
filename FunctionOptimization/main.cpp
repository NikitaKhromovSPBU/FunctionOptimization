#include <iostream>

#include "AbsoluteValueDifferenceSC.h"
#include "ExpModulatedSin.h"
#include "FletcherReevesOptimizer.h"
#include "HimmelblauFunction.h"
#include "IterationsNumberSC.h"
#include "LeviFunction.h"
#include "RectangularArea.h"
#include "RosenbrockFunction.h"
#include "StohasticOptimizer.h"

int main()
{
    auto rect = RectangularArea(std::vector<double>{0.5,1.5, 0.5, 1.5});
    const GeneralStopCriterion *sc = new IterationsNumberSC(100'000);
    const GeneralFunction *func = new LeviFunction();
    GeneralOptimizer *opt = new StohasticOptimizer(func, std::vector<double>{0.8, 0.8}, rect, sc, 0.5, 0.05, 0.6);

    opt->optimize();

    std::cout << opt->get_optimizing_point()[0] << ' ' << opt->get_optimizing_point()[1] << ' ' << opt->get_optimized_value();
}
