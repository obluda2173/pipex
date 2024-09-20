/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:37:16 by erian             #+#    #+#             */
/*   Updated: 2024/09/20 21:14:34 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check(t_pipex *data)
{
	if (!access(data->cmd1[0], X_OK) || !access(data->cmd2[0], X_OK))
		print_exit(data, "Command is not valid\n");
	if (!access(data->file1, R_OK))
		print_exit(data, "Can not read from infile\n");
	if (!access(data->file2, W_OK) && access(data->file2, F_OK) == 0)
		print_exit(data, "Can not write in outfile\n");
	data->fd[0] = open(data->file1, O_RDONLY);
	data->fd[1] = open(data->file2, O_WRONLY | O_TRUNC | O_CREAT, 0644);
}
