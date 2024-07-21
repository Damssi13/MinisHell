/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:26:32 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/21 15:36:21 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_new_env(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

t_env *create_env(char **env)
{
	int i;
	char **tmp;
	t_env *head;
	t_env *new;
	
	i = 0;
	head = NULL;
	while(env[i])
	{
		tmp = ft_split(env[i], '=');
		new = ft_new_env(tmp[0], tmp[1]);
		ft_lstadd(&head, new);
		i++;
	}
	return head;
}


void print_env(t_env **env)
{
	t_env **tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s=%s\n", (*tmp)->key, (*tmp)->value);
		tmp = &(*tmp)->next;
	}
}