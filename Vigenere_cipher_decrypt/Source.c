#include <stdio.h>
#include <Windows.h>

#define STRING_SIZE 256

void Encrypt(unsigned char* shifrtext, unsigned char* key, char* text)
{
	int keylen = strlen(key);
	int shifrtextlen = strlen(shifrtext);
	for (int i = 0; i < shifrtextlen; i++)
	{
		text[i] = (unsigned char)'а' + ((shifrtext[i] + 32 - key[i % keylen]) % 32);
	}
	text[shifrtextlen] = '\0';
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char key[STRING_SIZE];
	printf("Введите ключ(ру, ниж): ");
	gets_s(key, STRING_SIZE);


	char shifrtext[STRING_SIZE];
	printf("Введите зашифрованный текст(ру, ниж): ");
	gets_s(shifrtext, STRING_SIZE);

	char text[STRING_SIZE];
	Encrypt(shifrtext, key, text);
	printf("Расшифрованный текст: %s\n", text);


	return 0;
}