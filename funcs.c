#include "header.h"


int fillbinary(char *name) {  // Заполнение бинарного файла
	float input;
	int n=0;
	char temp;
	FILE *file = fopen(name, "wb");
	
	if (file == NULL) {    //  Ошибка, если не удалось открыть файл
		printf("Error opening the file\n");
		exit(1);
	}

	printf("Input float numbers to add, entering invalid number finishes the input.\n");
	while (1) {
		if ((scanf_s("%f%c", &input, &temp) != 2 || temp != '\n')) {
			printf("Input finished\n");
			fclose(file);
			return n;   // Возвращение числа добавленных элементов
		}
		else {
			fwrite(&input, sizeof(float), 1, file);
			n++;
		}
	}
	return 0;
}

int count(char *name, int sign) {    // Подсчет чисел с заданным знаком в файле
	FILE *file = fopen(name, "rb");

	if (file == NULL) {    //  Ошибка, если не удалось открыть файл
		printf("Error opening the file\n");
		exit(1);
	}

	float num;
	int count = 0;
	while (!feof(file)) {
		fread(&num, sizeof(float), 1, file);
		if ((!feof(file)) && (sign*num) > 0) {
			count++;
		}
	}
	fclose(file);
	return count;
}

int countall(char *name) {    // Подсчет всех элементов в файле
	FILE *file = fopen(name, "rb");

	if (file == NULL) {    //  Ошибка, если не удалось открыть файл
		printf("Error opening the file\n");
		exit(1);
	}

	float num;
	int count = 0;
	while (!feof(file)) {
		fread(&num, sizeof(float), 1, file);
		count++;
	}
	fclose(file);
	return count;
}

void file_float_out(char *name) {   // Вывод бинарного файла на экран
	FILE *file = fopen(name, "rb");
	float num;

	if (file == NULL) {    //  Ошибка, если не удалось открыть файл
		printf("Error opening the file\n");
		exit(1);
	}

	while (1) {
		fread(&num, sizeof(float), 1, file);
		if (feof(file))
			break;
		printf("%f ", num);
	}
	printf("\n");
	fclose(file);
}

void file_text_out(char *name) {
	char line[30];
	int k=0;
	FILE *file = fopen(name, "rt");

	if (file == NULL) {    //  Ошибка, если не удалось открыть файл
		printf("Error opening the file\n");
		exit(1);
	}

	while (fgets(line, sizeof(line), file) != NULL) {
		printf("%s", line);
		k++;
	}
	if (k==0)
		printf("***The file is empty***\n");
	fclose(file);
}

char *trim_string(char *str){    //  Обрезка пробелов в начале и конце строки
	char *end;    //  Указатель на конец строки

	while (isspace((unsigned char)*str))   //   Смещаем указатель на начало текста
		str++;

	if (*str == 0) {     // Если в строке только пробелы
		printf("Error: the string contains all spaces\n");
		return NULL;
	}
	
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))    //  Двигаем указатель на конец влево
		end--;

	end[1] = '\0';

	return str;
}

int edit_lines(char *name, char *dest, int n) {
	FILE *file = fopen(name, "rt");
	FILE *g = fopen(dest, "wt");

	if (file == NULL || g == NULL) {
		printf("Error opening the file\n");
		exit(1);
	}

	char *temp, *temp1, t[100], line[100], lines[100][100];
	int i,j, k = 0;

	while ((temp = fgets(line, sizeof(line), file)) != NULL) {
		if (temp[0] == ' ' || temp[strlen(temp)-2] == ' ') {   // Проверка на наличие пробелов в начале и конце
			if ((temp1 = trim_string(temp)) == NULL){   //  Обрезаем и проверяем строку
				fclose(file);
				fclose(g);
				exit(-1);
			}
			strcpy(lines[k], temp1);   // Записываем обрезанную строку в массив
			k++;
		}
	}

	for (i = 0; i < k; i++)
		for (int j = i + 1; j < k; j++) {
			if (strcmp(lines[i], lines[j]) > 0) {   //  Перестановка массива в алфавитный порядок
				strcpy(t, lines[i]);
				strcpy(lines[i], lines[j]);
				strcpy(lines[j], t);
			}
		}
	for (i = 0; i < k; i++) {
		fprintf(g, "%s\n", lines[i]);    // Запись упорядоченных строк в файл
	}

	fclose(file);
	fclose(g);
	return 0;
}

int filltext(char *name){     //  Заполнение текстового файла
	char input[100];
	int n = 0;
	char temp;
	FILE *file = fopen(name, "wt");

	if (file == NULL) {    //  Ошибка, если не удалось открыть файл
		printf("Error opening the file\n");
		exit(1);
	}

	fseek(stdin, 0, SEEK_END);   //  Переходим в конец stdin, иначе перестает работать после меню из main
	printf("Input strings, ENTER on the blank line will finish the input:\n");
	while (1) {    //  Заполнение текстового файла, пока не введен ENTER

		fgets(input, sizeof(input), stdin);
		
		if (input[0] == '\n') {
			fclose(file);
			return n;   //  Возвращение количества записанных строк
		}
		fprintf(file, "%s", input);
		n++;
	}
	fclose(file);
	return 0;
}

int task1(char *name) {
	float num, temp;
	int i, n = 0;

	n = fillbinary(name);

	float cneg, cpos;
	
	cpos = count(name, 1);
	cneg = count(name, -1);
	
	FILE *file = fopen(name, "r+b");

	if (file == NULL) {    //  Ошибка, если не удалось открыть файл
		printf("Error opening the file\n");
		exit(1);
	}
	
	fseek(file, (n - 1) * sizeof(float), SEEK_SET);
	for (i = n+1; i > 0; i--) {   // Смещение всех элементов файла на 2 вперед
		fread(&temp, sizeof(float), 1, file);
		fseek(file, i * sizeof(float), SEEK_SET);
		fwrite(&temp, sizeof(float), 1, file);
		fseek(file, (i - 3) * sizeof(float), SEEK_SET);
	}

	fseek(file, 0, SEEK_SET);
	fwrite(&cpos, sizeof(float), 1, file);   //  Запись количества положительных и отрицательных элементов в начало
	fwrite(&cneg, sizeof(float), 1, file);
	fclose(file);

	file_float_out(name);

	return 0;
}

int task2(char *name, char *dest) {
	
	int n;
	n = filltext(name);
	if (edit_lines(name, dest, n) == -1) { 
		return -1;
	}

	printf("Output file:\n");
	file_text_out(dest);

	return 0;
}