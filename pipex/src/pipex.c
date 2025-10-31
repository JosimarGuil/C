#include "pipex.h"

void	first_child(int *fd, char **argv, char **envp)
{
	int		infile;
	char	**cmd;
	char	*path;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		error_exit("open infile");

	if (dup2(infile, STDIN_FILENO) == -1)
		error_exit("dup2 infile");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error_exit("dup2 pipe write");

	/* fechar descritores desnecessários */
	if (close(fd[0]) == -1)
		perror("close");
	if (close(fd[1]) == -1)
		perror("close");
	if (close(infile) == -1)
		perror("close");

	cmd = ft_split(argv[2], ' ');
	if (!cmd || !cmd[0])
	{
		ft_free_split(cmd);
		fprintf(stderr, "pipex: invalid command\n");
		exit(EXIT_FAILURE);
	}

	path = get_path(cmd[0], envp);
	if (!path)
	{
		fprintf(stderr, "pipex: command not found: %s\n", cmd[0]);
		ft_free_split(cmd);
		exit(127);
	}
	execve(path, cmd, envp);

	/* Se chegou aqui, execve falhou */
	perror("execve");
	ft_free_split(cmd);
	free(path);
	exit(EXIT_FAILURE);
}

void	second_child(int *fd, char **argv, char **envp)
{
	int		outfile;
	char	**cmd;
	char	*path;

	outfile = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (outfile < 0)
		error_exit("open outfile");

	if (dup2(fd[0], STDIN_FILENO) == -1)
		error_exit("dup2 pipe read");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		error_exit("dup2 outfile");

	/* fechar descritores desnecessários */
	if (close(fd[0]) == -1)
		perror("close");
	if (close(fd[1]) == -1)
		perror("close");
	if (close(outfile) == -1)
		perror("close");

	cmd = ft_split(argv[3], ' ');
	if (!cmd || !cmd[0])
	{
		ft_free_split(cmd);
		fprintf(stderr, "pipex: invalid command\n");
		exit(EXIT_FAILURE);
	}

	path = get_path(cmd[0], envp);
	if (!path)
	{
		fprintf(stderr, "pipex: command not found: %s\n", cmd[0]);
		ft_free_split(cmd);
		exit(127);
	}
	execve(path, cmd, envp);

	/* Se chegou aqui, execve falhou */
	perror("execve");
	ft_free_split(cmd);
	free(path);
	exit(EXIT_FAILURE);
}

void	error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
