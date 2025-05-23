/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:44:19 by ttsubo            #+#    #+#             */
/*   Updated: 2025/05/16 11:26:14 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "error.h"
# include "free_functions.h"
# include "initialize.h"
# include "libft.h"
# include "struct.h"
# include <stdbool.h>
# include <stddef.h>

bool	is_key_start(int c);
bool	is_key_char(int c);
bool	is_valid_key(char *str);
bool	is_quote(char c);
bool	is_line_empty(char *line);
bool	has_closing_quote(const char *s, char quote, size_t i);
void	error_mes(char *name, char *mes);
void	close_fd(int std_fileno, int minish_std);

#endif