#include <iostream>
#include "Math.h"

using namespace std;
using namespace sablin;

int main(){
    Vector3f one(1.0f, 2.0f, 3.0f);
    Vector3f two(10.0f, 11.0f, 12.0f);
    one.Normalized();
    cout << one.x_ << endl;
    cout << one.y_ << endl;
    cout << one.z_ << endl;
    return 0;
}
