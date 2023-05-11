

#include <stdexcept>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.hpp"
#include <iostream>
#include <string>
#include <vector>


// tested source
#include "../src/lazy_tree.hpp"


TEST_CASE(".insert")
{
    Lazy_tree<int> tree;
    std::vector<int> path = {5, 2, 1, 7, 9, 6, 10, 4};

    int j = 1;
    for (int i : path) {
        CHECK_EQ(tree.insert(i), true);
        CHECK_EQ(tree.size(), j++);
    }

    CHECK_EQ(tree.insert(5),false);

    CHECK_EQ(tree.front(), 1);
    CHECK_EQ(tree.back(), 10);
    CHECK_EQ(tree.height(), 4);
}

TEST_CASE(".erase")
{
    Lazy_tree<int> tree;
    std::vector<int> path = {5, 2, 1, 7, 9, 6, 10, 4};

    int j = 1;
    for (int i : path) {
        CHECK_EQ(tree.insert(i), true);
    }

    CHECK_EQ(tree.erase(2), true);
    CHECK_EQ(tree.erase(1), true);

    CHECK_EQ(tree.erase(1), false);
    CHECK_EQ(tree.front(), 4);

    CHECK_EQ(tree.erase(10), true);
    CHECK_EQ(tree.back(), 9);

    CHECK_EQ(tree.insert(2), true);
    CHECK_EQ(tree.front(), 2);

    tree.breadth_first_traversal();
    tree.clean();
    tree.breadth_first_traversal();
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
