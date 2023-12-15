#include "main.h"

/**
 * _erratoi - converts string to integer
 * @s: string to be converted
 *
 * Return: 0 if no numbers in string, else 1
 */

int _erroratoi(char *s)
{
	int m = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (m = 0; s[m] != '\0'; m++)
	{
		if (s[m] >= '0' && s[m] <= '9')
		{
			result *= 10;
			result += (s[m] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * prints_error - prints error message
 * @info: parameter
 * @estr: string containing error
 *
 * Return: 0 if no digit on string on error -1
 */
void prints_error(info_t *info, char *estr)
{
	_putstr(info->fname);
	_putstr(": ");
	prints_d(info->line_count, STDERR_FILENO);
	_putstr(": ");
	_putstr(info->argv[0]);
	_putstr(": ");
	_putstr(estr);
}

/**
 * prints_d - function prints decimal number
 * @input: the input
 * @fd: file descriptor
 *
 * Return: number of printed characters
 */
int prints_d(int input, int fd)
{
	int (*__putchars)(char) = _putchar;
	int m, counts = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchars = _putscharacter;
	if (input < 0)
	{
		_abs_ = -input;
		__putchars('-');
		counts++;
	}
	else
	{
		_abs_ = input;
		current = _abs_;
	}
		for (m = 1000000000; m > 1; m /= 10)
		{
			if (_abs_ / m)
			{
				__putchars('0' + current / m);
				counts++;
			}
			current %= m;
		}
		__putchars('0' + current);
		counts++;

		return (counts);
}

/**
 * convertsnumber - converter function
 * @num: number
 * @base: base
 * @flags: arguement flags
 *
 * Return: string
 */

char *convertsnumber(long int num, int base, int flags)
{
	static char *arr;
	static char buffer[50];
	char sign = 0;
	char *pointer;
	unsigned long number = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		number = -num;
		sign = '-';
	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';

	do {
		*--pointer = arr[number % base];
		number /= base;
	} while (number != 0);

	if (sign)
		*--pointer = sign;
	return (pointer);
}

/**
 * removes_comments - replaces instance of '#' to '\0'
 * @buf: address string to modify
 *
 * Return: Always 0;
 */

void removes_comments(char *buf)
{
	int s;

	for (s = 0; buf[s] != '\0'; s++)
		if (buf[s] == '#' && (!s || buf[s - 1] == ' '))
		{
			buf[s] = '\0';
			break;
		}
}



