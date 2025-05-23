/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:28:00 by ttsubo            #+#    #+#             */
/*   Updated: 2025/04/29 12:57:29 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialize.h"
#include "env_utils_2.h"
#include "parser.h"
#include "tokenizer.h"

static void	_free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

static void	_show_cmd(t_cmd *cmd)
{
	size_t	arg_i;

	arg_i = 0;
	printf("\tcmd->type=%d\n", cmd->type);
	printf("\tcmd->argc=%d\n", cmd->argc);
	printf("\tcmd->argv=[");
	while (cmd->argv[arg_i])
		printf("%s,", cmd->argv[arg_i++]);
	printf("NULL]\n");
}

int	main(int argc, char **argv, char **envp)
{
	int			i;
	char		**tokens;
	t_cmd		**cmds;
	t_minish	*minish;

	minish = initialize(envp);
	if (argc != 2)
		return (printf("usage: ./test_tokenizer.out <any message>"), 1);
	tokens = tokenizer(argv[1]);
	cmds = parser(tokens, minish);
	if (!tokens || !cmds)
		return (1);
	i = 0;
	while (cmds[i])
		_show_cmd(cmds[i++]);
	_free_tokens(tokens);
	free_cmds(cmds, cmds_len(cmds));
	cleanup_minish(minish);
	return (0);
}
