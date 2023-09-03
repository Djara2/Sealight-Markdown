#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 1. modified to use strdup to stop destruction of source
char** split_string(char *source, char *delimiter)
{
	char *source_copy = strdup(source);
	int len = 0;
	int capacity = 10;
	char **string_tokens = malloc(sizeof(char*) * capacity);

	char *token = strtok(source_copy, delimiter);
	while(token != NULL)
	{
		string_tokens[len] = strdup(token);
		len = len + 1;
		if(len >= capacity)
		{
			capacity *= 2;
			string_tokens = realloc(string_tokens, sizeof(char*) * capacity);
		}
		token = strtok(NULL, delimiter);
	}
	// final element is NULL so that you can traverse
	string_tokens[len] = NULL;

	free(source_copy);
	return string_tokens;
}

bool flip_boolean(bool b)
{
	if(b) return false;
	else return true;
}

void insert_char(char **string_ptr, int *len, int *capacity, char c)
{
	if( (*len) >= (*capacity) )
	{
		(*capacity) *= 2;
		char *new_addr = realloc((*string_ptr), sizeof(char) * (*capacity));
		if(new_addr == NULL)
		{
			printf("Could not reallocate more memory to insert char \'%c\'\n", c);
			return;
		}
		(*string_ptr) = new_addr;
	}
	(*string_ptr)[(*len)] = c;
	(*len)++;
}

void concatenate(char **string_ptr, int *len, int *capacity, char *operand)
{
	int limit = strlen(operand);
	for(int i = 0; i < limit; i++)
	{
		if( (*len) >= (*capacity) )
		{
			(*capacity) *= 2;
			char *new_addr = realloc((*string_ptr), sizeof(char) * (*capacity));
			if(new_addr == NULL)
			{
				printf("Could not allocate more memory to concatenate strings.\n");
				return;

			}
			(*string_ptr) = new_addr;
		}
		(*string_ptr)[(*len)] = operand[i];
		(*len)++;
	}
}

int main(int argc, char *argv[])
{
	if(argc < 2) return 1;
	char *source = strdup(argv[1]);
	int source_len = strlen(source); 

	bool italic_initiated = false;
	int html_len = 0;
	int html_capacity = 15;
	char *html = malloc(sizeof(char) * html_capacity);
	int i = 0;
	// actual work -- the idea is to copy character by character until we reach the delimiter. If we reach
	//                the delimiter, then do not copy the characters. Instead copy <b> or </b> depending on
	//                whether or not we have already opened a <b> tag. This is indicated by the
	//                italic_initiated variable. Then, skip ahead 2 characters so that we skip the first and
	//                second asterisk.
	while(i < source_len)
	{
		// case: bold delimiter -- do not copy characters, instead copy <b> and </b> depending on
		//                         whether bold is being initiated or terminated
		if(source[i] == '*')
		{
			italic_initiated = flip_boolean(italic_initiated);

			if(italic_initiated) concatenate(&html, &html_len, &html_capacity, "<i>");
			else concatenate(&html, &html_len, &html_capacity, "</i>");
		}
		else
		{
			insert_char(&html, &html_len, &html_capacity, source[i]);
		}
		i++;
	}

	// display results
	printf("i: %d\n", i);
	printf("source_len: %d\n", source_len);
	/*
	if(i < source_len && source[source_len - 1] != '*')
	{
		insert_char(&html, &html_len, &html_capacity, source[source_len - 1]);
	}
	*/
	printf("HTML conversion: \"%s\"\n", html);
	free(html);
	free(source);
	return 0;
}

