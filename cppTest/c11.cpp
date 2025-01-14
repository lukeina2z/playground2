
#include <iostream>
using namespace std;

/// g++ -std=c++17  ./c11.cpp

int constexpr A = 12;

constexpr auto Add(int a, int b)
{
	return a + b + A;
}


int main()
{
	int a = 12;
	int b = 13;
	int c = Add(a, b);

    std::cout << "hello world! \t" << c << std::endl;
	return 0;
}