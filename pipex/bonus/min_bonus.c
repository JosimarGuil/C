#include "../includes/pipex.h"

static int	open_infile(char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("open infile");
	return fd;
}

static int	open_outfile(char *filename, int append)
{
	int fd;
	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error_exit("open outfile");
	return fd;
}

/* ./pipex infile cmd1 cmd2 ... cmdn outfile
   ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn outfile */
int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	infile;
	int	outfile;
	int	fd[2];
	pid_t	pid;
	int	here_doc;

	if (argc < 5)
	{
		fprintf(stderr, "Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n");
		fprintf(stderr, "   or: ./pipex here_doc LIMITER cmd1 ... cmdn file2\n");
		exit(EXIT_FAILURE);
	}

	here_doc = (strcmp(argv[1], "here_doc") == 0);
	if (here_doc)
	{
		handle_here_doc(argv[2]);
		infile = open(".heredoc_tmp", O_RDONLY);
		outfile = open_outfile(argv[argc - 1], 1);
		i = 3;
	}
	else
	{
		infile = open_infile(argv[1]);
		outfile = open_outfile(argv[argc - 1], 0);
		i = 2;
	}

	dup2(infile, STDIN_FILENO);
	close(infile);

	while (i < argc - 2)
	{
		if (pipe(fd) == -1)
			error_exit("pipe");
		pid = fork();
		if (pid == -1)
			error_exit("fork");
		if (pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			execute_child(argv[i], envp);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			waitpid(pid, NULL, 0);
		}
		i++;
	}
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute_child(argv[argc - 2], envp);
	return (0);
}
