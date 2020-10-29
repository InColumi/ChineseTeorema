#include <iostream>

using namespace std;

int GetGCD(int a, int b)
{
	return (b == 0) ? a : GetGCD(b, a % b);
}

bool CheackDivisors(int*  arr, int size)
{
	for(int i = 0; i < size; i++)
	{
		for(int j = i + 1; j < size; j++)
		{
			if(i != j)
			{
				if(GetGCD(arr[i], arr[j]) != 1)
				{
					return false;
				}
			}
		}
	}
	return true;
}

int* InputDivisors(int size)
{
	int* divisors = new int[size];
	cout << "¬ведите делители:\n";
	for(int i = 0; i < size; i++)
	{
		cout << "m[" << i << "] = ";
		cin >> divisors[i];
	}
	return divisors;
}

int* InputRemains(int*  divisors, int size)
{
	int* remains = new int[size];
	cout << "¬ведите остатки:\n";
	for(int i = 0; i < size; i++)
	{
		cout << "a[" << i << "] = ";
		cin >> remains[i];
		if(remains[i] > divisors[i])
		{
			cout << "ќстаток не может быть больше делител€!\n";
			exit(0);
		}
	}
	return remains;
}

int GetMullArray(int*  arr, int size)
{
	int res = 1;
	for(int i = 0; i < size; i++)
	{
		res *= arr[i];
	}
	return res;
}

int* GetSupporsNumbers(int number, int* divisors, int size)
{
	int* supportNumbers = new int[size];
	for(int i = 0; i < size; i++)
	{
		supportNumbers[i] = number / divisors[i];
	}
	return supportNumbers;
}

int* GetY(int* remains, int* divisors, int* M, int size)
{
	int* y = new int[size];

	int value;
	int gcd;
	int tempM;
	int tempRemains;
	int tempY = 1;
	for(int i = 0; i < size; i++)
	{
		tempM = M[i];
		tempRemains = remains[i];
		if(tempRemains == 1)
		{
			value = tempM % divisors[i];
		}
		else
		{
			gcd = GetGCD(M[i], tempRemains);
			if(gcd != 1)
			{
				value = tempM / gcd;
				tempRemains /= gcd;
			}
			else
			{
				value = tempM % divisors[i];
			}
		}

		while((value * tempY) % divisors[i] != tempRemains)
		{
			++tempY;
		}
		y[i] = tempY;
		tempY = 1;
	}
	return y;
}

int GetResult(int mainNumber, int* y, int* M, int size)
{
	int res = 0;
	for(int i = 0; i < size; i++)
	{
		res += M[i] * y[i];
	}
	return res % mainNumber;
}

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
	cout << "¬ведите кол-во ограничений: ";
	cin >> size;

	int* divisors = InputDivisors(size);
		
	if(CheackDivisors(divisors, size) == false)
	{
		cout << "ƒелители должны быть взаимно простыми!\n";
		exit(0);
	}	

	int* remains = InputRemains(divisors, size);
	
	int mainNumber = GetMullArray(divisors, size);

	int* M = GetSupporsNumbers(mainNumber, divisors, size);

	int* y = GetY(remains, divisors, M, size);

	int result = GetResult(mainNumber, y, M, size);

	cout << "»скомое число:" << result << '\n';
	return 0;
}