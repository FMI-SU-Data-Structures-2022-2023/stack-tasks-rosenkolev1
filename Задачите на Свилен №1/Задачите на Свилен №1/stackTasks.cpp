#include <string>
#include <vector>
using namespace std;

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

int factorial(int n)
{
    int product = 1;
    if (n < 0) throw std::invalid_argument("The factorial number is negative!");
    //if (n == 1 || n == 0) return product;

    for (size_t i = 2; i <= n; i++)
    {
        product *= i;
    }
    return product;
}

bool correctRacketExpr(std::string racketExpr)
{
    std::vector<char> bracesTypes;

    for (size_t i = 0; i < racketExpr.length(); i++)
    {
        char symbol = racketExpr[i];

        if (symbol == '(' || symbol == '{' || symbol == '[') bracesTypes.push_back(symbol);
        else if (symbol == ')')
        {
            if (bracesTypes.size() == 0 || bracesTypes.back() != '(') return false;
            else bracesTypes.pop_back();

        }
        else if (symbol == '}')
        {
            if (bracesTypes.size() == 0 || bracesTypes.back() != '{') return false;
            else bracesTypes.pop_back();
        }
        else if (symbol == ']')
        {
            if (bracesTypes.size() == 0 || bracesTypes.back() != '[') return false;
            else bracesTypes.pop_back();
        }

    }

    return bracesTypes.size() == 0;
}

std::vector<std::vector<int>> changeGraphRepresentation(std::vector<std::vector<int>> graph)
{
    std::vector<std::vector<int>> graphOther;

    for (int i = 0; i < graph.size(); i++)
    {
        for (int y = 0; y < graph[i].size(); y++)
        {
            graphOther.push_back(std::vector<int>{i, graph[i][y]});
        }
    }

    return graphOther;
}

bool existsPathDFS(std::vector<std::vector<int>> graph, int from, int to, std::vector<int> visitedFromPoints)
{
    //Check if the 2 points are the same. This is the base case for the recursion
    if (from == to) return true;

    //Add the beginning point as already visited
    visitedFromPoints.push_back(from);

    //Check if the from point is connected to any other point in the graph, 
    //If yes, then do DFS search using that point as a new starting point 
    for (size_t i = 0; i < graph.size(); i++)
    {
        int fromPoint = graph[i][0];
        int toPoint = graph[i][1];

        if (fromPoint == from && std::count(visitedFromPoints.begin(), visitedFromPoints.end(), toPoint) == 0)
        {
            //Check if there is a path from the destination point to the end point
            if (existsPathDFS(graph, toPoint, to, visitedFromPoints)) return true;
        }
    }

    //If we get here, then there is no path inbetween the original points
    return false;
}

bool existsPathDFS(std::vector<std::vector<int>> graph, int from, int to)
{
    graph = changeGraphRepresentation(graph);

    return existsPathDFS(graph, from, to, std::vector<int>{});
}

