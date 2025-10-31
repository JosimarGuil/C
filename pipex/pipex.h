#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

/* Funções principais */
void	first_child(int *fd, char **argv, char **envp);
void	second_child(int *fd, char **argv, char **envp);

/* Funções auxiliares */
char	*get_path(char *cmd, char **envp);
/* ft_split: recebe string e separador, retorna array terminado em NULL */
char	**ft_split(char *str, char sep);
void	error_exit(char *msg);
void	ft_free_split(char **arr);

/* utilitários internos */
char	*join_path(const char *dir, const char *cmd);

/* bonus */
void	execute_child(char *cmd, char **envp);
void	handle_here_doc(char *limiter);

#endif