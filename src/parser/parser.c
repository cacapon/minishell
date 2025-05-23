/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:14:32 by ttsubo            #+#    #+#             */
/*   Updated: 2025/05/18 14:32:44 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief
 *
 * @param tokens
 * @return t_cmd**
 */
t_cmd	**parser(char **tokens, t_minish *minish)
{
	char	**formatted_tokens;
	t_cmd	**cmds;

	if (!tokens)
		return (NULL);
	formatted_tokens = expand_tokens(tokens, minish);
	if (!formatted_tokens)
		return (NULL);
	cmds = allocate_cmds(formatted_tokens);
	if (!cmds)
		return (free_strs(&formatted_tokens), NULL);
	cmds = setup_cmds(cmds, formatted_tokens);
	if (!cmds)
		return (free_strs(&formatted_tokens), NULL);
	parser_validate(&cmds, minish);
	free_strs(&formatted_tokens);
	return (cmds);
}
