
#include <stdexcept>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.hpp"
#include <iostream>
#include <string>


// tested source
#include "../src/sorted_list.hpp"

TEST_CASE(".insert")
{
    Sorted_list<std::string> slist;
    CHECK(slist.size() == 0);
    CHECK(slist.empty() == true);

    slist.insert("c");
    CHECK(slist.size() == 1);
    CHECK(slist.empty() == false);

    slist.insert("b");
    CHECK(slist.size() == 2);
    CHECK_EQ(slist.front(), "b");

    slist.insert("a");
    CHECK(slist.size() == 3);
    CHECK(slist.front() == "a");
}


TEST_CASE(".erase")
{
    Sorted_list<std::string> slist;

    // Removing from front w/ one node
    slist.insert("d");
    slist.erase("d");
    CHECK(slist.empty() == true);
    CHECK_EQ(slist.erase("X"), 0);


    // Check that head and tail are reset properly after removal
    slist.insert("a");
    CHECK(slist.front() == "a");

    slist.insert("b");
    slist.insert("c");

    // Removing from middle
    slist.erase("b");
    CHECK_EQ(slist.front(), "a");
    CHECK_EQ(slist.count("c"), 1);

    // Erase from back
    slist.erase("c");
    CHECK_EQ(slist.front(), "a");

}

TEST_CASE("list is sorted")
{

    Sorted_list<char> slist;
    std::string input = "giadcfebh";
    std::string output = "";
    std::string sorted = "abcdefghi";

    for (char c : input) {
        slist.insert(c);
    }
    while (!slist.empty()) {

        output += slist.pop_front();
    }

    CHECK_EQ(output, sorted);
}


TEST_CASE(".count")
{

    Sorted_list<std::string> slist;

    CHECK_EQ(slist.erase("x"), 0);

    slist.insert("a");
    slist.insert("a");
    slist.insert("a");
    slist.insert("c");
    slist.insert("e");
    slist.insert("c");

    CHECK_EQ(slist.count("a"), 3);
    CHECK_EQ(slist.count("x"), 0);

    slist.erase("a");
    CHECK_EQ(slist.count("a"), 2);
    CHECK_EQ(slist.count("c"), 2);

}

TEST_CASE(".pop_front")
{

    Sorted_list<std::string> slist;

    slist.insert("a");
    slist.insert("b");
    slist.insert("c");

    CHECK_EQ(slist.pop_front(), "a");
    CHECK_EQ(slist.pop_front(), "b");
    CHECK_EQ(slist.pop_front(), "c");

    slist.insert("c");
    slist.insert("b");
    slist.insert("a");

    CHECK_EQ(slist.pop_front(), "a");

    CHECK_EQ(slist.front(), "b");
}

TEST_CASE(".swap")
{

    Sorted_list<std::string> list1;
    Sorted_list<std::string> list2;

    list1.insert("c");
    list1.insert("a");
    list1.insert("b");

    list2.insert("z");
    list2.insert("x");
    list2.insert("y");

    CHECK_EQ(list1.front(), "a");
    CHECK_EQ(list2.front(), "x");

    list1.swap(list2);


    CHECK_EQ(list1.front(), "x");
    CHECK_EQ(list2.front(), "a");
}

TEST_CASE("copy constructor")
{

    Sorted_list<std::string> list1;

    list1.insert("a");
    list1.insert("b");
    list1.insert("c");

    Sorted_list<std::string> list2(list1);

    CHECK_EQ(list1.size(), list2.size());

    std::cout << "list1" << std::endl;
    std::cout << list1 << std::endl;
    std::cout << "list2" << std::endl;
    std::cout << list2 << std::endl;

    list1.pop_front();

    CHECK(list1.front() != list2.front());

    list2.pop_front();

    CHECK(list1.front() == list2.front());

    list1.insert("a");
    CHECK(list1.front() != list2.front());

    std::cout << "\n";
    std::cout << "list1" << std::endl;
    std::cout << list1 << std::endl;
    std::cout << "list2" << std::endl;
    std::cout << list2 << std::endl;
}
