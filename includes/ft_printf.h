/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 08:50:33 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/16 12:03:20 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include <unistd.h>
#include <wchar.h>
#include <libft.h>
#include <fmt.h>

typedef struct s_colors
{
	char color[COLOR_LEN];
	char *value;
}				t_colors;

typedef void	(*t_convfunc)(t_fmt*, t_buffer_static*, va_list*, int*);

typedef struct			s_print
{
	t_buffer_static		sbuff;
	t_buffer_malloc		mbuff;
	t_fmt				fmt_flag;
	va_list				args;
	const char 			*format;
	t_convfunc			convfunc[16];
	int					ret;
}						t_print;

int		ft_printf(const char *format, ...);
int		init(t_print *print, const char *format);
int		do_fmt(char *format_string, t_print *print);
int		do_convch(t_fmt *fmt, t_print *print);
int		do_filler(t_buffer_static *sbuff, void *str, size_t size);
int		do_filler_n(t_buffer_static *sbuff, void *c, size_t n);
int		do_filler_wstr(t_buffer_static *sbuff, wchar_t *wstr, size_t n);
char	*add_color(char *ptr, t_buffer_static *sbuff);



#endif
