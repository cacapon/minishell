/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:07:28 by dayano            #+#    #+#             */
/*   Updated: 2025/05/02 13:45:05 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int	i;

	printf("=====check function=====");
	printf("argc = %d\n", argc);
	i = 0;
	while (argv[i])
	{
		printf("argv[%d] = %s\n", i, argv[i]);
		i++;
	}
	printf("========================\n");
	if (builtin_pwd(argc, argv, NULL))
		printf("error\n");
	return (0);
}
