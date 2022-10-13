#define CATCH_CONFIG_MAIN // This should come **before** including the 'catch.hpp'.
#include <vector>
#include "stackTasks.cpp"
#include "catch.hpp"

TEST_CASE( "1: Task" ) {
    //Mine
    REQUIRE(task1(0) == 1);

    //Svilen
    REQUIRE( task1(1) == 1 );
    REQUIRE( task1(2) == 2 );
    REQUIRE( task1(3) == 6 );

    //Mine
    REQUIRE(task1(7) == 5040);

    //Svilen
    REQUIRE( task1(10) == 3628800 );
}

TEST_CASE( "2: Task" ) {
    //Svilen
    REQUIRE(task2("") == true);
    REQUIRE( task2("()") == true );
    REQUIRE( task2("{}()[]") == true );
    REQUIRE( task2("())") == false );
    REQUIRE( task2("[)(]") == false );

    //Mine
    REQUIRE(task2("(define [sum n] {+ n 1})") == true);
    REQUIRE(task2("(define [sum n] {+ n 1}) ([{define anything 13}])") == true);
    REQUIRE(task2("(]") == false);
    REQUIRE(task2("(define [sum n] {+ n 1]) ([{define anything 13}])") == false);
}


TEST_CASE( "3: Task" ) {
    //Svilen
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

    //Mine
    std::vector<vector<int>> g2; //(1, 2) (1, 4) (2, 3)
    g2.push_back(empty);
    g2.push_back(std::vector<int>{2, 4});
    g2.push_back(std::vector<int>{3});
    g2.push_back(empty);
    g2.push_back(empty);

    REQUIRE(task3(g2, 1, 2) == true);
    REQUIRE(task3(g2, 1, 3) == true);
    REQUIRE(task3(g2, 2, 1) == false);
    REQUIRE(task3(g2, 4, 1) == false);
    REQUIRE(task3(g2, 3, 4) == false);

    std::vector<vector<int>> g3; //(1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3)
    g3.push_back(empty);
    g3.push_back(std::vector<int>{2, 3});
    g3.push_back(std::vector<int>{4, 5});
    g3.push_back(std::vector<int>{7});
    g3.push_back(std::vector<int>{5});
    g3.push_back(std::vector<int>{2, 6});
    g3.push_back(empty);
    g3.push_back(empty);
    g3.push_back(std::vector<int>{9});
    g3.push_back(std::vector<int>{3});

    REQUIRE(task3(g3, 1, 6) == true);
    REQUIRE(task3(g3, 4, 2) == true);
    REQUIRE(task3(g3, 1, 7) == true);
    REQUIRE(task3(g3, 1, 9) == false);
    REQUIRE(task3(g3, 8, 1) == false);
    REQUIRE(task3(g3, 8, 7) == true);
    REQUIRE(task3(g3, 1, 1) == true);
}

TEST_CASE( "4: Task") {
    //Svilen
	REQUIRE( task4("3(A)") == "AAA" );
    REQUIRE( task4("12(ZQ)") == "ZQZQZQZQZQZQZQZQZQZQZQZQ" );
    REQUIRE( task4("2(2(A)3(B))") == "AABBBAABBB" );

    //Mine
    REQUIRE(task4("aBz3(XY2(io))RoS2(En)") == "aBzXYioioXYioioXYioioRoSEnEn");
    REQUIRE(task4("PochUv3(S2(TvAl)2(2(Ite)))4(See) E Mega 3(qkata) GRU10(aA3(a)100())") == "PochUvSTvAlTvAlIteIteIteIteSTvAlTvAlIteIteIteIteSTvAlTvAlIteIteIteIteSeeSeeSeeSee E Mega qkataqkataqkata GRUaAaaaaAaaaaAaaaaAaaaaAaaaaAaaaaAaaaaAaaaaAaaaaAaaa");
    REQUIRE(task4("") == "");
}

TEST_CASE( "5: Task" ) {
    //Svilen
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

    REQUIRE(task5(g, 0, 6) == true );
    REQUIRE(task5(g, 5, 6) == false );
    REQUIRE(task5(g, 1, 3) == true );

    //Mine
    std::vector<vector<int>> g2; //(1, 2) (1, 4) (2, 3)
    g2.push_back(empty);
    g2.push_back(std::vector<int>{2, 4});
    g2.push_back(std::vector<int>{3});
    g2.push_back(empty);
    g2.push_back(empty);

    REQUIRE(task5(g2, 1, 2) == true);
    REQUIRE(task5(g2, 1, 3) == true);
    REQUIRE(task5(g2, 2, 1) == false);
    REQUIRE(task5(g2, 4, 1) == false);
    REQUIRE(task5(g2, 3, 4) == false);

    std::vector<vector<int>> g3; //(1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3)
    g3.push_back(empty); //0
    g3.push_back(std::vector<int>{2, 3}); //1
    g3.push_back(std::vector<int>{4, 5}); //2
    g3.push_back(std::vector<int>{7}); //3
    g3.push_back(std::vector<int>{5}); //4
    g3.push_back(std::vector<int>{2, 6}); //5
    g3.push_back(empty); // 6
    g3.push_back(empty);
    g3.push_back(std::vector<int>{9});
    g3.push_back(std::vector<int>{3});

    REQUIRE(task5(g3, 1, 6) == true);
    REQUIRE(task5(g3, 4, 2) == true);
    REQUIRE(task5(g3, 1, 7) == true);
    REQUIRE(task5(g3, 1, 9) == false);
    REQUIRE(task5(g3, 8, 1) == false);
    REQUIRE(task5(g3, 8, 7) == true);
    REQUIRE(task5(g3, 1, 1) == true);
}

TEST_CASE( "6: Task" ) {
    //Svilen
    REQUIRE( task6("a-c", "c-a") == false );
    REQUIRE( task6("a+b-c", "a+(b-c)") == true );
    REQUIRE( task6("a-(b-(c-d+e))", "a-b+c-d+e") == true );
    REQUIRE( task6("a+c-d", "a-d+c") == false );

    //Mine
    REQUIRE(task6("c-(a+b)", "(-(-c+a)-b)") == true);
    REQUIRE(task6("-a-((-b)-(d-c+(-e-f+g))-(+h-(-i)))", "-a+b+d-c-e-f+g+h+i") == true);
    REQUIRE(task6("d-(c-(-a)+(-b))", "d-c-a+b") == true);
}
