#include "src/defs/SOFT_RTR.h"
#include <iostream>

using namespace std;
using namespace sablin;

int main(){
    Object object_one{nullptr, Vector3f(1.0f,1.0f,1.0f),
            Vector3f(0.0f,0.0f,0.0f), 0.0f, Vector3f(0.0f, 1.0f, 0.0f),
            Vector3f(1.0f, 1.0f, 0.0f), 45.0f, Vector3f(0.0f, 0.0f, 1.0f)};
    Matrix4x4f W = object_one.GetWorldMatrix();
    std::cout << W.e00_ << " " << W.e01_ << " " << W.e02_ << " " << W.e03_ << std::endl;
    std::cout << W.e10_ << " " << W.e11_ << " " << W.e12_ << " " << W.e13_ << std::endl;
    std::cout << W.e20_ << " " << W.e21_ << " " << W.e22_ << " " << W.e23_ << std::endl;
    std::cout << W.e30_ << " " << W.e31_ << " " << W.e32_ << " " << W.e33_ << std::endl;
    return 0;
}
