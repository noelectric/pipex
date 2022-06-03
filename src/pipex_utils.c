/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimzaoua <yimzaoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:57:33 by yimzaoua          #+#    #+#             */
/*   Updated: 2022/03/24 18:47:22 by yimzaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_paths(char *envp[])
{
	int		i;
	char	*paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = envp[i] + 5;
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*find_path(char *envp[], char *str)
{
	int		i;
	char	*paths;
	char	**mypaths;
	char	*final_paths;
	char	*cmd;

	i = 0;
	if (!(access(str, X_OK)))
		return (str);
	paths = ft_paths(envp);
	mypaths = ft_split(paths, ':');
	while (mypaths[i])
	{
		cmd = ft_strjoin(mypaths[i], "/");
		final_paths = ft_strjoin(cmd, str);
		if (!(access(final_paths, X_OK)))
		{
			free_ptr(mypaths);
			return (free(cmd), final_paths);
		}
		free(cmd);
		free(final_paths);
		i++;
	}
	return (free_ptr(mypaths), NULL);
}
