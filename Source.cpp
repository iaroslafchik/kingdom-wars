#define _CRT_SECURE_NO_WARNINGS 

#include <windows.h>

#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>

#define SELECT ?" \033[7m":""

int main() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	char prevKey = 0x00, key = 0x00;
	clock_t clk = clock();
	printf("\033[?25l");
	setlocale(LC_ALL, "ru_RU");

	for (int menu = -1; menu != 0;) {
		for (int loop = 0; menu == -1; loop++) {
			if (loop == 0) printf("\033[2J");


			prevKey = key;

			if (_kbhit()) key = _getch();
			clk = clock();
			printf("\033[H\033[38;2;%d;%d;%dm%02d:%02d:%02d\033[0m\n\n\033[103m\033[30mПОРТФОЛИО | К. Я. С. | ПЭ-231\033[0m\n\n", 250 - (clk / 4 % 250),250 - (clk / 4 % 250), 250 - (clk / 4 % 250), clk / 3600000 % 24, clk / 60000 % 60, clk / 1000 % 60);

			printf("%s1 ДЗ 1\033[0m \n", key == '1' SELECT);
			printf("%s2 Время\033[0m \n", key == '2' SELECT);
			printf("%s3 Рисунки вложенными циклами\033[0m \n", key == '3' SELECT);
			printf("%s4 ДЗ 2 - Число эйлера\033[0m \n", key == '4' SELECT);
			printf("%s5 ДЗ 3 - Число пи с точностью\033[0m \n", key == '5' SELECT);
			printf("%s6 Вертикальный эквалайзер\033[0m \n", key == '6' SELECT);
			printf("%s7 Эквалайзер - игра\033[0m \n ", key == '7' SELECT);

			if (prevKey == '1' && key == 13) menu = 1;
			if (prevKey == '2' && key == 13) menu = 2;
			if (prevKey == '3' && key == 13) menu = 3;
			if (prevKey == '4' && key == 13) menu = 4;
			if (prevKey == '5' && key == 13) menu = 5;
			if (prevKey == '6' && key == 13) menu = 6;
			if (key == 27) menu = 0;

			for (loop = 0; menu == 1; loop++) { // Первый пункт
				if (loop == 0) printf("\033[2J");

				printf("Введите t, в диапазоне [0,5; 3]");

				double t = 0;
				if (scanf("%lf", &t) != 1) {
					printf("Ошибка!!!\nНеверное значение");
					_getch();
					menu = -1;
				}

				printf("Вы ввели следующий t: %lf\n", t);

				if (t >= 0.5 && t <= 3){
					double a = 1.3, b = 2.5, z = 0.0;

					if (t < a) z = a * pow(t, 2) - b * sqrt(t + 1);
					else if (t > b) z = a * pow(t, 2.0 / 3.0) - pow(t - 1, 1.0 / 3.0);
					else z = a - b;

					printf("Z = %lf", z);
				}
				else printf("Введеный t находится вне диапазона допустимых значений - [0,5; 3]!");

				_getch();
				printf("\033[2J");
				menu = -1, key = 0x00;
			}
			for (loop = 0; menu == 2; loop++) { // Втрой пункт
				if (loop == 0) printf("\033[2J");

				prevKey = key;

				if (_kbhit()) key = _getch();

				clock_t prev = 0, cur = clock();

				printf("clocks per second = %d\n", CLOCKS_PER_SEC);

				if (cur != prev)
				{
					printf("%02d:%02d:%02d %.3f\033[H", \
						cur / 3600000 % 24, \
						cur / 60000 % 60, \
						cur / 1000 % 60, \
						cur / 1000.0);
				}

				if (key == 27) {
					printf("\033[2J");
					menu = -1, key = 0x00;
				}

				prev = cur, cur = clock();
			}
			for (loop = 0; menu == 3; loop++) { // Третий пункт
				if (loop == 0) printf("\033[2J");

				prevKey = key;

				if (_kbhit()) key = _getch();

				int columns = 10, rows = 10;

				printf("\033[H");

				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < columns; j++)
						if (i == 0 || j == 0 || j == columns - 1 || i == rows - 1) printf("#");
						else printf(" ");
					printf("\n");
				}

				if (key == 27) {
					printf("\033[2J");
					menu = -1, key = 0x00;
				}
			}
			for (loop = 0; menu == 4; loop++) {
				if (loop == 0) printf("\033[2J");

				printf("Число Эйлера должно быть таким (80 симоволов после запятой):\n2,71828182845904523536028747135266249775724709369995957496696762772407663035354759\n");
				printf("Введите количество шагов для подсчета числа Эйлера: ");

				int N = 0;
				double eiler = 1;
				double f = 1;

				scanf("%d", &N);

				for (int i = 1; i <= N; i++) {
					f *= i, eiler += 1 / f;
					printf("e = %.60lf, f(%d) = %.0lf\n", eiler, i, f);
				}
				
				_getch();
				printf("\033[2J");
				menu = -1, key = 0x00;
			}
			for (loop = 0; menu == 5; loop++) {
				if (loop == 0) printf("\033[2J");

				printf("Введетие желаемую точность\nНапример: 0,000000001 (обязательно через запятую! не точку! максимум 15 символов после запятой!)\n> ");

				double t;

				scanf("%lf", &t);

				double sum, sumOld, i, tt;
				for (i = 3, sum = sumOld = 2;; i += 2) {
					sum *= ((i - 1) / i) * ((i + 1) / i);
					tt = sum - sumOld;
					if (tt < 0) tt *= -1;
					//printf("\r%.15lf %.15lf %.15lf", 2 * sum, 2 * sumOld, 2 * tt);
					if (tt < t) break;
					sumOld = sum;
				}

				printf("\n%.15lf", 2 * sum);

				_getch();
				printf("\033[2J");
				menu = -1, key = 0x00;
			}
			for (loop = 0; menu == 6; loop++) {
				if (loop == 0) printf("\033[2J");

				setlocale(0, ".1251");
				srand(time(0));

				printf("Вериткальный эквалайзер\n");
				printf("Введите ширину эквалайзера (количество столбцов): ");
				int M;
				scanf("%d", &M);
				printf("Введите высоту эквалайзера (максимально возможная высота столбца): ");
				int N;
				scanf("%d", &N);

				int seed = 0;

				for (int i = 0; i < N; i++) {
					for (int j = rand() % M; j > 0; j--); { // заполняем
						seed = seed | (1 << rand() % M);
					}
					for (int j = 0; j < M; j++) { // выводим
						printf(" %c", (seed & (1 << j)) ? '#' : ' ');
					}
					printf("\n");
				}

				_getch();
				printf("\033[2J");
				menu = -1, key = 0x00;
			}
		}
	}
}