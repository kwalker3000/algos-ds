
#include <stdexcept>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.hpp"
#include <iostream>
#include <string>


// tested source
#include "../src/dynamic_queue.hpp"

TEST_CASE(".enqueue and .dequeue")
{
    Dynamic_queue<std::string> d_queue(4);

    CHECK(d_queue.empty() == true);
    d_queue.enqueue("one");
    CHECK(d_queue.empty() == false);
    CHECK_EQ(d_queue.size(), 1);

    d_queue.dequeue();
    CHECK_EQ(d_queue.size(), 0);
    CHECK(d_queue.empty() == true);

    d_queue.enqueue("two");
    d_queue.enqueue("three");
    d_queue.enqueue("four");

    CHECK_EQ(d_queue.size(), 3);
    CHECK_EQ(d_queue.head(), "two");

    d_queue.dequeue();
    CHECK_EQ(d_queue.head(), "three");

    d_queue.enqueue("five");
    d_queue.enqueue("six");
    d_queue.enqueue("seven");

    // After doubling container size
    CHECK_EQ(d_queue.head(), "three");


    d_queue.dequeue();
    d_queue.dequeue();
    d_queue.dequeue();

    // After halving container size
    d_queue.enqueue("eight");
    CHECK_EQ(d_queue.head(), "six");


}

TEST_CASE(".clear")
{
    Dynamic_queue<std::string> d_queue(4);

    d_queue.enqueue("one");
    d_queue.enqueue("two");
    d_queue.enqueue("three");

    std::cout << d_queue << std::endl;

    d_queue.clear();
    CHECK_EQ(d_queue.size(), 0);

    d_queue.enqueue("one");
    CHECK_EQ(d_queue.size(), 1);

    CHECK_EQ(d_queue.head(),"one");

}


TEST_CASE(".swap")
{
    Dynamic_queue<std::string> d_queue1(4);
    d_queue1.enqueue("one");
    d_queue1.enqueue("two");
    d_queue1.enqueue("three");

    Dynamic_queue<std::string> d_queue2(4);
    d_queue2.enqueue("cat");
    d_queue2.enqueue("dog");
    d_queue2.enqueue("mouse");

    CHECK_EQ(d_queue1.head(), "one");
    CHECK(d_queue2.head() != "one");

    d_queue1.swap(d_queue2);
    CHECK_EQ(d_queue2.head(), "one");
    CHECK(d_queue1.head() != "one");

}

TEST_CASE("copy constructor")
{

    Dynamic_queue<std::string> d_queue1(4);
    d_queue1.enqueue("one");
    d_queue1.enqueue("two");
    d_queue1.enqueue("three");

    Dynamic_queue<std::string> d_queue2(d_queue1);

    CHECK_EQ(d_queue1.head(), d_queue2.head());

    d_queue2.dequeue();

    CHECK(d_queue1.head() != d_queue2.head());
}
