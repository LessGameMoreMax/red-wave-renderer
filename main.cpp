#include "src/defs/SOFT_RTR.h"

using namespace std;
using namespace sablin;

int main(){
    DisplayConfiguration display_configuration{640, 480};
    Display::Create(display_configuration);
    Display::GetSingleton();
    return 0;
}
