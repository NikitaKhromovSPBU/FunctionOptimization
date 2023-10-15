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
#include "RelativeDifferenceSC.h"

int main()
{
    char input{};

    while (true)
    {
        std::cout << "Choose the function to optimize:\n\n"
                  << "1) Exponent modulated sine (e^x * sin(y)),\n"
                  << "2) Himmelblau function, dim = 2\n"
                  << "3) Levi function, dim = 2\n"
                  << "4) Rosenbrock function, dim = 3\n"
                  << std::endl;

        GeneralFunction *function{};
        bool correct_input{};

        while (!correct_input)
        {
            std::cin >> input;
            switch (input)
            {
            case '1':
                function = new ExpModulatedSin();
                correct_input = true;
                break;
            case '2':
                function = new HimmelblauFunction();
                correct_input = true;
                break;
            case '3':
                function = new LeviFunction();
                correct_input = true;
                break;
            case '4':
                function = new RosenbrockFunction();
                correct_input = true;
                break;
            default:
                std::cerr << "Wrong function number, enter a number from 1 to 4.\n";
                break;
            }
        }
        std::cout << std::endl;

        const size_t dimensions = function->get_dimensions();

        std::cout << "Enter the boundaries of the area in which the function will be optimized\n"
                  << "You must enter " << (2 * dimensions)
                  << " real numbers, each pair of subsequent numbers are the lower and upper bounds for the "
                     "corresponding coordinate, respectively:\n\n";

        correct_input = false;
        RectangularArea area(dimensions);
        while (!correct_input)
        {
            for (size_t i{}; i < 2 * dimensions; ++i)
            {
                std::cin >> area[i];
            }

            if (area.is_valid())
            {
                correct_input = true;
            }
            else
            {
                std::cerr << "The rectangular area is not valid: one of the lower bounds is greater or equal to the "
                             "corresponding upper bound.\n";
            }
        }
        std::cout << std::endl;

        std::cout << "Choose the optimization process stopping criterion:\n\n"
            << "1) Stop, when the number of iterations is equal to some n\n"
            << "2) Stop, when the number of iterations is equal to some n, or when |f(x_{n+1}) - f(x_{n})| < e "
            "is fulfilled for some e\n"
            << "3) Stop, when the number of iterations is equal to some n, or when |f(x_{n+1}) - f(x_{n})| / |f(x_{n})| < e "
            "is fulfilled for some e\n\n";

        GeneralStopCriterion *sc{};
        correct_input = false;
        while (!correct_input)
        {
            size_t n;
            double e;
            std::cin >> input;
            switch (input)
            {
            case '1':

                std::cout << "\nEnter maximum number of iterations n = ";
                std::cin >> n;
                sc = new IterationsNumberSC(n);
                correct_input = true;
                break;
            case '2':
                std::cout << "\nEnter maximum number of iterations n = ";
                std::cin >> n;
                std::cout << "\nEnter precision e = ";
                std::cin >> e;
                while (e <= 0)
                {
                    std::cerr << "Wrong precision value, e must be positive.\n e = ";
                    std::cin >> e;
                }
                sc = new AbsoluteValueDifferenceSC(n, e);
                correct_input = true;
                break;
            case '3':
                std::cout << "\nEnter maximum number of iterations n = ";
                std::cin >> n;
                std::cout << "\nEnter precision e = ";
                std::cin >> e;
                while (e <= 0)
                {
                    std::cerr << "Wrong precision value, e must be positive.\n e = ";
                    std::cin >> e;
                }
                sc = new RelativeDifferenceSC(n, e);
                correct_input = true;
                break;
            default:
                std::cerr << "Wrong stop criterion number, enter a number from 1 to 2.\n";
                break;
            }
        }
        std::cout << std::endl;

        std::cout << "Enter the starting point coordinates, it must be within the given rectangular area\n"
                  << "You must enter " << dimensions << " real numbers:\n\n";
        std::vector<double> starting_point(dimensions);
        correct_input = false;
        while (!correct_input)
        {
            for (size_t i{}; i < dimensions; ++i)
            {
                std::cin >> starting_point[i];
            }
            if (area.contains(starting_point))
                correct_input = true;
            else
            {
                std::cerr << "The given point lies outside the given rectangular area.\n";
            }
        }
        std::cout << std::endl;

        std::cout << "Choose the optimization method:\n\n"
                  << "1) Fletcher-Reeves conjugate gradient method\n"
                  << "2) Stohastic method\n\n";

        GeneralOptimizer *optimizer{};
        correct_input = false;
        while (!correct_input)
        {
            std::cin >> input;
            switch (input)
            {
            case '1':
                optimizer = new FletcherReevesOptimizer(function, starting_point, area, sc);
                correct_input = true;
                break;
            case '2':
                double p, delta, alpha;
                std::cout
                    << "Enter the probability of generating a point inside the vicinity of the last point:\n p = ";
                std::cin >> p;
                while (p < 0 || p > 1)
                {
                    std::cerr << "Probability must be within range [0,1].\n p = ";
                    std::cin >> p;
                }

                std::cout << "Enter the radius of the ball in the Chebyshev metric in which the new point might be "
                             "generated with probability p:\n delta = ";
                std::cin >> delta;
                while (delta <= 0)
                {
                    std::cerr << "Radius must be positive.\n delta = ";
                    std::cin >> delta;
                }

                std::cout << "Enter the delta reduction rate:\n alpha = ";
                std::cin >> alpha;
                while (alpha <= 0)
                {
                    std::cerr << "Reduction rate must be positive.\n alpha = ";
                    std::cin >> alpha;
                }

                optimizer = new StohasticOptimizer(function, starting_point, area, sc, p, delta, alpha);
                correct_input = true;
                break;
            default:
                std::cerr << "Wrong stop criterion number, enter a number from 1 to 2.\n";
                break;
            }
        }
        std::cout << std::endl;

        optimizer->optimize();
        std::cout << "Resulting point: x_" << optimizer->trajectory_size() << " = (";
        for (size_t i{}; i < dimensions - 1; ++i)
        {
            std::cout << optimizer->get_optimizing_point()[i] << ", ";
        }
        std::cout << optimizer->get_optimizing_point()[dimensions - 1] << ")\n"
                  << "Resulting function value: f(x_" << optimizer->trajectory_size()
                  << ") = " << optimizer->get_optimized_value() << std::endl
                  << "\nWould you like to input another parameters? Y/n: ";

        bool repeat{};
        std::cin >> input;
        switch (input)
        {
        case 'Y':
            repeat = true;
            std::cout << '\n';
            break;
        default:
            break;
        }

        delete optimizer;
        delete sc;
        delete function;

        if (!repeat)
            break;
    }
}
