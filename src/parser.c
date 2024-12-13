/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:37:16 by erian             #+#    #+#             */
/*   Updated: 2024/12/13 12:39:01 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_paths(char **ep)
{
	int	i;

	i = 0;
	if (!ep)
		return (NULL);
	while (ep[i])
	{
		if (ft_strncmp(ep[i], "PATH=", 5) == 0)
			return (ep[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*find_path(char *cmd, char **ep)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	paths = ft_split(get_paths(ep), ':');
	if (!cmd || !paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = part_path ? ft_strjoin(part_path, cmd) : NULL;
		free(part_path);
		if (path && access(path, F_OK) == 0)
		{
			free_matrix(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_matrix(paths);
	return (NULL);
}

static int	get_cmd(char *av, char ***cmd, char **ep)
{
	char	*full_path;

	if (!av || !cmd || !ep)
		return (0);
	*cmd = ft_split(av, ' ');
	if (!*cmd)
		return (0);
	full_path = find_path((*cmd)[0], ep);
	if (full_path)
	{
		free((*cmd)[0]);
		(*cmd)[0] = full_path;
		return (1);
	}
	free_matrix(*cmd);
	return (0);
}

void	parse(char **av, t_pipex *data, char **ep)
{
	if (!av || !data || !ep)
		print_exit(data, "Invalid input\n");
	data->file1 = ft_strdup(av[1]);
	data->file2 = ft_strdup(av[4]);
	if (!data->file1 || !data->file2)
		print_exit(data, "File allocation error\n");
	if (!get_cmd(av[2], &data->cmd1, ep) || !get_cmd(av[3], &data->cmd2, ep))
		print_exit(data, "Command allocation error\n");
}
