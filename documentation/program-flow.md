# Note

This document reviews the entire main source code as you see it, from start to finish. 

It will explain the procedure that is followed in plain English, so as to provide a more clear understanding, compared to just reading the code and the comments explicitly. As it happens, sometimes the exact intention behind and circumstances for which code was written the way it is written can be lost or otherwise not fully embodied by just the individual statements and comments alone.

# Function Definitions

**NOTE:** for right now, the functions remain defined in the beginning of the program. Later, this may be changed. For the moment, there are no plans to move the functions into a separate libsealightmarkdown.h header file.

## is\_substring 

`bool is_substring(char *source, char *sub)` returns true if a string (sub) is a substring of another string (source).

**What it is used for:** to determine if a token (1) is itself italic/bold/bold italic, (2) marks the beginning of a section of italic/bold/bold italic text, or (3) marks the end of a section of italic/bold/bold italic text, it must be determined if a token contains the special delimiters corresponding to italic/bold/bold italic Markdown text. 

- **Note:** the information above also applies to other formatting features, such as underline and highlight; however, the checks for whether or not text needs underline and highlight tags are not joined by if-else if-else cases, instead they are individual if cases.

This is evident in the [pre-processing section](#pre-processing), with lines such as `if(is_substring(split[split_index], "***"))` for determining if Markdown formatting symbols need to be replaced with their HTML equivalents.

**NOTE:** this function is often used in the following pattern. The reason for this is due to the way that the Markdown delimiters for italic, bold, and bold italic text overlap. For example, since italic text uses just one asterisk to delimit the text, if you check for italic text first, then bold text, you will always overwrite the changes made when handling the italic text, because bold Markdown text uses two asterisks to delimit the bold text.

1. italic bold
2. bold
3. italic

## string\_contains\_char

## insert\_char

`void insert_char(char **string_ptr, int *len, int *capacity, char c)` inserts a character into a dynamically allocated string at index `(*len)`. `char **string_ptr` is the string into which the character will be inserted. It requires the parameters `int *len` and `int *capacity` so that it may check if there is enough memory allocated to the string for the character `char c` to be inserted into it. This function is really just meant to append a character to the end of of a string, or to overwrite a string, starting from whichever value you choose for `len`. ==You should not use this function to insert a character at a particular index==, for that just use `string[i] = 'c';`

## concatenate

`void concatenate(char **string_ptr, int *len, int *capacity, char *operand)` concatenates the string `char *operand` to the end of the string `(*string_ptr)`. It is a version of `strcat` that will expand the memory automatically. 

**Note:** this function requires [insert\_char](#insert\_char) to be defined, as this function just repeatedly calls `insert_char`, iterating through the individual characters of `operand`.

## split\_string

`char** split_string(char *source, char *delimiter)` returns a NULL-terminated array of strings, where each member of the array is a substring of `source` until individual instances of `delimiter` are encountered within `source`. 

**Note:** because the array returned by the function is NULL-terminated, you have to iterate through it with a while loop. Of course, you can also then use the while loop to determine its length.

Please remember to free the memory held by the array that the function returns!

## determine\_header\_level

`int determine_header_level(char *source)` returns an integer corresponding to the amount of times that the '#' character appears concurrently starting from the 0th index in `source`. 

This function exists just to make the code a little easier to read. Beyond that, it exists to determine if a header tag should be a h1 or h2 tag.



