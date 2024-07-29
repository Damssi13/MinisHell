/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:52:56 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/29 11:41:08 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pwd_builtin(void)
{
    char *buf;

    buf = getcwd(NULL, 0);
    if (!buf)
    {
        ft_putendl_fd("minishell: pwd: error retrieving current directory: getcwd: cannot access parent directories: ", 2);
        return(1);
    }
    ft_putendl_fd(buf, 1);
    free(buf);
    return(0);
}
