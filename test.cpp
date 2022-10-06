#include <iostream>

int	main(void)
{
	std::string test = "s";
	test.erase(0, 1);
	std::cout << "test =" <<  test << std::endl;
}
