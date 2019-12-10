
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
void refactor(char* line, char *out)
{
	int i = 0, j = 0;
	int f = 0, i1 = 0, l = 0, no = 0;
	char c = line[0];
	
	while (c != '\n' && c != 0 && c != EOF)
	{	
		f = 0;
		i1 = 0;
		l = 0;

		if (c == 'f' && (i == 0 || line[i - 1] == 32 || line[i - 1] == '.'))
		{
			i++;
			c = line[i];
			f++;
		}
		if (c == 'i' && f)
		{
			i++;
			c = line[i];
			i1++;
		}
		if (c == 'l' && i1)
		{
			i++;
			c = line[i];
			l++;
		}		
		if (c == 'e' && l && (line[i + 1] == ' ' || line[i + 1] == '.' || line[i + 1] == '\r' || line[i + 1] == '\n' || line[i + 1] == EOF))
		{
			out[j++] = 'E';
			out[j++] = 'L';
			out[j++] = 'I';
			out[j++] = 'F';
			i++;
			c = line[i];

		}
		else
		{
			no = f + i1 + l;
			j += no;
			if (l)
			{
				out[--j] = line[--i];
			}
			if (i1)
			{
				out[--j] = line[--i];
			}
			if (f)
			{
				out[--j] = line[--i];
				j += no;
				i += no;
			}
			else
			{
				out[j++] = c;
				i++;
				c = line[i];
			}
		}
		
	}
	out[j] = 0;


}

int main()
{
	char str[4096];
	char strOut[4096];
	FILE* fileInput;
	FILE* fileOut;
	fileInput = fopen("input.txt", "r");
	fileOut = fopen("input_temp.txt", "w");
	while (!feof(fileInput))
	{
		fgets(str, sizeof(str), fileInput);
		refactor(str, strOut);
		puts(strOut);
	}
	fclose(fileInput);
	fclose(fileOut);

	return 0;
}