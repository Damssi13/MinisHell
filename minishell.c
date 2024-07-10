/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:09:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/10 16:57:25 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"





int main(void)
{
	t_parser *cmds;
	char *rl;
	t_lexer *head;

	head = NULL;
	cmds = NULL;
	while (1)
	{
		rl = readline("minishell> ");
		if (!rl)
			break;
		first_parse(rl, &head);
		// while(head)
		// {
		// 	printf("word [%s]  type[%i] index[%d] \n", head->word, head->token, head->index);
		// 	head = head->next;
		// }
		parsing(&head, &cmds);
		free_tokens(head);
		head = NULL;
	}
	free(rl);
	return (0);
}
