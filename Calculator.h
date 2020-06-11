#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
class Calculator
{
    string parentheses(string input);
    // ფუნქცია, რომელიც ტექსტიდან იღებს ოპერატორებს და ციფრებს
 long double InputFilter(string text);
    //გამოთვლის ფუნქცია
    long double Calculate(string* opz, vector<long double>* nums);
public:
    Calculator(string input); // კონსტრუქტორი, რომელიც იღებს მომხმარებელის შეყვანილ ტექტს
   
};

