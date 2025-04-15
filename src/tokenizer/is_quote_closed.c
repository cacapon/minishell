/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote_closed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:59:15 by ttsubo            #+#    #+#             */
/*   Updated: 2025/04/15 14:06:12 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/**
 * @brief ',"が閉じているか判定します。
 * 
 * @param str 
 * @return int 
 */
int	is_quote_closed(char *str)
{
	int		in_squote;
	int		in_dquote;

	in_squote = 0;
	in_dquote = 0;
	while (*str)
	{
		if (*str == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (*str == '"' && !in_squote)
			in_dquote = !in_dquote;
		str++;
	}
	return !(in_squote || in_dquote);
}