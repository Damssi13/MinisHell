/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:40:39 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/27 11:02:37 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd_builtin(void)
{
    char *buf;

    buf = getcwd(NULL, 0);
    ft_putendl_fd(buf, 1);
    free(buf);
    return(0);
}

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

char *getenv_value(t_env *env, const char *key)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}

t_env *ft_new_env(const char *key, const char *value)
{
    t_env *new_node;
    
    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return NULL;
    new_node->key = ft_strdup(key);
    if(value)
        new_node->value = ft_strdup(value);
    else
        new_node->value = NULL;
    new_node->next = NULL;
    return new_node;
}

void update_env(t_env **env, const char *key, const char *value)
{
    t_env *temp;
    t_env *new_node;
    
    temp = *env;
    while (temp)
    {
        if (!(ft_strcmp(temp->key, key)))
        {
            if (temp->value)
                free(temp->value);
            if (value)
                temp->value = ft_strdup(value);
            else
                temp->value = NULL;
            return;
        }
        temp = temp->next;
    }
    new_node = ft_new_env(key, value);
    ft_lstadd(env, new_node);
}


void cd_builtin(char **args, t_env **env)
{
    char *path;
    char *oldpwd;

    if (args[1] != NULL && args[2] != NULL)
    {
        ft_putendl_fd("minishell: cd: too many arguments", 2);
        return;
    }
    oldpwd = getenv_value(*env, "PWD");
    if (!args[1])
        path = getenv_value(*env, "HOME");
    else if (!ft_strncmp(args[1], "-", 1))
        path = getenv_value(*env, "OLDPWD");
    else
        path = args[1];
    if (chdir(path) == -1)
        ft_putendl_fd("cd: no such file or directory", 2);
    else
        update_env(env, oldpwd, path);
}

void exit_builtin(char **args)
{
    int i;

    i = 1;
    if (args[i])
        exit(ft_atoi(args[i]));
    else
        exit(0);
}

void unsetenv_custom(t_env **env, const char *key)
{
    t_env *temp; 
    t_env *prev; 

    temp = *env;
    prev= NULL;
    while (temp)
    {
        if (!(ft_strcmp(temp->key, key)))
        {
            if (prev)
                prev->next = temp->next;
            else
                *env = temp->next;
            free(temp->key);
            free(temp->value);
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void unset_builtin(char **args, t_env **env)
{
    int i = 1;

    while (args[i])
    {
        unsetenv_custom(env, args[i]);
        i++;
    }
}

int is_valid_identifier(const char *str)
{
    if (!str || (!ft_isalpha(*str) && *str != '_'))
        return 0;
    while (*str)
    {
        if (!ft_isalnum(*str) && *str != '_')
            return 0;
        str++;
    }
    return 1;
}

void export_builtin(char **args, t_env **env)
{
    int i;
    char *key;
    char *value;
    char *equal_sign_pos;
    char *plus_equal_sign_pos;

    if (!args[1])
    {
        print_sorted_env(env);
        return;
    }
    i = 1;
    while (args[i])
    {
        remove_quotes(args[i]);
        char *arg = args[i];
        equal_sign_pos = ft_strchr(arg, '=');
        plus_equal_sign_pos = strstr(arg, "+=");

        if (equal_sign_pos || plus_equal_sign_pos)
        {
            if (plus_equal_sign_pos)
            {
                key = ft_substr(arg, 0, plus_equal_sign_pos - arg);
                char *existing_value = getenv_value(*env, key);
                char *new_value_part = ft_strdup(plus_equal_sign_pos + 2);
                if (existing_value)
                    value = ft_strjoin(existing_value, new_value_part);
                else
                    value = ft_strdup(new_value_part);
            }
            else
            {
                key = ft_substr(arg, 0, equal_sign_pos - arg);
                value = ft_strdup(equal_sign_pos + 1);
            }
        }
        else
        {
            key = ft_strdup(arg);
            value = NULL;
        }
        if (!is_valid_identifier(key))
        {
            ft_putendl_fd("minishell: export: not a valid identifier", 2);
            free(key);
            if (value)
                free(value);
            i++;
            continue;
        }
        update_env(env, key, value);
        free(key);
        if (value)
            free(value);
        i++;
    }
}


void env_builtin(t_env **env)
{
    t_env *tmp;

	tmp = *env;
	while (tmp)
	{
        if(tmp->value)
		    printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

