#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
	{
		fprintf(stderr, "Usage: ./pipex file1 cmd1 cmd2 file2\n");
		exit(EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
		error_exit("pipe");

	pid1 = fork();
	if (pid1 == -1)
		error_exit("fork");
	if (pid1 == 0)
		first_child(fd, argv, envp);

	pid2 = fork();
	if (pid2 == -1)
		error_exit("fork");
	if (pid2 == 0)
		second_child(fd, argv, envp);

	/* Parent closes both ends and waits children */
	if (close(fd[0]) == -1)
		perror("close");
	if (close(fd[1]) == -1)
		perror("close");

	if (waitpid(pid1, NULL, 0) == -1)
		perror("waitpid");
	if (waitpid(pid2, NULL, 0) == -1)
		perror("waitpid");

	return (0);
}
