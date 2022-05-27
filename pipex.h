/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <gufestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:02:51 by gufestin          #+#    #+#             */
/*   Updated: 2022/05/27 18:48:36 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

void	pipex(int outfile, const char *argv[], char **envp, int i);
void	ft_execve(const char *cmd, char **envp);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	**ft_split(char const *src, char c);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
