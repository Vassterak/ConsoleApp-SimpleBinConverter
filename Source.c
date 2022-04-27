#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MESSAGE_LENGHT 64

void initial(char* str)
{
	printf("If your input is longer than %d characters, overflow chars will be ignored\n", MAX_MESSAGE_LENGHT - 1);
	printf("Enter ASCII message to transform it to binary code: ");

	strcpy_s(str, MAX_MESSAGE_LENGHT, fgets(str, MAX_MESSAGE_LENGHT, stdin));
}

void convert_each_char(char letter, int arrayIndex, int* strOut)
{
	unsigned char workaround = letter; //char is signed by default so bitshift to left -> overflow to negative values. For fix we use unsigned char
	for (size_t i = 0; i < 8; i++)
	{
		if ((workaround & 0x80) != 0)
			strOut[arrayIndex * 8 + i] = 1;
		else
			strOut[arrayIndex * 8 + i] = 0;

		workaround = workaround << 1;
	}
}

void loop_throught_message(char* str, int* strOutput)
{
	//int* strOutput = malloc(strlen(str) * 8 * sizeof(int));
	for (size_t i = 0; i < strlen(str); i++)
		convert_each_char(str[i], i, strOutput);
}

void print_message(size_t messageLenght, int* strOutput)
{
	for (int i = 0; i < messageLenght - 1; i++)
	{
		for (int j = 0; j < 8; j++)
			printf("%d", strOutput[i * 8 + j]);
		printf("\n");
	}
	printf("--------------------------------------\n");
}

int main()
{
	while (1)
	{
		char inputMesssage[MAX_MESSAGE_LENGHT]; //user text
		initial(inputMesssage); //save the message from user input

		printf("Your message lenght: %zu\n", strlen(inputMesssage) - 1);

		int* strOutput = malloc(strlen(inputMesssage) * 8 * sizeof(int)); //create array used to store output values

		loop_throught_message(inputMesssage, strOutput);
		print_message(strlen(inputMesssage), strOutput);
	}

	return 0;
}