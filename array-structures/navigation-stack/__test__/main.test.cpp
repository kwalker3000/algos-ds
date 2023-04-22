

#include <stdexcept>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.hpp"
#include <iostream>
#include <string>


// tested source
#include "../src/navigation_stack.hpp"

TEST_CASE(".insert")
{
    Navigation_stack<std::string> nStack;

    nStack.event("draw circle");
    nStack.event("draw square");
    nStack.event("erase square");
    nStack.event("cut circle");

    CHECK(nStack.can_undo() == true);
    CHECK(nStack.can_redo() == false);
}

TEST_CASE(".undo")
{
    Navigation_stack<std::string> nStack;

    nStack.event("draw circle");
    nStack.event("draw square");
    nStack.event("erase square");
    nStack.event("cut circle");

    std::string undoEvent_1 = nStack.undo();
    CHECK_EQ(undoEvent_1, "cut circle");
    CHECK(nStack.can_redo() == true);
    CHECK(nStack.can_undo() == true);

    nStack.undo();
    nStack.undo();
    std::string undoEvent_2 = nStack.undo();
    CHECK_EQ(undoEvent_2, "draw circle");
    CHECK(nStack.can_redo() == true);
    CHECK(nStack.can_undo() == false);

    CHECK_THROWS_WITH(nStack.undo(), "Undo stack is empty");

    nStack.event("add circle");
    CHECK(nStack.can_redo() == false);
    CHECK(nStack.can_undo() == true);
}

TEST_CASE(".redo")
{
    Navigation_stack<std::string> nStack;

    nStack.event("draw circle");
    nStack.event("draw square");
    nStack.event("erase square");
    nStack.event("cut circle");

    nStack.undo();
    std::string redoEvent_1 = nStack.redo();
    CHECK_EQ(redoEvent_1, "cut circle");
    CHECK(nStack.can_redo() == false);
    CHECK(nStack.can_undo() == true);

    nStack.undo();
    nStack.undo();
    std::string redoEvent_2 = nStack.redo();
    CHECK_EQ(redoEvent_2, "erase square");

    std::string redoEvent_3 = nStack.redo();
    CHECK_EQ(redoEvent_3, "cut circle");
    CHECK(nStack.can_redo() == false);
    CHECK(nStack.can_undo() == true);

    CHECK_THROWS_WITH(nStack.redo(), "Redo stack is empty");

    nStack.event("add circle");
    CHECK(nStack.can_redo() == false);
    CHECK(nStack.can_undo() == true);
}


TEST_CASE(".clear")
{
    Navigation_stack<std::string> nStack;

    nStack.event("draw circle");
    nStack.event("draw square");
    nStack.event("erase square");
    nStack.event("cut circle");

    nStack.undo();
    nStack.undo();

    CHECK(nStack.can_redo() == true);
    CHECK(nStack.can_undo() == true);

    nStack.clear();
    CHECK(nStack.can_redo() == false);
    CHECK(nStack.can_undo() == false);

    nStack.event("draw square");
    nStack.event("erase square");

    nStack.undo();
    CHECK(nStack.can_redo() == true);
    CHECK(nStack.can_undo() == true);
}

TEST_CASE(".swap")
{
    Navigation_stack<std::string> nStack_1;
    Navigation_stack<std::string> nStack_2;

    nStack_1.event("draw circle");
    nStack_1.event("draw square");
    nStack_2.event("erase square");
    nStack_2.event("cut circle");

    std::string ele_2 = nStack_2.undo();

    nStack_2.swap(nStack_1);

    std::string ele_1 = nStack_1.redo();

    CHECK_EQ(ele_2, ele_1);

}

TEST_CASE("copy constructor")
{
    Navigation_stack<std::string> nStack_1;

    nStack_1.event("draw circle");
    nStack_1.event("draw square");
    nStack_1.event("erase square");
    nStack_1.event("cut circle");

    nStack_1.undo();
    nStack_1.undo();
    Navigation_stack<std::string> nStack_2(nStack_1);

    std::string ele_2 = nStack_2.redo();
    std::string ele_1 = nStack_1.redo();

    CHECK_EQ(ele_2, ele_1);

    nStack_2.redo();

    CHECK(nStack_2.can_redo() == false);
    CHECK(nStack_1.can_redo() == true);

    CHECK(nStack_2.can_undo() == true);
    CHECK(nStack_1.can_undo() == true);

    nStack_1.clear();

    CHECK(nStack_2.can_undo() == true);
    CHECK(nStack_1.can_undo() == false);

}
