#include "include/systemproxysetter.h"

int main() {

    SetGlobalProxy("127.0.0.1", "80");
    SetPacProxy("http://127.0.0.1/proxy.pac");
    SetNoProxy();

    return 0;
}