#include <unistd.h>
#include <stdlib.h>

static char	*my_realloc(char *buf, ssize_t bufsize)
{
	char	*new_buf;

	new_buf = realloc(buf, bufsize);
	if (!new_buf)
	{
		free(buf);
		return (NULL);
	}
	return (new_buf);
}

// tmp
char	*read_fd_by_size(int fd, size_t size)
{
	ssize_t	bufsize;
	ssize_t	readsize;
	ssize_t	read_status;
	char	*buf;

	bufsize = 0;
	readsize = 0;
	buf = NULL;
	while (42)
	{
		if (bufsize <= readsize)
		{
			bufsize += size;
			buf = my_realloc(buf, bufsize);
			if (!buf)
				return (NULL);
		}
		read_status = read(fd, buf + readsize, size);
		if (read_status <= 0)
			break ;
		readsize += read_status;
	}
	buf[readsize] = '\0';
	return (buf);
}