std::string decompressText(std::string text)
{
    bool foundGroup = false;
    std::string repeatCountString = "";
    int repeatCount = -1;
    int startOfGroupIndex = -1;
    std::string currentGroupString = "";
    int closingBracketIndex = -1;

    std::string revText = "";
    std::stack<char> charStack = std::stack<char>();

    for (size_t i = 0; i < text.length(); i++)
    {
        char symbol = text[i];

        if (symbol == ')')
        {
            //Get the repeated word
            std::string bracketsRevText = "";
            int numberOfRepeats = 0;
            while (charStack.top() != '(')
            {
                bracketsRevText += charStack.top();
                charStack.pop();
            }
            charStack.pop(); //Removes the '('

            //Get the number of times to repeat a word
            int digitPos = 0;
            while (!charStack.empty() && isdigit(charStack.top()))
            {
                int digit = charStack.top() - '0';

                numberOfRepeats += pow(10, digitPos) * digit;
                
                digitPos++;
                charStack.pop();
            }

            //Repeat the bracket words many times
            for (size_t i = 0; i < numberOfRepeats; i++)
            {
                for (int y = bracketsRevText.length() - 1; y >= 0; y--)
                {
                    charStack.push(bracketsRevText[y]); 
                }
            }
        }
        else
        {
            charStack.push(symbol);
        }        

        //if (isalpha(symbol) && foundGroup)
        //{
        //    currentGroupString.push_back(symbol);
        //}
        //else if (isdigit(symbol))
        //{
        //    foundGroup = true;
        //    startOfGroupIndex = i;

        //    repeatCountString = "";
        //    repeatCount = -1;
        //    currentGroupString = "";
        //    closingBracketIndex = -1;

        //    for (size_t y = i; y < text.length(); y++)
        //    {
        //        if (isdigit(text[y]))
        //        {
        //            repeatCountString.push_back(text[y]);
        //        }
        //        else
        //        {
        //            //We have reached a '(' character
        //            repeatCount = std::stoi(repeatCountString);
        //            i = y;
        //            break;
        //        }
        //    }
        //}
        //else if (symbol == ')' && foundGroup)
        //{
        //    closingBracketIndex = i;

        //    std::string replacementString = "";
        //    for (size_t i = 0; i < repeatCount; i++)
        //    {
        //        replacementString.append(currentGroupString);
        //    }

        //    text.replace(startOfGroupIndex, closingBracketIndex - startOfGroupIndex + 1, replacementString);

        //    //Reset all the values back to normal and start the cycle from the beginning
        //    bool foundGroup = false;
        //    std::string repeatCountString = "";
        //    int repeatCount = -1;
        //    int startOfGroupIndex = -1;
        //    std::string currentGroupString = "";
        //    int closingBracketIndex = -1;

        //    i = -1;
        //}
    }

    //Now poop the text from the stack
    while (!charStack.empty())
    {
        revText += charStack.top();
        charStack.pop();
    }

    //Reverse the text
    reverse(revText.begin(), revText.end());

    return revText;
    //return text;
}

bool existsPathDFSNoRecursion(std::vector<std::vector<int>> graph, int from, int to)
{
    graph = changeGraphRepresentation(graph);

    std::vector<std::string> visitedDeadEndPaths;
    std::string currentPath = std::to_string(from);

    int currentFrom = from;

    while (true)
    {
        for (size_t i = 0; i < graph.size(); i++)
        {
            int fromPoint = graph[i][0];
            int toPoint = graph[i][1];

            //Check if the from point matches the current one and also if the toPoint is causing a loop in the path
            if (fromPoint == currentFrom && currentPath.find(std::to_string(toPoint)) == std::string::npos)
            {
                //Check if all emerging paths have been visited already
                std::string potentialPath = currentPath + std::to_string(toPoint);

                bool isVisited = false;
                for (size_t y = 0; y < visitedDeadEndPaths.size(); y++)
                {
                    std::string deadEndPath = visitedDeadEndPaths[y];
                    if (deadEndPath.find(potentialPath) != std::string::npos)
                    {
                        //In this case, the path has already been visited so we cannot visit it again
                        isVisited = true;
                        break;
                    }
                }

                //In this case, we have found a new path to explore
                if (!isVisited)
                {
                    currentFrom = toPoint;
                    currentPath.push_back(toPoint + '0');
                    i = -1;
                }
            }
        }

        if (currentPath[0] - '0' == from && currentPath[currentPath.size() - 1] - '0' == to) return true;
        else
        {
            //In this case, all the paths starting from the first node are a dead end, so we return false
            if (currentPath.size() == 1) return false;

            //In this case, the path is a dead end so we add it to the list of visited paths 
            //and move back one node from the current one and try a different path
            visitedDeadEndPaths.push_back(currentPath);

            currentPath.pop_back();
            currentFrom = currentPath[currentPath.size() - 1] - '0';
        }
    }

}

