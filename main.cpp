#include <iostream>
#include <time.h>
#include "Math.h"
using namespace std;
using namespace sablin;
int main(){
    // Matrix3x3f one(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    // struct timespec time_start = {0, 0};
    // struct timespec time_end = {0, 0};
    // long long time = 0;
    // for(int i = 0;i != 10; ++i){
    //     clock_gettime(CLOCK_REALTIME, &time_start);
    //     for(int j = 0;j != 100000; ++j)
    //         one.Det();
    //     clock_gettime(CLOCK_REALTIME, &time_end);
    //     time += time_end.tv_nsec - time_start.tv_nsec;
    // }
    // cout << time / 10 << endl;

    // Matrix3x3f L{1.0f, 0.0f, 0.0f, 0.2f, 1.0f, 0.0f, 0.6f, 0.5f, 1.0f};
    // Matrix3x3f U{5.0f, 6.0f, 3.0f, 0.0f, 0.8f, -0.6f, 0.0f, 0.0f, 2.5f};
    // Vector3i pi{2, 0, 1};
    // Vector3f b{3.0f, 7.0f, 8.0f};
    // Vector3f x = LUPSolve3f(L, U, pi, b);
    // cout << x.x_ << endl;
    // cout << x.y_ << endl;
    // cout << x.z_ << endl;

    Matrix3x3f A{1.0f, 2.0f, -1.0f,
                 3.0f, 4.0f, -2.0f,
                 5.0f, -4.0f, 1.0f};
    Matrix3x3f B = A.Inverse();
    for(int i = 0;i != 3; ++i)
        for(int j = 0;j != 3; ++j)
            cout << B.m_[i][j] << endl;
    A.Inversed();
    for(int i = 0;i != 3; ++i)
        for(int j = 0;j != 3; ++j)
            cout << A.m_[i][j] << endl;
    return 0;
}
