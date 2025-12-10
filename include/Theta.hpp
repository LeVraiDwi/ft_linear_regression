#ifndef THETA
# define THETA

struct Theta
{
    /* data */
    double x;
    double y;
    Theta(double x, double y): x(x), y(y) {}
    Theta(const Theta* t): x(t->x), y(t->y) {}
    Theta() {}
};

#endif