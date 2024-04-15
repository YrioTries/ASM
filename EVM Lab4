#include <iostream>;
using namespace std;
// Вариант 19
// Найти произведение квадратов всех отрицательных элементов массива A={a[i]}.

void cinner(int& mas_size) {
	cout << "==========================================" << endl;
	cout << "Input array size" << endl;
	cout << ">";
	cin >> mas_size;
	cout << "==========================================" << endl;
	cout << endl;

}

int main() {
	int mas_size;
	int error = 0;
	int asm_result, cpp_result = 1;

	cinner(mas_size);
	int* mas = new int[mas_size];
	
	int has_negative = 0;
	bool no_negatives = true;

	for (int i = 0; i < mas_size; ++i) {
		cout << "Input element arr[" << i + 1 << "]" << endl;
		cout << ">";
		cin >> mas[i];
		if (mas[i] < 0) {
			no_negatives = false;
		}
		if (mas[i] < 0) {
			cpp_result *= mas[i] * mas[i];
		}
		cout << endl;
	}
	if (no_negatives) {
		cpp_result = 0;
	}
	

	__asm {
		xor esi, esi; подготовим регистр индекса в массиве <esi> = 0
		mov ebx, mas; ebx указывает на начало массива
		mov ecx, mas_size; счётчик цикла по всем элементам массива <ecx> = size(5)
		cmp ecx, 0 // mas_size > 0
		jle zero_size_error
		push 1 // В стеке произведение кубов
		begin_loop:
		mov eax, [ebx + esi * 4] // определяем текущий элемент
			cmp eax, 0 // сравниваем с 0
			jge end_loop // если не отрицательное, то завершаем цикл
			mov has_negative, 1 // флаг для существования отрицательных чисел в массиве
			mov edi, eax // <esp> = mas[i]
			imul edi // mas[i] ^ 2
			jo error_of // ошибка переполнения

			pop edi // произведение кубов достаём со стека
			imul edi // mas[i] ^ 3 * &lt;edi&gt;
			//jo error_of_not_pop // ошибка переполнения
			push eax // ответ на стек
			jo error_of // ошибка переполнения

			// увеличиваем счётчик
			end_loop :
		inc esi; переходим к следующему элементу
			loop begin_loop; повторяем цикл для всех элементов массива
			// После цикла
			pop edi;
			// Проверка на наличие отрицательных
			cmp has_negative, 0
			je set_zero
			jmp set_ok

			error_zf :
			mov error, 1;
				jmp quit;

			error_of :
		mov error, 2
			pop edi;
			jmp quit;

			error_of_not_pop :
			mov error, 2
				jmp quit;

			zero_size_error :
			mov error, 3;
			jmp quit

			set_zero :
			mov asm_result, 0;
			jmp quit;

			set_ok :
			mov asm_result, edi;
		quit :
	}
	switch (error)
	{
	case 1:
		cout << "==========================================" << endl;
		cout << "Error: Division by zero" << endl;
		cout << "==========================================" << endl;
		break;
	case 2:
		cout << "==========================================" << endl;
		cout << "Error: Overflow" << endl;
		cout << "==========================================" << endl;
		break;
	case 3:
		cout << "==========================================" << endl;
		cout << "Zero size array error" << endl;
		cout << "==========================================" << endl;
		break;
	default:
		cout << "==========================================" << endl;
		cout << "No errors" << endl;
		cout << "==========================================" << endl;
		cout << "Result asm: " << asm_result << endl;
		cout << "Result C++: " << cpp_result << endl;
		cout << "==========================================" << endl;
		break;
	}
	delete[] mas;
}
