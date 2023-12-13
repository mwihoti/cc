#include "main.h"

/**
 * _myexit - exit shell
 * @info: struct containing arguements
 * Return: exit stattus exit status 0
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Enter valid number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * _mycd - change process directory
 * @info: structure containing potential arguements
 *
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int child_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("Get: >>getcwd error message<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "home=");
		if (!dir)
			child_ret =
				chdir((dir = _getenv(info, "pwd=")) ? dir : "/");
		else
		child_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "oldpwd"))
		{
			_puts(s);
			_putchar('\n');
			return (1);
			}
			_puts(_getenv(info, "oldpwd=")), _putchar('\n');
			child_ret =
				chdir((dir = _getenv(info, "oldpwd=")) ? dir : "/");
				}
				else
				child_ret = chdir(info->argv[1]);
				if (child_ret == -1)
				{
				print_error(info, " can't change change cd");
				_eputs(info->argv[1]), _eputchar('\n');
				}
				else
				{
					_setenv(info, "oldpwd", _getenv(info, "pwd="));
					_setenv(info, "pwd", getcwd(buffer, 1024));
				}
				return (0);
}
/**
 * _myhelp - changes current directory of the process
 * @info: structure containing arguements
 *
 * Return: always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Functions not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}



