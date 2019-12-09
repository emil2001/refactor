
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
int refactor(char* line, char *out)
{
	int changed = 0;
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
			out[j++] = '#';
			i++;
			c = line[i];
			changed++;
		}
		else
		{
			no = f + i1 + l;
			/*
			if (l)
			{

				out[j++] = line[i - 3];
				out[j++] = line[i - 2];
				out[j++] = line[i - 1];
			}
			else
			if (i1)
			{ 
				out[j++] = line[i - 2];
				out[j++] = line[i - 1];
			}
			else
			if (f)
				out[j++] = line[i - 1];
			else
			{
				out[j++] = c;
				i++;
				c = line[i];
			}
			*/

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

	if (c == '\n')
		out[j++] = '\n';

	out[j] = 0;

	return changed;
}



int main_ok()
{
	char str[4096];
	char strOut[4096];
	FILE* file;
	file = fopen("input.txt", "r+");
	int changed = 0;
	int posr = 0, posw = 0;
	while (!feof(file))
	{
		fseek(file, posr, SEEK_SET);
		if (!fgets(str, sizeof(str), file))
			break;
		posr = ftell(file);

		changed += refactor(str, strOut);

		fseek(file, posw, SEEK_SET);
		fputs(strOut, file);
		posw = ftell(file);
		fflush(file);
	}
	_chsize(_fileno(file), posr - 3 * changed);
	fclose(file);
	return 0;
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
		fputs(strOut, fileOut);
	}
	fclose(fileInput);
	fclose(fileOut);
	//_unlink("input.txt");
	//rename("input_temp.txt", "input.txt");
	return 0;
}