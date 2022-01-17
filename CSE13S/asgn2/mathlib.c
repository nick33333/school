#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define EPSILON 1E-10

// mathlib is a library of my implementations of the arcsin, arccos, arctan and log base e
// functions. These functions were implemented primarily through Newton's method and trig
// identities.

double arcSin(double x);
double arcCos(double x);
double arcTan(double x);
double Log(double x);

// My absolute value function
static double my_abs(double x) {
    if (x >= 0) {
        return x;
    } else {
        return -1 * x;
    }
}

// This Exp function was provided by Professor Long on Piazza
static double Exp(double x) {
    double term = 1, sum = 1;
    for (int k = 1; my_abs(term) > EPSILON; k += 1) {
        term *= x / k;
        sum += term;
    }
    return sum;
}

// sqrt using Newton's Method
static double Sqrt(double x) {
    assert(x >= 0);
    double old = 1;
    double neo = old;
    double dif = old;
    while (my_abs(dif) > EPSILON) {
        neo = old - (((old * old) - x) / (2 * old));
        dif = neo - old;
        old = neo;
    }
    return neo;
}

// arcsin using Newton's Method used for arcCos
// intermediate function for implementing trig identity
// into arcCos function
double parcSin(double x) {
    double old = M_PI / 20;
    double neo = old;
    double dif = old;
    while (my_abs(dif) > EPSILON) {
        double s = sin(old);
        double c = cos(old);
        neo = old - ((s - x) / (c));
        dif = neo - old;
        old = neo;
    }
    return neo;
}
// arccos using Newton's Method
double arcCos(double x) {
    if (-.75 < x && x < .75) {
        return M_PI / 2 - parcSin(x);
    } else if (x > 0) {
        x = Sqrt((1 - (x * x)));
        return parcSin(x);
    } else {
        x = Sqrt((1 - (x * x)));
        return M_PI + parcSin(-x);
    }
}

// arcsin using Newton's Method
double arcSin(double x) {
    return M_PI / 2 - arcCos(x);
}

// arctan using Newton's Method
double arcTan(double x) {
    double old = M_PI / 8.0;
    double neo = old;
    double dif = old;
    x = x / (Sqrt((x * x) + 1));
    while (my_abs(dif) > EPSILON) {
        double s = sin(old);
        double c = cos(old);
        neo = old - ((s - x) / (c));
        dif = neo - old;
        old = neo;
    }
    return neo;
}

// log base e using Newton's Method
double Log(double x) {
    double old = M_PI / 8.0;
    double neo = old;
    double dif = old;
    while (my_abs(dif) > EPSILON) {
        neo = old - 1 + (x / (Exp(old)));
        dif = neo - old;
        old = neo;
    }
    return neo;
}
