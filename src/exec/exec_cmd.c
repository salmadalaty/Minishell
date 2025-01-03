/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-faya <ral-faya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:14:51 by sdalaty           #+#    #+#             */
/*   Updated: 2024/09/21 13:19:33 by ral-faya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "events.h"
#include "exec.h"
#include "expansion.h"

#define ENOENT 2
#define EACCES 13
#define EISDIR 21

static void		spawn_process(char **argv, t_context *ctx);
static void		launch_executable(char **argv, t_context *ctx);
static t_bool	is_executable(char *filename, t_context *ctx);

void	exec_command(t_node *node, t_context *ctx)
{
	char	**argv;

	argv = expand(node->data.cmd);
	if (ft_strchr(argv[0], '/') == NULL)
	{
		if (exec_builtin(argv, ctx) == FALSE)
			launch_executable(argv, ctx);
	}
	else if (is_executable(argv[0], ctx))
		spawn_process(argv, ctx);
	set_exit_status(ctx->retcode);
	free_strtab(argv);
}

static void	launch_executable(char **argv, t_context *ctx)
{
	char	*fullpath;

	fullpath = search_path(argv[0]);
	if (fullpath)
	{
		free(argv[0]);
		argv[0] = fullpath;
		spawn_process(argv, ctx);
		ctx->retcode = 0;
	}
	else
	{
		msh_error(argv[0], "command not found", 0);
		ctx->retcode = 127;
	}
}

static t_bool	is_executable(char *filename, t_context *ctx)
{
	struct stat	statbuf;

	if (access(filename, F_OK) != 0)
	{
		msh_error(filename, NULL, ENOENT);
		ctx->retcode = 127;
		return (FALSE);
	}
	stat(filename, &statbuf);
	if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
	{
		msh_error(filename, NULL, EISDIR);
		ctx->retcode = 126;
		return (FALSE);
	}
	else if (access(filename, X_OK) != 0)
	{
		msh_error(filename, NULL, EACCES);
		ctx->retcode = 126;
		return (FALSE);
	}
	return (TRUE);
}

static void	spawn_process(char **argv, t_context *ctx)
{
	int		pid;
	char	**env_array;

	env_array = convert_envl_to_array(*get_envl());
	if (!env_array)
		return ;
	wait_child_signals();
	pid = pfork();
	if (pid == FORKED_CHILD)
	{
		dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
		dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
		if (ctx->fd_close >= 0)
			close(ctx->fd_close);
		execve(argv[0], argv, env_array);
		free_strtab(env_array);
		exit(EXIT_FAILURE);
	}
	if (ctx->fd[STDIN_FILENO] != STDIN_FILENO)
		close(ctx->fd[STDIN_FILENO]);
	if (ctx->fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(ctx->fd[STDOUT_FILENO]);
	free_strtab(env_array);
	enqueue(pid, ctx);
}
