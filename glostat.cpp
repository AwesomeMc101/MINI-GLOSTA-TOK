/*

Written by AwesomeMc101 for Lunar Guard Technologies

- This is kinda a joke, I had fun writing it but it doesn't function well. Could be cool if somebody actually make this into a working language (i'm working on smth similar.)

- 5.17.2022

*/

#include <iostream>
#include <Windows.h>

#include <string>
#include <string.h>
#include <sstream>
#include <streambuf>
#include <vector>
#include <algorithm>

namespace optional
{
    BOOL argCheck(std::string code)
    {
        if (code.find("(") == std::string::npos)
        {
            return FALSE;
        }
        return TRUE;
    }
}

namespace Functions
{
    std::vector<std::string> functionList = {"print","strlen"};

    void setFunctions(std::vector<std::string>& tokens)
    {
        for (int y = 0; y < functionList.size(); y++)
        {
            for (int i = 0; i < tokens.size(); i++)
            {
                if (tokens[i] == functionList[y])
                {
                    tokens[i] = tokens[i] + "(";
                }
            }
        }
    }

    void print(std::string x)
    {
        std::cout << "\nPRINTING: " << x << std::endl;
    }

    ///////////////////////////////

    int strlen(std::string str)
    {
        return str.length();
    }

  

    //tokens, i
    void runFunction(std::vector<std::string> tokens, int tokenCaller, std::vector<std::string> &stack);
    void runFunction(std::vector<std::string> tokens, int tokenCaller, std::vector<std::string> &stack)
    {
        //in the real GLOSTA this will work off of arguments but since we
        //only have a few functions it's fine to do this
        std::cout << "Token: " << tokens[tokenCaller] << std::endl;
        tokens[tokenCaller].erase(std::remove(tokens[tokenCaller].begin(), tokens[tokenCaller].end(), '('), tokens[tokenCaller].end());
        tokens[tokenCaller].erase(std::remove(tokens[tokenCaller].begin(), tokens[tokenCaller].end(), ')'), tokens[tokenCaller].end());
        if (tokens[tokenCaller] == "print")
        {
            std::string arg = tokens[tokenCaller + 1];
            if (!optional::argCheck(arg))
            {          
                std::string toPrint = "";
                for (int z = 0; z < tokens.size(); z++)
                {
                    if (z <= tokenCaller) { continue; }
                    toPrint += tokens[z];
                }
                print(toPrint);
            }
           
            printf("g");
            std::vector<std::string> newtok = tokens;

            newtok.erase(newtok.begin(), newtok.begin()+(tokenCaller+1));

            runFunction(newtok, tokenCaller, stack);

            std::string toPrint = "";
            for (int z = 0; z < stack.size(); z++)
            {
                std::cout << "Stack element: " << stack[z] << std::endl;
                toPrint += stack[z];
            }

            print(toPrint);

            //the arg is/has a function

        }
        else if (tokens[tokenCaller] == "strlen")
        {
            std::string arg = tokens[tokenCaller + 1];
            if (!optional::argCheck(arg))
            {
                tokens[tokenCaller].erase(std::remove(tokens[tokenCaller].begin(), tokens[tokenCaller].end(), ')'), tokens[tokenCaller].end());
                stack.push_back(std::to_string(strlen(arg)));
            }
        }
    }
}

int main()
{
    /*try something simple like
    
    print(strlen(This is a string!))
    |
    V

    Should print the number of characters.

    */
    while (1)
    {
        std::string code;
        std::getline(std::cin, code);

        if (!optional::argCheck(code)) { continue; }

        std::vector<std::string> tokens;
        std::stringstream strs(code);
        std::string tempFunction;

        while (std::getline(strs, tempFunction, '('))
        {
            std::cout << "Token A: " << tempFunction << std::endl;
            tokens.push_back(tempFunction);
        }

        Functions::setFunctions(tokens);
        for (std::string z : tokens)
        {
            std::cout << "Token B: " << z << std::endl;
        }

        std::vector<std::string> argStack;

       
        Functions::runFunction(tokens, 0, argStack);
        

    }
}
