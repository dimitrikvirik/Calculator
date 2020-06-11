#include "Calculator.h" //კლასის დაკავშირება
int main()
{

   //მისალმება
    cout << "Hello! it is simply Calculator! you just need input math text and it will solve!. for example: 5*(5+5)\n";
    Calculator* cs = new (nothrow) Calculator("5*(5+5)"); // მაგალითი
    cout << "If you want end just input N to exit\n";

    string* input = new (nothrow) string; //შესაყვანი ტექსტი
    while (true) {
        cout << "Input Text: ";
       getline(cin, *input);
        if (*input == "N") {
            break;
        }
        delete cs; //მეხსიერების გასუფთავბა
        cs = new (nothrow) Calculator(*input); // კლასში ტექსტის შეყვანა
    }
    cout << "Thank for use!"; 
    delete cs;
    delete input; 
}
