/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   typedefs.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/03 14:25:12 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/06/08 14:22:38 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include "libft.h"
// enums
typedef enum e_state
{
	STATE_DEFAULT,
	STATE_IN_WORD,			//non quoted words like : ls, file.txt
	STATE_IN_SINGLE_QUOTE,	//single quoted strings
	STATE_IN_DOUBLE_QUOTE,	// double quoted strings
	STATE_IN_ENV,			//env variable like : $PATH
	STATE_IN_QUOTED_ENV,	// when $ENV varbiable found in double quoted str
	STATE_IN_REDIR_IN,		// < , <<
	STATE_IN_REDIR_OUT,		// >, >>
	STATE_ESCAPE			// "\"
}	t_state;

typedef enum e_parse_state
{
	PARSE_DEFAULT,
	PARSE_REDIR,
	PARSE_HEREDOC,
	PARSE_APPEND,
	PARSE_PIPE,
	PARSE_ERROR
}	t_parser_state;


typedef enum e_token_type
{
	TOK_WORD,
	TOK_QUOTED,			//""
	TOK_PIPE,			//|
	TOK_REDIR_IN,		//<
	TOK_REDIR_OUT,		// >
	TOK_HEREDOC,		// <<
	TOK_APPEND,			// >>
	TOK_ENV_VAR,		// $PATH
	TOK_EXIT_STATUS,	// $?
}	t_toktype;

typedef enum e_mem_t
{
	MEM_TEMP,
	MEM_LONG
}	t_mem_t;

// structs
typedef struct s_alloc
{
	void			*ptr;
	struct s_alloc	*next;
}	t_alloc;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	void			*content;
	t_toktype		type;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char				**args;
	char				*infile;
	char				*outfile;
	int					append;
	char				*delimiter;
	int					is_builtin;
	struct s_command	*next;
}	t_command;

typedef struct s_parser
{
	t_token	*current_token;
	t_command		*cmd_list;
	t_command		*current_cmd;
	t_parser_state	state;
	t_env			*env;
	int				exit_value;

}	t_parser;


typedef struct s_exec_ctx
{
	int	prev_fd;
	int fds[2];
	int child_pids[100];
	int child_count;
	int last_exit_status;
} t_exec_ctx;

typedef struct s_mshell
{
	t_env		*env_list;
	t_list		*temp_allocs;
	t_list		*long_allocs;
	t_token		*tokens;
	t_command	*commands;
	char		*line;
	int			exit_status;
}	t_mshell;

#endif