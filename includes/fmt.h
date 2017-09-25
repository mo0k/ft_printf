/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 11:53:58 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/25 22:47:31 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FMT_H
# define FMT_H

#define FLAG_CHAR "#0-+ "
#define FLAG_CONVERT "sSpdDioOuUxXcCb%"
//#define FLAG_CONVERT "%CDOSUXbcdiopsux"
#define BUFF_SIZE_TEMP 1024
#define TAB_COLOR_LEN 17
#define COLOR_LEN 10

enum e_flag_mlen
{
	flag_mlen_nodef,
	flag_mlen_hh,
	flag_mlen_h,
	flag_mlen_l,
	flag_mlen_ll,
	flag_mlen_z,
	flag_mlen_j
};

union u_type
{
	char				c;
	long				l;
	int					d;
	t_uint				u;
	char*				s;
	t_llint				ll;
	t_ullint			ull;
	wchar_t				wchar;
	wchar_t*			wstr;
};

typedef struct			s_fmt
{
	int					flag_char[5];
	int					width;
	int					precision;
	enum e_flag_mlen	flag_mlen;
	char				convch;
	union u_type		type;
	int					prefix;
	int					len;
}						t_fmt;

int		parse_fmt(t_fmt *fmt, char *fmt_string);
char	*init_nbr(t_fmt *fmt, va_list *args, char nb[128], int base);
char	*init_unbr(t_fmt *fmt, va_list *args, char nb[128], int base);
int		init_fmt(t_fmt *fmt);
int		init_fmt_spec(t_fmt *fmt, char convch);
int		init_wchar(t_uchar *buff, wchar_t c, int *len);
int		add_prefix_hexa(t_buffer_static *sbuff, char convch, int *len);
int		do_preci_and_fill(t_fmt *fmt, t_buffer_static *sbuff, char *val, char sign);
int		do_preci_and_fill_spec(t_fmt *fmt, t_buffer_static *sbuff, char *val);
int 	do_preci_and_fill_spec2(t_fmt *fmt, t_buffer_static *sbuff, char *val);
int		fix_count_signed(t_fmt *fmt, int nbrlen);
int		fix_count_unsigned(t_fmt *fmt, int nbrlen);
int 	fix_count_unsigned1(t_fmt *fmt, int nbrlen, char *ptr);
int		do_sign(t_fmt *fmt, t_buffer_static *sbuff, t_llint nbr, int *ret);
void	do_space(t_buffer_static *sbuff, int width, int *nbrlen, int *ret);
void 	more_speed_signed(t_fmt *fmt, t_buffer_static *sbuff, char *val, int *ret);
void	more_speed_hexa(t_fmt *fmt, t_buffer_static *sbuff, char *ptr, int *ret);
void	ret_error(int *ret);
void	noconvert(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret);
void	convert_str(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret);
void	convert_char(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret);
void	convert_int(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret);
void	convert_uint(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret);
void	convert_octal(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret);
void	convert_hexa(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret);
void	convert_wchar(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret);
void	convert_wstr(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret);
void	convert_binary(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret);

#endif
