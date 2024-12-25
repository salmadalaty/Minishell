/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcall.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalaty <sdalaty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:36:04 by sdalaty           #+#    #+#             */
/*   Updated: 2024/09/14 15:44:49 by sdalaty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

int	pfork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		msh_error("fork", NULL, 0);
	return (pid);
}
