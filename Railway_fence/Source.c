#include <stdio.h>
#include <string.h>

#define BUFFER_LENGTH 256

void Encrypt(char* output, char* input, int n)
{
	int len = strlen(input);
	output[len] = 0;
	int pos = 0;

	int inc = (n - 1) * 2;
	for (int i = 0; i < len; i += inc, pos++)
	{
		output[pos] = input[i];
	}

	for (int i = 1; i < n - 1; i++)
	{
		input++;
		len--;
		output[pos] = input[0];
		pos++;
		int localinc = inc - i * 2;
		for (int j = localinc; j < len; j += localinc, pos++)
		{
			output[pos] = input[j];
			localinc = inc - localinc;
		}
	}

	input++;
	len--;
	for (int i = 0; i < len; i += inc, pos++)
	{
		output[pos] = input[i];
	}

}

int main()
{
	int n;
	char input[BUFFER_LENGTH];
	char output[BUFFER_LENGTH];

	gets_s(input, sizeof(input));
	scanf_s("%d", &n);
	Encrypt(output, input, n);
	puts(output);
	return 0;
}