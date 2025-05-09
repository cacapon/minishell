/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:19:19 by dayano            #+#    #+#             */
/*   Updated: 2025/05/09 14:19:00 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	redirect_stdout(t_cmd *cmd)
{
	int		fd;
	char	*path;

	path = cmd->argv[0];
	if (cmd->type == REDIR_OUT)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->type == REDIR_APPEND)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (false);
	if (fd < 0)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
		perror(path);
		return (false);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
		perror(path);
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

bool	is_limiter(int fd, char *limiter)
{
	char	*line;

	line = NULL;
	line = readline("> ");
	if (!line)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (true);
	}
	if (ft_strcmp(line, limiter) == 0)
	{
		free(line);
		return (true);
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (false);
}

void	here_doc(char *limiter)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
		perror("pipe");
		return ;
	}
	while (!is_limiter(pipefd[1], limiter))
		;
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
		perror("here_doc");
	}
	close(pipefd[0]);
}

bool	redirect_stdin(t_cmd *cmd)
{
	int		fd;
	char	*path;

	path = cmd->argv[0];
	if (cmd->type == REDIR_HEREDOC)
		return (here_doc(path), true);
	if (cmd->type != REDIR_IN)
		return (true);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
		perror(path);
		return (false);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
		perror(path);
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

/**
 * @note This function is only called if the caller's is_redirect is true
 * @note false if the internal function is not executed.
 */
bool	redirect(t_cmd *cmd)
{
	if (cmd->type == REDIR_IN || cmd->type == REDIR_HEREDOC)
		return (redirect_stdin(cmd));
	if (cmd->type == REDIR_OUT || cmd->type == REDIR_APPEND)
		return (redirect_stdout(cmd));
	return (false);
}
