#include <stdio.h>
#include <Windows.h>

#define STRING_SIZE 256

void Encrypt(char* text, unsigned char* key, char* shifrtext)
{
	int keylen = strlen(key);
	int textlen = strlen(text);
	int mincolumnpos = 0;

	for (int i = 0; i < keylen; i++)
	{
		if (key[i] < key[mincolumnpos])
		{
			mincolumnpos = i;
		}
	}

	int lastmincolumpos;
	do {

		for (int i = mincolumnpos; i < textlen; i += keylen)
		{
			*shifrtext = text[i];
			shifrtext++;
		}

		lastmincolumpos = mincolumnpos;
		for (int i = 0; i < keylen; i++)
		{
			if ((key[i] > key[lastmincolumpos]) && ((mincolumnpos == lastmincolumpos) || (key[i] < key[mincolumnpos])))
			{
				mincolumnpos = i;
			}
			else if ((key[i] == key[lastmincolumpos]) && (i > lastmincolumpos))
			{
				mincolumnpos = i;
				break;
			}
		}
	} while (mincolumnpos != lastmincolumpos);
	*shifrtext = '\0';
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char key[STRING_SIZE];
	printf("Введите ключ: ");
	gets_s(key, STRING_SIZE);


	char text[STRING_SIZE];
	printf("Введите шифруемый текст: ");
	gets_s(text, STRING_SIZE);

	char shifrtext[STRING_SIZE];
	Encrypt(text, key, shifrtext);
	printf("Зашифрованный текст: %s\n", shifrtext);


	return 0;
}