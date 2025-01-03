/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalaty <sdalaty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:17:48 by sdalaty           #+#    #+#             */
/*   Updated: 2024/09/14 15:21:12 by sdalaty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

#define CLOSED 0
#define UNCLOSED 1
#define METACHARS "|()<> \t\n"

static int	string(t_scanner *self, char c);

t_token	token_word(t_scanner *self, char c)
{
	self->iter.current--;
	while (!ft_strchr(METACHARS, *self->iter.current))
	{
		c = advance(self);
		if (c == '\'' || c == '"')
		{
			if (string(self, c) == UNCLOSED)
				return (error_token("unmatched string"));
			c = *self->iter.current;
		}
	}
	return (make_token(self, TOKEN_WORD));
}

static int	string(t_scanner *self, char c)
{
	char	close;

	close = c;
	c = advance(self);
	while (c != close && c != 0)
		c = advance(self);
	if (c == 0 && c != close)
		return (UNCLOSED);
	return (CLOSED);
}

t_token	peek(t_scanner *self)
{
	return (self->next);
}

t_token	next(t_scanner *self)
{
	t_token	actual;

	actual = self->next;
	self->next = scan_token(self);
	return (actual);
}

t_bool	has_next(t_scanner *self)
{
	return (self->next.type != TOKEN_EOF);
}
