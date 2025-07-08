/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:25:12 by rmhazres          #+#    #+#             */
/*   Updated: 2025/07/08 10:28:02 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include "libft.h"
# include "stdbool.h"
# define MAX_CHILDREN 200
# define SUCCESS 0
# define ERROR 1
# define CMD_NOT_FOUND 127

// enums
typedef enum e_lexstate
{
	LEXER_DEFAULT,
	LEXER_SQUOTE,
	LEXER_DQUOTE,
	LEXER_ENV,
	LEXER_QUOTED_ENV,
	LEXER_REDIR_IN,
	LEXER_REDIR_OUT,
	LEXER_ASSIGN,
	LEXER_INVALID,
	LEXER_ERROR
}	t_lexstate;

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
	TOK_ASSIGN,			// tokens for export "VAR=content"
}	t_toktype;

typedef enum e_mem_t
{
	MEM_TEMP,
	MEM_LONG
}	t_mem_t;

// structs
typedef struct s_alloc
{
	void				*ptr;
	struct s_alloc		*next;
}	t_alloc;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_token
{
	char				*content;
	t_toktype			type;
	int					quote_id;
	struct s_token		*next;
}	t_token;

typedef struct s_redir
{
	char				*file;
	bool				append;
	struct s_redir		*next;
}	t_redir;

typedef struct s_command
{
	char				**args;
	t_redir				*infile;
	t_redir				*outfile;
	bool				append;
	char				*delimiter;
	bool				is_heredoc;
	int					heredoc_fd;
	char				*heredoc_temp;
	struct s_command	*next;
}	t_command;

typedef struct s_parser
{
	t_token				*current_token;
	t_command			*cmd_list;
	t_command			*current_cmd;
	t_parser_state		state;
	t_env				*env;
	char				*exit_value;
	t_toktype			last_token_type;
	int					last_quote_id;
	int					last_arg;
}	t_parser;

typedef struct s_lexer
{
	t_lexstate			state;
	t_token				*tokens;
	char				*buffer;
	size_t				index;
	char				*input;
	char				c;
	int					current_quote_id;
	bool				in_dquote;
}	t_lexer;

typedef struct s_exec_ctx
{
	int					prev_fd;
	int					fds[2];
	int					child_pids[MAX_CHILDREN];
	int					child_count;
	int					last_exit_status;
}	t_exec_ctx;

typedef struct s_mshell
{
	t_env				*env_list;
	t_list				*temp_allocs;
	t_list				*long_allocs;
	t_token				*tokens;
	t_command			*commands;
	char				*line;
	bool				should_exit;
	int					exit_status;
}	t_mshell;

#endif