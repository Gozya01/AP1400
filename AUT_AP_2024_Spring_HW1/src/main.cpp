#include "algebra.h"

#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char **argv) {
	if (false) // make false to run unit-tests
	{	
		algebra::MATRIX<double> mat = {{4, 7}, {2, 6}};
algebra::MATRIX<double> invMat = algebra::inverse(mat);
algebra::display(invMat);
/* Expected Matrix
|  3/5  | -7/10 |
| -1/5  |  2/5  |
*/

	} else {
		::testing::InitGoogleTest(&argc, argv);
		std::cout << "RUNNING TESTS ..." << std::endl;
		int ret{RUN_ALL_TESTS()};
		if (!ret)
			std::cout << "<<<SUCCESS>>>" << std::endl;
		else
			std::cerr << "FAILED" << std::endl;
	}
	return 0;
}
