#define _POSIX_C_SOURCE 200809L
#include <math.h>
// Reusable, Double Precision Functions
// Note: We'll add single precision later

// Branchless Functions
// Scalar Multiplication
double scalar_mul(double a, double b) {
    return a * b;
}

// Signum (Function that returns Sign)
// In a 32-bit integer, the bits are numbered from 0 (the least
// significant bit) to 31 (the most significant bit, or the sign bit).
// For positive integers, the sign bit is 0, for negative integers, the sign bit is 1.
// When you right-shift a number by 31 bits (i.e., x >> 31), it effectively shifts the
// sign bit all the way to the least significant bit position, filling in all the other
// bits with either 0 or 1 depending on the sign of the number.
int signum(int x) {
    return (x > 0) - (x < 0);
}

// Absolute Value
int abs_val(int x) {
    int mask = x >> 31;  // -1 if negative, 0 if positive
    return (x + mask) ^ mask;
}

// Min/Max
int brls_min(int a, int b) { return b ^ ((a ^ b) & -(a < b)); }
int brls_max(int a, int b) { return a ^ ((a ^ b) & -(a < b)); }

// Clamp
int clamp(int x, int min, int max) {
    return (x < min) ? min : (x > max) ? max : x;
}

// Rational Trigonometry: Spread function approximation using squared ratios
double spread_ratio(double x) {
    // x should be quadrance (squared distance)
    double x2 = x * x;
    return x2 / (1 + x2);  // Approximates the spread function
}

// Dot Product
double dot_prod_geometry(double a1, double a2, double b1, double b2) {
    double a_sq = a1 * a1 + a2 * a2;
    double b_sq = b1 * b1 + b2 * b2;
    double dot_prod_sq = a1 * b1 + a2 * b2;
    double result = a_sq*b_sq - dot_prod_sq* dot_prod_sq;
    return result;
}

// Cross Product
void cross_prod(double *a, double *b, double *result) {
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
}

// Reciprocal (w/ NaN)
double reciprocal(double x) {
    // Generate NaN if x is zero, otherwise compute the reciprocal
    double result = (x == 0.0) * nan("DIV_BY_ZERO") + (x != 0.0) * (1.0 / x);
    
    // Adjust the sign based on whether x is negative
    result = result * (x < 0.0 ? -1.0 : 1.0);
    
    return result;
}

// Negative Reciprocal (w/ NaN)
double negative_reciprocal(double x) {
    // Generate NaN if x is zero, otherwise compute the negative reciprocal
    double result = (x == 0.0) * nan("DIV_BY_ZERO") + (x != 0.0) * (-1.0 / x);

    // Adjust the sign based on whether x is negative
    result = result * (x < 0.0 ? -1.0 : 1.0);

    return result;
}

// Reciprocal Multiply (w/ NaN)
double reciprocal_mul(double x, double y) {
    // Generate NaN if y is zero, otherwise compute the reciprocal
    double reciprocal_y = (y == 0.0) * nan("DIV_BY_ZERO") + (y != 0.0) * (1.0 / y);

    // Apply the correct sign to reciprocal_y based on y's sign
    reciprocal_y = reciprocal_y * (y < 0.0 ? -1.0 : 1.0);

    // Multiply x by the reciprocal of y
    return x * reciprocal_y;
}

// Negative Reciprocal Multiply (w/ NaN)
double negative_reciprocal_mul(double x, double y) {
    // Generate NaN if y is zero, otherwise compute the negative reciprocal
    double negative_reciprocal_y = (y == 0.0) * nan("DIV_BY_ZERO") + (y != 0.0) * (-1.0 / y);

    // Apply the correct sign to negative_reciprocal_y based on y's sign
    negative_reciprocal_y = negative_reciprocal_y * (y < 0.0 ? -1.0 : 1.0);

    // Multiply x by the negative reciprocal of y
    return x * negative_reciprocal_y;
}

// Note: Float
// Formula for powerof's is base=x, exponent=n, root=d
float ratio_pow_mathf(float x, float n, float d) {
    // Function effectively computes  sqrt{x^n}
    // Calculate the numerator power
    float numerator_pow = powf(x, n); // Use powf for float exponentiation
    float result = powf(numerator_pow, 1.0f / d);
    // if denominator is equal to "2", then x^(1/2) (square root operation)
    return result;
}

// Note: Double
// Function to compute x raised to the power n, and then the d-th root of that result
double ratio_pow_math(double x, double n, double d) {
    // Function effectively computes  sqrt{x^n}
    // Calculate the numerator power
    double numerator_pow = pow(x, n);
    double result = pow(numerator_pow, 1.0 / d);
    // if denominator is equal to "2", than x^(1/2) (square root operation)
    return result;
}

