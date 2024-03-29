#include "shell.h"
/**
 * get_path - get the path of command
 * @cmnd: command that i get path
 * Return: path the command if found or command it self if not found
 */
char *get_path(char *cmnd)
{
	char *path_env, *path_cpy, *token_dir, *path;
	int len_cmnd, len_token;
	struct stat buf;
	char *cmnd_cpy;

	cmnd_cpy = _strdub(cmnd);
	path_env = _getenv("PATH"); /*get path from enviroment*/
	if (path_env)
	{
		path_cpy = _strdub(path_env); /*need to free*/
		token_dir = _strtok(path_cpy, ":");
		len_cmnd = _strlen(cmnd);
		while (token_dir)
		{
			len_token = _strlen(token_dir); /*length of directory*/
			path = malloc(sizeof(char) * (len_token + len_cmnd + 2));
			_strcpy(path, token_dir);
			_strcat(path, "/");
			_strcat(path, cmnd);
			_strcat(path, "\0");
			if (stat(path, &buf) == 0)
			{
				free(path_cpy);
				free(cmnd_cpy);
				return (path);
			}
			else
			{
				free(path);
				token_dir = _strtok(NULL, ":");
			}
		}
		free(path_cpy);
		if (stat(cmnd, &buf) == 0)
			return (cmnd_cpy);
		free(cmnd_cpy);
		return (NULL);
	}
	return (NULL);
}
