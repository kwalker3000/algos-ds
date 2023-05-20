

#include <stdexcept>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.hpp"
#include <iostream>
#include <string>
#include <vector>


// tested source
#include "../src/quad_hash_table.hpp"


TEST_CASE("starter")
{
    Quad_hash<std::string> str_hash;

    str_hash.insert("eggs");
    CHECK_EQ(str_hash.member("eggs"), true);

    str_hash.insert("sausage");
    str_hash.insert("biscuit");
    str_hash.insert("coffee");
    str_hash.insert("cream");

    CHECK_EQ(str_hash.member("sausage"), true);
    CHECK_EQ(str_hash.member("biscuit"), true);
    CHECK_EQ(str_hash.member("cream"), true);
    CHECK_EQ(str_hash.member("coffee"), true);

    std::cout << str_hash.load_factor() << std::endl;

    CHECK_EQ(str_hash.erase("sausage"), true);
    CHECK_EQ(str_hash.member("sausage"), false);

    str_hash.clear();

    CHECK_EQ(str_hash.member("sausage"), false);
    CHECK_EQ(str_hash.member("biscuit"), false);
    CHECK_EQ(str_hash.member("cream"), false);
    CHECK_EQ(str_hash.member("coffee"), false);

}