// Extension into complex numbers
typedef struct {
    double real;
    double imag;
} Complex;

Complex complex_i() {
    Complex i = {0.0, 1.0};
    return i;
}

typedef struct {
    double s; // Scalar part
    double v[3]; // Vector part (bi + cj + dk)
} Quaternion;

Quaternion init_quaternion(double a, double b, double c, double d) {
    Quaternion q;
    q.s = a;
    q.v[0] = b;
    q.v[1] = c;
    q.v[2] = d;
    return q;
}

// Double Precision Reiterated
// Branching Functions (for demonstration purposes)
double dot_prod_array(double *a, double *b, int size) {
    double result = 0.0;
    for (int i = 0; i < size; i++) {
        result += a[i] * b[i];
    }
    return result;
}

// Hadamard Product
void hada_prod(double *a, double *b, double *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] * b[i];
    }
}

// Safe scalar division w/ zero handling
double scalar_nod(double n, double d) {
    if (d == 0.0) {
        return 0.0; // return zero if denominator is zero
    }
    return n / d; // or perform operation
}

// Note: The following are for demonstration purposes.
// Division by 0 is undefined in mathematics as a rule.
double reciprocal(double x) {
    if (x == 0.0) {
        // for a nonzero number x, the reciprocal of x is (1/x)
        // or equivalently, x^(-1)
        // any number x is the same as writing x/1
        // Handle division by zero error
        return nan("DIV_BY_ZERO"); // Not-A-Number
        // the value or payload denotes extra information
        // you can choose any string/macro that suits your needs
    }
    return (x > 0.0) ? (1.0 / x) : (-1.0 / x);
}

// Branched Reciprocal Multiply (Version 1)
double b1_recip_mul(double x, double y) {
    if (y == 0.0) {
        // see `reciprocal()` for info
        // Handle division by zero error
        return nan("DIV_BY_ZERO");
    }
    // Calculate the reciprocal of y
    // When you have the expression x/y it can be rewritten as
    // x * y^(-1), which is is equivalent to x * y^(1/-1)...
    // If you consider the denominator as x^(1/n), then n = -1
    double reciprocal_y = (y > 0.0) ? (1.0 / y) : (-1.0 / y);

    // Multiply x by the reciprocal of y
    double result = x * reciprocal_y;

    return result;
}

// Branched Reciprocal Multiply (Version 2)
double b2_recip_mul(double x, double y) {
    if (y == 0.0) {
        // Handle division by zero error, as division by zero is undefined
        return nan("DIV_BY_ZERO");
    }

    // Calculate the reciprocal of y
    // x/y can be rewritten as x * y^(-1)
    // We want to handle the sign of y separately if needed, but normally we just use the reciprocal
    double reciprocal_y = 1.0 / y;  // Reciprocal of y

    // Multiply x by the reciprocal of y
    double result = x * reciprocal_y;

    return result;
}

// Note: Double
// Function to compute x raised to the power n, and then the d-th root of that result
double ratio_pow(double x, double n, double d) {
    // Function effectively computes  sqrt{x^n}
    // Calculate the numerator power
    double numerator_pow = 1.0;
    for (int i = 0; i < n; i++) {
        numerator_pow *= x;
    }
    double result = 1.0;
    for (int i = 0; i < d; i++) {
        result *= numerator_pow;
    }
    // If denominator is equal to "2", than x^(1/2) (square root operation)
    return result;
}

// Modulo function and special cases for d = 0, d = 1, and d = 2
int lamod(int x, int d) {
    if (d == 0) {
        // Any number modulo 0 is undefined
        // Handle division by zero error
        return -1; // Return a flag value to indicate error
    } else if (d == 1) {
        // Any number modulo 1 is always 0
        return 0;
    } else if (d == 2) {
        // Any even number modulo 2 is 0 because evens divide evenly
        // Any odd number modulo 2 is 1 since dividing an odd by 2,
        // you get a quotient of 0 w/ a remainder of "1"
        return x % 2;
    } else {
        // For other divisors, use the standard modulo operation
        return x % d;
    }
}

// Memcpy w/ Loop Unrolling
void memcpy_unroll(char *dest, const char *src, size_t n) {
    while (n >= 8) {
        *(uint64_t*)dest = *(uint64_t*)src;
        dest += 8; src += 8; n -= 8;
    }
    while (n--) *dest++ = *src++;  // Copy remaining bytes
}

