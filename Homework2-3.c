#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 

#define KEY_Y 121 // определение кнопки "y", нажатой на клавиатуре
#define KEY_N 110 // определение кнопки "n", нажатой на клавиатуре
#define KEY_ESC 27 // определение кнопки "ESC", нажатой на клавиатуре

int main()
{
    int number, x, y, exp, check; // задаем переменные: number - количество вершин; x,y - вершины; exp - степень вершины; check - количество вершин, удовлетворяющих формуле
    printf("Enter the desired number of vers:\n"); 
    scanf("%d", &number);
    float formula=(number-1.0)/2.0; // задаем переменную (формулу) для проверки связности графа по теореме 1
    int matr[number][number]; // создаем матрицу
    for (int i=0; i<number; i++)
	{
	   for (int j=0; j<number; j++) 
	   {
	   matr[i][j] = 0; // заполняем матрицу нулями
	   }
    }

	while(1)  
    {
    	printf("\nFor add connection, please, press - y; for skip - n; for exit - ESC\n" );
        char c = getch(); // считываем кнопку с клавиатуры
        if(c=='Y') // добавляем возможность использования как заглавных, так и строчных букв
        c='y';
        else if(c=='N')
        c='n';
        switch(c) {
        case KEY_Y:
            printf("\nPlease, write outgoing vertex\n"); 
            scanf("%d",&x);
            while (x > number) // если введенное число больше количества вершин, программа выдаёт ошибку
            {
            	printf("Error, wrong number\n");
            	printf("\nPlease, write outgoing vertex\n"); 
            	scanf("%d",&x);
            }
            printf("\nPlease, write ingoing vertex\n");
            scanf("%d",&y);
            while (y > number) // если введенное число больше количества вершин, программа выдаёт ошибку
            {
            	printf("Error, wrong number\n");
            	printf("\nPlease, write ingoing vertex\n"); 
            	scanf("%d",&y);
            }
            matr [x-1][y-1]=1; // создаём соединения между вершинами
            matr [y-1][x-1]=1; // создаём зеркальные соединения, т.е. неопределенный граф
            break;
        case KEY_N:
                check=0;
            	for (int i=0; i<number; i++)
				{
                    exp=0;
				for (int j=0; j<number; j++) 
				{
                    if(matr[i][j]==1) // если есть соединения, то переменная exp будет увеличиваться на 1
                        exp++;
					printf("%d", matr[i][j]);
				}
                    if(exp >= formula) // если значение exp больше или равно значению formula, то значение check увеличивается на один
                        check++;
				    printf("\n");
				}
                    if(number==check) // если общее кол-во вершин равно кол-ву вершин, удовлетворяющих формуле, значит граф связный 
                        printf("\nGraph connected\n");
                    else // если общее кол-во вершин неравно кол-ву вершин, удовлетворяющих формуле, значит граф несвязный
                        printf("\nGraph disconnected\n");
                    printf("\n%d - the number of vertices satisfying the formula\n", check);

                    FILE* file = fopen("./graph.gv", "w+b"); // cоздание файла формата .gv для чтения и записи ребер графа
                    fputs("graph Graph {\n", file);
                    for (int i = 0;i < number; i++) 
                        for (int j = i; j < number; j++)
                            if (matr[i][j] == 1) // если мы находим в матрице смежности единицу 
                                fprintf(file, "\t%d -- %d;\n", i+1, j+1); // записываем связь в созданный файл;
                    fputs("}", file);
                    fclose(file);
                    system("dot -Tpng graph.gv -o graph.png");
            break;
        case KEY_ESC: // выход из программы
        	return 0;
        	break;    
        default:
            printf("\nStrict use of y or n is assumed\n");  // вывод ошибки при введении неправильной кнопки
            break;
        }
    }
    return 0; 
    system("pause");
}