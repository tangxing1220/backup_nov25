/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 07:11:51 by jaleman           #+#    #+#             */
/*   Updated: 2019/11/25 19:11:43 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/includes/libft.h"

/*
** Allocates sufficient memory for a copy of the string s1, does the copy,
** and returns a pointer to it.
*/

/*
static char			*ft_strdup(const char *s1)
{
	char		*s2;
	size_t		i;

	i = 0;
	while (s1[i])
		i += 1;
	if (!(s2 = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = -1;
	while (s1[++i])
		s2[i] = s1[i];
	s2[i] = '\0';
	return (s2);
}
*/
/*
** Allocates with malloc() and returns a “fresh” string ending with ’\0’,
** result of the concatenation of s1 and s2. If the allocation fails the
** function returns NULL.
*/
/*
static char			*ft_strjoin(char const *s1, char const *s2)
{
	char		*s3;
	char		*tmp_s3;
	size_t		i;
	size_t		j;

	j = 0;
	i = 0;
	while (s1[i])
		i += 1;
	while (s2[j])
		j += 1;
	if (!s1 || !s2 || !(s3 = (char *)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	tmp_s3 = s3;
	while (*s1 != '\0')
		*tmp_s3++ = *s1++;
	while (*s2 != '\0')
		*tmp_s3++ = *s2++;
	*tmp_s3 = '\0';
	return (s3);
}
*/
/*
** Verify if whatever is in the stack, has a newline. If it doesn't, returns
** a zero (0) to indicate that it's not valid. If there is a newline, we make a
** copy of the stack into the line, and we copied whatever was in the stack
** before, back to the stack (with the temporary stack that we created).
*/

 int			gnl_verify_line(char **stack, char **line)
{
	int		i;
	int		len;
	char	*tmp_stack;
	char	*strchr_stack;
	

	strchr_stack = *stack;

	i = 0;
	len = ft_strlen(strchr_stack);
	while(strchr_stack[i] != '\0')
	{
		if (strchr_stack[i] == '\n')
		{   
			if (i == (len - 1))
			{
				*line = ft_strsub(&strchr_stack[0], 0, i);
				tmp_stack = NULL;
			}
			else if (i == 0)
			{
				*line = ft_strsub(&strchr_stack[0], 0, i);
				tmp_stack = ft_strdup(&strchr_stack[i + 1]);
			}
			else
			{
				*line = ft_strsub(&strchr_stack[0], 0, i);
				tmp_stack = ft_strdup(&strchr_stack[i + 1]);
			}			
			free(*stack);
			*stack = tmp_stack;
			return (1);
		}
	i++;
	}
	return (0);
//	char			*tmp_stack;
//	char			*strchr_stack;
//	char			*temp_line;
//	char			*temp_stack;
//	int				i;
//	int 			len;

//	i = 0;
//	strchr_stack = *stack;
//	len = ft_strlen(strchr_stack);
//	while (strchr_stack[i] != '\n')
//		if (!strchr_stack[i++])
//			return (0);
//	tmp_stack = &strchr_stack[i+1];
//	temp_line = (char *)malloc(sizeof(char) * (i + 1));  
//	temp_stack = (char *)malloc(sizeof(char) * (len - i));
//	ft_strncpy(temp_line, strchr_stack,i);
//	temp_line[i]= '\0';
//	ft_strncpy(temp_stack, tmp_stack, (len - i));
//	temp_stack[len - i - 1] = '\0'; 
//	free(*stack);
//	free(strchr_stack);
//	strchr_stack = NULL;
//	*stack = NULL;
//	*line = temp_line;
//	*stack = temp_stack;
//	temp_stack = (char
//	tmp_stack = &strchr_stack[i + 1];
//	strchr_stack[i] = '\0';
//	*line = ft_strdup(*stack);
//	*stack = ft_strdup(tmp_stack);
//	if(ft_strcmp(tmp_stack, "") != 0)
//	{
//		free(tmp_stack);
//		tmp_stack =NULL;
//	}
//	if(ft_strcmp(strchr_stack, "") != 0)
//	{
//		free(strchr_stack);
//		strchr_stack = NULL;
//	}
//	if(ft_strcmp(tmp_stack, "") != 0)
//		free(tmp_stack);
//	return (1);
}

/*
** Reads into the heap, from the file descriptors, a specific number of bytes
** defined by the BUFF_SIZE macro in the get_nex_line.h file. It's going to
** continue the reading when the return value of the read function is greater
** than zero (no errors, or if there is nothing else to read).
** If there is something in the stack, we will concatinate whatever is in
** there, with whatever is read in the heap. If no, we will just add
** whatever is in the heap into the stack. Then we will verify the stack to
** see if there is a newline. If there is, we will break from the while loop
** and force the positive ret value into a one (1), using the RET_VALUE() macro.
** This answer form SO helped me visualize the stack and heap in a better way:
** http://stackoverflow.com/a/1213360
*/

	int			gnl_read_file(int fd, char *heap, char **stack, char **line)
{
	int				ret;
	char			*tmp_stack;

	while ((ret = read(fd, heap, BUFF_SIZE)) > 0)
	{
		heap[ret] = '\0';
		if (*stack)
		{
			tmp_stack = *stack;
			*stack = ft_strjoin(tmp_stack, heap);
			free(tmp_stack);
			tmp_stack = NULL;
		}
		else
			*stack = ft_strdup(heap);
		if (gnl_verify_line(stack, line))
			break ;
	}
	return (RET_VALUE(ret));
}

/*
** This is where the real shit happens.
** It first checks for errors (is the line is empty, if the number of the file
** descriptor is invalid, or if it fails to allocate the heap), so it can return
** a minus one (-1) if needed.
**
** If there is something in the stack (because we are using a static variable),
** we verify that there is a newline. If not, we allocate memory for the heap,
** and we read the file.
**
** When the reading of the file ends, we will free the heap (we're not gonna
** use it anymore), and we check for the value of ret (if it's 1 or -1, return
** that, if the stack is empty, return 0). If neither of these conditions are
** valid, we assing line to the value of the stack, free the stack, and return 1
**
** A good read about file descriptors:
** http://www.bottomupcs.com/file_descriptors.xhtml
*/

int					get_next_line(int const fd, char **line)
{
	static char		*stack[MAX_FD];
	char			*heap;
	int				ret;
	int				i;

	if (!line || (fd < 0 || fd >= MAX_FD) || (read(fd, stack[fd], 0) < 0) \
		|| !(heap = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	if (stack[fd])
		if (gnl_verify_line(&stack[fd], line))
		{
			free(heap);
			return (1);
		}
	i = 0;
	while (i < BUFF_SIZE)
		heap[i++] = '\0';
	ret = gnl_read_file(fd, heap, &stack[fd], line);
	free(heap);
	if (ret != 0 || stack[fd] == NULL || stack[fd][0] == '\0')
	{
		if (!ret && *line)
			*line = NULL;
		return (ret);
	}
	*line = stack[fd];
	stack[fd] = NULL;
	return (1);
}
