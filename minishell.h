/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:10:03 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/15 20:27:51 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
#include <signal.h>



typedef enum s_builtins{
	ECHO = 1,
	CD,
	PWD,
	EXPORT,
	UNSET,
	EXIT,
	ENV,
}e_builtins;

typedef enum s_tokens
{
	PIPE = 1,
	RED_OUT = 2,
	RED_IN = 3,
	HERDOC = 4,
	APP_OUT = 5,
	ARG = 6,
}					e_tokens;

typedef struct s_lexer
{
	char			*word;
	e_tokens		token;
	int 			index;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

typedef struct s_parser
{
	char 		**str;
	int 		n_redirections;
	t_lexer 	*redirections;
	e_builtins	builtin;
	struct s_parser *next;
	struct s_parser *prev;
}t_parser;

typedef struct s_mini{
	int		pipes;
	
}t_mini;

/***************************** JANDRI **********************************/
t_lexer				*ft_new_token(char *content);
void				ft_lstadd_back(t_lexer **lst, t_lexer *new);
int					type(char *p);
void				make_words(char *p, int start, int end, t_lexer **head);
void				split_args(char *p, int start, int inside, t_lexer **head);
void				free_tokens(t_lexer *head);
void				clear_screen(void);
void				first_parse(char *rl, t_lexer **head);
int					parse_quote(char *rl);
char				*ft_strtrim(char const *s1, char const *set);
int					check_next(char *first, char next);
int 				is_whitespace(char c);
void 				echo_builtin(char **args);
int 				pwd_builtin(void);



/**************             DAMSSI             *************/

void 		parsing(t_lexer **head, t_parser **commands);
void		cmd_addback(t_parser **command, t_parser *new_cmd);
t_parser 	*new_cmd(char **cmd, t_lexer *redirects, int num_redirects);
int 		find_builtin(char *first_word);
void 		argscpy(t_lexer **head, int args, char **cmd);
void 		rm_node(t_lexer **lst);
int 		count_args(t_lexer **lst);
int 		rm_redirection(t_lexer **head, t_lexer **redirection);
void 		add_redirection(t_lexer *lst, t_lexer **redirection);
void    	lex_addback(t_lexer **redirections, t_lexer *new_lex);
t_lexer     *new_lex(int r_num, e_tokens redirection, char *file);
e_tokens    red_join(e_tokens r1, e_tokens r2);
int     	redir_kind(t_lexer *lst);
void 		ft_error(char *message);
int 		redirection_check(t_lexer *tmp);

#endif
