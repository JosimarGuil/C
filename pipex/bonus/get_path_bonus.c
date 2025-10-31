#include "../includes/pipex.h"

char *join_path(const char *dir, const char *cmd)
{
	size_t len;
	char *full;

	if (!dir || !cmd)
		return (NULL);
	len = strlen(dir) + 1 + strlen(cmd) + 1;
	full = malloc(len);
	if (!full)
		return (NULL);
	strcpy(full, dir);
	strcat(full, "/");
	strcat(full, cmd);
	return (full);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*path_env;
	char	*full;

	if (!cmd)
		return (NULL);

	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
		{
			full = malloc(strlen(cmd) + 1);
			if (!full)
				return (NULL);
			strcpy(full, cmd);
			return (full);
		}
		write(2, "pipex: ", 7);
		perror(cmd);
		return (NULL);
	}

	i = 0;
	path_env = NULL;
	while (envp && envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break;
		}
		i++;
	}
	if (!path_env)
	{
		fprintf(stderr, "pipex: PATH not found\n");
		return (NULL);
	}

	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);

	i = 0;
	while (paths[i])
	{
		full = join_path(paths[i], cmd);
		if (!full)
		{
			ft_free_split(paths);
			return (NULL);
		}
		if (access(full, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full);
		}
		free(full);
		i++;
	}
	fprintf(stderr, "pipex: command not found: %s\n", cmd);
	ft_free_split(paths);
	return (NULL);
}
