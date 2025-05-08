/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:25:12 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/08 17:37:20 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

// enums
typedef enum e_state {
    STATE_DEFAULT,
    STATE_IN_WORD,  //non quoted words like : ls, file.txt
    STATE_IN_SINGLE_QUOTE,  //single quoted strings
    STATE_IN_DOUBLE_QUOTE, // double quoted strings
    STATE_IN_ENV,       //env variable like : $PATH
    STATE_IN_REDIR_IN, // < , <<
    STATE_IN_REDIR_OUT, // >, >>
    STATE_ESCAPE
} t_state;

typedef enum e_token_type {
	TOK_WORD,
	TOK_QUOTED,
	TOK_PIPE,
	TOK_REDIR_IN,     //< 
	TOK_REDIR_OUT,    // >
	TOK_HEREDOC,      // <<
	TOK_APPEND,       // >>
	TOK_ENV_VAR,      // $PATH
	TOK_EXIT_STATUS   // $?
}	t_token_type;

typedef enum e_mem_t {
	MEM_TEMP,
	MEM_LONG
	
} t_mem_t;

// structs
typedef struct s_alloc {
	void *ptr;
	struct s_alloc *next;	
} t_alloc;

typedef struct s_env
{
    char    *key;
    char    *value;
    struct s_env *next;
} t_env;

typedef struct s_command
{
	char	**args;
	char	*infile;
	char	*outfile;
	int 	append;
	struct s_command *next;
} t_command;

typedef struct s_token
{
	void			*content;
	t_token_type    type;
	struct s_token	*next;
}	t_token;

typedef struct s_mshell
{
    t_env *env_list;
	t_list *temp_allocs;
	t_list *long_allocs;
	t_token 	*tokens;
	char  *line;
	int		exit_status;
	t_command cmds;
} t_mshell;	


# endif