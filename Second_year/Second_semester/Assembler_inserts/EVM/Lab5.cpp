#include <iostream>

using namespace std;

void calculate_asm(double a, double b, double c) {
	const double two = 2, four = 4, seven = 7;
	bool dzero_error = false;
	double result = 0;

	_asm {
		/*(4 * a + b - 7) * (2 * c / b - c / a)*/
		finit
		fld qword ptr[c]; st0 = c
		fld qword ptr[b]; st0 = b, st1 = c
		ftst
		fstsw ax
		sahf
		jz divison_by_zero
		fdivp st(1), st; st0 = c / b
		fmul qword ptr[two]; st0 = 2 * c / b

		fld qword ptr[c]; st0 = c, st1 = 2 * c / b
		fld qword ptr[a]; st0 = a, st1 = c, st2 = 2 * c / b
		ftst
		fstsw ax
		sahf
		jz divison_by_zero
		fdivp st(1), st; st0 = c / a, st1 = 2 * c / b
		fsubp st(1), st; st0 = (2 * c / b - c / a)
		ftst
		fstsw ax
		sahf
		jz divison_by_zero

			fld qword ptr[a]; st0 = a, st1 = (2 * c / b - c / a);
			fmul qword ptr[four]; st0 = 4 * a, st1 = (2 * c / b - c / a);
			fadd qword ptr[b]; st0 = (4 * a + b), st1 = (2 * c / b - c / a);
			fsub qword ptr[seven]; st0 = (4 * a + b - 7), st1 = (2 * c / b - c / a);

		fxch st(1); st(0) = (2 * c / b - c / a), st(1) = (4 * a + b - 7)
		fmulp st(1), st; st0 = (4 * a + b - 7) * (2 * c / b + c / a)

		jmp endc

		divison_by_zero :
		mov dzero_error, 1

			endc :
			fstp result
	}

	cout << "ASM: ";
	if (dzero_error) cout << "Division by zero error.\n";
	else cout << "Result: " << result << endl;
}

void calculate_cpp(double a, double b, double c) {
	cout << "C++: ";
	if (2 * c / b - c / a) cout << "Result: " << (4 * a + b - 7) * (2 * c / b - c / a) << endl;
	else cout << "Division by zero error.\n";
}

int main()
{
	double a, b, c;
	cout << "=========================================== " << endl;
	cout << "Input A >> ";
	cin >> a;
	cout << "Input B >> ";
	cin >> b;
	cout << "Input C >> ";
	cin >> c;
	cout << "=========================================== " << endl;
	calculate_asm(a, b, c);
	calculate_cpp(a, b, c);
	cout << "=========================================== " << endl;

	return 0;
}
