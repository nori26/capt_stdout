#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "getstr.h"

static char			*g_buf = NULL;
static int			g_stdout_copy_fd;
static pthread_t	g_th;
static int			g_capture_pipe[2];

static void	*or_exit(void *allocated)
{
	if (!allocated)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	return (allocated);
}

static void	init_buf()
{
	free(g_buf);
	g_buf = NULL;
}

static void	store_stdout()
{
	g_stdout_copy_fd = dup(STDOUT_FILENO);
}

static void	restore_stdout(void)
{
	dup2(g_stdout_copy_fd, STDOUT_FILENO);
	close(g_stdout_copy_fd);
}

static void	hook_stdout()
{
	pipe(g_capture_pipe);
	dup2(g_capture_pipe[1], STDOUT_FILENO);
	close(g_capture_pipe[1]);
}

static void	*drain_stdout(void *p)
{
	(void)p;
	g_buf = or_exit(read_fd_by_size(g_capture_pipe[0], PIPE_BUF));
	close(g_capture_pipe[0]);
	return (NULL);
}

void	capture_stdout(void)
{
	init_buf();
	store_stdout();
	hook_stdout();
	pthread_create(&g_th, NULL, drain_stdout, NULL);
}

char	*get_captured(void)
{
	char	*buf;

	fflush(stdout);
	restore_stdout();
	pthread_join(g_th, NULL);
	if (g_buf)
		buf = or_exit(strdup(g_buf));
	else
		buf = NULL;
	init_buf();
	return (buf);
}
