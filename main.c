/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <gufestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:01:23 by gufestin          #+#    #+#             */
/*   Updated: 2022/05/27 18:54:29 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	main_init(int argc)
{
	if (argc != 5)
	{
		write(2, "4 arguments must be given : \
		./pipex infile cmd1 cmd2 outfile\n", 61);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, const char *argv[], char **envp)
{
	int	infile;
	int	outfile;
	int	status;

	main_init(argc);
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
