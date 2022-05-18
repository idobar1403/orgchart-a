#include "doctest.h"
#include "OrgChart.hpp"
#include <iostream>
#include <string>
using namespace ariel;
TEST_CASE("int chart")
{
    OrgChart<int> chart_int;
    CHECK_NOTHROW(chart_int.add_root(1));
    CHECK_NOTHROW(chart_int.add_sub(1, 2));
    CHECK_NOTHROW(chart_int.add_sub(1, 3));
    CHECK_NOTHROW(chart_int.add_sub(2, 4));
    CHECK_NOTHROW(chart_int.add_sub(2, 5));
    CHECK_THROWS(chart_int.add_sub(0, 1));
    CHECK_THROWS(chart_int.add_sub(6, 5));
    CHECK_THROWS(chart_int.add_sub(-1,2));

    int level_order[] = {1, 2, 3, 4, 5};
    int reverse_order[] = {4, 5, 2, 3, 1};
    int pre_order[] = {1, 2, 4, 5, 3};
    int i = 0;
    for (auto it = chart_int.begin_level_order(); it != chart_int.end_level_order(); ++it)
    {
        CHECK((*it) == level_order[i]);
        i++;
    }
    i = 0;
    for (auto it = chart_int.begin_reverse_order(); it != chart_int.reverse_order(); ++it)
    {
        CHECK((*it) == reverse_order[i]);
        i++;
    }
    i=0;
    for (auto it = chart_int.begin_preorder(); it != chart_int.end_preorder(); ++it)
    {
        CHECK((*it) == pre_order[i]);
        i++;
    }
}