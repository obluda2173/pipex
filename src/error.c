/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:43:38 by erian             #+#    #+#             */
/*   Updated: 2024/12/21 12:04:35 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_all(t_pipex *data)
{
	if (!data)
		return ;
	if (data->file1)
	{
		free(data->file1);
		data->file1 = NULL;
	}
	if (data->file2)
	{
		free(data->file2);
		data->file2 = NULL;
	}
	if (data->cmd1)
	{
		free_matrix(data->cmd1);
		data->cmd1 = NULL;
	}
	if (data->cmd2)
	{
		free_matrix(data->cmd2);
		data->cmd2 = NULL;
	}
	free(data);
}

void	print_exit(t_pipex *data, char *str)
{
	ft_putstr_fd(str, 1);
	free_all(data);
	exit(1);
}
