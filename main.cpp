#include <iostream>
#include "scr/number.h"

int main(int argc, char const *argv[])
{
	Number x(123);
	Number y(123);

	Number res=x*123;
	res.print();

	return 0;
}