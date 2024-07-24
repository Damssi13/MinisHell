/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:19:48 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/22 18:22:01 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void pipe_execution(t_parser *parser, t_mini *shell)
{
    int fd[2];
    int status;
    pid_t pid;
    t_parser *tmp;

    tmp = parser;
    while (tmp)
    {
        if (tmp->next)
        {
            pipe(fd);
            pid = fork();
            if (pid < 0)
            {
                ft_putendl_fd("minishell: fork failed", 2);
                return ;
            }
            if (pid == 0)
            {
                dup2(fd[1], 1);
                close(fd[0]);
                close(fd[1]);
                execve(tmp->str[0], tmp->str, shell->envp);
            }
            else
            {
                waitpid(pid, &status, 0);
                dup2(fd[0], 0);
                close(fd[0]);
                close(fd[1]);
            }
        }
        tmp = tmp->next;
    }
    execve(tmp->str[0], tmp->str, shell->envp);
}

int pipe_check(char **args)
{
    int i;

    i = 0;
    while (args[i])
    {
        if (ft_strncmp(args[i], "|", 1) == 0)
            return (1);
        i++;
    }
    return (0);
}

char *join_path(char *s1, char *s2)
{
    int len;
    char *result;
    int i;

    len = ft_strlen(s1) + ft_strlen(s2) + 1;
    i = 0;
    
    result = malloc(sizeof(char) * (len + 1));
    if(!result)
        return NULL;
    result[len] = '\0';
    while(*s1)
        result[i++] = *s1++;
    result[i++] = '/';
    while(*s2)
        result[i++] = *s2++;
    return(result);
}

void execute_command(char **path, char **args, t_mini *shell)
{
    pid_t pid;
    int status;
    // int i;
    char *pat;

    // i = 0;
    pid = fork();
    if (pid < 0)
    {
        ft_putendl_fd("minishell: fork failed", 2);
        return ;
    }
    if (pid == 0)
    {
        pat = join_path(path[3], args[0]);
        // printf("%s",pat);
        execve(pat, args, shell->envp); 
        exit(1);
    }
    else
        waitpid(pid, &status, 0);
}


void execute_builtin(t_parser *args, t_env **env, t_mini *shell)
{
    if(args->str[0] == NULL || args->str[0][0] == '\0')
        return ;
    if(ft_strncmp(args->str[0], "echo", 4) == 0)
        echo_builtin(args->str);
    else if(ft_strncmp(args->str[0], "pwd", 3) == 0)
        pwd_builtin();
    else if(ft_strncmp(args->str[0], "cd", 2) == 0)
        cd_builtin(args->str, env);
    else if(ft_strncmp(args->str[0], "export", 6) == 0)
        export_builtin(args->str, shell);
    else if(ft_strncmp(args->str[0], "unset", 5) == 0)
        unset_builtin(args->str);
    else if(ft_strncmp(args->str[0], "env", 3) == 0)
        env_builtin(env);
    else if(ft_strncmp(args->str[0], "exit", 4) == 0)
        exit_builtin(args->str);
    else
        ft_putendl_fd("minishell: command not found", 2);
}

void execute(t_parser *parser, t_mini *shell, t_env **env)
{
    t_parser *tmp;

    tmp = parser;
    while (tmp)
    {
        if (tmp->builtin)
            execute_builtin(tmp, env, shell);
        else
            execute_command(shell->path, tmp->str, shell);
        tmp = tmp->next;
    }
}


