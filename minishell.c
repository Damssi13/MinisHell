/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:09:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/20 09:11:59 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	init_mini(t_mini *shell, char **envm)
{
	int i;

	i = 0;
	while(envm[i])
	{
		if(ft_strncmp("PATH=", envm[i], 5) == 0)
		{
			shell->path = ft_split(envm[i] + 5, ':');
			break;
		}
		i++;
	}
	shell->envp = arr_dup(envm);
	shell->cmds = NULL;
	shell->head = NULL;
	shell->rl = NULL;	
	shell->pipes = 0;
}
int main(int ac, char **av, char **envm)
{
	(void)ac;
	(void)av;
	t_mini	shell;
	int i = 0;
	

	while(envm[i])
	{
		if(ft_strncmp("PATH=", envm[i], 5) == 0)
			shell.path = ft_split(envm[i] + 5, ':');
		i++;
	}
	
	for(int i = 0; shell.envp[i] != NULL; i++)
		printf("%s \n", shell.path[i]);
	exit (1);
	init_mini(&shell,envm);
	while (1)
	{
		shell.rl = readline("minishell> ");
		if (!shell.rl)
			break;
		first_parse(shell.rl, &shell.head);
		// while(head)
		// {
		// 	printf("word ==> [%s]  type ==> [%i] index ==> [%d] \n", head->word, head->token, head->index);
		// 	head = head->next;
		// }
		parsing(&shell.head, &shell.cmds);
		// while(cmds)
		// {
		// 	printf("%s ,%d [%s]0 [%s]1\n",cmds->redirections->word, cmds->n_redirections,  cmds->str[0] , cmds->str[1]);
		// 	cmds = cmds->next;
		// }
		free_tokens(shell.head);
		shell.head = NULL;
	}
	free(shell.rl);
	return (0);
}
              ///////////----- LAST UPDATE --------/////////
//YOU FOUND THAT WHEN FREEING PIPE; IT FREES BUT IT DOES NOT MOVE TO THE NEXT NODE 
//THIS IS YOU NEXT MISSION.