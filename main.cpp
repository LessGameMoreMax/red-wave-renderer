#include <iostream>
#include <time.h>
#include "Math.h"
using namespace std;
using namespace sablin;
int main(){
    Matrix3x3f one(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    struct timespec time_start = {0, 0};
    struct timespec time_end = {0, 0};
    long long time = 0;
    for(int i = 0;i != 10; ++i){
        clock_gettime(CLOCK_REALTIME, &time_start);
        for(int j = 0;j != 100000; ++j)
            one.Det();
        clock_gettime(CLOCK_REALTIME, &time_end);
        time += time_end.tv_nsec - time_start.tv_nsec;
    }
    cout << time / 10 << endl;
    return 0;
}
