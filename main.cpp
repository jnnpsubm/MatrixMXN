#include <iostream>
#include "test.h"

#pragma comment(lib, "Winmm.lib")

int main()
{
	testMatrixNXNInverse();
	testMatrixMXNTranspose();
	testDirectXMathSIMD();
	system("pause");
	return 0;
}