#include "main.h"

/**
 * _getexit - exit shell
 * @info: struct containing arguements
 * Return: exit stattus exit status 0
 */
int _getexit(info_t *info)
{
	int check;

	if (info->argv[1])
	{
		check = _erroratoi(info->argv[1]);
		if (check == -1)
		{
			info->status = 2;
			prints_error(info, "Enter valid number: ");
			_putstr(info->argv[1]);
			_putscharacter('\n');
			return (1);
		}
		info->err_num = _erroratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * _changecd - change process directory
 * @info: structure containing potential arguements
 *
 * Return: Always 0
 */
int _changecd(info_t *info)
{
	char *s, *directory, buffer[1024];
	int child_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("Get: >>getcwd error message<<\n");
	if (!info->argv[1])
	{
		directory = _getenviron(info, "home=");
		if (!directory)
			child_ret =
				chdir((directory = _getenviron(info, "pwd=")) ? directory : "/");
		else
		child_ret = chdir(directory);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenviron(info, "oldpwd"))
		{
			_puts(s);
			_putscharacter('\n');
			return (1);
			}
			_puts(_getenviron(info, "oldpwd=")), _putchar('\n');
			child_ret =
				chdir((directory = _getenviron(info, "oldpwd=")) ? directory : "/");
				}
				else
				child_ret = chdir(info->argv[1]);
				if (child_ret == -1)
				{
				prints_error(info, " can't change change cd");
				_putstr(info->argv[1]), _putscharacter('\n');
				}
				else
				{
					_setsenviron(info, "oldpwd", _getenviron(info, "pwd="));
					_setsenviron(info, "pwd", getcwd(buffer, 1024));
				}
				return (0);
}
/**
 * _cdc - changes current directory of the process
 * @info: structure containing arguements
 *
 * Return: always 0
 */
int _cdc(info_t *info)
{
	char **arr;

	arr = info->argv;
	_puts("Functions not yet implemented \n");
	if (0)
		_puts(*arr);
	return (0);
}



