/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:26:32 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/24 09:47:05 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));

	new->key = key;
	new->value = value;
	new->next = NULL;
	return new;
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
size_t	ft_nstrlen(char *s, char c)
{
	size_t i;

	i = 0;
	while(s[i] && s[i] != c)
		i++;
	return (i + 1);
}

t_env 	*create_env(char **env)
{
	int i;
	size_t key;
	char *keey;
	t_env *node;

	node = NULL;
	i = 0;
	while(env[i])
	{
		key = ft_nstrlen(env[i], '=');
		
		keey = malloc(sizeof(char) * (key + 1));
		////
		keey[key] = '\0';
		
		ft_strlcpy(keey, env[i], key);
		ft_lstadd(&node, new_env(keey, ft_strdup(env[i] + key + 1)));
		i++;
	}
	return node;
}


void print_env(t_env **env)
{
	t_env *tmp;

	tmp = *env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}