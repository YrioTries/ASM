#include<iostream>
using namespace std;

void cinner(int& a, int& b) {

    cout << "Enter a: \n" << ">";
    cin >> a;
    cout << endl;

    cout << "Enter b: \n" << ">";
    cin >> b;
    cout << endl;


}

void CPP_formula_culc(int a, int b) {
    cout << "C++ result: ";
    if (a == b)
        cout << -25;
    else if (a > b && b != 1)
        cout << 3 * b / (1 - b) - 2 * a;
    else if (a < b && a != 0)
        cout << (b * b - 5 + a) / a;
    cout << endl;
}

void ASM_formula_culc(int a, int b)
{
    int er = 0;
    int result = 0;

        //     { 3b / (1 - b) - 2a;   if a > b
        // X = < -25;                 if a = b
        //     { (b ^ 2 - 5 + a);     if a < b

    _asm {
        mov eax, a;              <eax> = a
        jo error_of
        mov ebx, b;              <ebx> = b
        jo error_of
        cmp eax, ebx;            сравнение a и b

        jg bigger;               переход если a > b
        jl smaller;              переход если a < b
        mov eax, -25;

        mov result, eax;
        jmp quit;                переход на конец программы

            bigger :
        mov eax, 3;
            imul eax, ebx;       <eax> = 3 * b
            jo error_of;         ошибка переполнения

            mov ebx, 1;
        mov ecx, b;
        jo error_of;
        sub ebx, ecx;
            jo error_of;         ошибка переполнения

            cdq
            jz error_zf
            idiv ebx;

        mov ecx, eax;


        mov ebx, 2
            mov eax, a;
        imul eax, ebx;           <eax> = 2 * a
            jo error_of
                                 ;ошибка переполнения
            sub ecx, eax;        <ecx> = 3 * b - 2 * a
            jo error_of
                                 ;ошибка переполнения
            mov eax, ecx;        <eax> = 3 * b - 2 * a
            mov result, eax;
            jmp quit

            smaller :
                cmp eax, 0;      сравнение a и 0
                jz error_zf
                                 ;ошибка деление на ноль
                mov ecx, b;      <ecx> = b
                imul ecx, ebx;   <ecx> = b ^ 2
                jo error_of
                                 ;ошибка переполнения
                mov ebx, 5
                sub ecx, ebx;    <ecx> = b ^ 2 - 5
                jo error_of
                                ;ошибка переполнения
                mov eax, ecx;    < eax > = b ^ 2 - 5
                cdq; подготовка деления
                mov ecx, a;
            cmp ecx, 0;
            jz error_zf
            idiv ecx;           < eax > = (b ^ 2 - 5) / a
            jo error_of;        ошибка переполнения
 

        jmp quit
            error_of :
        mov er, 1; <er> = 1
          
        jmp quit
            error_zf :
        mov er, -1; <er> = -1

            quit:
        mov result, eax; <result> = <eax>
    }
    
    switch (er) {
    case 0:
        cout << "ASM result: " << result << endl;
        CPP_formula_culc(a, b);
        cout << "==========================================" << endl;
        cout << "No errors" << endl;
        cout << "==========================================" << endl;
        break;
    case 1:
        cout << "==========================================" << endl;
        cout << "Error: Overflow" << endl;
        cout << "==========================================" << endl;
        break;
    case -1:
        cout << "==========================================" << endl;
        cout << "Error: Division by zero" << endl;
        cout << "==========================================" << endl;
        break;
    }

}



int main()
{
    int a, b;

    cinner(a, b);

    ASM_formula_culc(a, b);
    
    return 0;
}
