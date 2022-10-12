#define CATCH_CONFIG_MAIN // This should come **before** including the 'catch.hpp'.
#include <vector>
#include "catch.hpp"
#include "stackTasks.cpp"

TEST_CASE( "1: Task" ) {
    REQUIRE( task1(1) == 1 );
    REQUIRE( task1(2) == 2 );
    REQUIRE( task1(3) == 6 );
    REQUIRE( task1(10) == 3628800 );
}

TEST_CASE( "2: Task" ) {
    REQUIRE( task2("()") == true );
    REQUIRE( task2("{}()[]") == true );
    REQUIRE( task2("())") == false );
    REQUIRE( task2("[)(]") == false ); 
}


TEST_CASE( "3: Task" ) {
    std::vector<vector<int>> g;
    vector<int> first = {1, 2};
    vector<int> second = {0, 2, 3, 6};
    vector<int> empty;
    g.push_back(first); // 0
    g.push_back(second); // 1
    g.push_back(empty); // 2
    g.push_back(empty); // 3
    g.push_back(empty); // 4
    g.push_back(empty); // 5
    g.push_back(empty); // 6
    g.push_back(empty); //
    REQUIRE( task3(g, 0, 6) == true );
    REQUIRE( task3(g, 5, 6) == false );
    REQUIRE( task3(g, 1, 3) == true );
}

TEST_CASE( "4: Task") {
	REQUIRE( task4("3(A)") == "AAA" );
    REQUIRE( task4("12(ZQ)") == "ZQZQZQZQZQZQZQZQZQZQZQZQ" );
    REQUIRE( task4("2(2(A)3(B))") == "AABBBAABBB" );
}

TEST_CASE( "5: Task" ) {
    std::vector<vector<int>> g;
    vector<int> first = {1, 2};
    vector<int> second = {0, 2, 3, 6};
    vector<int> empty;
    g.push_back(first); // 0
    g.push_back(second);// 1
    g.push_back(empty); // 2
    g.push_back(empty); // 3
    g.push_back(empty); // 4
    g.push_back(empty); // 5
    g.push_back(empty); // 6
    g.push_back(empty); // 7
    REQUIRE( task3(g, 0, 6) == true );
    REQUIRE( task3(g, 5, 6) == false );
    REQUIRE( task3(g, 1, 3) == true );
}

TEST_CASE( "6: Task" ) {
    REQUIRE( task6("a-c", "c-a") == false );
    REQUIRE( task6("a+b-c", "a+(b-c)") == true );
    REQUIRE( task6("a-(b-(c-d+e))", "a-b+c-d+e") == true );
    REQUIRE( task6("a+c-d", "a-d+c") == false );
}
