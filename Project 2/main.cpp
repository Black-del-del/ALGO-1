// University of Arkansas at Little Rock
// Department of Computer Science
// CPSI 28003: Algorithms
// Fall 2026
// Project 2: Infix to Postfix Conversion
// Name: Lawson Black
// ID-number (Last 4 Digits): 9680
// Description:
// This program converts an arithmetic expression in infix notation
// to postfix notation using a stack. Each operator and operand is
// separated by spaces for correct processing.
// Date Written:4/20/2026
// Date Revised: 4/20/2026

#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

// Function prototypes
string InfixToPostfix(char* str);
int precedence(char op);
bool isOperator(char c);

// Determine operator precedence
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;

    if (op == '*' || op == '/')
        return 2;

    return 0;
}

// Check if character is an operator
bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Convert infix expression to postfix
string InfixToPostfix(char* str)
{
    stack<char> s;
    string postfix = "";

    int i = 0;

    while (str[i] != '\0')
    {
        char token = str[i];

        // Ignore spaces
        if (token == ' ')
        {
            i++;
            continue;
        }

        // If operand (single digit)
        if (isdigit(token))
        {
            postfix += token;
            postfix += ' ';
        }

        // If left parenthesis
        else if (token == '(')
        {
            s.push(token);
        }

        // If right parenthesis
        else if (token == ')')
        {
            while (!s.empty() && s.top() != '(')
            {
                postfix += s.top();
                postfix += ' ';
                s.pop();
            }

            if (!s.empty())
                s.pop(); // remove '('
        }

        // If operator
        else if (isOperator(token))
        {
            while (!s.empty() &&
                   precedence(s.top()) >= precedence(token))
            {
                postfix += s.top();
                postfix += ' ';
                s.pop();
            }

            s.push(token);
        }

        i++;
    }

    // Pop remaining operators
    while (!s.empty())
    {
        postfix += s.top();
        postfix += ' ';
        s.pop();
    }

    return postfix;
}

// Provided function: adds spaces between characters
char* AddDelimetersToStr(char* str)
{
    int spacesNeeded = 0;
    int length = 0;

    while (str[length] != '\0')
    {
        if (str[length] != ' ')
            spacesNeeded = spacesNeeded + 1;

        length = length + 1;
    }

    int size = length + spacesNeeded + 1;
    char* adjustedStr = new char[size];

    int newInx = 0;

    for (int inx = 0; inx < length; inx++)
    {
        if (str[inx] != ' ')
        {
            adjustedStr[newInx] = str[inx];
            newInx = newInx + 1;

            adjustedStr[newInx] = ' ';
            newInx = newInx + 1;
        }
    }

    adjustedStr[newInx] = '\0';

    return adjustedStr;
}

// Main program
int main()
{
    char* str = new char[80];

    while (1) // runs until Ctrl+C
    {
        cout << "Enter an arithmetic equation..." << endl;

        cin.getline(str, 80);

        str = AddDelimetersToStr(str);

        cout << InfixToPostfix(str) << endl;
    }

    return 0;
}