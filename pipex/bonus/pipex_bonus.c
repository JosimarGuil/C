#include "../includes/pipex.h"

void	execute_child(char *cmd, char **envp)
{
	char **args;
	char *path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		ft_free_split(args);
		fprintf(stderr, "pipex: invalid command\n");
		exit(EXIT_FAILURE);
	}
	path = get_path(args[0], envp);
	if (!path)
	{
		fprintf(stderr, "pipex: command not found: %s\n", args[0]);
		ft_free_split(args);
		exit(127);
	}
	execve(path, args, envp);
	perror("execve");
	ft_free_split(args);
	free(path);
	exit(EXIT_FAILURE);
}

/* lê do stdin até encontrar LIMITER e grava em .heredoc_tmp */
void	handle_here_doc(char *limiter)
{
	int		fd;
	char	*line;
	size_t	len = 0;
	ssize_t	n;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		error_exit("open .heredoc_tmp");

	write(1, "heredoc> ", 9);
	line = NULL;
	while ((n = getline(&line, &len, stdin)) != -1)
	{
		if (strncmp(line, limiter, strlen(limiter)) == 0
			&& line[strlen(limiter)] == '\n')
			break;
		write(fd, line, n);
		write(1, "heredoc> ", 9);
	}
	free(line);
	close(fd);
}
