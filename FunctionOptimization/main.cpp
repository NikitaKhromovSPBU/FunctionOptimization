#include <iostream>

#include "AbsoluteValueDifferenceSC.h"
#include "ExpModulatedSin.h"
#include "FletcherReevesOptimizer.h"
#include "HimmelblauFunction.h"
#include "IterationsNumberSC.h"
#include "LeviFunction.h"
#include "RectangularArea.h"
#include "RosenbrockFunction.h"

int main()
{

    auto rect = RectangularArea(std::vector<double>{-5, 5, -5, 5});
    const GeneralStopCriterion *sc = new AbsoluteValueDifferenceSC(1000, 1e-16);
    const GeneralFunction *func = new LeviFunction();
    GeneralOptimizer *opt = new FletcherReevesOptimizer(func, std::vector<double>{1.5, 1.5}, rect, sc);

    opt->optimize();

    std::cout << opt->get_optimizing_point()[0] << ' ' << opt->get_optimizing_point()[1] << ' ' << opt->get_optimized_value();
}
