

#include <stdexcept>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.hpp"
#include <iostream>
#include <string>
#include <vector>


// tested source
#include "../src/lazy_tree.hpp"

#define HAPPY_BALANCE_PATH {5, 2, 1, 7, 9, 6, 10, 4}
#define MIN_VALUE 1
#define MAX_VALUE 10

TEST_CASE(".insert")
{
    Lazy_tree<int> tree;
    std::vector<int> path = HAPPY_BALANCE_PATH;

    for (int i : path) {
        CHECK_EQ(tree.insert(i), true);
    }

    CHECK_EQ(tree.insert(5),false);

    CHECK_EQ(tree.erase(9), true);
    // tree.clean();

    CHECK_EQ(tree.front(), MIN_VALUE);
    CHECK_EQ(tree.back(), MAX_VALUE);
}

TEST_CASE(".undo")
{
}

TEST_CASE(".redo")
{
}


TEST_CASE(".clear")
{
}

TEST_CASE(".swap")
{
}

TEST_CASE("copy constructor")
{
}
