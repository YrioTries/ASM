#include <iostream>
using namespace std;

void ASM_formula_culc(int a, int b, int c)
{
	bool er_of = false;
	bool er_zf = false;
	int result = 0;

	cout << "ASM: "; 

	_asm {
		;(c ^ 2 - b * 17) / (c - 4a - 1)

		mov eax, a;           <eax> = a
		jo error_of
		mov ebx, 4;           <ebx> = 4
		imul ebx;             <eax> = a * 4
		jo error_of

		mov ecx, c;           <ecx> = c
		jo error_of
		sub ecx, eax;         <ecx> = c - 4 * a
		jo error_of
		mov eax, ecx;         записываем результат в eax

		mov ebx, 1;           <ebx> = 1
		sub eax, ebx;         <eax> = (c - 4a - 1)
		jo error_of
		push eax;             <eax> = (c - 4a - 1) в стек

		mov eax, c;           <eax> = c сохраняем результат
		jo error_of
		mov ebx, c;           <ebx> = c
		imul ebx;             <eax> = c ^ 2
		jo error_of
		mov ecx, eax;         записываем результат в ecx

		mov eax, b;           <eax> = b
		jo error_of
		mov ebx, 17;          <ebx> = 17
		imul ebx;             <eax> = b * 17
		jo error_of

		sub ecx, eax;         <ecx> = c ^ 2 - b * 17
		jo error_of
		mov eax, ecx;         <eax> = (c ^ 2 - b * 17)

		pop ebx;              берём значение (c - 4a - 1) из стека

		cdq
		jz error_zf
		idiv ebx;             <eax> = (c * c - b * 17) / (c - 4 * a - 1) производим деление

		jmp quit
		    error_of :
		mov er_of, 1; <er_of> = 1
			
		jmp quit
			error_zf :
		mov er_zf, 1; <er_zf> = 1 

			quit:
		mov result, eax; <result> = <eax>
	}

	if (er_of) cout << "Int overflow\n";
	else if (er_zf) cout << "Division by zero\n";
	else cout << "Result: " << result << endl;
}

void CPP_formula_culc(int a, int b, int c) {
	cout << "C++: ";
	if (a == 0 || b == 0 || c == 0 || c - 4 * a - 1 == 0) {
		cout << "Division by zero\n";
	}if (true) {
		cout << "Int overflow\n";
	}else {
		cout << "Result: " << (c * c - b * 17) / (c - 4 * a - 1) << endl;
	}
}

void cinner(int& a, int& b, int& c) {
	cout << "Enter a: \n" << ">";
	cin >> a;
	cout << endl;

	cout << "Enter b: \n" << ">";
	cin >> b;
	cout << endl;

	cout << "Enter c: \n" << ">";
	cin >> c;
	cout << endl;
}

int main()
{
	int a, b, c;

	cinner(a, b, c);

	ASM_formula_culc(a, b, c);
	CPP_formula_culc(a, b, c);

	return 0;
}
