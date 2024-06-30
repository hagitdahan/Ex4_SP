#include <iostream>
#include <cmath>
using namespace std;

/**
 * @brief A class representing a complex number.
 */
class Complex {
private:
    double real; ///< Real part of the complex number.
    double imag; ///< Imaginary part of the complex number.
    
public:
    /**
     * @brief Constructor for Complex class.
     * 
     * @param r Real part of the complex number (default is 0).
     * @param i Imaginary part of the complex number (default is 0).
     */
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    /**
     * @brief Getter for the real part of the complex number.
     * 
     * @return The real part of the complex number.
     */
    double getReal() const { return real; }
    /**
     * @brief Setter for the real part of the complex number.
     * 
     * @param r The value to set as the real part.
     */
    void setReal(double r) { real = r; }
    /**
     * @brief Getter for the imaginary part of the complex number.
     * 
     * @return The imaginary part of the complex number.
     */
    double getImag() const { return imag; }
    /**
     * @brief Setter for the imaginary part of the complex number.
     * 
     * @param i The value to set as the imaginary part.
     */
    void setImag(double i) { imag = i; }
    /**
     * @brief Overload the + operator to add two Complex numbers.
     * 
     * @param other Another Complex object to add.
     * @return A new Complex object that is the sum of the current and other Complex objects.
     */
    Complex operator + (const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    /**
     * @brief Overload the < operator to compare two Complex numbers.
     * 
     * @param other Another Complex object to compare.
     * @return true if the current Complex number is less than the other, false otherwise.
     */
    bool operator < (const Complex& other) const {
        //return this->real < other.real && this->imag < other.imag;
        return std::sqrt(real * real + imag * imag) < std::sqrt(other.real * other.real + other.imag * other.imag);
    }
    /**
     * @brief Overload the == operator to check equality of two Complex numbers.
     * 
     * @param other Another Complex object to compare.
     * @return true if the current Complex number is equal to the other, false otherwise.
     */
    bool operator ==(const Complex& other) const{
        return this->real == other.real && this->imag == other.imag;
    }
    /**
     * @brief Overload the << operator to print Complex numbers.
     * 
     * @param out Output stream where the Complex number will be printed.
     * @param c Complex object to print.
     * @return Reference to the output stream after printing.
     */
    friend ostream& operator << (ostream& out, const Complex& c) {
        out << c.real << " + " << c.imag << "i";
        return out;
    }


};

