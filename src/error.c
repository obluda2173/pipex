/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:43:38 by erian             #+#    #+#             */
/*   Updated: 2024/09/21 11:52:07 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_matrix(char **matrix)
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

void	error_free(t_pipex *data)
{
	if (!data)
		return ;
	free(data->file1);
	free(data->file2);
	free_matrix(data->cmd1);
	free_matrix(data->cmd2);
	free(data);
}

void	print_exit(t_pipex *data, char *str)
{
	ft_printf("%s", str);
	error_free(data);
	exit(1);
}
