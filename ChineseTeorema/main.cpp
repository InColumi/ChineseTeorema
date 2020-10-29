#include <iostream>

using namespace std;

/// <summary>
/// Возвращает наибольший общий делитель
/// </summary>
/// <param name="a">первое число</param>
/// <param name="b">второе число</param>
/// <returns></returns>
int GetGCD(int a, int b)
{
	return (b == 0) ? a : GetGCD(b, a % b);
}

/// <summary>
/// Проверка делителей на взаимную простоту
/// </summary>
/// <param name="arr">массив с делителями</param>
/// <param name="size">размер массива</param>
/// <returns></returns>
bool CheackDivisors(int* arr, int size)
{
	for(int i = 0; i < size; i++)
	{
		for(int j = i + 1; j < size; j++)
		{
			if(i != j) // чтобы не сравинмать число с собой же
			{
				if(GetGCD(arr[i], arr[j]) != 1) // если наибольший общий делитель не ноль, тогда вернуть false
				{
					return false;
				}
			}
		}
	}
	return true; // Если все варианты прогнали и условие в цикле ни разу не выполнилось, тогда вернуть true
}

/// <summary>
/// Вводим делители( В видео они назывались m(i))
/// </summary>
/// <param name="size">кол-во делителей</param>
/// <returns>массив делителей</returns>
int* InputDivisors(int size)
{
	int* divisors = new int[size];// Выделяем память под массив делителей
	cout << "Введите делители:\n";
	for(int i = 0; i < size; i++)
	{
		cout << "m[" << i << "] = ";
		cin >> divisors[i]; // Вводим делители
	}
	return divisors; // Возвращаем массив
}

/// <summary>
/// Вводим остатки( В видео они назывались a(i))
/// </summary>
/// <param name="divisors">массив делителей</param>
/// <param name="size">кол-во остатков</param>
/// <returns>массив остатков</returns>
int* InputRemains(int* divisors, int size)
{
	int* remains = new int[size];// Выделяем память под массив остатков
	cout << "Введите остатки:\n";
	for(int i = 0; i < size; i++)
	{
		cout << "a[" << i << "] = ";
		cin >> remains[i];
		if(remains[i] > divisors[i] || remains[i] < 0) // В условии теоремы сказано, чтобы остаток меньше делителя и больше либо равено нуля
		{
			// очистка памяти из под массивов
			delete divisors;
			delete remains;
			// Если условию не выполенится, то выведет сообщения и программа закроется
			cout << "Остаток не может быть отрицательными или больше делителя!\n";
			exit(0);
		}
	}
	return remains; // Вернёт массив остатков
}

/// <summary>
/// Перемножает элементы массива между собой
/// </summary>
/// <param name="arr">массив, который нужно перемножить</param>
/// <param name="size">размер массива</param>
/// <returns>произведение элементво массива</returns>
int GetMullArray(int* arr, int size)
{
	int res = 1;// Переменная для хранениня результата
	for(int i = 0; i < size; i++)
	{
		res *= arr[i]; // Поэлементно перемножем и сохраняем в переменную
	}
	return res; // Возращаем число
}

/// <summary>
/// Возвращем вспомогаетельныйе переменные( В видео они назывались M(i))
/// </summary>
/// <param name="number"></param>
/// <param name="divisors"></param>
/// <param name="size"></param>
/// <returns></returns>
int* GetSupporsNumbers(int number, int* divisors, int size)
{
	int* supportNumbers = new int[size];
	for(int i = 0; i < size; i++)
	{
		supportNumbers[i] = number / divisors[i];
	}
	return supportNumbers;
}

/// <summary>
/// Находим y(i)
/// </summary>
/// <param name="remains">массив с a(i)</param>
/// <param name="divisors">массив с m(i)</param>
/// <param name="M">массив с М(i)</param>
/// <param name="size"></param>
/// <returns>массив y</returns>
int* GetY(int* remains, int* divisors, int* M, int size)
{
	int* y = new int[size]; // Выделяем память под массив "y"

	int value; // временное значения, для промежуточных вычислений
	int gcd; // наибольший общий делитеть
	int tempM; // временная переменная для M(i)
	int tempRemains; // временная переменная для остата (a(i))
	int tempY = 1; // переменная предпологаемого "y(i)" 
	for(int i = 0; i < size; i++)
	{
		tempM = M[i]; // Записываем во временную переменную значение M(i)
		tempRemains = remains[i];// Записываем во временную переменную значение a(i)
		if(tempRemains == 1) // если остаток равен 1, то смело можно делить M(i) по модулю делителя (m(i))
		{
			value = tempM % divisors[i];
		}
		else// Иначе будем сокращать
		{
			gcd = GetGCD(M[i], tempRemains); // находим наибольший делитель чисел, которые хотим сократить.
			if(gcd != 1) // Если НОД не 1
			{
				value = tempM / gcd; // тогда сокращем временную переменную с M(i)
				tempRemains /= gcd; // и сокращаем временную переменную с остатком (a(i))
			}
			else// иначе смело делим по модулю делителя
			{
				value = tempM % divisors[i];
			}
		}

		while((value * tempY) % divisors[i] != tempRemains) // увеличивам tempY до тех пор, пока не найдет подходящее значение
		{
			++tempY;
		}
		y[i] = tempY; // записываем найденный "y" в массив
		tempY = 1; // присваиваем значение по умолчанию
	}
	return y;
}

/// <summary>
/// Получние искомого числа
/// </summary>
/// <param name="mainNumber">число M0</param>
/// <param name="y">найденные y(i)</param>
/// <param name="M">найденные M(i)</param>
/// <param name="size">кол-во чисел</param>
/// <returns>Возвращаем M0</returns>
int GetResult(int mainNumber, int* y, int* M, int size)
{
	int res = 0; //переменная для сохранения результата
	for(int i = 0; i < size; i++)
	{
		res += M[i] * y[i]; // как в видео, просто собираем сумму 
	}
	return res % mainNumber; // возвращаем число по модулю M0
}

/// <summary>
/// Выводим красиво массив
/// </summary>
/// <param name="arr">массив</param>
/// <param name="size">размер массива</param>
void ShowArray(int* arr, int size)
{
	cout << '{';
	for(int i = 0; i < size - 1; i++)
	{
		cout << arr[i] << ", ";
	}
	cout << arr[size - 1] << "}\n";
}

int main()
{
	setlocale(LC_ALL, "rus");
	int size;
	cout << "Введите кол-во ограничений: ";
	cin >> size;

	int* divisors = InputDivisors(size); // получаем делители m(i)

	if(CheackDivisors(divisors, size) == false) // если делители не взаимно простые, то выведет сообщение и закроет программу
	{
		delete divisors;
		cout << "Делители должны быть взаимно простыми!\n";
		exit(0);
	}

	int* remains = InputRemains(divisors, size); // получаем остатки а(i)

	int mainNumber = GetMullArray(divisors, size);// получаем М0

	int* M = GetSupporsNumbers(mainNumber, divisors, size); // получаем M(i)

	int* y = GetY(remains, divisors, M, size);// получаем y(i)

	int result = GetResult(mainNumber, y, M, size);// получаем искомое число

	cout << "Искомое число:" << result << '\n';

	//очистка памяти из под массивов
	delete divisors;
	delete remains;
	delete M;
	delete y;

	return 0;
}