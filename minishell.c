/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:09:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/10 15:42:38 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redirection_check(t_lexer *tmp)
{
	t_lexer *curr;
	int infile;
	int outfile;

	infile = 0;
	outfile = 0;
	curr = tmp;
	while (curr)
	{
		if (curr->token == RED_IN)
			infile++;
		else if (curr->token == RED_OUT)
			outfile++;
		if (outfile > 2 || infile > 2 || (outfile && infile))
			return 1;
		curr = curr->next;
	}
	return 0;
}

void ft_error(char *message)
{
	ft_putstr_fd(message, 2);
	// you free all the nodes
	//
}

void add_redirection(t_lexer *lst, t_parser **cmd)
{
	t_parser *redirects;

	if (lst->next->)

		if (lst->token >= 2 && lst->token <= 5)
			(*cmd)->redirections =
}

void rm_redirection(t_lexer **head, t_parser **cmd)
{
	t_lexer *tmp;

	(void)cmd;
	tmp = *head;
	while (tmp)
	{
		if (tmp->token == PIPE)
			return;
		if (tmp->token >= 2 && tmp->token <= 5)
			if (redirection_check(tmp))
				ft_error("syntax error near unexpected token");
		if (tmp->token >= 2 && tmp->token <= 5)
		{
			// add_redirection(tmp, cmd);
			printf("add redirection");
			exit(0);
		}
		tmp = tmp->next;
	}
	return;
}
int count_args(t_lexer **lst)
{
	int i;
	t_lexer *curr;

	curr = *lst;
	i = 0;
	while (curr->token != PIPE && curr)
	{
		i++;
		curr = curr->next;
	}
	return i;
}
void rm_node(t_lexer **lst)
{
	// int i;	
	t_lexer *tmp;

	tmp = *lst;
	tmp->next->prev = NULL;
	*lst = tmp->next;
	free(tmp);
}

void 	argscpy(t_lexer **head, int args, char **cmd)
{
	t_lexer *tmp;
	int i;

	i = 0;
	tmp = *head;
	while (args)
	{
		if (tmp->token == ARG)
		{
			cmd[i++] = ft_strdup(tmp->word);
			rm_node(head);
			tmp = *head;
		}
		args--;
	}
}


int find_builtin(char *first_word) /**** it checks if the first string in the array matches the command ****/
{
	int i;
	char *builtin_array[7][2] = {
		{"echo", "1"},
		{"cd", "2"},
		{"pwd", "3"},
		{"env", "4"},
		{"exit", "5"},
		{"export", "6"},
		{"unset", "7"}};

	i = 0;
	while(i < 7)
	{
		if(ft_strcmp(builtin_array[i][0], first_word) != 0)
			i++;
		else
			return(ft_atoi(builtin_array[i][1]));
	}
	return 0;
}

t_parser *new_cmd(char **cmd)
{
	t_parser *new;

	new = malloc(sizeof(t_parser));
	if (!new)
		ft_error("malloc failed to allocate");
	new->str = cmd;
	new->builtin = find_builtin(cmd[0]);
	new->next = NULL;
	return new;
}

void	cmd_addback(t_parser **command, t_parser *new_cmd)
{
	t_parser *curr;
	
	curr = *command
}

void parsing(t_lexer **head, t_parser **commands)
{
	int args;
	char **cmd;
	// t_lexer *tmp;

	// tmp = *head;
	rm_redirection(head, commands);
	args = count_args(head);
	cmd = malloc(sizeof(char *) * (args + 1));
	if (!cmd)
		ft_error("malloc failed to allocate");
	argscpy(head, args, cmd);

	cmd_addback(commands, new_cmd(cmd));
}

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
