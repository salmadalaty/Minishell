/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-faya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:54:26 by ral-faya          #+#    #+#             */
/*   Updated: 2024/09/03 16:54:50 by ral-faya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include "libft.h"

typedef enum e_token_type
{
	TOKEN_UNKNOWN,
	TOKEN_LESS,
	TOKEN_GREAT,
	TOKEN_PIPE,
	TOKEN_LEFT_PAREN,
	TOKEN_RIGHT_PAREN,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_DLESS,
	TOKEN_DGREAT,
	TOKEN_WORD,
	TOKEN_ERROR,
	TOKEN_EOF,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	const char		*start;
	int				length;
}	t_token;

typedef struct s_iter
{
	const char	*start;
	const char	*current;
}	t_iter;

typedef struct s_scanner
{
	t_iter	iter;
	t_token	next;
}	t_scanner;

t_scanner	init_scanner(const char *source);
t_token		scan_token(t_scanner *self);
t_token		error_token(const char *message);
t_token		make_token(const t_scanner *self, t_token_type type);
t_token		scan_double_char_token(t_scanner *self, char c);
t_token		token_word(t_scanner *self, char c);
char		advance(t_scanner *self);
t_bool		is_at_end(t_scanner *self);
t_token		peek(t_scanner *self);
t_token		next(t_scanner *self);
t_bool		has_next(t_scanner *self);

#endif
