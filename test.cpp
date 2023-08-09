//
// Created by zzm on 2023/8/8.
//
#include <iostream>
#include <vector>
#include <fstream>

struct Point {
    double x;
    double y;
};

class CustomBspline {
private:
    std::vector<Point> controlPts_;
    std::vector<Point> resultPts_;

public:
    CustomBspline(const std::vector<Point>& controlPts) : controlPts_(controlPts) {}

    void calculateBspline() {
        int N = controlPts_.size();
        double t;
        for (int i = 0; i < N - 3; i++) {
            Point temp;
            for (int j = 0; j < 100; j++) {
                t = static_cast<double>(j) / 100;
                temp.x = basisFunction0(t) * controlPts_[i].x + basisFunction1(t) * controlPts_[i + 1].x +
                         basisFunction2(t) * controlPts_[i + 2].x + basisFunction3(t) * controlPts_[i + 3].x;
                temp.y = basisFunction0(t) * controlPts_[i].y + basisFunction1(t) * controlPts_[i + 1].y +
                         basisFunction2(t) * controlPts_[i + 2].y + basisFunction3(t) * controlPts_[i + 3].y;
                resultPts_.push_back(temp);
            }
        }
    }

    std::vector<Point> getResultPts() {
        return resultPts_;
    }

private:
    double basisFunction0(double t) {
        return (1.0 / 6) * (-t * t * t + 3 * t * t - 3 * t + 1);
    }

    double basisFunction1(double t) {
        return (1.0 / 6) * (3 * t * t * t - 6 * t * t + 4);
    }

    double basisFunction2(double t) {
        return (1.0 / 6) * (-3 * t * t * t + 3 * t * t + 3 * t + 1);
    }

    double basisFunction3(double t) {
        return (1.0 / 6) * (t * t * t);
    }
};

int main() {
    std::vector<Point> controlPts = {{0, 0}, {1, 2}, {3, 1}, {4, 3}, {6, 2}, {7, 4}};
    CustomBspline bspline(controlPts);
    bspline.calculateBspline();
    std::vector<Point> resultPts = bspline.getResultPts();

    // Print the result points
    for (const auto& point : resultPts) {
        std::cout << "x: " << point.x << ", y: " << point.y << std::endl;
    }

    std::ofstream  test;
    test.open("/home/zzm/Desktop/test_path_figure-main/src/bsp.txt",std::ios::out);
    for(auto it : resultPts){
        test << " " << it.x;
    }
    test << std::endl;
    for(auto im : resultPts){
        test << " " << im.y;
    }
    test << std::endl;
    test.close();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

