#include "Lattice.h"
#include <stdio.h>
#include <string.h>

#define MAX_FILE_NAME_LENGTH 256

int* GetLattice(int* size)
{
	printf("Введите путь к файлу с решёткой: ");
	char fileName[MAX_FILE_NAME_LENGTH];
	gets_s(fileName, MAX_FILE_NAME_LENGTH);

	FILE *latticeFile;
	fopen_s(&latticeFile, fileName, "r");
	if (!latticeFile)
	{
		printf("Не удалось открыть файл\n");
		return NULL;
	}

	fscanf_s(latticeFile, "%d", size);
	if (*size < 1)
	{
		printf("Решётка недопустимого размера\n");
		return NULL;
	}
	if (*size & 1)
	{
		printf("Размер решётки должен быть чётным\n");
		return NULL;
	}

	int* lattice = (int*)malloc(sizeof(int) * *size * *size);
	for (int i = 0; i < *size * *size; i++)
	{
		fscanf_s(latticeFile, "%d", lattice + i);
		if ((lattice[i] != 0) && (lattice[i] != 1))
		{
			return NULL;
		}
	}

	return lattice;
}

int* GetTurnedLattice(int *lattice, const int size)
{
	int* turnedLattice = (int*)malloc(sizeof(int) * size * size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			turnedLattice[j * size + size - 1 - i] = lattice[i * size + j];
		}
	}
	return turnedLattice;
}

int CheckLattice(int* lattice, const int size)
{
	int cellsCount = size * size / 4;
	int* used = (int*)malloc(sizeof(int) * cellsCount);
	memset(used, 0, sizeof(int) * cellsCount);

	int cellNumber = 0;
	for (int i = 0; i < size / 2; i++)
	{
		for (int j = 0; j < size / 2; j++)
		{
			if (lattice[i * size + j])
			{
				if (used[cellNumber])
				{
					printf("Поля решётки перекрываются\n");
					return 0;
				}
				used[cellNumber] = 1;
			}
			cellNumber++;
		}
	}

	cellNumber = 0;
	for (int i = size - 1; i >= size / 2; i--)
	{
		for (int j = 0; j < size / 2; j++)
		{
			if (lattice[j * size + i])
			{
				if (used[cellNumber])
				{
					printf("Поля решётки перекрываются\n");
					return 0;
				}
				used[cellNumber] = 1;
			}
			cellNumber++;
		}
	}

	cellNumber = 0;
	for (int i = size - 1; i >= size / 2; i--)
	{
		for (int j = size - 1; j >= size / 2; j--)
		{
			if (lattice[i * size + j])
			{
				if (used[cellNumber])
				{
					printf("Поля решётки перекрываются\n");
					return 0;
				}
				used[cellNumber] = 1;
			}
			cellNumber++;
		}
	}

	cellNumber = 0;
	for (int i = 0; i < size / 2; i++)
	{
		for (int j = size - 1; j >= size / 2; j--)
		{
			if (lattice[j * size + i])
			{
				if (used[cellNumber])
				{
					printf("Поля решётки перекрываются\n");
					return 0;
				}
				used[cellNumber] = 1;
			}
			cellNumber++;
		}
	}

	for (int i = 0; i < cellsCount; i++)
	{
		if (used[i] == 0)
		{
			printf("!Не все поля решётки использованы\n");
			return 1;
		}
	}

	return 1;
}