std::string simplifyExpression(std::string expr)
{
    //If the expr begins with an unknown, then add a + before it
    if (isalpha(expr[0]))
    {
        expr.insert(expr.begin(), '+');
    }

    for (size_t i = 0; i < expr.size(); i++)
    {
        char symbol = expr[i];

        if (symbol == '(')
        {
            int openingBracketsIndex = i;
            int closingBracketsIndex = -1;
            for (size_t y = i + 1; y < expr.size(); y++)
            {
                if (expr[y] == ')')
                {
                    closingBracketsIndex = y;
                    break;
                }
                else if (expr[y] == '(')
                {
                    break;
                }
            }

            //In this case, we have found bottom nested brackets (without any brackets inside the brackets)
            if (closingBracketsIndex > -1)
            {
                std::string exprInBrackets = expr.substr(openingBracketsIndex + 1, closingBracketsIndex - openingBracketsIndex - 1);

                if (i > 0 && (expr[i - 1] == '-' || expr[i - 1] == '+'))
                {
                    char signForBrackets = expr[i - 1];

                    //If the expr in the brackets begins with an unknown, then add a '+' in front of the digit
                    if (isalpha(exprInBrackets[0])) exprInBrackets.insert(exprInBrackets.begin(), '+');

                    //If the sign for the brackets is -, then invert the operators
                    if (signForBrackets == '-')
                    {
                        for (size_t y = 0; y < exprInBrackets.size(); y++)
                        {
                            if (exprInBrackets[y] == '+') exprInBrackets[y] = '-';
                            else if (exprInBrackets[y] == '-') exprInBrackets[y] = '+';
                        }
                    }

                    //Replace the exprInBrackets inside the expr string // -(a+b)+c //0 1 5
                    expr.replace(openingBracketsIndex - 1, closingBracketsIndex - openingBracketsIndex + 2, exprInBrackets);
                }
                //In this case, we have something like (a+b) or a+((b)) where we have brackets that do not have an operator before them
                else
                {
                    //Replace the exprInBrackets inside the expr string
                    expr.replace(openingBracketsIndex, closingBracketsIndex - openingBracketsIndex + 1, exprInBrackets);
                }

                //Finally, start iterating the expr again and resolving all the other brackets
                i = -1;
            }
        }
    }

    //Now that the brackets are all resolved, then remove all the unknowns as necessary
    std::vector<char> uniqueUnknowns;
    for (size_t i = 0; i < expr.size(); i++)
    {
        if (isalpha(expr[i]) && std::count(uniqueUnknowns.begin(), uniqueUnknowns.end(), expr[i]) == 0) uniqueUnknowns.push_back(expr[i]);
    }

    std::vector<std::string> partsOfFinalExpr;

    //Search for +x and -x variants for all unique unknown
    for (size_t i = 0; i < uniqueUnknowns.size(); i++)
    {
        std::string plusVariant = "+" + std::string(1, uniqueUnknowns[i]);
        std::string minusVariant = "-" + std::string(1, uniqueUnknowns[i]);

        //Count plus variants
        int plusVariantCount = 0;
        int variantSearchIndex = -1;
        while (expr.find(plusVariant, variantSearchIndex + 1) != std::string::npos)
        {
            variantSearchIndex = expr.find(plusVariant, variantSearchIndex + 1);
            plusVariantCount++;
        }

        int minusVariantCount = 0;
        variantSearchIndex = -1;
        while (expr.find(minusVariant, variantSearchIndex + 1) != std::string::npos)
        {
            variantSearchIndex = expr.find(minusVariant, variantSearchIndex + 1);
            minusVariantCount++;
        }

        if (plusVariantCount > minusVariantCount) partsOfFinalExpr.push_back(plusVariant);
        else if (plusVariantCount < minusVariantCount) partsOfFinalExpr.push_back(minusVariant);
    }

    std::string finalExpr = "";
    for (size_t i = 0; i < partsOfFinalExpr.size(); i++)
    {
        finalExpr += partsOfFinalExpr[i];
    }

    //If the finalExpr starts with a '+', then remove it
    if (finalExpr[0] == '+') finalExpr.replace(0, 1, "");

    return finalExpr;
}

bool compareExpressions(std::string expr1, std::string expr2)
{
    return simplifyExpression(expr1) == simplifyExpression(expr2);
}

int task1( int number ) {
    return factorial(number);
}

bool task2 (const string& list) {
    return correctRacketExpr(list);
}

bool task3(const vector<vector<int>>& g, unsigned from, unsigned to) {
	return existsPathDFS(g, from, to);
}

string task4 (const string& input) {
    return decompressText(input);
}

bool task5(vector<vector<int>>g, unsigned from, unsigned to) {
	return existsPathDFSNoRecursion(g, from, to);
}

bool task6(const string& a, const string& b) {
	return compareExpressions(a, b);
}

