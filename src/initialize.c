/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:42:46 by dayano            #+#    #+#             */
/*   Updated: 2025/05/02 14:11:51 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	_set_envp(char *env_val, t_env *node)
{
	size_t	env_len;
	size_t	eq_pos;

	if (!env_val || !node)
		return (1);
	env_len = ft_strlen(env_val);
	eq_pos = ft_strlen_until(env_val, '=');
	if (eq_pos == env_len)
		return (1);
	node->key = ft_substr(env_val, 0, eq_pos);
	node->value = ft_substr(env_val, eq_pos + 1, env_len - eq_pos - 1);
	if (!node->key || !node->value)
		return (1);
	node->is_exported = 1;
	return (0);
}

static void	_free_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

static void	_free_nodes(t_env **head)
{
	t_env	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		_free_node(*head);
		*head = tmp;
	}
}

/**
 * @brief Create a envp list object
 *
 * @param envp
 * @return t_env*
 */
static t_env	*create_envp_list(char **envp)
{
	t_env	*head;
	t_env	*tail;
	int		i;
	t_env	*node;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		node = ft_calloc(1, sizeof(t_env));
		if (!node)
			return (NULL);
		if (_set_envp(envp[i], node))
			return (_free_nodes(&head), _free_node(node), NULL);
		node->next = NULL;
		if (!head)
			head = node;
		else
			tail->next = node;
		tail = node;
		i++;
	}
	return (head);
}

t_minish	*initialize(char **envp)
{
	t_minish	*minish;

	rl_clear_history();
	minish = ft_calloc(1, sizeof(t_minish));
	if (!minish)
		handle_error_and_exit("ft_calloc", minish);
	minish->env = create_envp_list(envp);
	if (!minish->env)
		handle_error_and_exit("create_envp_list", minish);
	return (minish);
}
