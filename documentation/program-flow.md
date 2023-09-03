\tableofcontents

# Note

This document reviews the entire main source code as you see it, from start to finish. 

It will explain the procedure that is followed in plain English, so as to provide a more clear understanding, compared to just reading the code and the comments explicitly. As it happens, sometimes the exact intention behind and circumstances for which code was written the way it is written can be lost or otherwise not fully embodied by just the individual statements and comments alone.

# Function Definitions

**NOTE:** for right now, the functions remain defined in the beginning of the program. Later, this may be changed. For the moment, there are no plans to move the functions into a separate libsealightmarkdown.h header file.

## is\_substring 

`bool is_substring(char *source, char *sub)` is returns true if a string (sub) is a substring of another string (source).

**What it is used for:** to determine if a token (1) is itself italic/bold/bold italic, (2) marks the beginning of a section of italic/bold/bold italic text, or (3) marks the end of a section of italic/bold/bold italic text, it must be determined if a token contains the special delimiters corresponding to italic/bold/bold italic Markdown text. 

This is evident in the [pre-processing section](#pre-processing), with lines such as `if(is_substring(split[split_index], "***"))` for determining if Markdown formatting symbols need to be replaced with their HTML equivalents.

**NOTE:** this function is often used in the following pattern. The reason for this is due to the way that the Markdown delimiters for italic, bold, and bold italic text overlap. For example, since italic text uses just one asterisk to delimit the text, if you check for italic text first, then bold text, you will always overwrite the changes made when handling the italic text, because bold Markdown text uses two asterisks to delimit the bold text.

1. italic bold
2. bold
3. italic



