/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:42:09 by erian             #+#    #+#             */
/*   Updated: 2024/12/13 12:34:13 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include "../include/Libft/libft.h"
# include "../include/ft_printf/ft_printf.h"

typedef struct s_pipex
{
	char	*file1;
	char	*file2;
	char	**cmd1;
	char	**cmd2;
	int		fd[2];
}		t_pipex;

/* ************************************************************************** */
/* error.c                                                                    */
/* ************************************************************************** */
void	free_matrix(char **matrix);
void	free_all(t_pipex *data);
void	print_exit(t_pipex *data, char *str);

/* ************************************************************************** */
/* parser.c                                                                   */
/* ************************************************************************** */
void	parse(char **av, t_pipex *data, char **ep);

/* ************************************************************************** */
/* pipex.c                                                                    */
/* ************************************************************************** */
int		main(int ac, char **av, char **ep);

#endif