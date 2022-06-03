/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimzaoua <yimzaoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:57:37 by yimzaoua          #+#    #+#             */
/*   Updated: 2022/03/24 18:42:49 by yimzaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_ptr(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		free(str[i++]);
	free(str);
}

void	ft_last_cmd(int *fd, int *end, char **av, char **envp)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(av[3], ' ');
	if (!cmd)
	{
		perror("Split Error : ");
		exit (0);
	}
	path = find_path(envp, cmd[0]);
	if (!path)
	{
		write(1, "Path not found", 14);
		exit (0);
	}
	dup2(end[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close (end[1]);
	close (fd[1]);
	if (execve(path, cmd, envp) == -1)
	{
		free_ptr(cmd);
		perror("Execve Error : ");
		exit(0);
	}
}

char	*ft_process(int *fd, int end, char **av, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av[2], 32);
	if (!cmd)
	{
		perror("Split Error : ");
		return (NULL);
	}
	path = find_path(envp, cmd[0]);
	if (!path)
	{
		write(1, "Path not found", 14);
		return (NULL);
	}
	dup2(end, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close (end);
	if (execve(path, cmd, envp) == -1)
	{
		free_ptr(cmd);
		perror("Execve Error : ");
		return (NULL);
	}
	return ("OK");
}

void	pipex(int *fd, char **av, char **envp)
{
	int		end[2];
	pid_t	child;
	char	*error;

	error = "start";
	if (pipe(end) == -1)
	{
		perror("Pipe error : ");
		exit(0);
	}
	child = fork();
	if (child == -1)
	{
		perror ("Fork error : ");
		exit(0);
	}
	if (!child)
		error = ft_process(fd, end[1], av, envp);
	else
	{
		waitpid(child, NULL, 0);
		if (!error)
			exit (0);
		ft_last_cmd(fd, end, av, envp);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	fd[2];
	int	i;

	i = 0;
	if (!envp[i])
	{
		write(1, "Envp Error\n", ft_strlen("Envp Error\n"));
		exit(0);
	}
	if (ac == 5)
	{
		fd[0] = open(av[1], O_RDONLY);
		fd[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[0] == -1 || fd[1] == -1)
		{
			perror("fd error : ");
			return (0);
		}
		pipex(fd, av, envp);
	}
	else
		write(1, "Arguments Error!!\n", 18);
	return (0);
}
