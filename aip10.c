#include "header.h"

// Вариант 29

int main(){
	int choice;
	printf("Enter the number of task:\n");
	scanf_s("%d", &choice);
	switch (choice)
	{
	case 1:
		task1("task1");
		break;
	case 2:
		task2("task2_f.txt", "task2_g.txt");
		break;
	default:
		printf("Error: invalid choice\n");
		break;
	}

	return 0;
}
