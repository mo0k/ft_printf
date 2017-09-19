/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 00:06:52 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/19 10:39:15 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h>

int	do_convch(t_fmt *fmt, t_print *print)
{
	//static char flag_convert[] = "sSpdDioOuUxXcC%";
	char *ptr;
	//if (!fmt || !mbuff)
	if (!fmt || !print)
		return (-1);
	if (!(ptr = ft_strchr(FLAG_CONVERT, fmt->convch)))
		return (-1);
	//protection temporaire
	if (print->convfunc[ptr - FLAG_CONVERT])
		print->convfunc[ptr - FLAG_CONVERT](fmt, &print->sbuff, &print->args, &print->ret);
	return (print->ret);
}

void	ajust_fmt(t_fmt *fmt)
{
	if (!fmt)
		return;
	if (fmt->convch == 'D' || fmt->convch == 'U' || fmt->convch == 'O')
	{
		fmt->convch += 32;
		fmt->flag_mlen = FLAG_MLEN_L;
	}
	else if ((fmt->convch == 'c' || fmt->convch == 's' ) && fmt->flag_mlen == FLAG_MLEN_L)
	{
		fmt->convch -= 32;
		fmt->flag_mlen = FLAG_MLEN_NODEF;
	}
	if (fmt->flag_char[1] && fmt->flag_char[2])
		fmt->flag_char[1] = 0;
	if (fmt->flag_char[4] && fmt->flag_char[3])
		fmt->flag_char[4] = 0;

}

int		do_fmt(char *fmt_string, t_print *print)
{
	t_fmt	fmt;

	//printf("DEBUG | Start do_fmt => fmt_string:%s\n", fmt_string);
	if (!fmt_string || !print)
		return (0);
	init_fmt(&fmt);
	//print_fmt(&fmt);
	if (!parse_fmt(&fmt, fmt_string))
	{
		//printf("DEBUG | do_fmt => 0 - return (0)\n");
		return (0);
	}
	ajust_fmt(&fmt);
	//print_fmt(&fmt);
	//printf("OK\n");
	//sleep(3);
	if (do_convch(&fmt, print) > -1)
	{
		//printf("DEBUG | do_fmt => return (1)\n");
		return (1);
	}
	//printf("DEBUG | do_fmt => 1 - return (0)\n");
	return (-1);
}