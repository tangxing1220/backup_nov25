/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 12:25:47 by krusthol          #+#    #+#             */
/*   Updated: 2019/11/25 14:13:39 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/includes/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void	greetings(char *argv[])
{
	ft_putendl("");
	ft_putendl("Get Next Line Testing Suite     by [krusthol]\n"
			"Includes: main.c and /tests/       [Hive Helsinki]");
	ft_putendl("");
	ft_putstr("Usage:    ");
	ft_putstr(argv[0]);
	ft_putendl(" [filename] (-v) (-a) (-l) (-lv) (-m) (-mv)\n");
	ft_putendl("When [filename] is given, file is iterated using get_next_line");
	ft_putendl("Unix | pipes Standard Output for the program as Standard Input");
	ft_putendl("Maximum of one extra (option flag) supported after [filename]\n");
	ft_putendl("Option flags:");
	ft_putendl("-v:    verbose action");
	ft_putendl("-a:    test with an arbitary file descriptor [42]");
	ft_putendl("-l/mv: test memory leaks with infinite loop (verbosely with lv)");
	ft_putendl("-m/mv: test multiple file descriptor support (verbosely with mv)\n");
}

int		main(int argc, char *argv[])
{
	int		gnl_ret;
	int		fd;
	int		fd2;
	int		fd3;
	int		rd;
	int		gd;
	int		in[3];
	char	*line;
	char	greet[1];

	line = NULL;
	in[0] = 1;
	in[1] = 1;
	in[2] = 1;
	fd = 0;
	if (argc == 1)
	{
		gd = open("greetings", O_RDONLY, 0);
		rd = read(gd, greet, 1);
		if (rd < 1)
		{
			greetings(argv);
			gd = creat("greetings", 0700);
			gd = open("greetings", O_WRONLY, 0);
			write(gd, "krusthol's amazing test main has been run!\n", 44);
			close(gd);
			return (0);
		}
		close(gd);
		ft_putstr(argv[0]);
		ft_putstr(" -h (usage) ");
		if (get_next_line(fd, &line))
		{
			ft_putstr("[output of get_next_line]\n");
			ft_putendl("");
			ft_putstr(line);
			ft_strdel(&line);
		}
		while (get_next_line(fd, &line))
		{
			ft_putendl("");
			ft_putstr(line);
			ft_strdel(&line);
		}
		ft_putendl("");
		if (line)
			ft_strdel(&line);
	}
	else if (argc == 2 && ft_strequ("-v", argv[1]))
	{
		while (get_next_line(fd, &line))
		{
			ft_putstr("line ");
			ft_putnbr(in[0]);
			ft_putstr("> ");
			ft_putstr(line);
			ft_putendl(" [end-of-line]");
			ft_strdel(&line);
			in[0]++;
		}
		if (line)
			ft_strdel(&line);
	}
	else if (argc == 2 && ft_strequ("-h", argv[1]))
	{
		greetings(argv);
		return (0);
	}
	else if (argc == 3 && ft_strequ("-a", argv[2]))
	{
		fd = open(argv[1], O_RDONLY, 0);
		fd = 42; 
		gnl_ret = get_next_line(fd, &line);
		ft_putnbr(gnl_ret);
		ft_putendl("= get_next_line return value, fd was set at 42"); 
		if (line)
			ft_strdel(&line);
	}
	else if (argc == 3 && ft_strequ("-l", argv[2]))
	{
		fd = open(argv[1], O_RDONLY, 0);
		while (get_next_line(fd, &line))
		{
			ft_putendl(line);
			ft_strdel(&line);
		}
		if (line)
			ft_strdel(&line);
	}
	else if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY, 0);
		while (get_next_line(fd, &line))
		{
			ft_putendl(line);
			ft_strdel(&line);
		}
		if (line)
			ft_strdel(&line);
	}
	else if ((argc == 3 && ft_strequ("-v", argv[2])) ||
			(argc == 3 && ft_strequ("-lv", argv[2])))
	{
		fd = open(argv[1], O_RDONLY, 0);
		while (get_next_line(fd, &line))
		{
			ft_putstr("line ");
			ft_putnbr(in[0]);
			ft_putstr("> ");
			ft_putstr(line);
			ft_putendl(" [end-of-line]");
			ft_strdel(&line);
			in[0]++;
		}
		if (line)
			ft_strdel(&line);
	}
	else if (argc == 3 && ft_strequ("-m", argv[2]))
	{
		fd = open(argv[1], O_RDONLY, 0);
		fd2 = open("tests/m2", O_RDONLY, 0);
		fd3 = open("tests/m3", O_RDONLY, 0);
		while (get_next_line(fd, &line))
		{
			ft_putendl(line);
			ft_strdel(&line);
			if (get_next_line(fd2, &line))
			{
				ft_putendl(line);
				ft_strdel(&line);
			}
			if (get_next_line(fd3, &line))
			{
				ft_putendl(line);
				ft_strdel(&line);
			}
		}
		if (line)
			ft_strdel(&line);
		close(fd2);
		close(fd3);
	}
	else if (argc == 3 && ft_strequ("-mv", argv[2]))
	{
		ft_putendl("Multiple file descriptors Bonus test [verbose]\n");
		fd = open(argv[1], O_RDONLY, 0);
		fd2 = open("tests/m2", O_RDONLY, 0);
		fd3 = open("tests/m3", O_RDONLY, 0);
		while (get_next_line(fd, &line))
		{
			ft_putstr("1,");
			ft_putnbr(in[0]);
			ft_putstr("> ");
			ft_putstr(line);
			ft_putendl(" [end-of-line]");
			ft_strdel(&line);
			in[0]++;
			if (get_next_line(fd2, &line))
			{
				ft_putstr("2,");
				ft_putnbr(in[1]);
				ft_putstr("> ");
				ft_putstr(line);
				ft_putendl(" [end-of-line]");
				ft_strdel(&line);
				in[1]++;
			}
			if (get_next_line(fd3, &line))
			{
				ft_putstr("3,");
				ft_putnbr(in[2]);
				ft_putstr("> ");
				ft_putstr(line);
				ft_putendl(" [end-of-line]");
				ft_strdel(&line);
				in[2]++;
			}
		}
		if (line)
			ft_strdel(&line);
		close(fd2);
		close(fd3);
	}
	if ((argc == 3 && ft_strequ("-l", argv[2])) ||
			(argc == 3 && ft_strequ("-lv", argv[2])))
	{
		close(fd);
		ft_putendl("\n[Tutorial for memory leaks checking]\n");
		ft_putendl("1> Open terminal [CMD + N]\n2> leaks [binary name]\nOR\n"
				"2> ps -ax (for checking process ID for leaks)\n"
				"3> leaks [pid] (for checking memory leaks of process ID)");
		ft_putendl("\n[CTRL + C] to close this process");
		while (1)
			fd = 0;
	}
	close(fd);
	return (0);
}
