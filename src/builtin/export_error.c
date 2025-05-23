/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:11:06 by ttsubo            #+#    #+#             */
/*   Updated: 2025/05/08 17:58:36 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	export_err_invalid_opt(char *sh, char c)
{
	ft_putstr_fd(sh, STDERR_FILENO);
	ft_putstr_fd(": export: -", STDERR_FILENO);
	ft_putchar_fd(c, STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
	return (EXIT_EXPORT_INVALID_OPT);
}

int	export_err_invalid(char *sh, char *key, char *value)
{
	ft_putstr_fd(sh, STDERR_FILENO);
	ft_putstr_fd(": export: `", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	if (value)
	{
		ft_putchar_fd('=', STDERR_FILENO);
		ft_putstr_fd(value, STDERR_FILENO);
	}
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (EXIT_EXPORT_NOT_A_VALID);
}
