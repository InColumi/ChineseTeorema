#include <iostream>

using namespace std;

/// <summary>
/// ���������� ���������� ����� ��������
/// </summary>
/// <param name="a">������ �����</param>
/// <param name="b">������ �����</param>
/// <returns></returns>
int GetGCD(int a, int b)
{
	return (b == 0) ? a : GetGCD(b, a % b);
}

/// <summary>
/// �������� ��������� �� �������� ��������
/// </summary>
/// <param name="arr">������ � ����������</param>
/// <param name="size">������ �������</param>
/// <returns></returns>
bool CheackDivisors(int* arr, int size)
{
	for(int i = 0; i < size; i++)
	{
		for(int j = i + 1; j < size; j++)
		{
			if(i != j) // ����� �� ���������� ����� � ����� ��
			{
				if(GetGCD(arr[i], arr[j]) != 1) // ���� ���������� ����� �������� �� ����, ����� ������� false
				{
					return false;
				}
			}
		}
	}
	return true; // ���� ��� �������� �������� � ������� � ����� �� ���� �� �����������, ����� ������� true
}

/// <summary>
/// ������ ��������( � ����� ��� ���������� m(i))
/// </summary>
/// <param name="size">���-�� ���������</param>
/// <returns>������ ���������</returns>
int* InputDivisors(int size)
{
	int* divisors = new int[size];// �������� ������ ��� ������ ���������
	cout << "������� ��������:\n";
	for(int i = 0; i < size; i++)
	{
		cout << "m[" << i << "] = ";
		cin >> divisors[i]; // ������ ��������
	}
	return divisors; // ���������� ������
}

/// <summary>
/// ������ �������( � ����� ��� ���������� a(i))
/// </summary>
/// <param name="divisors">������ ���������</param>
/// <param name="size">���-�� ��������</param>
/// <returns>������ ��������</returns>
int* InputRemains(int* divisors, int size)
{
	int* remains = new int[size];// �������� ������ ��� ������ ��������
	cout << "������� �������:\n";
	for(int i = 0; i < size; i++)
	{
		cout << "a[" << i << "] = ";
		cin >> remains[i];
		if(remains[i] > divisors[i] || remains[i] < 0) // � ������� ������� �������, ����� ������� ������ �������� � ������ ���� ������ ����
		{
			// ������� ������ �� ��� ��������
			delete divisors;
			delete remains;
			// ���� ������� �� �����������, �� ������� ��������� � ��������� ���������
			cout << "������� �� ����� ���� �������������� ��� ������ ��������!\n";
			exit(0);
		}
	}
	return remains; // ����� ������ ��������
}

/// <summary>
/// ����������� �������� ������� ����� �����
/// </summary>
/// <param name="arr">������, ������� ����� �����������</param>
/// <param name="size">������ �������</param>
/// <returns>������������ ��������� �������</returns>
int GetMullArray(int* arr, int size)
{
	int res = 1;// ���������� ��� ��������� ����������
	for(int i = 0; i < size; i++)
	{
		res *= arr[i]; // ����������� ���������� � ��������� � ����������
	}
	return res; // ��������� �����
}

/// <summary>
/// ��������� ����������������� ����������( � ����� ��� ���������� M(i))
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
/// ������� y(i)
/// </summary>
/// <param name="remains">������ � a(i)</param>
/// <param name="divisors">������ � m(i)</param>
/// <param name="M">������ � �(i)</param>
/// <param name="size"></param>
/// <returns>������ y</returns>
int* GetY(int* remains, int* divisors, int* M, int size)
{
	int* y = new int[size]; // �������� ������ ��� ������ "y"

	int value; // ��������� ��������, ��� ������������� ����������
	int gcd; // ���������� ����� ��������
	int tempM; // ��������� ���������� ��� M(i)
	int tempRemains; // ��������� ���������� ��� ������ (a(i))
	int tempY = 1; // ���������� ��������������� "y(i)" 
	for(int i = 0; i < size; i++)
	{
		tempM = M[i]; // ���������� �� ��������� ���������� �������� M(i)
		tempRemains = remains[i];// ���������� �� ��������� ���������� �������� a(i)
		if(tempRemains == 1) // ���� ������� ����� 1, �� ����� ����� ������ M(i) �� ������ �������� (m(i))
		{
			value = tempM % divisors[i];
		}
		else// ����� ����� ���������
		{
			gcd = GetGCD(M[i], tempRemains); // ������� ���������� �������� �����, ������� ����� ���������.
			if(gcd != 1) // ���� ��� �� 1
			{
				value = tempM / gcd; // ����� �������� ��������� ���������� � M(i)
				tempRemains /= gcd; // � ��������� ��������� ���������� � �������� (a(i))
			}
			else// ����� ����� ����� �� ������ ��������
			{
				value = tempM % divisors[i];
			}
		}

		while((value * tempY) % divisors[i] != tempRemains) // ���������� tempY �� ��� ���, ���� �� ������ ���������� ��������
		{
			++tempY;
		}
		y[i] = tempY; // ���������� ��������� "y" � ������
		tempY = 1; // ����������� �������� �� ���������
	}
	return y;
}

/// <summary>
/// �������� �������� �����
/// </summary>
/// <param name="mainNumber">����� M0</param>
/// <param name="y">��������� y(i)</param>
/// <param name="M">��������� M(i)</param>
/// <param name="size">���-�� �����</param>
/// <returns>���������� M0</returns>
int GetResult(int mainNumber, int* y, int* M, int size)
{
	int res = 0; //���������� ��� ���������� ����������
	for(int i = 0; i < size; i++)
	{
		res += M[i] * y[i]; // ��� � �����, ������ �������� ����� 
	}
	return res % mainNumber; // ���������� ����� �� ������ M0
}

/// <summary>
/// ������� ������� ������
/// </summary>
/// <param name="arr">������</param>
/// <param name="size">������ �������</param>
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
	cout << "������� ���-�� �����������: ";
	cin >> size;

	int* divisors = InputDivisors(size); // �������� �������� m(i)

	if(CheackDivisors(divisors, size) == false) // ���� �������� �� ������� �������, �� ������� ��������� � ������� ���������
	{
		delete divisors;
		cout << "�������� ������ ���� ������� ��������!\n";
		exit(0);
	}

	int* remains = InputRemains(divisors, size); // �������� ������� �(i)

	int mainNumber = GetMullArray(divisors, size);// �������� �0

	int* M = GetSupporsNumbers(mainNumber, divisors, size); // �������� M(i)

	int* y = GetY(remains, divisors, M, size);// �������� y(i)

	int result = GetResult(mainNumber, y, M, size);// �������� ������� �����

	cout << "������� �����:" << result << '\n';

	//������� ������ �� ��� ��������
	delete divisors;
	delete remains;
	delete M;
	delete y;

	return 0;
}