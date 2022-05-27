/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <gufestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:01:23 by gufestin          #+#    #+#             */
/*   Updated: 2022/05/27 17:08:39 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char *cmd, char **envp)
{
	char	*path;
	int		i;
	char	**split_path;
	char	*path_tmp;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	split_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (split_path[i])
	{
		path_tmp = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(path_tmp, cmd);
		free(path_tmp);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}

void	ft_execve(const char *cmd, char **envp)
{
	char	**split_cmd;
	char	*path;
	int	i;

	split_cmd = ft_split(cmd, ' ');
	path = get_path(split_cmd[0], envp);
	if (execve(path, split_cmd, envp) == -1)
	{
		i = 0;
		while (split_cmd[i])
		{
			free(split_cmd[i]);
			i++;
		}
		free(split_cmd);
		free(path);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	pipex(int outfile, const char *argv[], char **envp, int i)
{
	int		pipefd[2];
	pid_t	child;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	child = fork();
	if (child == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child == 0 && i == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(pipefd[1]);
		ft_execve(argv[2], envp);
	}
	else if (child == 0 && i == 1)
	{
		if (dup2(outfile, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(outfile);
		ft_execve(argv[3], envp);
	}
	else
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(pipefd[0]);
	}
}

int	main(int argc, const char *argv[], char **envp)
{
	int	infile;
	int	outfile;
	int	status;

	if (argc != 5)
	{
		write(2,
	"4 arguments must be given : ./pipex infile cmd1 cmd2 outfile\n", 61);
		exit(EXIT_FAILURE);
	}
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
	{
		write(2, "open fail\n", 10);
		exit(EXIT_FAILURE);
	}
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(infile);
	pipex(outfile, argv, envp, 0);
	pipex(outfile, argv, envp, 1);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
	return (0);
}
