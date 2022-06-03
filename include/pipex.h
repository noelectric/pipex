/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimzaoua <yimzaoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:59:58 by yimzaoua          #+#    #+#             */
/*   Updated: 2022/03/24 18:45:26 by yimzaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include  <fcntl.h>
# include  <stdio.h>
# include  <string.h>
# include  <unistd.h>
# include  <sys/wait.h>
# include  <stdlib.h>

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*find_path(char *envp[], char *str);
void	pipex(int *fd, char **av, char **envp);
void	child_two(int f2, char *cmd2, int end, char *envp[]);
void	child_one(int f1, char *cmd1, int end, char *envp[]);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	free_ptr(char **str);
size_t	ft_strlen(char const *str);
int		ft_strncmp( const char *s1, const char *s2, size_t length);

#endif
