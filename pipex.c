/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <gufestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:02:24 by gufestin          #+#    #+#             */
/*   Updated: 2022/05/27 19:52:17 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_child(int pipefd[2], const char *argv[], char **envp)
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

static void	second_child(int pipefd[2],
		int outfile, const char *argv[], char **envp)
{
	close(pipefd[1]);
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(outfile);
	ft_execve(argv[3], envp);
}

static void	ft_parent(int pipefd[2])
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
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
		first_child(pipefd, argv, envp);
	else if (child == 0 && i == 1)
		second_child(pipefd, outfile, argv, envp);
	else
		ft_parent(pipefd);
}
