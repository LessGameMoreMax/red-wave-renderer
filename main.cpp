#include "src/defs/SOFT_RTR.h"
#include <iostream>
using namespace sablin;
using namespace std;

int main(){
    Camera c{Vector4f(1.0f, 0.0f, 0.0f, 1.0f),
            Vector4f(0.0f, 0.0f, 0.0f, 1.0f),
            Vector4f(0.0f, 0.0f, 1.0f, 0.0f)};
    Matrix4x4f view = c.GetViewMatrix();
    std::cout << view.e00_ << " " << view.e01_ << " " << view.e02_ << " " << view.e03_ << std::endl;
    std::cout << view.e10_ << " " << view.e11_ << " " << view.e12_ << " " << view.e13_ << std::endl;
    std::cout << view.e20_ << " " << view.e21_ << " " << view.e22_ << " " << view.e23_ << std::endl;
    std::cout << view.e30_ << " " << view.e31_ << " " << view.e32_ << " " << view.e33_ << std::endl;
    return 0;
}
