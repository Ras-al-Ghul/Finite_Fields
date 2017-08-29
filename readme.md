# Finite Field Construction

### To execute

Compile and run

### List of files

- `Euclidean.cpp` - Implementation of Euclidean algorithm for integers
- `ExtendedEuclidean.cpp` - Implementation of Extended Euclidean algorithm for integers
- `Polynomial.cpp` - Implementation of Polynomial Division algorithm
- `EuclideanPolynomial.cpp` - Implementation of Euclidean algorithm for polynomials
- `ExtendedEuclideanPolynomial.cpp` - Implementation of Extended Euclidean algorithm for polynomials
- `Q6a.cpp` - Finite Field implementation for fields F1 and F2, where |F1| = p^3 and |F2| = p^5 and p is chosen as 3
- `Q6b.cpp` - Finds the generator of the multiplicative group F1* i.e. F1 \ {0} 
- `Q6c.cpp` - Compute three distinct element-inverse pairs in F2

**NOTE :** You will need output of `Q6a.cpp` for `Q6b.cpp` and `Q6c.cpp`.

Whenever a polynomial has to be entered, start entering coefficients from the **lowest** degree term (ie the constant term)
The degree of the polynomial is the highest degree of its terms.

Eg:
4x^3 + 3x + 7
degree:3
Enter coefficients as:
7
3
0
4
