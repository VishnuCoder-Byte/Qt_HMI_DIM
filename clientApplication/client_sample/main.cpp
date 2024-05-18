#include <iostream>
#include <client_sample.h>

using namespace std;

int main()
{
    client_sample obj;

    if(obj.init())
        obj.start();
    return 0;
}
