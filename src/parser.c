/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:37:16 by erian             #+#    #+#             */
/*   Updated: 2024/12/15 15:00:18 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_paths(char **ep)
{
	int	i;

	i = 0;
	if (!ep)
		return (NULL);
	while (ep[i] != NULL)
	{
		if (ft_strncmp(ep[i], "PATH=", 5) == 0)
			return (ep[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*search_in_paths(char *cmd, char **paths)
{
	int		i;
	char	*part_path;
	char	*final_path;

	i = 0;
	while (paths[i] != NULL)
	{
		part_path = ft_strjoin(paths[i], "/");
		if (!part_path)
		{
			i++;
			continue ;
		}
		final_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (final_path && access(final_path, F_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (NULL);
}

static char	*find_path(char *cmd, char **ep)
{
	char	*path_env;
	char	**paths;
	char	*final_path;

	path_env = get_paths(ep);
	if (!cmd || !path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	final_path = search_in_paths(cmd, paths);
	free_matrix(paths);
	return (final_path);
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
