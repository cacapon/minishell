/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:35:06 by ttsubo            #+#    #+#             */
/*   Updated: 2025/04/05 14:46:39 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish_signal.h"

/**
 * @brief ctrl+cを押されたときのハンドラ関数
 * 
 * @param signum 
 */
static void	ctrl_c(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief sigaction構造体の値を設定します。
 * 
 * @param sa		: sigaction構造体
 * @param handler	: ハンドラ関数
 * @note sigaction構造体のうち、次の値を設定しています。
 * @note - sa_handler	:ハンドラ関数。引数fを設定します。NULLの場合はSIG_IGN。
 * @note - sa_mask		:ハンドラ実行中にブロックするマスク。ブロックはしない。
 * @note - sa_flags		:ハンドラの挙動を制御するフラグ。特に設定しない。
 */
static void	_set_sigaction(struct sigaction *sa, void (*handler)(int))
{
	if (!handler)
		sa->sa_handler = SIG_IGN;
	else
		sa->sa_handler = handler;
	sigemptyset(&(sa->sa_mask));
	sa->sa_flags = 0;
}

/**
 * @brief SIGINT(ctrl+c), SIGQUIT(ctrl+\)を設定します。
 * 
 * @note ctrl+dはEOFのため、別途管理しています。
 */
void	minish_signal(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	_set_sigaction(&sa_int, ctrl_c);
	_set_sigaction(&sa_quit, NULL);
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
