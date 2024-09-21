/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:37:16 by erian             #+#    #+#             */
/*   Updated: 2024/09/21 15:23:08 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_start(t_pipex *data)
{
	if (access(data->cmd1[0], X_OK) == -1)
		print_exit(data, "Command 1 is not executable\n");
	if (access(data->cmd2[0], X_OK) == -1)
		print_exit(data, "Command 2 is not executable\n");
	if (access(data->file1, R_OK) == -1)
		print_exit(data, "Cannot read from infile\n");
	if (access(data->file2, W_OK) == -1 && access(data->file2, F_OK) == 0)
		print_exit(data, "Cannot write in outfile\n");
	data->fd[0] = open(data->file1, O_RDONLY);
	data->fd[1] = open(data->file2, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->fd[0] == -1 || data->fd[1] == -1)
		print_exit(data, "File open error\n");
}

static void	close_all(t_pipex *data, int pipe[])
{
	close(pipe[0]);
	close(pipe[1]);
	close(data->fd[0]);
	close(data->fd[1]);
}

static void	child2(t_pipex *data, char **ep, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_exit(data, "Fork failed\n");
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (execve(data->cmd2[0], data->cmd2, ep) == -1)
			print_exit(data, "Execution command 2 fails\n");
	}
	waitpid(pid, NULL, 0);
	close_all(data, fd);
}

void	pipex(t_pipex *data, char **ep)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		print_exit(data, "Creation of pipe failed\n");
	pid = fork();
	if (pid == -1)
		print_exit(data, "Fork failed\n");
	if (pid == 0)
	{
		dup2(data->fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (execve(data->cmd1[0], data->cmd1, ep) == -1)
			print_exit(data, "Execution command 1 fails\n");
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		child2(data, ep, fd);
	}
}
