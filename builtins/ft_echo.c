/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:52:33 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/28 10:57:10 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void echo_builtin(char **args)
{
    int i;
    int n_flag;
    
    i = 1;
    n_flag = 0;
    if (!args[i])
    {
        write(1, "\n", 1);
        return ;
    }
    while (args[i] && is_n_flag(args[i]))
    {
        n_flag = 1;
        i++;
    }    
    while (args[i])
    {
        remove_quotes(args[i]);
        write(1, args[i], ft_strlen(args[i]));
        if (args[i++ + 1])
            write(1, " ", 1);
    }
    if (!n_flag)
        write(1, "\n", 1);
}
