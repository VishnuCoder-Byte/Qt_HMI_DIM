#include <iostream>
#include <server_sample.h>

using namespace std;

int main()
{
    server_sample obj;

    if(obj.init())
        obj.start();
    return 0;
}
