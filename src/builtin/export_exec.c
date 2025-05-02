/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:11:06 by ttsubo            #+#    #+#             */
/*   Updated: 2025/05/01 14:04:19 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	_update_value(char *key, char *value, t_minish *minish)
{
	t_env	*node;

	if (!is_valid_key(key))
		return (export_err_invalid("minish", key), EXIT_FAILURE);
	node = get_env_node(minish->env, key);
	if (!node)
		return (EXIT_FAILURE);
	if (node->value)
		free(node->value);
	node->value = ft_strdup(value);
	node->is_exported = 1;
	return (EXIT_SUCCESS);
}

static int	_append_value(char *key, char *value, t_minish *minish)
{
	t_env	*node;
	char	*join_str;

	if (!is_valid_key(key))
		return (export_err_invalid("minish", key), EXIT_FAILURE);
	node = get_env_node(minish->env, key);
	join_str = NULL;
	if (!node)
		return (EXIT_FAILURE);
	if (node->value)
		join_str = ft_strjoin(node->value, value);
	else
		join_str = ft_strdup(value);
	if (!join_str)
		return (EXIT_FAILURE);
	free(node->value);
	node->value = join_str;
	node->is_exported = 1;
	return (EXIT_SUCCESS);
}

static int	_add_key_value(char *key, char *value, t_minish *minish)
{
	t_env	*node;

	if (!is_valid_key(key))
		return (export_err_invalid("minish", key), EXIT_FAILURE);
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (EXIT_FAILURE);
	node->key = ft_strdup(key);
	if (!node->key)
		return (free(node), EXIT_FAILURE);
	node->value = ft_strdup(value);
	if (!node->value)
		return (free(node->key), free(node), EXIT_FAILURE);
	node->is_exported = 1;
	add_env_back(&minish->env, node);
	return (EXIT_SUCCESS);
}

static int	_add_key(char *key, t_minish *minish)
{
	t_env	*node;

	if (!is_valid_key(key))
		return (export_err_invalid("minish", key), EXIT_FAILURE);
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (EXIT_FAILURE);
	node->key = ft_strdup(key);
	if (!node->key)
		return (free(node), EXIT_FAILURE);
	node->value = NULL;
	node->is_exported = 0;
	add_env_back(&minish->env, node);
	return (EXIT_SUCCESS);
}

int	export_exec(int argc, char **argv, t_minish *minish)
{
	int					i;
	char				*key;
	char				*value;
	t_export_exec_bool	bools;

	i = 1;
	while (i < argc)
	{
		split_key_value(argv[i], &key, &value);
		bools.exists = has_env_key(minish->env, key);
		bools.has_plus = ft_strnstr(argv[i], "+=", ft_strlen(argv[i])) != NULL;
		bools.has_eq = ft_strchr(argv[i], '=') != NULL;
		if (bools.exists && bools.has_plus)
			_append_value(key, value, minish);
		else if (bools.exists && !bools.has_plus && bools.has_eq)
			_update_value(key, value, minish);
		else if (!bools.exists && (bools.has_plus || bools.has_eq))
			_add_key_value(key, value, minish);
		else if (!bools.exists)
			_add_key(key, minish);
		free(key);
		free(value);
		i++;
	}
	return (EXIT_SUCCESS);
}
