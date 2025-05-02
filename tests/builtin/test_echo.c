/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:39:28 by ttsubo            #+#    #+#             */
/*   Updated: 2025/05/02 21:01:13 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

static size_t	_count_words(char **cmds)
{
	size_t	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

static void	cmds_free(char **cmds)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = _count_words(cmds);
	while (i < length)
		free(cmds[i++]);
	free(cmds);
}

int	main(void)
{
	char	*line;
	char	**cmds;

	while (1)
	{
		line = readline("minish>");
		if (!line)
			break ;
		if (line[0] == '\0')
			continue ;
		cmds = ft_split(line, ' ');
		if (!ft_strncmp(cmds[0], "echo", 4))
			builtin_echo(_count_words(cmds), cmds, NULL);
		cmds_free(cmds);
		free(line);
	}
	free(line);
	return (EXIT_SUCCESS);
}
