# 牛顿迭代法（Newton's Method)

让我们从一个函数 $$f(x) = x^2 - 3$$ 开始，来求它的根。

牛顿法建议以一个初始猜测值，比如2，作为我们的 $$x_0$$。然后，我们在此点上画一条切线。

![image](https://github.com/user-attachments/assets/1fabc684-c9f6-4f9e-b0ae-a26bec028d86)

如果我们直接观察图像，可以看到切线与x轴的交点 $$x_1$$ 非常接近我们的根。那么我们如何确定这个交点呢？让我们考虑切线的定义：

$$
f'(x) = \lim_{\Delta x \to 0} \frac{\Delta y}{\Delta x}
$$

将 $$x_0$$ 代入 $$x$$，并且知道 $$\Delta y$$ 为 $$f(x_0)$$，$$\Delta x$$ 则为 $$x_0 - x_1$$：

$$
f'(x_0) = \frac{f(x_0)}{x_0 - x_1}
$$

现在，我们将 $$x_1$$ 用 $$f'(x_0)$$、$$f(x_0)$$ 和 $$x_0$$ 表达出来：

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

因此，如果我们提供一个初始猜测、想要解决的函数以及它的导数，就可以找到该函数的根。

## #️⃣ 编码时间

让我们一步一步实现这个算法。

正如讨论的那样，我们需要一个函数，接受一个初始猜测、该函数本身及其导数。为了使用 `std::function`，我们需要引入 `<functional>` 头文件。

```cpp
#include <functional>

double newton_raphson(std::function<double(double)> func, std::function<double(double)> dervi,
                      double initialGuess)
{
    // 实现代码
}
```

我们需要一个用于停止计算的容差值以及一个最大迭代次数，以防止无限循环。我们使用定义在 `<cstddef>` 中的 `size_t`。

```diff
#include <functional>
+ #include <cstddef>

double newton_raphson(std::function<double(double)> func, std::function<double(double)> dervi,
+                     double initialGuess, double tolerance, size_t maxIteration)
{
    // implementation here
}
```

在这个函数中，我们将循环直到达到最大迭代次数或者找到满足条件的结果。让我们为此定义一个 `while` 循环。

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

在开始迭代之前，我们应该将初始猜测赋值给当前的 `x`，即我们正在处理的 `x`：

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

对于每次迭代，我们使用公式$$x_{current} = x_{previous} - \frac{f(x_{previous})}{f'(x_{previous})}$$:

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

然后，如果满足精度要求，我们返回当前的 `x` 值：

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

此外，我们需要处理可能的除零问题：

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

现在！你已经成功实现了这个函数！🥳

## 💪 挑战时间！
牛顿-拉弗森方法需要一个导数函数才能成功进行。你可以使用有限差分法来代替导数：

$$
f'(x) = \frac{f(x1) - f(x2)}{x1 - x2}
$$

因此，需要两个初始点来计算第一个差分。

试着自己实现这个函数吧！
