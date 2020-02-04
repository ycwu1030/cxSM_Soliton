/*
 * @Description  : typedef for convenience 
 * @Author       : Yongcheng Wu
 * @Date         : 2019-12-22 13:50:35
 * @LastEditors  : Yongcheng Wu
 * @LastEditTime : 2020-02-04 12:33:17
 */
#ifndef VTypes_H
#define VTypes_H
#include <vector>

typedef std::vector<double> VD;
typedef std::vector<std::vector<double> > VVD;
typedef std::vector<std::vector<std::vector<double> > > VVVD;

std::vector<double> operator+(const std::vector<double> &lhs, const std::vector<double> &rhs);
std::vector<double> operator+(const std::vector<double> &lhs, const double &cons);
std::vector<double> operator+(const double &cons, const std::vector<double> &rhs);
std::vector<double> operator+(const std::vector<double> &lhs, const std::vector<double> &rhs);

std::vector<double> operator-(const std::vector<double> &lhs, const std::vector<double> &rhs);

std::vector<double> operator*(const std::vector<double> &lhs, const double &s);
std::vector<double> operator*(const double &s, const std::vector<double> &rhs);
double operator*(const std::vector<double> &lhs, const std::vector<double> &rhs); // Scalar Product

std::vector<double> operator/(const std::vector<double> &lhs, const double &s);

#endif