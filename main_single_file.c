/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:02:13 by xtang             #+#    #+#             */
/*   Updated: 2019/11/15 16:56:36 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft/includes/libft.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*buff;
	int		linenum;
	int		ret;

	linenum = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			ft_putstr("open() error");
			return (1);
		}
		while ((ret = get_next_line(fd, &buff)) > 0)
		{
			printf("[Return: %d] Line #%d: %s\n", ret, ++linenum, buff);
			free(buff);
		}
		printf("[Return: %d] Line #%d: %s\n", ret, ++linenum, buff);
		if (ret == 0)
			printf("----------\nEnd of file\n");
		else if (ret == -1)
			printf("----------\nError\n");
		if (close(fd) == -1)
		{
			ft_putstr("close() error");
			return (1);
		}
	while(1);
	}
	return (0);
}
