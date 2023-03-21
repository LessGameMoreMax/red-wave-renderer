#include <iostream>
#include "math/Vectors.h"

using namespace std;
using namespace sablin;

int main(){
   Vector3f one{1.0f, 2.0f, 3.0f};
   void* pointer = &one;
   float* float_pointer = static_cast<float*>(pointer);
   cout << *float_pointer << endl;
   cout << *(float_pointer + 1) << endl;
   cout << *(float_pointer + 2) << endl;

   Vector4f two(10.0f,9.0f,8.0f,7.0f);
   pointer = &two;
   float_pointer = static_cast<float*>(pointer);
   cout << *float_pointer << endl;
   cout << *(float_pointer + 1) << endl;
   cout << *(float_pointer + 2) << endl;
   cout << *(float_pointer + 3) << endl;
   return 0;

}
