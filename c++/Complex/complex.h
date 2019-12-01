#ifndef _COMPLEX_H
#define _COMPLEX_H

#include <iostream>
using namespace std;

class complex
{
public:
    complex(double r = 0, double i = 0) : re(r), im(i) {}
    ~complex() {}
    complex& operator += (const complex&);
    complex& operator -= (const complex&);
    complex& operator *= (const complex&);
    complex& operator /= (const complex&);
    double real() const { return re; }
    double imag() const { return im; }
private:
    double re, im;

    friend complex& _doapl(complex*, const complex&);
    friend complex& _doami(complex*, const complex&);
    friend complex& _doaml(complex*, const complex&);
    friend complex& _doadl(complex*, const complex&);
};

//取得实部
inline double real(const complex& x)
{
    return x.real();
}

//取得虚部
inline double imag(const complex& x)
{
    return x.imag();
}

// +=
inline complex& _doapl(complex *ths, const complex& r)
{
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
}
inline complex& complex::operator += (const complex& r)
{
    return _doapl(this, r);
}

// -=
inline complex& _doami(complex *ths, const complex& r)
{
    ths->re -= r.re;
    ths->im -= r.im;
    return *ths;
}
inline complex& complex::operator -= (const complex& r)
{
    return _doami(this, r);
}

// *=
inline complex& _doaml(complex *ths, const complex& r)
{
    double a = ths->re;
    double b = ths->im;
    ths->re = a * r.re - b * r.im;
    ths->im = a * r.im + r.re * b;
    return *ths;
}
inline complex& complex::operator *= (const complex& r)
{
    return _doaml(this, r);
}

// /=
inline complex& _doadl(complex *ths, const complex& r)
{
    double a = ths->re;
    double b = ths->im;
    double z = r.re * r.re + r.im * r.im;
    ths->re = (a * r.re + b * r.im) / z;
    ths->im = (b * r.re - a * r.im) / z;
    return *ths;
}
inline complex& complex::operator /= (const complex& r)
{
    return _doadl(this, r);
}

// +
inline complex operator + (const complex& x, const complex& y)
{
    return complex(real(x) + real(y), imag(x) + imag(y));
}
inline complex operator + (const complex& x, double y)
{
    return complex(real(x) + y, imag(x));
}
inline complex operator + (double x, const complex& y)
{
    return complex(x + real(y), imag(y));
}

// -
inline complex operator - (const complex& x, const complex& y)
{
    return complex(real(x) - real(y), imag(x) - imag(y));
}
inline complex operator - (const complex& x, double y)
{
    return complex(real(x) - y, imag(x));
}
inline complex operator - (double x, const complex& y)
{
    return complex(x - real(y), imag(y));
}

// *
inline complex operator * (const complex& x, const complex& y)
{
    return complex(real(x) * real(y) - imag(x) * imag(y), real(x) * imag(y) + real(y) + imag(x));
}
inline complex operator * (const complex& x, double y)
{
    return complex(real(x) * y, imag(x) * y);
}
inline complex operator * (double x, const complex& y)
{
    return complex(x * real(y), x * imag(y));
}

// /
inline complex operator / (const complex& x, const complex& y)
{
    double z = real(y) * real(y) + imag(y) * imag(y);
    return complex((real(x) * real(y) + imag(x) * imag(y)) / z, (real(y) * imag(x) - real(x) + imag(y)) / z);
}
inline complex operator / (const complex& x, double y)
{
    double z = y * y;
    return complex(real(x) * y / z, imag(x) * y / z);
}
inline complex operator / (double x, const complex& y)
{
    double z = real(y) * real(y) + imag(y) * imag(y);
    return complex(x * real(y) / z, -1 * x * imag(y) / z);
}

// ==
inline bool operator == (const complex& x, const complex& y)
{
  return real (x) == real (y) && imag (x) == imag (y);
}
inline bool operator == (const complex& x, double y)
{
  return real (x) == y && imag (x) == 0;
}
inline bool operator == (double x, const complex& y)
{
  return x == real (y) && imag (y) == 0;
}

// !=
inline bool operator != (const complex& x, const complex& y)
{
  return real (x) != real (y) || imag (x) != imag (y);
}
 
inline bool operator != (const complex& x, double y)
{
  return real (x) != y || imag (x) != 0;
}
 
inline bool operator != (double x, const complex& y)
{
  return x != real (y) || imag (y) != 0;
}

//正号
inline complex operator + (const complex& x)
{
    return x;
}

//负号
inline complex operator - (const complex& x)
{
    return complex(-real(x), -imag(x));
}

//共轭复数
inline complex conj(const complex& x)
{
    return complex(real(x), -imag(x));
}

//重载<<
inline ostream& operator << (ostream& os, const complex& x)
{
    return os << real(x) << "+" << "(" << imag(x) << ")i";
}

#endif
