/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:19:11 by dayano            #+#    #+#             */
/*   Updated: 2025/04/29 11:25:22 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	builtin_env(int argc, char **argv, t_minish *minish)
{
	t_env	*next;
	t_env	*current;

	if (argc != 1)
		return (error_mes(argv[0], "too many arguments"), EXIT_FAILURE);
	current = minish->env;
	while (current)
	{
		next = current->next;
		if (current->is_exported)
			if (printf("%s=%s\n", current->key, current->value) < 0)
				handle_error_and_exit("printf", minish);
		current = next;
	}
	return (EXIT_SUCCESS);
}
