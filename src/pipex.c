/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:40:31 by erian             #+#    #+#             */
/*   Updated: 2024/09/21 14:25:40 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_cmd(char *av, char ***cmd)
{
	char	*tmp;
	char	*full_path;

	*cmd = ft_split(av, ' ');
	if (!*cmd)
		return (0);
	tmp = (*cmd)[0];
	full_path = ft_strjoin("/bin/", tmp);
	if (access(full_path, X_OK) == 0)
	{
		(*cmd)[0] = full_path;
        return 1;
	}
	free(full_path);
	full_path = ft_strjoin("/usr/bin/", tmp);
	if (access(full_path, X_OK) == 0)
	{
		(*cmd)[0] = full_path;
        return 1;
	}
	free(full_path);
	return (0);
}

static void	parse(char **av, t_pipex *data)
{
	data->file1 = ft_strdup(av[1]);
	data->file2 = ft_strdup(av[4]);
	if (!data->file1 || !data->file2)
		print_exit(data, "File allocation error\n");
	if (!get_cmd(av[2], &data->cmd1) || !get_cmd(av[3], &data->cmd2))
		print_exit(data, "Command allocation error\n");
}

int	main(int ac, char **av, char **ep)
{
	t_pipex	*data;

	if (ac != 5)
		print_exit(NULL, "Incorect amount of arguments\n");
	data = malloc(sizeof(t_pipex));
	if (!data)
		print_exit(NULL, "Memory allocation error\n");
	parse(av, data);
	check_start(data);
	pipex(data, ep);
	error_free(data);
	return (0);
}
