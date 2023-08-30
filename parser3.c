#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool string_contains_char(char *source, char c)
{
	for(int i = 0; i < strlen(source); i++)
		if(source[i] == c) return true;

	return false;
}

int char_occurences(char *source, char c)
{
	int count = 0;
	for(int i = 0; i < strlen(source); i++)
	{
		if(source[i] == c) count++;
	}
	return count;
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

// modified to use strdup to stop destruction of source
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

int determine_header_level(char *source)
{
	if(source[0] != '#') return 0;
	int i = 1;
	while(source[i] == '#') i++;
	return i;
}

int determine_code_level(char *source)
{
	if(source[0] != '`') return 0;
	int i = 1;
	while(source[i] == '`') i++;
	return i;
}

int determine_admoninition_level(char *source)
{
	if(source[0] != '!') return 0;
	int i = 1;
	while(source[i] == '!') i++;
	return i;
}

bool is_unordered_list(char *source)
{
	int tab_level = 0;
	int len = strlen(source);

	// must, at minimum, start with "- a" (a can be any char)
	if(len < 3) return false; 

	// must start with tab or '-'
	if(source[0] != '-' && source[0] != '\t') return false;

	// case: highest level outer list
	if(source[0] == '-')
	{
		if(source[1] != ' ') return false;

		// since whole file is newline delimited, you dont have to worry about 
		// "- \n" as an argument
		return true;
	}

	// case: nested list
	if(source[0] == '\t')
	{
		tab_level = 1;
		for(int i = tab_level; i < len; i++)
		{
			if(source[i] == '\t') tab_level++;
			else break;
		}
		if(source[tab_level] == '-') return true;
		else return false;
	}
}

// modified to use strdup so that it does not modify original string.
// for some reason, original string was being messed up
/*
char* determine_admonition_type(char *source)
{
	char **split = split_string(source, " ");
	char *result = split[1];
	free(split[0]);
	for(int i 
	return split_string(source, " ")[1];
}
*/

char* string_substring(char *source, int inclusive_start, int exclusive_end)
{
	int required_chars = (exclusive_end - inclusive_start) + 1;
	char *result = malloc(sizeof(char) * required_chars);
	int j = 0;
	for(int i = inclusive_start; i < exclusive_end; i++)
	{
		result[j] = source[i];
		j++;
	}
	result[j] = '\0';
	return result;
}

bool flip_boolean(bool b)
{
	if(b) return false;
	else return true;
}

int main(int argc, char *argv[])
{
	if(argc < 2) return 1;

	FILE *source = fopen(argv[1], "r");
	if(source == NULL) 
	{
		printf("Could not open file \"%s\". Does it exist?\n", argv[1]);
		return 1;
	}

	// get all contents of the file
	int len = 0;
	int capacity = 100;
	char *contents = malloc(sizeof(char) * capacity);
	char c;
	while(true)
	{
		c = fgetc(source);
		if(c == EOF) break;

		contents[len] = c;
		len = len + 1;
		if(len >= capacity)
		{
			capacity *= 2;
			contents = realloc(contents, sizeof(char) * capacity);
		}
	}
	contents[len] = '\0';
	len = len + 1; 



	// tokenize the file (split by new lines)
	char **string_tokens = split_string(contents, "\n");
	free(contents);
	int j = 0; // remove later
	printf("File contents (delimited by newlines):\n\n");
	while(string_tokens[j] != NULL)
	{
		printf("line %d: %s\n", j, string_tokens[j]);
		j++;
	}



	// HTML translation
	int html_len = 0;
	int html_capacity = 100;
	char *html = malloc(sizeof(char) * html_capacity);
	concatenate(&html, &html_len, &html_capacity, "<!DOCTYPE html>\n<html>\n"); // top of document
	concatenate(&html, &html_len, &html_capacity, "<head>\n\t <style>\n\t\tbody {\n\t\t\tfont-family: Minion Pro Display;\n\t\t}\n.admonition {\nbackground-color: #f7f7f7;\nmargin-bottom: 10px;\nposition: relative;\noverflow: hidden;\npadding-left: 12px; /* Added padding to create space between the vertical stripe and the label */\n}\n/* This is the vertical stripe */\n.admonition:before {\ncontent: "";\nposition: absolute;\ntop: 0;\nleft: 0;\nwidth: 6px;\nheight: 100%;\nbackground-color: #ffa500; /* Default vertical stripe color */\n}\n\n/* Add more custom classes and styles for different variants if desired */\n\n.admonition h4 {\nmargin: 0;\npadding: 10px 8px;\nfont-size: 18px;\ncolor: black; /* Adjust the color as needed */\nbackground-color: #f4e7d4; /* Adjust the default header background color as needed */\nborder-radius: 0 4px 4px 0; /* Added border-radius to only round the right side */\nmargin-left: -6px;\nmargin-right: -8px;\n}\n\n.admonition.example h4 {\nbackground-color: #f2edff;\n}\n\n/* format for admonition variants */\n.admonition.example:before {\nbackground-color: #7C4DFF;\n}\n\n.admonition.note h4 {\nbackground-color: #ecf3ff;\n}\n\n.admonition.note:before {\nbackground-color: #448aff;\n}\n\n.admonition.tip h4 {\nbackground-color: #e5f8f6;\n}\n\n.admonition.tip:before {\nbackground-color: #00bfa5;\n}\n.admonition.success h4 {\nbackground-color: green;\n}\n\n.admonition.success:before {\nbackground-color: green;\n}\n\n.admonition.warning h4 {\nbackground-color: ##fff4e5;\n}\n\n.admonition.warning:before {\nbackground-color: #ff9100;\n}\n\n.admonition.danger h4 {\nbackground-color: #ffe7ec;\n}\n\n.admonition.danger:before {\nbackground-color: #ff1744;\n}\n.admonition p {\nmargin-top: 10px;\n}\n</style></head>\n<body>\n");

	// variables for HTML translation
	int header_level;
	int code_level;
	int admonition_level;
	char *substring;
	char **split;
	char *admonition_type;
	bool building_code_block = false;
	bool building_admonition = false;
	bool building_unordered_list = false;
	int lower_bound;
	int upper_bound;
	int split_index;

	// go through all the string_tokens, which are all just individual lines of the file
	int i = 0;
	while(string_tokens[i] != NULL)
	{
		// case: header
		if(string_tokens[i][0] == '#')
		{	
			// determine level of header
			header_level = determine_header_level(string_tokens[i]);
			printf("Header level found to be %d for line \"%s\"\n", header_level, string_tokens[i]); 
			while(string_tokens[i][header_level] == '#')
			{
	header_level++;
			}

			// add header tag 
			concatenate(&html, &html_len, &html_capacity, "<h");
			insert_char(&html, &html_len, &html_capacity, header_level + '0');
			insert_char(&html, &html_len, &html_capacity, '>');
	
			// add header contents -- this requires the removal of the # characters
			substring = string_substring(string_tokens[i], header_level+1, strlen(string_tokens[i]));
			concatenate(&html, &html_len, &html_capacity, substring);
			free(substring);

			// end the tag
			concatenate(&html, &html_len, &html_capacity, "</h");
			insert_char(&html, &html_len, &html_capacity, header_level + '0');
			concatenate(&html, &html_len, &html_capacity, ">");
			header_level = 0;
		}

		// case: code block
		else if(string_tokens[i][0] == '`')
		{
			code_level = determine_code_level(string_tokens[i]);
			if(code_level == 3)
			{
				printf("Determined line \"%s\" to be a code block delimiter, but nothing was added to the HTML, because this feature is not implemented yet!\n", string_tokens[i]);
				building_code_block = flip_boolean(building_code_block);
			}
			if(building_code_block) concatenate(&html, &html_len, &html_capacity, "<code>");
			else concatenate(&html, &html_len, &html_capacity, "</code>");
		}

		// case: admonition
		else if(string_tokens[i][0] == '!')
		{
			admonition_level = determine_admoninition_level(string_tokens[i]);
			if(admonition_level == 3)
			{
				printf("DEBUG: Determined line \"%s\" to be an admonition delimiter, but nothing was added to the HTML, because this feature is not implemented yet!\n", string_tokens[i]);
				// upon reaching admonition beginning, invert value of building_admonition so as to indicate when
				// we have stopped and started building an admonition. The start and stop of an admonition looks the same
				// except that the start has more text after it.
				building_admonition = flip_boolean(building_admonition);
			}
			printf("%s\n", string_tokens[i]);

			// get the type of admonition -- remember to free this later
			split = split_string(string_tokens[i], " ");
			admonition_type = split[1];
			printf("DEBUG: string_tokens[i] after split to get admonition type: \"%s\"\n", string_tokens[i]);

			if(building_admonition)
			{
				// create div tag including the admonition class and the subclass (e.g. admonition note)
				concatenate(&html, &html_len, &html_capacity, "<div class=\"admonition ");
				concatenate(&html, &html_len, &html_capacity, admonition_type);
				concatenate(&html, &html_len, &html_capacity, "\">\n");

				// add the admonition type in the form of h4 (e.g. <h4>example<h4>)
				concatenate(&html, &html_len, &html_capacity, "<h4>");
				concatenate(&html, &html_len, &html_capacity, admonition_type);

				// add the rest of the title -- this is just everything after the "!!! example " or "!!! note " part
				lower_bound = 4 + strlen(admonition_type); // The +4 skips over the "!!! " part
				                                           // and the strlen(admonition_type) skips over the "example part"
														   // of the "!!! example ". finally since index is 1 smaller, the space
														   // after "example" is ignored
				upper_bound = strlen(string_tokens[i]);    
				printf("DEBUG: found lower bound = %d and upper bound = %d for line \"%s\"\n", lower_bound, upper_bound, string_tokens[i]);
				if(upper_bound > lower_bound)
				{
					// add the rest of the title
					substring = string_substring(string_tokens[i], 4 + strlen(admonition_type), strlen(string_tokens[i])); // the rest of the title
					insert_char(&html, &html_len, &html_capacity, ':'); // since default C (no unicode -- I cannot figure out how to get it to work
					                                                    // on my system with unicode), write it like "example: How to parse markdown"
																		// instead of with an emoji preceding the title
					concatenate(&html, &html_len, &html_capacity, substring); 

					// free memory
					free(substring);
					free(split[0]);
					split_index = 2;
					while(split[split_index] != NULL)
					{
						free(split[split_index]);
						split_index++;
					}
					free(split);
				}
				
				free(admonition_type);

				// close the h4 label tag
				concatenate(&html, &html_len, &html_capacity, "</h4>");
			}
			else concatenate(&html, &html_len, &html_capacity, "</div>");
		}

		// case: bulleted list
		else if(is_unordered_list(string_tokens[i]) && (!building_unordered_list))
		{
			building_unordered_list = flip_boolean(building_unordered_list);
			
			// add the <ul> tag
			if(building_unordered_list) concatenate(&html, &html_len, &html_capacity, "<ul>");
			else concatenate(&html, &html_len, &html_capacity, "</ul>");
		}

		// case: paragraph
		else
		{
			if(!building_unordered_list)
			{
				// add p tag
				concatenate(&html, &html_len, &html_capacity, "<p>");
				concatenate(&html, &html_len, &html_capacity, string_tokens[i]);
				concatenate(&html, &html_len, &html_capacity, "</p>");
			}
			else
			{
				if(building_unordered_list)
				{
					concatenate(&html, &html_len, &html_capacity, "<li>");
					concatenate(&html, &html_len, &html_capacity, string_tokens[i]);
					concatenate(&html, &html_len, &html_capacity, "</li>");
				}
			}
		}

		// go to next token
		insert_char(&html, &html_len, &html_capacity, '\n');
		i++;
	} // end of while



	// terminate and display HTML
	concatenate(&html, &html_len, &html_capacity, "\n</body>\n</html>");
	insert_char(&html, &html_len, &html_capacity, '\0');
	printf("len %d capacity %d\n", html_len, html_capacity);
	printf("%s", html);



	// cleanup
	for(int j = 0; j < i; j++)
		free(string_tokens[j]);
	
	free(string_tokens);
	return 0;
	
}
