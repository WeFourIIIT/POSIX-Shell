#include <iostream>
#include <signal.h>

#include "prashant.h"
#include "priyank.h"
#include "rishabh.h"
#include "ujjwal.h"

using namespace std;

int main()
{
    signal(SIGINT, exitShell);
    initialise();
    return 0;
}