//int main()
//{
//    //TASK 1 - Factorial function
//    std::cout << "TASK 1" << std::endl;
//    int n = 0;
//    std::cout << "The factorial of " << n << "! is: " << factorial(n) << std::endl;
//    n = 1;
//    std::cout << "The factorial of " << n << "! is: " << factorial(n) << std::endl;
//    n = 2;
//    std::cout << "The factorial of " << n << "! is: " << factorial(n) << std::endl;
//    n = 7;
//    std::cout << "The factorial of " << n << "! is: " << factorial(n) << std::endl;
//
//    //New line between tasks
//    std::cout << std::endl;
//
//    //TASK 2 - Racket expr
//    std::cout << "TASK 2" << std::endl;
//    std::string racketExpr = "";
//    std::cout << "The racket expr is correct?: \"" << racketExpr << "\" --> "
//        << (correctRacketExpr(racketExpr) == 1 ? "True" : "False") << std::endl;
//
//    racketExpr = "(define [sum n] {+ n 1})";
//    std::cout << "The racket expr is correct?: \"" << racketExpr << "\" --> "
//        << (correctRacketExpr(racketExpr) == 1 ? "True" : "False") << std::endl;
//
//    racketExpr = "(define [sum n] {+ n 1}) ([{define anything 13}])";
//    std::cout << "The racket expr is correct?: \"" << racketExpr << "\" --> "
//        << (correctRacketExpr(racketExpr) == 1 ? "True" : "False") << std::endl;
//
//    racketExpr = "(]";
//    std::cout << "The racket expr is correct?: \"" << racketExpr << "\" --> "
//        << (correctRacketExpr(racketExpr) == 1 ? "True" : "False") << std::endl;
//
//    racketExpr = "(define [sum n] {+ n 1]) ([{define anything 13}])";
//    std::cout << "The racket expr is correct?: \"" << racketExpr << "\" --> "
//        << (correctRacketExpr(racketExpr) == 1 ? "True" : "False") << std::endl;
//
//    //New line between tasks
//    std::cout << std::endl;
//
//    //TASK 3 - DFS search of graph
//    std::cout << "TASK 3" << std::endl;
//    std::vector<std::vector<int>> graph1;
//    /*
//
//    (1, 2) (1, 4) (2, 3)
//
//    */
//    graph1.push_back(std::vector<int> {1, 2});
//    graph1.push_back(std::vector<int> {1, 4});
//    graph1.push_back(std::vector<int> {2, 3});
//
//    int from = 1;
//    int to = 2;
//    std::cout << "Is there a path for the graph (1, 2) (1, 4) (2, 3) from: " << from << " --> " << to << " |==> "
//        << (existsPathDFS(graph1, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 1;
//    to = 3;
//    std::cout << "Is there a path for the graph (1, 2) (1, 4) (2, 3) from: " << from << " --> " << to << " |==> "
//        << (existsPathDFS(graph1, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 2;
//    to = 1;
//    std::cout << "Is there a path for the graph (1, 2) (1, 4) (2, 3) from: " << from << " --> " << to << " |==> "
//        << (existsPathDFS(graph1, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 4;
//    to = 1;
//    std::cout << "Is there a path for the graph (1, 2) (1, 4) (2, 3) from: " << from << " --> " << to << " |==> "
//        << (existsPathDFS(graph1, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 3;
//    to = 4;
//    std::cout << "Is there a path for the graph (1, 2) (1, 4) (2, 3) from: " << from << " --> " << to << " |==> "
//        << (existsPathDFS(graph1, from, to) == 1 ? "True" : "False") << std::endl;
//
//    std::vector<std::vector<int>> graph2;
//    /*
//
//    (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3)
//
//    */
//    graph2.push_back(std::vector<int> {1, 2});
//    graph2.push_back(std::vector<int> {1, 3});
//    graph2.push_back(std::vector<int> {2, 4});
//    graph2.push_back(std::vector<int> {2, 5});
//    graph2.push_back(std::vector<int> {4, 5});
//    graph2.push_back(std::vector<int> {5, 2});
//    graph2.push_back(std::vector<int> {5, 6});
//    graph2.push_back(std::vector<int> {3, 7});
//    graph2.push_back(std::vector<int> {8, 9});
//    graph2.push_back(std::vector<int> {9, 3});
//
//    from = 1;
//    to = 6;
//    std::cout << "Is there a path for the graph (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3) from: "
//        << from << " --> " << to << " |==> "
//        << (existsPathDFS(graph2, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 4;
//    to = 2;
//    std::cout << "Is there a path for the graph (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3) from: "
//        << from << " --> " << to << " |==> "
//        << (existsPathDFS(graph2, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 4;
//    to = 2;
//    std::cout << "Is there a path for the graph (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3) from: "
//        << from << " --> " << to << " |==> "
//        << (existsPathDFS(graph2, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 1;
//    to = 7;
//    std::cout << "Is there a path for the graph (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3) from: "
//        << from << " --> " << to << " |==> "
//        << (existsPathDFS(graph2, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 1;
//    to = 9;
//    std::cout << "Is there a path for the graph (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3) from: "
//        << from << " --> " << to << " |==> "
//        << (existsPathDFS(graph2, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 8;
//    to = 1;
//    std::cout << "Is there a path for the graph (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3) from: "
//        << from << " --> " << to << " |==> "
//        << (existsPathDFS(graph2, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 8;
//    to = 7;
//    std::cout << "Is there a path for the graph (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3) from: "
//        << from << " --> " << to << " |==> "
//        << (existsPathDFS(graph2, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 1;
//    to = 1;
//    std::cout << "Is there a path for the graph (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3) from: "
//        << from << " --> " << to << " |==> "
//        << (existsPathDFS(graph2, from, to) == 1 ? "True" : "False") << std::endl;
//
//    //New line between tasks
//    std::cout << std::endl;
//
//    //TASK 4
//    std::cout << "TASK 4" << std::endl;
//
//    std::string compressedText = "aBz3(XY2(io))RoS2(En)"; //aBz3(XYioio)RoSEnEn --> aBzXYioioXYioioXYioioRoSEnEn
//    std::string expectedDecompressedText = "aBzXYioioXYioioXYioioRoSEnEn";
//    std::string decompressedText = decompressText(compressedText);
//
//    std::cout << "Decompressing text from \"" << compressedText << "\" to --> " << decompressedText << " |==> "
//        << (decompressedText == expectedDecompressedText ? "True" : "False") << std::endl;
//
//    compressedText = "PochUv3(S2(TvAl)2(2(Ite)))4(See) E Mega 3(qkata) GRU10(aA3(a)100())";
//    //PochUvSTvAlTvAlIteIteIteIteSTvAlTvAlIteIteIteIteSTvAlTvAlIteIteIteIteSeeSeeSeeSee E Mega qkataqkataqkata GRUaAaaaaAaaaaAaaaaAaaaaAaaaaAaaaaAaaaaAaaaaAaaaaAaaa
//    expectedDecompressedText = "PochUvSTvAlTvAlIteIteIteIteSTvAlTvAlIteIteIteIteSTvAlTvAlIteIteIteIteSeeSeeSeeSee E Mega qkataqkataqkata GRUaAaaaaAaaaaAaaaaAaaaaAaaaaAaaaaAaaaaAaaaaAaaaaAaaa";
//    decompressedText = decompressText(compressedText);
//
//    std::cout << "Decompressing text from \"" << compressedText << "\" to --> " << decompressedText << " |==> "
//        << (decompressedText == expectedDecompressedText ? "True" : "False") << std::endl;
//
//    //New line between tasks
//    std::cout << std::endl;
//
//    //TASK 5
//    std::cout << "TASK 5" << std::endl;
//
//    std::vector<std::vector<int>> graph3;
//    /*
//
//    (1, 2) (1, 4) (2, 3)
//
//    */
//    graph3.push_back(std::vector<int> {1, 2});
//    graph3.push_back(std::vector<int> {1, 4});
//    graph3.push_back(std::vector<int> {2, 3});
//
//    from = 1;
//    to = 2;
//    std::cout << "Is there a path for the graph (1, 2) (1, 4) (2, 3) from: " << from << " --> " << to << " |==> "
//        << (existsPathDFSNoRecursion(graph3, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 1;
//    to = 3;
//    std::cout << "Is there a path for the graph (1, 2) (1, 4) (2, 3) from: " << from << " --> " << to << " |==> "
//        << (existsPathDFSNoRecursion(graph3, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 2;
//    to = 1;
//    std::cout << "Is there a path for the graph (1, 2) (1, 4) (2, 3) from: " << from << " --> " << to << " |==> "
//        << (existsPathDFSNoRecursion(graph3, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 4;
//    to = 1;
//    std::cout << "Is there a path for the graph (1, 2) (1, 4) (2, 3) from: " << from << " --> " << to << " |==> "
//        << (existsPathDFSNoRecursion(graph3, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 3;
//    to = 4;
//    std::cout << "Is there a path for the graph (1, 2) (1, 4) (2, 3) from: " << from << " --> " << to << " |==> "
//        << (existsPathDFSNoRecursion(graph3, from, to) == 1 ? "True" : "False") << std::endl;
//
//    std::vector<std::vector<int>> graph4;
//    /*
//
//    (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3)
//
//    */
//    graph4.push_back(std::vector<int> {1, 2});
//    graph4.push_back(std::vector<int> {1, 3});
//    graph4.push_back(std::vector<int> {2, 4});
//    graph4.push_back(std::vector<int> {2, 5});
//    graph4.push_back(std::vector<int> {4, 5});
//    graph4.push_back(std::vector<int> {5, 2});
//    graph4.push_back(std::vector<int> {5, 6});
//    graph4.push_back(std::vector<int> {3, 7});
//    graph4.push_back(std::vector<int> {8, 9});
//    graph4.push_back(std::vector<int> {9, 3});
//
//    from = 1;
//    to = 6;
//    std::cout << "Is there a path for the graph (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3) from: "
//        << from << " --> " << to << " |==> "
//        << (existsPathDFSNoRecursion(graph4, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 4;
//    to = 2;
//    std::cout << "Is there a path for the graph (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3) from: "
//        << from << " --> " << to << " |==> "
//        << (existsPathDFSNoRecursion(graph4, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 4;
//    to = 2;
//    std::cout << "Is there a path for the graph (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3) from: "
//        << from << " --> " << to << " |==> "
//        << (existsPathDFSNoRecursion(graph4, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 1;
//    to = 7;
//    std::cout << "Is there a path for the graph (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3) from: "
//        << from << " --> " << to << " |==> "
//        << (existsPathDFSNoRecursion(graph4, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 1;
//    to = 9;
//    std::cout << "Is there a path for the graph (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3) from: "
//        << from << " --> " << to << " |==> "
//        << (existsPathDFSNoRecursion(graph4, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 8;
//    to = 1;
//    std::cout << "Is there a path for the graph (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3) from: "
//        << from << " --> " << to << " |==> "
//        << (existsPathDFSNoRecursion(graph4, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 8;
//    to = 7;
//    std::cout << "Is there a path for the graph (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3) from: "
//        << from << " --> " << to << " |==> "
//        << (existsPathDFSNoRecursion(graph4, from, to) == 1 ? "True" : "False") << std::endl;
//
//    from = 1;
//    to = 1;
//    std::cout << "Is there a path for the graph (1, 2) (1, 3) (2, 4) (2, 5) (4, 5) (5, 2) (5, 6) (3, 7) (8, 9) (9, 3) from: "
//        << from << " --> " << to << " |==> "
//        << (existsPathDFSNoRecursion(graph4, from, to) == 1 ? "True" : "False") << std::endl;
//
//    //New line between tasks
//    std::cout << std::endl;
//
//    //TASK 6
//    std::cout << "TASK 6" << std::endl;
//
//    std::string expr = "a+b";
//    std::cout << "Simplifying the expression: " << expr << " ==> " << simplifyExpression(expr) << std::endl;
//
//    expr = "c-(a+b)";
//    std::cout << "Simplifying the expression: " << expr << " ==> " << simplifyExpression(expr) << std::endl;
//
//    expr = "d-(c-(-a)+(-b))";
//    std::cout << "Simplifying the expression: " << expr << " ==> " << simplifyExpression(expr) << std::endl;
//
//    expr = "-a-((-b)-(d-c+(-e-f+g))-(+h-(-i)))"; //-a-(-b-d+c+e+f-g-h-i) = -a+b+d-c-e-f+g+h+i
//    std::cout << "Simplifying the expression: " << expr << " ==> " << simplifyExpression(expr) << std::endl;
//
//    expr = "((-a-((-b)-(b-a+(-b-b+a))-(+a-(-b)))))"; //-a-((-b)-(b-a+(-b-b+a))-(+a-(-b))) = -a-(-b-b+a+b+b-a-a-b) = -a+b+b-a-b-b+a+a+b=b
//    std::cout << "Simplifying the expression: " << expr << " ==> " << simplifyExpression(expr) << std::endl;
//}
