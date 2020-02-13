/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: goosterl <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/21 15:16:56 by goosterl      #+#    #+#                 */
/*   Updated: 2020/01/23 16:32:09 by goosterl      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

typedef struct  s_test {
    char    *line;
    int     fd;
    int     ret;
}   t_test;

void    print_result(int ret, char *line)
{
    if (ret == -1)
        printf("\033[1;31m%d |\033[0m ERROR\n", ret);
    if (ret == 0)
        printf("\033[1;32m%d |\033[0m %s\n", ret, line);
    if (ret == 1)
        printf("\033[1;36m%d |\033[0m %s\n", ret, line);
}

void    t_init(t_test *main, char *file)
{
    main->fd = open(file, O_RDONLY);
    main->ret = 0;
    main->line = NULL;
}

int		main(void)
{
    t_test  e;
	
    /*	Read through entire file	                    */
	printf("PRINT:	\033[1;37mEntire file: \n");
    t_init(&e, "hello_land.txt");
	while ((e.ret = get_next_line(e.fd, &e.line)) != 0)
    {
        print_result(e.ret, e.line);
		if (e.ret == -1)
			break ;
	}
	printf("\n");
   
 
	/*  try to read one more line after last line       */
	printf("PRINT:	\033[1;37mEntire file with EOF return: \n");
	t_init(&e, "get_next_line.h");
	for (int i = 0; i < 58; i++) {
		e.ret = get_next_line(e.fd, &e.line);
		print_result(e.ret, e.line);
	}
	printf("\n");

	
	/*	try to read non-existing file					*/
	t_init(&e, "hello_world.txt");
	printf("PRINT:	\033[1;37mFalse input: \n");
	for (int i = 0; i < 5; i++) {
		e.ret = get_next_line(e.fd, &e.line);
		print_result(e.ret, e.line);
	}
    
	return (1);
}
