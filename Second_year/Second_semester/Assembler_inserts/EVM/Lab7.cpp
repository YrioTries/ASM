#include <iostream>
#include <string>
#include <cmath>
using namespace std;


//B-4
//tg(ln(x + pi * x^2))

void cinner(double& a, double& b, double& x) {
	cout << "==========================================" << endl;
	cout << "Enter a: \n" << ">";
	cin >> a;
	cout << endl;

	cout << "Enter b: \n" << ">";
	cin >> b;
	cout << endl;

	cout << "Enter x: \n" << ">";
	cin >> x;
	cout << endl;
}

void CPP_formula_culc(double a, double b, double x) {
	float pi = 3.14159;
	cout << "C++ result: ";
	if (a == b)
		cout << 51;
	else if (a > b && a != 5)
		cout << (5 + a * b) / (b - 5) + 10;
	else if (a < b)
		cout << tan(log(x + pi * x * x));
	cout << endl;
}

void ASM_formula_culc(double a, double b, double x) {
	double k;

	bool overflow = false, div0 = false;
	const double four = 4, five = 5, ten = 10, fiftyOne = 51;
	/*  [ (5 + ab) / (b - 5) + 10   if a > b
	X = {         51                if a = b
		[ tg(ln(x + pi * x^2))      if a < b          */
	__asm {
		finit
		fld b; st(0) = b
		fld a; st(0) = a, st(1) = b
		fcomi st, st(1); сравнение st(0) и st(1)
		ja a_bigger; a > b
		jb a_smaller; a < b
		fld fiftyOne; st(0) = 51, st(1) = a, st(2) = b

		jmp quit
		a_smaller :
		// tan(log(x + pi * x * x))
		finit
			fld1
			fldpi;
		fmul qword ptr[x]; s(0) = pi * x
			fmul qword ptr[x]; s(0) = pi * x ^ 2
			fadd qword ptr[x]; s(0) = x + pi * x ^ 2


			fyl2x; st(0) = log2(x + pi * x ^ 2)
			fldl2e; st(0) = log2(e), s(1) = log2(x + pi * x ^ 2)

			fdiv; st(0) = log2(x + pi * x ^ 2) / log2(e)

			fptan; st(0) = 1, s(1) = tg(ln(x + pi * x ^ 2))
			fmul; вытаскиваем в s(0) = tg(ln(x + pi * x ^ 2))
			fld st

		jmp quit
			a_bigger :
		fmul; st(0) = a * b
			fadd five; st(0) = a * b + 5
			fld b; st(0) = b, st(1) = a * b + 5
			fsub five; st(0) = b - 5, st(1) = a * b + 5
			ftst; сравнение st(0) и 0
			fstsw ax; содержимое swr в регистр ax
			sahf; запись флагов из ah в flags
			jz error_zf; если знаменатель = 0
			fdivp st(1), st; st(0) = (5 + a * b) / (b - 5)
			fadd ten; st(0) = (5 + a * b) / (b - 5) + 10

			jmp quit
			error_of :
		mov overflow, 1; <overflow> = 1 (true)

			jmp quit
			error_zf :
		mov div0, 1; <div0> = 1 (true)

			quit:
		fstp k; записываем в k значение st(0)
	}

	if (div0)
	{
		cout << "==========================================" << endl;
		cout << "Error: Division by zero" << endl;
		cout << "==========================================" << endl;

	}
	else if (overflow) {
		cout << "==========================================" << endl;
		cout << "Error: Overflow" << endl;
		cout << "==========================================" << endl;

	}
	else {
		cout << "==========================================" << endl;
		cout << "No errors" << endl;
		cout << "==========================================" << endl;
		cout << "ASM result: " << k << endl;
		CPP_formula_culc(a, b, x);
	}
}
int main() {
	double a, b, x;
	cinner(a, b, x);
	ASM_formula_culc(a, b, x);
}
