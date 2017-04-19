// lagnarok.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "lagnarok.h"


// This is an example of an exported variable
LAGNAROK_API int nlagnarok=0;

// This is an example of an exported function.
LAGNAROK_API int fnlagnarok(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see lagnarok.h for the class definition
Clagnarok::Clagnarok()
{
    return;
}
