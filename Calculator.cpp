#include "Calculator.h"
#include <algorithm>

Calculator::Calculator(string input){
    input.erase(std::remove_if(input.begin(), input.end(), std::isspace), input.end()); // Space Remove.
cout << "Result is: " <<  parentheses(input) << endl; //ფუნქციის გამოძახება
}


string Calculator::parentheses(string input) {
    short* x = new(nothrow) short;  // შესამოწმებელი აღმნიჩვნელი
    short* y = new (nothrow) short; 
    short* n = new (nothrow) short(0); //ფრჩხილებები რაოდენობა
    bool* opened = new(nothrow) bool(false);  // თუ ფრჩხილები ღიაა
    bool* openedonce = new(nothrow) bool(false); //თუ ფრჩხილები ერთხელ მაინც ღია იყო
    for (int i = 0; i <= input.size(); i++) {
        
        if (input[i] == '(') {
            if (!*opened) {
                *x = i;
                *opened = true;
                *openedonce = true;
            }
            *n += 1; 
        }
        if (input[i] == ')') {
            *n -= 1;
        }
        //თუ ფრჩხილებების რაოდენობა გახდა 0-ზე ნაკლები
        if (*n < 0) {
            return "Error Input!";
        }
        if (*n == 0 && *opened) {
            //რეკურსიის გამოძახება ახლიდან
            *y = i;
            break;
        }
    }
    //თუ ფრჩხილებების რაოდენობა არაა 0, ანუ, არაა ყველა ფრჩხილი დაკეტილი
    if (*n > 0) {
      return "Error Input!";
    }
    //თუ ფრჩხილები არ არის
    delete n;
    delete opened;
    if (!*openedonce) { //თუ ფრჩხილები არ იყო
        return  to_string(InputFilter(input));; //გაფილტვრის ფუნქციის გამოძახება
    }
    else {
        delete openedonce;
        return parentheses(input.replace(*x, *y - *x + 1, parentheses(input.substr(*x + 1, *y - *x - 1)))); //რეკურსია, რომლითაც ფრჩხილების ნაწილ-ნაწილ იხსნება.
        delete x; 
        delete y;
    }

}
long double Calculator::InputFilter(string text) {
    string* ops = new (nothrow) string; //ნიშნების სია
   string* digits = new (nothrow) string; //ციფრების სია
    vector<long double>* numbers = new(nothrow) vector <long double>; //რიცხვების სია
    int* n = new int(0); //შესამოწმებლად
    bool* isNegative = new(nothrow) bool(false);


    for (int i = 0; i < text.size(); i++) { //გადაირბენს ტექსტის თითო ასოს
#define smb text[i] //აღნიშვნა input[i] smb-თი   
#define smb2 text[i-1]
        if ((smb >= '0' && smb <= '9') || smb == '.') { // თუ ციფრია და თუ წერტილი მაშინ ამოწმებს თუ მის წინ არის ციფრი
            digits->push_back(smb); // ციფრების სიაში ამატებს სიმბოლოს
       
            *n = i; // იმახსოვრებს i-ს მნიშვნელობას
        }
        else if (smb == '+' || smb == '-' || smb == '/' || smb == '*' || smb == '%' || smb == '^' || smb == '|') { // თუ ოპერატორია
            if (i == 0) {
                numbers->push_back(0);
                 }
         
                if ((text[i + 1] >= '0' && text[i + 1] <= '9') && text[i] == '-'  && i != 0 && (smb2 == '+' || smb2 == '-' || smb2 == '/' || smb2 == '*' || smb2 == '%' || smb2 == '^' || smb2 == '|')){
                     *isNegative = true;
                    
                    *n = i;

                }
                else {

                    ops->push_back(smb); // ოპერატორების სიაში ამატებს სიმბოლოს  
                }
            
        }
        else if (smb == '(' || smb == ')') {}
        else {// თუ არასწორად იყო შეყვანილი
            cout << "Incorrect Input!\n Please Try Again!\n";
            return 0;
        }
        if (i != *n ) { //თუ არ ემთხვევა, ანუ ციფრები შორის არის გამოტოვება ან პირველი უარყოფითია
            if (*isNegative) {

                numbers->push_back(-1*stold(*digits)); // გადაჰყავს ტექსტი long double-ში და აგდებს რიცხვების სიაში
                *isNegative = false;
            }
            else {
                // გადაჰყავს ტექსტი long double-ში და აგდებს რიცხვების სიაში
                    numbers->push_back(stold(*digits));
            }
            digits->clear();



        }
    }
    //ბოლო რიცხვის დამატება
    if (*isNegative) {
        numbers->push_back(-1*stold(*digits)); // გადაჰყავს ტექსტი long double-ში და აგდებს რიცხვების სიაში
    }
    else {
        numbers->push_back(stold(*digits)); // გადაჰყავს ტექსტი long double-ში და აგდებს რიცხვების სიაში
    }
    digits->clear();
    delete digits;
    delete isNegative;
    delete n;
    text.clear();

    return (Calculate(ops, numbers)); //გამოთვლის ფუნქციის გამოძახება
}
//გამოთვლის ფუნქცია
long double Calculator::Calculate(string* opz, vector<long double>* nums) {
    long double *res =  new (nothrow) long double(0); // რეზულტატი
    for (int i = 0; i < opz->size(); i++) {
#define first (*nums)[i] //აღვნიშნოთ პირველი ელემენტი
#define second (*nums)[i+1] //აღვნიშნოთ მეორე ლემენტი
        switch ((*opz)[i]) {
        case '+': break;
        case '-': second *= -1; break; //გამოკლებისა მეორეს ხდება უარყოფითი(გამოკლების ილუზია)
        case '*': second *= first; first = 0; break; //გამრავლება
        case '/': second = first / second; first = 0; break; //გაყოფვა
        case '%': second *= first / 100; first = 0; break; //პროცენტის გამოთვლა. 
        case '^': second = pow(first, second); first = 0; break; //ხარისხში აყვანა 
        case '|': second = pow(second, 1 / first); first = 0; break; //ფეცვის გამოყვანა ხარისხში
        default: cout << "ERROR!"; break; break;
        }
    }
    //დათვლა
    for (int i = 0; i < nums->size(); i++) {
        *res += (*nums)[i];
    }

    //გასუფთავება
    delete opz;
    delete nums;
    return *res;

    

}

