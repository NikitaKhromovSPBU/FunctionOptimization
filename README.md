# Function Optimization

Performs an optimization of some hard-coded functions of arbitrary dimensions in a rectangular area.

### Implemented methods:
1.  Fletcher–Reeves nonlinear conjugate gradient method
2.  Stohastic method (with user-specified parameters)

Optimization process starts in a user-given point of the user-specified rectangular area.

### Implemented stopping criteria:
1.  Number of iterations exceeds some n
2.  The absolute value difference of the function in two last different points is less than some epsilon
3.  The relation of value difference of the function in two last different points to the absolute value of the function in the starting point is less than some epsilon
Criteria 2 & 3 also check for criterion 1.

TODO:
1.  Graphical interface
2.  More functions (probably)
