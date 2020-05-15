//
// Created by elrond on 11/1/19.
//

#include <cmath>
#include <iostream>
#include <vector>
#include <numeric>
#include <limits>

#include <lokialg/mean.h>

int main()
{
    std::vector<int> v = {1,2,3,4,5};
    auto sec = v.begin();
    sec++;

    double value1 = lokimath::mean_recursive<double>::calc(v.begin(), v.end());
    double value2 = lokimath::mean_directly<double>::calc(v.begin(), v.end());

    double exact = 3.0;
    double diff1 = abs(value1 - exact);
    double diff2 = abs(value2 - exact);

    bool test_is_fine = (diff1 < 0.00001) && (diff2 < 0.00001);
    std::cout << "lokimath::mean is fine: " << test_is_fine << std::endl;
}