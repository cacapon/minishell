/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:42:14 by dayano            #+#    #+#             */
/*   Updated: 2025/05/05 22:40:17 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
 * @brief Wait for one command’s process to finish.
 *
 * This function calls waitpid() for cmd->pid, stores the exit
 * or signal status into cmd->status, and returns that status.
 *
 * @param cmd  The command whose child process to wait for.
 * @return     The exit status or 128+signal number on signal,
	or EXIT_FAILURE on error.
 */
static int	_get_status(t_cmd *cmd)
{
	int	ret;
	int	status;

	ret = 0;
	ret = waitpid(cmd->pid, &status, 0);
	if (ret < 0)
	{
		cmd->status = EXIT_FAILURE;
		return (cmd->status);
	}
	if (WIFEXITED(status))
		cmd->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		cmd->status = 128 + WTERMSIG(status);
	else
		cmd->status = EXIT_FAILURE;
	return (cmd->status);
}

/**
 * @brief Wait for all child processes in the pipeline to finish.
 *
 * This function walks through each command in the pipeline,
 * calls waitpid() for every non-redirect node, stores each
 * child’s exit or signal status into cmd->status, and then
 * returns the status of the last command executed.
 *
 * @param cmd_head  Pointer to the head of the command list.
 * @return          The exit status of the last command in the pipeline.
 */
int	wait_pipeline(t_cmd *cmd_head)
{
	int		last_status;
	t_cmd	*cmd;
	bool	saw_sigint;
	bool	saw_sigquit;

	saw_sigint = false;
	saw_sigquit = false;
	last_status = 0;
	cmd = cmd_head;
	while (cmd)
	{
		if (!is_redirect(cmd))
			last_status = _get_status(cmd);
		if (last_status == 130)
			saw_sigint = true;
		else if (last_status == 131)
			saw_sigquit = true;
		cmd = cmd->next;
	}
	if (saw_sigint)
		write(STDOUT_FILENO, "\n", 1);
	if (last_status == 131 && saw_sigquit)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	return (last_status);
}
