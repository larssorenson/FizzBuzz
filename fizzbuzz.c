#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* intToString(int x)
{
	char* result = malloc(sizeof(char)*11);
	if(result == NULL)
	{
		return NULL;
	}
	
	memset(result, 0, 11);
	int length = 0;
	while(x > 0)
	{
		int digit = (x-((int)(x/10)*10));
		switch(digit)
		{
			case 0:
				strcat(result, "0");
				break;
			case 1:
				strcat(result, "1");
				break;
			case 2:
				strcat(result, "2");
				break;
			case 3:
				strcat(result, "3");
				break;
			case 4:
				strcat(result, "4");
				break;
			case 5:
				strcat(result, "5");
				break;
			case 6:
				strcat(result, "6");
				break;
			case 7:
				strcat(result, "7");
				break;
			case 8:
				strcat(result, "8");
				break;
			case 9:
				strcat(result, "9");
				break;
		}
		x /= 10;
		length++;
	}
	
	char* rev_result = malloc(sizeof(char)*(length+1));
	if(rev_result == NULL)
		return NULL;
		
	memset(rev_result, 0, length+1);
	
	int y;
	for(y = 0; x < length; x++)
	{
		rev_result[x] = result[(length-1)-x];
	}
	
	return rev_result;
}

int main(int argc, char** argv)
{
	char* target_prog = malloc(sizeof(char)*32768);
	if(target_prog == NULL)
	{
		printf("Malloc error!\r\n");
		return -1;
	}
	
	memset(target_prog, 0, 32768);
	strcpy(target_prog, "#include <stdio.h>\r\n");
	strcat(target_prog, "int main(int argc, char** argv)\r\n");
	strcat(target_prog, "{\r\n");
	strcat(target_prog, "for(int i = 0; i < 100; i++)\r\n");
	strcat(target_prog, "{\r\n");
	strcat(target_prog, "if (i == 0 ) { printf(\"FizzBuzz\\r\\n\"); }\r\n");
	int x;
	int flag = 0;
	for(x = 1; x < 100; x++)
	{
		flag = 0;
		strcat(target_prog, "else if (i == ");
		char* intString = intToString(x);
		if(intString == NULL)
		{
			printf("Malloc failed!\r\n");
			return -1;
		}
		
		strcat(target_prog, intString);
		strcat(target_prog, ") { printf(\"");
		if(x % 3 == 0)
		{
			strcat(target_prog, "Fizz");
			flag = 1;
		}
		if(x % 5 == 0)
		{
			strcat(target_prog, "Buzz");
			flag = 1;
		}
		
		if(!flag)
		{
			strcat(target_prog, intString);
		}
		
		strcat(target_prog, "\\r\\n\"); }\r\n");
		
		free(intString);
	}
	
	strcat(target_prog, "}\r\n");
	strcat(target_prog, "}\r\n");
	FILE* file = fopen("fizzbuzz_gen.c", "w");
	if(file == NULL)
		return -1;	
	
	fprintf(file, "%s", target_prog);
	
	fclose(file);
	
	system("gcc -std=c99 fizzbuzz_gen.c -o fizzbuzz");
	system("./fizzbuzz");
	return 0;
}
