//
// Created by elrond on 11/1/19.
//

#include <mean.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <numeric>
#include <limits>

int main()
{
    std::vector<int> v = {1,2,3,4,5};
    auto sec = v.begin();
    sec++;

    double value = lokimath::mean<double>::calc(v.begin(), v.end());
    double exact = 3.0;
    double diff = abs(value - exact);
    bool test_is_fine = (diff == 0.0);
    std::cout << "lokimath::mean is fine: " << test_is_fine << std::endl;
}