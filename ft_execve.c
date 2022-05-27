/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:46:57 by gufestin          #+#    #+#             */
/*   Updated: 2022/05/27 19:01:05 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_split(char ***split)
{
	int	i;

	i = 0;
	while ((*split)[i])
	{
		free((*split)[i]);
		i++;
	}
	free(*split);
}

static char	*get_path(char *cmd, char **envp)
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
		free(path);
	}
	free_split(&split_path);
	return (0);
}

void	ft_execve(const char *cmd, char **envp)
{
	char	**split_cmd;
	char	*path;

	split_cmd = ft_split(cmd, ' ');
	path = get_path(split_cmd[0], envp);
	if (path)
		execve(path, split_cmd, envp);
	free_split(&split_cmd);
	perror("execve");
	exit(EXIT_FAILURE);
}
