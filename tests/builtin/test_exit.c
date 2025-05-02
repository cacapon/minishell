/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:48:09 by dayano            #+#    #+#             */
/*   Updated: 2025/05/02 21:01:03 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

// builtin_exit argcは手動で操作する必要あり
int	main(void)
{
	char	*line;
	char	**strings_line;

	while (1)
	{
		line = readline("minish>");
		if (!line)
			break ;
		if (strcmp("exit", line) == 0)
		{
			strings_line = ft_split(line, ' ');
			if (builtin_exit(1, strings_line, NULL) == 1)
			{
				printf("error\n");
				free(line);
				exit(EXIT_FAILURE);
			}
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}
