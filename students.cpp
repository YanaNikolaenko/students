// 5-c-struct-muhammed-students2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include "string.h"
#include "locale.h"
#include <stdlib.h>
#include <malloc.h>
#include <conio.h>
#include <windows.h>
#include <algorithm>

using namespace std;

FILE *file = NULL;
int col_std = 0;

int const min_zp = 360;




struct student {
	char FIO[20];
	char group[20];
	float average;
	int income_per1;
} students[100] = { NULL };




student* read()
{
	col_std = 0;

	if ((file = fopen("students.txt", "rb")) == NULL)
	{
		printf("Cannot open directory file.");
		exit(1);
	}


	for (int i = 0; feof(file) == 0; i++)
	{
		fread(&students[i], sizeof(student), 1, file);
		col_std++;
	}

	col_std = col_std - 1;

	cout << "---- Содержимое файла:\n";
	for (int i = 0; i<col_std; i++)
	{
		printf("\n%-12i | %-34s | %-12s | %-20f | %i\n", i + 1, students[i].FIO, students[i].group, students[i].average, students[i].income_per1);
	}




	fclose(file);

	return students;
}




void task() 
{
	read();




	if ((file = fopen("students.txt", "w+")) == NULL)
	{
		printf("Cannot open directory file.");
		exit(1);
	}



	student malo[100];
	student mnogo[100];

	int count_malo = 0;
	int count_mnogo = 0;

	for (int i = 0; i < col_std; i++) {
		

		if (students[i].income_per1 < 2 * min_zp) {
			malo[count_malo] = students[i];
			count_malo++;
		}

		else {
			mnogo[count_mnogo] = students[i];
			count_mnogo++;
		}
	}




	int i, j;
	student tmp;

	for (int i = 0; i < count_mnogo - 1; i++)
	{
		for (j = 0; j < count_mnogo - i - 1; j++) {

			if (mnogo[j].average < mnogo[j + 1].average)
			{
				tmp= mnogo[j];
				mnogo[j] = mnogo[j + 1];
				mnogo[j + 1] = tmp;
			}
		}
	}




	for (int i = 0; i < count_malo; i++)
	{
		students[i] = malo[i];
	}


	i = 0;

	for (count_malo; count_malo < col_std; count_malo++)
	{
		students[count_malo] = mnogo[i];
		i++;
	}



	cout << "---- Готово задание выполненно:\n";
	for (int i = 0; i<col_std; i++)
	{
		printf("\n%-12i | %-34s | %-12s | %-20f | %i\n", i + 1, students[i].FIO, students[i].group, students[i].average, students[i].income_per1);
	}



	for (int i = 0; i < col_std; i++)
	{
		fwrite(&students[i], sizeof(student), 1, file);
	}

	fclose(file);
}






student* write(int col)
{


	if ((file = fopen("students.txt", "a+b")) == NULL)
	{
		printf("Cannot open directory file.");
		exit(1);
	}



	for (int i = 0; i < col; i++) 
	{
		cout << "\n" << " Введите Ф.И.О. студента " << i+1 << "\t";
		cin >> students[i].FIO;
		cout << " Введите группу:" << "\t";
		cin >> students[i].group;
		cout << " Введите средний балл:" << "\t";
		cin >> students[i].average;
		cout << " Введите доход на одного члена семьи:" << "\t";
		cin >> students[i].income_per1;

		fwrite(&students[i], sizeof(student), 1, file);
	}

	fclose(file);

	return students;
}
















student* del(int number)
{

	number--;
	read();



	if ((file = fopen("students.txt", "wb")) == NULL)
	{
		printf("Cannot open directory file.");
		exit(1);
	}




	int count = 0;
	for (int i = 0; i<col_std; i++)
	{
		if (i != number)
		{
			students[count] = students[i];
			count++;
		}
	}

	col_std = count;


	for (int i = 0; i < col_std-1; i++)
	{
		fwrite(&students[i], sizeof(student), 1, file);
	}





	fclose(file);

	return students;
}













student* edit(int number)
{
	number--;


	if ((file = fopen("students.txt", "wb")) == NULL)
	{
		printf("Cannot open directory file.");
		exit(1);
	}


	cout << "\n" << " Введите Ф.И.О. студента " << number+1 << "\t";
	cin >> students[number].FIO;
	cout << " Введите группу:" << "\t";
	cin >> students[number].group;
	cout << " Введите средний балл:" << "\t";
	cin >> students[number].average;
	cout << " Введите доход на одного члена семьи:" << "\t";
	cin >> students[number].income_per1;



	for (int i = 0; i < col_std;i++) 
	{
		fwrite(&students[i], sizeof(student), 1, file);
	}


	fclose(file);

	return students;
}






int main()
{

	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	int menu=0;

	start:
	cout << "------------------------------------------Менюха:-----------------------------------------------\n\n";
	cout << "1. Прочитать файл\n";
	cout << "2. Записать в  файл\n";
	cout << "3. Редактировать  файл\n";
	cout << "4. Удалить запись с файла\n";
	cout << "5. Задание\n\n\n";
	cout << "Выберите действие: >";
	cin >> menu;


	switch (menu) 
	{

		case 1: 
		{
			system("cls"); 
			read(); 
			cout << "\n\n\n\n"; 
			goto start;

		} break;

		case 2: 
		{
			int howmuch;
			system("cls");
			cout<<"\nСколько надо студиков записать братан?\n >";
			cin >> howmuch;
			write(howmuch);
			system("cls");
			cout << "\n------Данные успешно добавленны\n\n";
			goto start;
		} break;


		case 3:
		{
			int whichone;
			system("cls");
			read();
			cout << "\nКакого студика надо изменить братан?\n >";
			cin >> whichone;
			edit(whichone);
			system("cls");
			cout << "\n------Данные успешно обновленны\n\n";
			goto start;
		} break;


		case 4:
		{
			int whichone;
			system("cls");
			read();
			cout << "\nКому пора в армию братан?\n >";
			cin >> whichone;
			del(whichone);
			system("cls");
			cout << "\n------Был студент стал солдатом - данные обновленны\n\n";
			goto start;

		} break;


		case 5:
		{
			task();
			_getch();
			system("cls");
			goto start;
		} break;


		default: {
			cout << "\nШота косяк какой-то, такого пункта меню нет >"; _getch(); system("cls");
			goto start;
		}
	}



	//write(2);
	////read();
	//edit(1);
	//read();
	//del(1);
	//read();

	system("pause");
    return 0;
}

