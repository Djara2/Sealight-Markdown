# Sealight Markdown

Sealight Markdown is a utility that parses Markdown and generates equivalent HTML. It is written in C and designed to be a simple and lightweight tool, hence the pun-name "Sealight Markdown."

As Sealight Markdown is intended to be lightweight and simple, it is also designed so that it can be compiled without any fuss. At the moment, all relevant code is contained within a single .c file; no additional libraries or header files are required. If you have a C compiler and the source code, you can compile Sealight Markdown with a simple `gcc sealight.c -o sealight`, if you are using GCC. 

- In the future this may be subject to change where an additional header file containing all the functions I have defined will be required to compile the project; however, even then it will remain a simple compilation process, and instructions on exactly how to compile the project for all operating systems will be included in this repository.

Sealight Markdown is inspired by the Markdown converter in the Joplin application, because Joplin is the application I use to take my notes. Likewise, Sealight Markdown is designed to accept Markdown files that are formatted how one would format them in Joplin. This also means that Sealight Markdown is made to recognize common Markdown extensions that one may already be using with Joplin. Check out the [Features](#features) section for more on this.

# Notice

Because Sealight Markdown is written in C, and is also my first C project, it does not support Unicode characters. It can only be used with the regular 256 ASCII characters supported by C using the regular data types.

I am aware of the `wchar_t` data type; however, I have still not gotten it to work on any other programs I have written in C. This will be addressed later.

# Features

This section goes over features that are "unique" to this project; baseline features such as picking up on header tags are not included.

## Admonitions

Joplin's Markdown renderer is compatible with admonitions, likewise Sealight Markdown will detect and convert admonitions in Markdown files passed to it. 

The expected formatting for an admonition is the same in Sealight Markdown as it is in Joplin with the admonition extension:
```md
!!! example How to format an admonition
This is the body text of the admonition

# You can put headers inside of admonitions

You can also put code inside of admonitions
```c
int main(void)
{
	printf("Sealight Markdown is my first project in C.\n");
	return 0;
}
!!!

You end an admonition by writing !!! followed by a newline.
```

## Automatic Generation of Table of Contents

All you have to do is write `[toc]` at the top of the file, and your output HTML will have a table of contents with clickable links to navigate throughout the document

```md
[toc]

# Introduction

The rendered HTML will have links to the Introduction, Purpose, and Conclusion sections of this document.

# Purpose

To save time of course!

# Conclusion

I am passionate about Markdown and this project.
```
