/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:35:46 by dayano            #+#    #+#             */
/*   Updated: 2025/04/17 10:29:26 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// unset with no options
// description: delete VALUE
// use case: unset VALUE

static void	_error_mes(char *name, char *mes)
{
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(mes, STDERR_FILENO);
}

static int	is_value(char **value, int value_count, t_env *env)
{
	char	*env_name;
	int		i;

	env_name = get_env_name(env->value);
	if (!env_name)
	{
		ft_putstr_fd("Error: malformed environment entry: ", STDERR_FILENO);
		ft_putendl_fd(env->value, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < value_count)
	{
		if (ft_strcmp(value[i], env_name) == 0)
		{
			free(env_name);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	free(env_name);
	return (EXIT_FAILURE);
}

static void	unset_values(char **value, int value_count, t_env **env_lst)
{
	t_env	*current;
	t_env	*next;

	if (!env_lst || !*env_lst)
		return ;
	current = *env_lst;
	while (current)
	{
		next = current->next;
		if (!is_value(value, value_count, current))
			remove_env_node(env_lst, current);
		current = next;
	}
}

int	builtin_unset(int argc, char *argv[], t_minish *minish)
{
	char	**values;
	int		values_count;

	if (argc < 2)
	{
		_error_mes(argv[0], ": wrong argument\n");
		return (EXIT_FAILURE);
	}
	values = &argv[1];
	values_count = argc - 1;
	unset_values(values, values_count, &minish->env);
	return (EXIT_SUCCESS);
}
