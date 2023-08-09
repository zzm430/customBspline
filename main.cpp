#include <iostream>
#include "customBspline.h"
#include <fstream>

int main() {
    std::vector<point>   originPts;
//    0, 0}, {1, 2}, {3, 1}, {4, 3}, {6, 2}, {7, 4}};
    originPts.push_back(point(0,0));
    originPts.push_back(point(1,2));
    originPts.push_back(point(3,1));
    originPts.push_back(point(4,3));
    originPts.push_back(point(6,2));

    point directionstart,directionend;
    directionstart.x = originPts[1].x - originPts[0].x;
    directionstart.y = originPts[1].y - originPts[0].y;

    directionend.x = originPts[originPts.size()-1].x - originPts[originPts.size()-2].x;
    directionend.y = originPts[originPts.size()-1].y - originPts[originPts.size()-2].y;
    double L = 1;
    auto ptsstart =  customBspline::TocomputeCurveWaypoints(originPts[0],directionstart,L);
    auto ptsend = customBspline::TocomputeCurveWaypoints(originPts[originPts.size()-1],directionend,L);


    std::vector<point>  transferedPts;
    for(auto it : ptsstart){
        transferedPts.push_back(it);
    }
    for(auto it : ptsend){
        transferedPts.push_back(it);
    }
    for(int i = 1;i < originPts.size() -1;i++){
        transferedPts.push_back(originPts[i]);
    }
    //增加途径点
    customBspline   newBsp(4,3,transferedPts);

    auto pts = newBsp.getResultPts();
   std::ofstream  test;
   test.open("/home/zzm/Desktop/test_path_figure-main/src/bsp.txt",std::ios::out);
   for(auto it : pts){
       test << " " << it.x;
   }
   test << std::endl;
   for(auto im : pts){
       test << " " << im.y;
   }
   test << std::endl;
   test.close();

    std::ofstream  test_origin;
    test_origin.open("/home/zzm/Desktop/test_path_figure-main/src/test_origin.txt",std::ios::out);
    for(auto it : originPts){
        test_origin << " " << it.x;
    }
    test_origin << std::endl;
    for(auto im : originPts){
        test_origin << " " << im.y;
    }
    test_origin << std::endl;
    test_origin.close();

   std::cout << "Hello, World!" << std::endl;
    return 0;
}