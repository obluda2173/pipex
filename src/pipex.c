/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:40:31 by erian             #+#    #+#             */
/*   Updated: 2024/09/20 18:01:24 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	parse(char **av, t_pipex *data)
{
	data->file1 = ft_strdup(av[1]);
	data->file2 = ft_strdup(av[4]);
	if (!data->file1 || !data->file2)
		print_exit(data, "File allocation error\n");
	if (!get_cmd(av[2], &data->cmd1) || !get_cmd(av[3], &data->cmd2))
		print_exit(data, "Command allocation error\n");
}

static int	get_cmd(char *av, char ***cmd)
{
	char	*tmp;

	*cmd = ft_split(av, ' ');
	if (!*cmd)
		return (0);
	tmp = strdup((*cmd)[0]);
	free((*cmd)[0]);
	(*cmd)[0] = ft_strjoin("/bin/", tmp);
	free(tmp);
	return (1);
}

int	main(int ac, char **av)
{
	t_pipex	*data;

	if (ac != 5)
	{
		ft_printf("Incorect amount of arguments\n");
		exit(1);
	}
	data = malloc(sizeof(t_pipex));
	if (!data)
	{
		ft_printf("Memory allocation error\n");
		exit(1);
	}
	parse(av, data);
	check(data);
}
