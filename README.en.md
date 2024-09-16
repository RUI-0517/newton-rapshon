# 牛顿迭代法 (Newton's Method)

[![简体中文](https://img.shields.io/badge/语言-%E7%AE%80%E4%BD%93%E4%B8%AD%E6%96%87-red.svg)](https://github.com/RuiJiang-A/2d-platformer/tree/main/README/README.zh-cn.md)
[![English](https://img.shields.io/badge/lang-English-blue.svg)](https://github.com/RuiJiang-A/2d-platformer/tree/main/README/README.en.md)

Let's start with a function $$f(x) = x^2 - 3$$ and determine its roots.

Newton's method suggests starting with an initial guess, say 2, as our $$x_0$$. Then, we draw a tangent line at this point.

![image](https://github.com/user-attachments/assets/1fabc684-c9f6-4f9e-b0ae-a26bec028d86)

If we directly observe the graphic, we can see that the intersection point, denoted as $$x_1$$, where the tangent line crosses the x-axis is very close to our root. But how do we determine this intersection point? Let’s consider the definition of a tangent:

$$
f'(x) = \lim_{\Delta x \to 0} \frac{\Delta y}{\Delta x}
$$

Plugging in $$x_0$$ for $$x$$, and knowing $$\Delta y$$ which is $$f(x_0)$$ and $$\Delta x$$ which becomes $$x_0 - x_1$$:

$$
f'(x_0) = \frac{f(x_0)}{x_0 - x_1}
$$

Now, let’s isolate $$x_1$$ to express it as a function of $$f'(x_0)$$, $$f(x_0)$$, and $$x_0$$:

$$
f'(x_0) = \frac{f(x_0)}{x_0 - x_1}
$$

$$
f'(x_0)(x_0 - x_1) = f(x_0)
$$

$$
x_0 - x_1 = \frac{f(x_0)}{f'(x_0)}
$$

$$
x_1 = x_0 - \frac{f(x_0)}{f'(x_0)}
$$

Therefore, if we provide an initial guess, the function we want to resolve, and its derivative, we can find the root.

## #️⃣ Coding Time

Let’s implement this step by step.

As discussed, we need a function that takes an initial guess, the function itself, and its derivative. To use `std::function`, we include the `<functional>` header file.

```cpp
#include <functional>

double newton_raphson(std::function<double(double)> func, std::function<double(double)> dervi,
                      double initialGuess)
{
    // implementation here
}
```

We need a tolerance to stop our calculation and a maximum iteration count to prevent looping forever. We use `size_t`, defined in `<cstddef>`.

```diff
#include <functional>
+ #include <cstddef>

double newton_raphson(std::function<double(double)> func, std::function<double(double)> dervi,
+                     double initialGuess, double tolerance, size_t maxIteration)
{
    // implementation here
}
```

In this function, we will loop until the maximum iteration is reached or we find a result within the tolerance error. Let’s define a `while` loop for this.

```diff
#include <functional>
#include <cstddef>

double newton_raphson(std::function<double(double)> func, std::function<double(double)> dervi,
                      double initialGuess, double tolerance, size_t maxIteration)
{
+   size_t currentIteration = 0;
+
+   while (currentIteration <= maxIteration)
+   {
+       ++currentIteration;
+   }
}
```

Before starting the iteration, we should assign our initial guess to the current `x`, which is the `x` we are dealing with:

```diff
#include...

double newton_raphson(std::function<double(double)> func, std::function<double(double)> dervi,
                      double initialGuess, double tolerance, size_t maxIteration)
{
    size_t currentIteration = 0;
+   double currentX = initialGuess;

    while (currentIteration <= maxIteration)
    {
        ++currentIteration;
    }
}
```

For each iteration, we want to calculate the new x using the formula $$x_{current} = x_{previous} - \frac{f(x_{previous})}{f'(x_{previous})}$$:

```diff
#include...

double newton_raphson(std::function<double(double)> func, std::function<double(double)> dervi,
                      double initialGuess, double tolerance, size_t maxIteration)
{
    size_t currentIteration = 0;
    double currentX = initialGuess;

    while (currentIteration <= maxIteration)
    {
+       // Store the x value from the previous iteration as previousX in each iteration
+       double previousX = currentX;
+
+       // Calculate the function and derivative values at the current iteration
+       double functionValue = func(previousX);
+       double derivativeValue = dervi(previousX);
+
+       // Update the value using the Newton-Raphson formula
+       currentX = previousX - functionValue / derivativeValue;

        ++currentIteration;
    }
}
```

Then, we want to return the current x value if we are satisfied with the precision:

```diff
#include...

double newton_raphson(std::function<double(double)> func, std::function<double(double)> dervi,
                      double initialGuess, double tolerance, size_t maxIteration)
{
    size_t currentIteration = 0;
    double currentX = initialGuess;

    while (currentIteration <= maxIteration)
    {
        // Store the x value from the previous iteration as previousX in each iteration
        double previousX = currentX;

        // Calculate the function and derivative values at the current iteration
        double functionValue = func(previousX);
        double derivativeValue = dervi(previousX);

        // Update the value using the Newton-Raphson formula
        currentX = previousX - functionValue / derivativeValue;

+       if (std::abs(currentX - previousX) <= tolerance)
+           return currentX;

        ++currentIteration;
    }
}
```

Additionally, we need to handle the potential division by zero problem:

```diff
#include...

double newton_raphson(std::function<double(double)> func, std::function<double(double)> dervi,
                      double initialGuess, double tolerance, size_t maxIteration)
{
    size_t currentIteration = 0;
    double currentX = initialGuess;

    while (currentIteration <= maxIteration)
    {
        // Store the x value from the previous iteration as previousX in each iteration
        double previousX = currentX;

        // Calculate the function and derivative values at the current iteration
        double functionValue = func(previousX);
        double derivativeValue = dervi(previousX);

        if (std::abs(derivativeValue) < 1e-12)
            return currentX;

        // Update the value using the Newton-Raphson formula
        currentX = previousX - functionValue / derivativeValue;

+       if (std::abs(currentX - previousX) <= tolerance)
+           return currentX;

        ++currentIteration;
    }
}
```

There you go! You’ve just implemented the function! 🥳

## 💪 Challenge Time!

The Newton-Raphson method requires a derivative function to proceed successfully. Instead of the derivative, you can use a finite difference method: $$f'(x) = \frac{f(x1) - f(x2)}{x1 - x2}$$. Consequently, two initial points are needed to calculate the first difference.

Try to implement this function by yourself!
