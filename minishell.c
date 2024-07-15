/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:09:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/15 20:27:03 by rachid           ###   ########.fr       */
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
		while(cmds)
		{
			printf("redirection[%s] its_token[%d]  its_number[%d]\n", cmds->redirections->word, cmds->redirections->token, cmds->n_redirections);
			printf("[%s] [%s]\n", cmds->str[0] , cmds->str[1]);
			// printf("str[0]-->%s  str[1]-->%s\n",cmds->str[0], cmds->str[1]);
			
			cmds = cmds->next;
			// exit(0);
		}
		free_tokens(head);
		head = NULL;
	}
	free(rl);
	return (0);
}
              ///////////----- LAST UPDATE --------/////////
//YOU FOUND THAT WHEN FREEING PIPE; IT FREES BUT IT DOES NOT MOVE TO THE NEXT NODE 
//THIS IS YOU NEXT MISSION.