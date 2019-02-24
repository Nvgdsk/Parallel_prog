// Lab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <thread>
#include <vector>
#include <future>
using namespace std;
int print_array(int **my_array, int column, int from = 0, int to = 0);
vector <future<int>> streams;
int main()
{
	srand(time(0)); // генерация случайных чисел
					// динамическое создание двумерного массива вещественных чисел на десять элементов
	int row, column;
	int middle,count_thread;
	//////////////////////////////////////////////////////////////

	cout << "Enter count row: ";
	cin >> row;
	cout << "Enter count column: ";
	cin >> column;	
	cout << "Count threads: ";
	cin >> count_thread;
	middle = row / count_thread;

	//////////////////////////////////////////////////////////////

	int  **ptrarray = new int*[row];

	for (int count_row = 0; count_row < row; count_row++)
	{
		ptrarray[count_row] = new int[column];
		for (int count_column = 0; count_column < column; count_column++)
		{
			ptrarray[count_row][count_column] = 1;
		}
	}


	//////////////////////////////////////////////////////////////
	unsigned int start_time;
	unsigned int end_time;
	unsigned int search_time;

	start_time = clock();
	int start = 0;
	for (int i = 0; i < count_thread; i++)
	{
		streams.push_back(async(print_array, ptrarray, column, start, middle));
		start = middle;
		middle = i== count_thread-2 ? middle = row: middle +=middle;
		

	}
	
	
	int final_sum = 0;
	for (int i = 0; i < streams.size(); i++)
	{
		final_sum += streams[i].get();
	}
	end_time = clock();
	search_time = end_time - start_time;

	cout << "Final sum : " << final_sum << endl;
	cout << "Working multi thread time: " << search_time / 1000.0 << endl;

	//////////////////////////////////////////////////////////////

	start_time = clock();
	int sum11 = print_array(ptrarray, column, 0, row);
	end_time = clock();
	search_time = end_time - start_time;
	cout << "Final sum : " << sum11<< endl;
	cout << "Working singl thread time: " << search_time / 1000.0 << endl;

	//////////////////////////////////////////////////////////////
	for (int count = 0; count < row; count++)
		delete[]ptrarray[count];
	system("pause");
	return 0;

}

int print_array(int **my_array, int column, int from, int to)
{

	int sum = 0;
	for (int i = from; i < to; i++) {
		for (int j = 0; j < column; j++) {
			//cout << setw(4) << my_array[i][j] << "  ";
			sum += my_array[i][j];
		}
		//cout << endl;
	}
	//cout << sum << endl;
	return sum;
}
