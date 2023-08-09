//
// Created by zzm on 2023/8/7.
//
#include "customBspline.h"

customBspline::customBspline(int k, int n, vector<point> &controlPts) {
    point v1 ,v2;
    v1.x = 1;
    v1.y = 0;
    v2.x = 1;
    v2.y = 0;
    double L = 0.5;
    double lenghtsize = controlPts.size();
    std::vector<point>  startPtbigger;
    std::vector<point>  endPtbigger;
    point  temp1,temp2;
    temp1.x = controlPts[0].x - 0.5;
    temp1.y = controlPts[0].y ;
    temp2.x = controlPts[0].x + 0.5;
    temp2.y = controlPts[0].y;
    point temp3,temp4;
    temp3.x = controlPts[lenghtsize-1].x - 0.5;
    temp3.y = controlPts[lenghtsize-1].y;
    temp4.x = controlPts[lenghtsize-1].x + 0.5;
    temp4.y = controlPts[lenghtsize-1].y;
    resultPts_.push_back(temp1);
    resultPts_.push_back(temp2);
    for(auto i : controlPts){
        resultPts_.push_back(i);
    }
//    resultPts_.push_back(temp3);
//    resultPts_.push_back(temp4);
    int N = resultPts_.size();
    double t;
    point  temp;
    for(int i = 0;i < N - 3;i++){
       auto Node1 = resultPts_[i];
       auto Node2 = resultPts_[i+1];
       auto Node3 = resultPts_[i+2];
       auto Node4 = resultPts_[i+3];
       for(int j = 0;j < 100;j++){
           t = static_cast<double>(j) / 100;
           temp.x = Node1.x * basisFunction0(t) + Node2.x * basisFunction1(t) +
                    Node3.x * basisFunction2(t)  + Node4.x * basisFunction3(t);
           temp.y = Node1.y * basisFunction0(t) + Node2.y * basisFunction1(t) +
                    Node3.y * basisFunction2(t)  + Node4.y * basisFunction3(t);
           endResultPts_.push_back(temp);
       }
    }
    std::cout << "hello !!!!!!!!" << std::endl;
}
customBspline::~customBspline(){}


//公式：经过Ck点需要扩展的三个点
//扩展的3个点为Ck- Vk * L, Ck,  Ck + Vk * L
//Vk表示经过该点的速度方向,L一般为车长的一半
//输入1个点和输出3个点
 std::vector<point>  customBspline::TocomputeCurveWaypoints(point  pointm ,
                                                           point & direction,
                                                           double L){
            point pt1 ,pt2;
            pt1.x = pointm.x - direction.x * L;
            pt1.y = pointm.y - direction.y * L;
            pt2.x = pointm.x + direction.x * L;
            pt2.y = pointm.y + direction.y * L;
            std::vector<point>  orderedPts;
            orderedPts.push_back(pt1);
            orderedPts.push_back(pointm);
            orderedPts.push_back(pt2);
            return orderedPts;
}


std::vector<point> customBspline::getResultPts() {
    return endResultPts_;
}

double customBspline::basisFunction0(double t){
    return 1.0/6*(-t*t*t+3*t*t-3*t+1);
}

double customBspline::basisFunction1(double t){
    return 1.0/6*(3*t*t*t-6*t*t+4);
}

double customBspline::basisFunction2(double t){
      return 1.0/6*(-3*t*t*t+3*t*t+3*t+1);
}

double customBspline::basisFunction3(double t){
    return 1.0/6*t*t*t;
}