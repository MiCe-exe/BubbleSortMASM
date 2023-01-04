// Sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
using namespace std;

void showArray(int arr[], int size);
void bubbleSort(int arr[], int size, int mode);
void GenArr(int* ptrArr, int arrSIZE);

extern"C"
{
	void masmBubbleSort(int*, int, int);
}

int main()
{

	const int SIZE = 10000;		
	int myArr[SIZE];			//array to be used with C++
	int assemblyArr[SIZE];		//array to be used with MASM
	int sortOrder = 0;			//
	int menuInput = 0;
	bool userQuit = false;
	long int time = 0;
	long int masmTime = 0;


	time_t t1; // time variable in milliseconds
	
	// menu options
	do
	{
		//Gen array values
		cout << "Generating array..." << endl;
		GenArr(myArr, SIZE);

		//copy myArr to assemblyArr
		cout << "Copying array..." << endl;
		copy(begin(myArr), end(myArr), begin(assemblyArr));

		cout << "===================" << endl;
		cout << "       Menu" << endl;
		cout << "-------------------" << endl;
		cout << "0 - Ascending Order" << endl;
		cout << "1 - Decending ORder" << endl;
		cout << "Enter: ";
		
		do 
		{
			while (!(cin >> sortOrder))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Enter a value 1 or 2" << endl;
			}

			if (sortOrder < 0 || sortOrder > 1)
			{
				cout << "User input is out of range" << endl;
			}
		} while (sortOrder < 0 || sortOrder > 1);

		//bubbleSort() with c++ 
		cout << "\nUsing C++ bubbleSort()..." << endl;
		time = 0;
		t1 = clock();
		bubbleSort(myArr, SIZE, sortOrder);
		time = clock() - t1;

		//masmBubbleSort() with masm
		cout << "Using Aseembly masmBubbleSort()...\n\n";
		masmTime = 0;
		t1 = clock();
		masmBubbleSort(assemblyArr, SIZE, sortOrder);
		masmTime = clock() - t1;

		// Display Time
		cout << "===================" << endl;
		cout << "    Sort Time" << endl;
		cout << "-------------------" << endl;
		cout << "Time to execute bubbleSort(): " << time << " milliseconds" << endl;
		cout << "Time to execute masmBubbleSort(): " << masmTime << " milliseconds" << "\n\n";

		//Options to display Arrays;
		do
		{
			cout << "===================" << endl;
			cout << "      Display" << endl;
			cout << "-------------------" << endl;
			cout << "1 - Display bubbleSort() array" << endl;
			cout << "2 - Display masmBubbleSort() array" << endl;
			cout << "3 - Exit Display" << endl;
			cout << "Enter: ";

			while (!(cin >> menuInput))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input, Enter a value 1 or 2" << endl;
			}

			switch(menuInput){
				case 1:
					showArray(myArr, SIZE);
					break;
				case 2:
					showArray(assemblyArr, SIZE);
					break;
				case 3:
					cout << "Exiting display menu." << endl;
					break;
				default:
					cout << "Invalid input." << endl;
			}

		} while (menuInput != 3);

		//exit program or restart
		do
		{
			cout << "\n===================" << endl;
			cout << "      Menu" << endl;
			cout << "-------------------" << endl;
			cout << "1 - Exit " << endl;
			cout << "2 - Start a new sort" << endl;
			cout << "Enter: ";

			while (!(cin >> menuInput))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input: Enter a value 1 or 2" << endl;
			}

			if (menuInput == 1)
			{
				cout << "Exiting program. Have a nice day." << endl;
				userQuit = true;
			}
			else if (menuInput == 2)
			{
				cout << "Restarting...\n\n";
			}
			else
			{
				cout << "Invalid input: out of range." << endl;
			}

		} while ( (menuInput != 1) && (menuInput != 2) );

	} while (!userQuit);
	
}

//Generate an array
void GenArr(int* ptrArr, int arrSIZE)
{
	for (int i = 0; i < arrSIZE; i++)
	{
		ptrArr[i] = rand();
	}
}


void bubbleSort(int arr[], int size, int md)
{
	bool swap = true;
	int temp = 0;

	for (int idx = 0; idx < size - 1; idx++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			if (md == 0)
			{
				//sorting ascending
				if (arr[j] > arr[j + 1])
				{
					//swap
					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
			else
			{
				//sorting descending
				if (arr[j] < arr[j + 1])
				{
					//swap
					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}
	}
}

void showArray(int arr[], int size)
{
	for (int i = 0; i < size; i += 100)
		cout << arr[i] << ", ";
	cout << endl;
}
