/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 08:13:32 by bjandri           #+#    #+#             */
/*   Updated: 2024/06/29 12:20:38 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_lstadd_back(t_token **lst, t_token *new)
{
    t_token *tmp;

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

char    *type(char *p)
{
    if(p[0] == '|')
        return("PIPE");
    else if(p[0] == '>' && p[1] != '>')
        return("RED_OUT");
    else if(p[0] == '<' && p[1] != '<')
        return("RED_INP");
    else if(p[0] == '<' && p[1] == '<')
        return("APP_RED_INP");
    else if(p[0] == '>' && p[1] == '>')
        return("APP_RED_OUT");
    else
        return("ARG");
}

t_token *ft_new_token(char *content)
{
    t_token *new_node = (t_token *)malloc(sizeof(t_token));
    if (!new_node)
        return NULL;
        
    new_node->token = content;
    new_node->type = type(content);
    new_node->next = NULL; 
    return new_node;
}

void make_words(char *p, int start, int end)
{
    char *word;
    int i;
    t_token *new_word;
    t_token *tmp;

    word = (char *)malloc((end - start + 1) * sizeof(char));
    if (!word)
    {
        perror("Failed to allocate memory for word");
        return;
    }
    new_word = NULL;
    i = 0;
    while (start < end)
        word[i++] = p[start++];
    word[i] = '\0';
    ft_lstadd_back(&new_word, ft_new_token(word));
    tmp = new_word;
    while(tmp)
    {
        printf("TYPE = %s ==> [token = %s]\n",tmp->type, tmp->token);
        tmp =  tmp->next;
    }  
    free(word);
    free(new_word);
}