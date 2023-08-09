//
// Created by zzm on 2023/8/7.
//

#ifndef TESTBSPLINE_CUSTOMBSPLINE_H
#define TESTBSPLINE_CUSTOMBSPLINE_H
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;

class point{
public:
    point(double a, double b){x = a; y = b; }
    point()= default ;
    double x;
    double y;
};

class customBspline{
public:
    customBspline(int k, int n,vector<point> & controlPts);
    customBspline() = default;
    ~customBspline();



    double basisFunction0(double t);
    double basisFunction1(double t);
    double basisFunction2(double t);
    double basisFunction3(double t);

    std::vector<point>  getResultPts();


    static std::vector<point> TocomputeCurveWaypoints(point pointm ,
                                                      point & direction,
                                                      double L);
private:
    vector<point>   resultPts_;
    vector<point>   endResultPts_;
};
#endif //TESTBSPLINE_CUSTOMBSPLINE_H
