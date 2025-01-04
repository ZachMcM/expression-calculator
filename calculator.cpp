#include "stack.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <regex>
#include <vector>
#include <sstream>
#include <regex>
using namespace std;

int getPrecedence(string val) {
  if (val == "^") {
    return 3;
  } else if (val == "*" || val == "/") {
    return 2;
  }
  return 1;
}

bool isNumber(const std::string& str) {
  std::regex number_regex("^[+-]?([0-9]*[.])?[0-9]+$");
    
  return std::regex_match(str, number_regex);
}

double calculateExpr(string oper, double c1, double c2) {
  if (oper == "+") {
    return c1 + c2;
  } else if (oper == "-") {
    return c1 - c2; 
  } else if (oper == "^") {
    return pow(c1, c2);
  } else if (oper == "*") {
    return c1 * c2;
  } 
  return c1 / c2;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    throw runtime_error("Please enter an valid expression with surrounding quotes");
  }
  
  string init = argv[1];
  string exprStr;

  for (char c : init) {
    if (c == '(') {
      exprStr += c;
      exprStr += ' ';
    } else if (c == ')') {
      exprStr += ' ';
      exprStr += c;
    } else if (c == '^') {
      exprStr += ' ';
      exprStr += c;
      exprStr += ' ';
    } else {
      exprStr += c;
    }
  }

  string token;

  vector<string> infixArr;
  istringstream infixStream(exprStr);

  while (getline(infixStream, token, ' ')) {
    infixArr.push_back(token);
  }

  Stack<string> postfixStack;
  string postfix = "";

  for (string s : infixArr) {
    if (isNumber(s)) {
      postfix += s + " ";
    } else if ("(" == s) {
      postfixStack.push(s);
    } else if (")" == s) {
      while (postfixStack.peek() != "(") {
        postfix += postfixStack.pop() + " ";
      }
      postfixStack.pop();
    } else { // operator case
      if (postfixStack.isEmpty() || postfixStack.peek() == "(" || getPrecedence(s) > getPrecedence(postfixStack.peek())) {
        postfixStack.push(s);
      } else {
        while (!postfixStack.isEmpty() && 
              postfixStack.peek() != "(" && 
              getPrecedence(postfixStack.peek()) >= getPrecedence(s)) {
            postfix += postfixStack.pop() + " ";
        }
        postfixStack.push(s);
      }
    }
  }

  while (!postfixStack.isEmpty()) {
    postfix += postfixStack.pop() + " ";
  }

  postfix.erase(postfix.find_last_not_of(" \n\r\t")+1);

  vector<string> postfixArr;
  istringstream postfixStream(postfix);

  while (getline(postfixStream, token, ' ')) {
    postfixArr.push_back(token);
  }

  Stack<double> exprStack;

  for (string s : postfixArr) {
    if (isNumber(s)) {
      double value = stod(s);
      exprStack.push(value);
    } else {
      double c2 = exprStack.pop();
      double c1 = exprStack.pop();

      exprStack.push(calculateExpr(s, c1, c2));
    }
  }

  cout << exprStack.pop() << endl;
}