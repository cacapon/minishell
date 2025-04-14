/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:19:01 by ttsubo            #+#    #+#             */
/*   Updated: 2025/04/14 11:13:08 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define PATH_MAX 4096

int	builtin_pwd(int argc, char *argv[]);
int	builtin_exit(int argc, char *argv[]);
int	builtin_cd(int argc, char *argv[]);

#endif
