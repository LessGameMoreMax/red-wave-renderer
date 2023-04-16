#include <iostream>
#include <time.h>
#include "Math.h"
using namespace std;
using namespace sablin;

void print4(const Matrix4x4f &m){
    for(int i = 0; i != 4; ++i){
        for(int j = 0;j != 4; ++j)
            cout << m.m_[i][j] << " ";
        cout << endl;
    }
    cout << "----------" << endl;
}

void print3(const Matrix3x3f &m){
    for(int i = 0; i != 3; ++i){
        for(int j = 0;j != 3; ++j)
            cout << m.m_[i][j] << " ";
        cout << endl;
    }
    cout << "----------" << endl;
}
int main(){
    // Matrix3x3f one(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    // Matrix4x4f one{1.0f, 2.0f, 3.0f, 4.0f,
    //                5.0f, 6.0f, 7.0f, 8.0f,
    //                9.0f, 10.0f, 11.0f, 12.0f,
    //                13.0f, 14.0f, 15.0f, 16.0f};
    // Vector4f two{1.0f, 2.0f, 3.0f, 4.0f};
    // struct timespec time_start = {0, 0};
    // struct timespec time_end = {0, 0};
    // long long time = 0;
    // for(int i = 0;i != 10; ++i){
    //     clock_gettime(CLOCK_REALTIME, &time_start);
    //     for(int j = 0;j != 100000; ++j)
    //         one.Transpose();
    //     clock_gettime(CLOCK_REALTIME, &time_end);
    //     time += time_end.tv_nsec - time_start.tv_nsec;
    // }
    // cout << time / 10 << endl;

    Matrix4x4f one{1.0f, 2.0f, 3.0f, 4.0f,
                   5.0f, 6.0f, 7.0f, 8.0f,
                   9.0f, 10.0f, 11.0f, 12.0f,
                   13.0f, 14.0f, 15.0f, 16.0f};
    Matrix4x4f two{1.0f, 2.0f, 3.0f, 4.0f,
                   5.0f, 6.0f, 7.0f, 8.0f,
                   9.0f, 10.0f, 11.0f, 12.0f,
                   13.0f, 14.0f, 15.0f, 16.0f};
    one += two;
    print4(one);

    print4(one + two);

    one += 2.0f;
    print4(one);

    print4(one + 2.0f);

    one -= two;
    print4(one);

    print4(one - two);

    one -= 2.0f;
    print4(one);

    print4(one - 2.0f);

    one *= 2.0f;
    print4(one);

    print4(one * 2.0f);

    one /= 2.0f;
    print4(one);

    print4(one / 2.0f);
    return 0;
}
