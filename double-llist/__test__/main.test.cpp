
#include <stdexcept>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest.hpp"
#include <iostream>
#include <string>


// tested source
#include "../src/double-node.hpp"
#include "../src/llist.hpp"


TEST_CASE("Test DoubleNode .get() accessor method")
{

    std::string const SOME_STRING = "hello world";
    int const SOME_INT = 42;
    struct SOME_STRUCT {
        int one = 1;
        std::string two = "world";
    } TUPLE;

    DoubleNode<int> nodeWithIntData(SOME_INT);
    DoubleNode<std::string> nodeWithStringData(SOME_STRING);
    DoubleNode<SOME_STRUCT> nodeWithStructData(TUPLE);

    CHECK(nodeWithIntData.get() == SOME_INT);
    CHECK(nodeWithStringData.get() == SOME_STRING);
    CHECK(nodeWithStructData.get().one == TUPLE.one);
    CHECK(nodeWithStructData.get().two == TUPLE.two);

}

TEST_CASE(".push_front")
{
    LinkList<std::string> llist;
    CHECK(llist.size() == 0);
    CHECK(llist.empty() == true);

    llist.push_front("c");
    CHECK(llist.size() == 1);
    CHECK(llist.empty() == false);

    llist.push_front("b");
    CHECK(llist.size() == 2);
    CHECK_EQ(llist.front(), "b");
    CHECK(llist.back() == "c");

    llist.push_front("a");
    CHECK(llist.size() == 3);
    CHECK(llist.front() == "a");
    CHECK(llist.back() == "c");
}

TEST_CASE(".push_back")
{
    LinkList<std::string> llist;
    CHECK(llist.size() == 0);
    CHECK(llist.empty() == true);

    llist.push_back("c");
    CHECK(llist.size() == 1);
    CHECK(llist.empty() == false);

    llist.push_back("b");
    CHECK(llist.size() == 2);
    CHECK(llist.front() == "c");
    CHECK(llist.back() == "b");

    llist.push_back("a");
    CHECK(llist.size() == 3);
    CHECK(llist.front() == "c");
    CHECK(llist.back() == "a");
}

TEST_CASE(".erase")
{
    LinkList<std::string> llist;

    // Removing from front w/ one node
    llist.push_front("d");
    llist.erase("d");
    CHECK(llist.empty() == true);
    // CHECK_THROWS_WITH(llist.erase("X"), "Your list is empty");
    // CHECK_THROWS_AS(llist.erase("X"), std::invalid_argument);
    CHECK_EQ(llist.erase("X"), 0);


    // Check that head and tail are reset properly after removal
    llist.push_front("c");
    CHECK(llist.front() == "c");

    llist.push_front("b");
    llist.push_front("a");

    // Removing from middle
    llist.erase("b");
    CHECK_EQ(llist.front(), "a");
    CHECK_EQ(llist.back(), "c");

    // Erase from back
    llist.erase("c");
    CHECK_EQ(llist.back(), "a");

}

// the client should not need to implement a traversal
// this is done while implementing functions, it is not a feature of a link list

TEST_CASE("traversing nodes")
{

    LinkList<std::string> llist;

    llist.push_front("c");
    llist.push_front("b");
    llist.push_front("a");

    // Foward traversal chain
    CHECK(llist.front() == "a");


    // Backward traversal chain
    // CHECK(llist.back()->get() == "c");
    // CHECK(llist.back()->m_prev->get() == "b");
    // CHECK(llist.back()->m_prev->m_prev->get() == "a");
}

TEST_CASE(".contains")
{
    LinkList<std::string> llist;

    llist.push_front("c");
    llist.push_front("b");
    llist.push_front("a");

    std::cout << llist << std::endl;

    CHECK(llist.contains("a"));
    CHECK(llist.contains("c"));
    CHECK(llist.contains("b"));

    llist.erase("b");
    CHECK(llist.contains("a"));
    CHECK(llist.contains("c"));
    REQUIRE_FALSE(llist.contains("b"));

    llist.erase("a");
    llist.erase("c");
    REQUIRE_FALSE(llist.contains("c"));

    CHECK_EQ(llist.size(), 0);
    REQUIRE_FALSE(llist.contains("x"));
}

TEST_CASE(".count")
{

    LinkList<std::string> llist;

    llist.erase("x");

    llist.push_front("a");
    llist.push_front("a");
    llist.push_front("a");

    CHECK_EQ(llist.count("a"), 3);
    CHECK_EQ(llist.count("x"), 0);

    llist.erase("a");
    CHECK_EQ(llist.count("a"), 2);

}

TEST_CASE(".pop_front and .pop_back")
{

    LinkList<std::string> llist;

    llist.push_front("c");
    llist.push_front("b");
    llist.push_front("a");

    CHECK_EQ(llist.pop_front(), "a");
    CHECK_EQ(llist.pop_front(), "b");
    CHECK_EQ(llist.pop_front(), "c");

    llist.push_front("c");
    llist.push_front("b");
    llist.push_front("a");

    CHECK_EQ(llist.pop_back(), "c");
    CHECK_EQ(llist.pop_front(), "a");

    CHECK_EQ(llist.back(), "b");
    CHECK_EQ(llist.front(), "b");
    CHECK_EQ(llist.pop_back(), "b");
}

TEST_CASE(".swap")
{

    LinkList<std::string> list1;
    LinkList<std::string> list2;

    list1.push_front("c");
    list1.push_front("b");
    list1.push_front("a");

    list2.push_front("z");
    list2.push_front("y");
    list2.push_front("x");

    list1.swap(list2);

    std::cout << "list1" << std::endl;
    std::cout << list1 << std::endl;
    std::cout << "list2" << std::endl;
    std::cout << list2 << std::endl;

    CHECK_EQ(list1.front(), "x");
    CHECK_EQ(list2.front(), "a");
}