#include <cstddef>
#include <functional>
#include <cmath>

/**
 * @brief Uses the Newton-Raphson method to find a root of a function.
 *
 * This function applies the Newton-Raphson iteration method to approximate a root
 * of a given function `func`. The derivative of the function `dervi` is used in
 * each iteration. The method stops when the difference between consecutive
 * approximations is smaller than the specified tolerance or when the maximum
 * number of iterations is reached.
 *
 * @param func The function for which we want to find the root.
 * @param dervi The derivative of the function `func`.
 * @param initialGuess The initial guess for the root.
 * @param tolerance The stopping criterion; the method stops when the difference
 *                  between consecutive approximations is smaller than this value.
 * @param maxIteration The maximum number of iterations to perform.
 * @return The approximated root of the function.
 */
double newton_raphson(std::function<double(double)> func, std::function<double(double)> dervi,
                      double initialGuess, double tolerance, size_t maxIteration)
{
    size_t currentIteration = 0;
    double currentX = initialGuess;

    while (currentIteration <= maxIteration)
    {
        double previousX = currentX;

        double functionValue = func(previousX);
        double derivativeValue = dervi(previousX);

        if (std::abs(derivativeValue) < 1e-12)
            return currentX;

        currentX = previousX - functionValue / derivativeValue;

        if (std::abs(currentX - previousX) <= tolerance)
            return currentX;

        ++currentIteration;
    }

    return currentX; // Return the last computed value if max iteration is reached
}

int main()
{
    /**
     * @brief Defines the function for which we are finding the root.
     *
     * In this case, the function is x^2 - 3.
     */
    auto func = [](double x) -> double
    { return x * x - 3; };

    /**
     * @brief Defines the derivative of the function.
     *
     * In this case, the derivative is 2 * x.
     */
    auto dervi = [](double x) -> double
    { return 2 * x; };

    double initialGuess = 1;
    double tolerance = 1e-15;
    size_t maxIteration = 100;

    /**
     * @brief Call the Newton-Raphson method and output the result.
     */
    double result = newton_raphson(func, dervi, initialGuess, tolerance, maxIteration);
    printf("Result is: %.15e", result);

    return 0;
}
