#include <stdio.h>
#include <Windows.h>
#include "Lattice.h"

void Encrypt(char *text, int *lattice, const int width)
{
	int* latticeTurn[4];

	latticeTurn[0] = lattice;
	for (int i = 1; i < 4; i++)
	{
		latticeTurn[i] = GetTurnedLattice(latticeTurn[i - 1], width);
	}
	int textlen = strlen(text);
	char* enctyptedstring = (char*)malloc(256 * 2);
	char* pstr = enctyptedstring;

	int tcount = 0;
	int size = width * width;
	while (*text != '\0')
	{
		char* shifr = (char*)malloc(size);
		memset(shifr, '.', size);

		for (int j = 0; (j < 4) && (*text != '\0'); j++)
		{
			for (int i = 0; (i < size) && (*text != '\0'); i++)
			{
				if (latticeTurn[j][i])
				{
					shifr[i] = *text;
					text++;
				}
			}
		}

		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < width; j++)
			{
				enctyptedstring[tcount * size + i * width + j] = shifr[i * width + j];
				printf("%c ", shifr[i * width + j]);
			}
			printf("\n");
		}
		tcount++;
		printf("\n");
	}

	enctyptedstring[tcount * size] = '\0';
	printf("Зашифрованная строка: %s", enctyptedstring);
}

int main()
{
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251);
	
	int size;
	int *lattice = GetLattice(&size);
	if (lattice == NULL)
	{
		printf("Не удалось загрузить решётку\n");
		return -1;
	}
	printf("Решётка загружена\n");

	if (!CheckLattice(lattice, size))
	{
		printf("Решётка не корректна\n");
		return -1;
	}

	printf("Текст для шифрования: ");
	char text[256];
	gets_s(text, 256);

	Encrypt(text, lattice, size);

	return 0;
}