/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_filler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 00:13:52 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/19 17:24:30 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int do_filler(t_buffer_static *sbuff, void *str, size_t size)
{
	//ft_putendlcolor("DEBUG | start do_fill", C_LBLUE);
	//int buff_len;
	int ret;
	//sleep(2);
	ret = 0;
	if (!str)
		return (0);
	if (size <= BUFF_SIZE_INIT)
	{
		//ft_putendlcolor("DEBUG | do_fill => size <= BUFF_SIZE_INIT", C_LBLUE);
		//buff_len = sbuff->buff_size - sbuff->remaining_size;
		while (!fill_buffer_static(sbuff, str, size))
		{
			write(1, sbuff->buffer, sbuff->used_size);
			ret += sbuff->used_size;
			init_buffer_static(sbuff);
		}
		return (ret);
	}
	else
	{
		//ft_putendlcolor("DEBUG | do_fill => size > BUFF_SIZE_INIT", C_LBLUE);
		unsigned int i;
		//printf("size:%zu, buff_len:%d, str:%s\n", size, buff_len, str);
		i = -1;
		write(1, sbuff->buffer, sbuff->used_size);
		ret += sbuff->used_size;
		init_buffer_static(sbuff);
		while (++i < size)
		{
			//buff_len = sbuff->buff_size - sbuff->remaining_size;
			//printf("buff_len:%d\tstr[%d](%p):'%c'\n", buff_len, i, str + i, *(str + i));
			while (!fill_buffer_static(sbuff, str + i, 1))
			{
				write(1, sbuff->buffer, sbuff->used_size);
				ret += sbuff->used_size;
				init_buffer_static(sbuff);
			}
			//i++;
		}
		return (ret);
	}
	return (ret);
}

int do_filler_n(t_buffer_static *sbuff, void *c, size_t n)
{
	//ft_putendlcolor("DEBUG | start do_fill", C_LBLUE);
	//printf("size:%zu\n", n);
	//sleep(2);
	//int buff_len;
	unsigned int i;
	int ret;
	//sleep(2);
	ret = 0;
	if (n <= BUFF_SIZE_INIT)
	{
		//ft_putendlcolor("DEBUG | do_fill => size <= BUFF_SIZE_INIT", C_LBLUE);
		//buff_len = sbuff->buff_size - sbuff->remaining_size;
		while (!filln_buffer_static(sbuff, (void*)c, n))
		{
			//printf("%zu\n", n);
			//sleep(2);
			write(1, sbuff->buffer, sbuff->used_size);
			ret += sbuff->used_size;
			init_buffer_static(sbuff);
		}
	}
	else
	{
		//buff_len = sbuff->buff_size - sbuff->remaining_size;
		//ft_putendlcolor("DEBUG | do_fill => size > BUFF_SIZE_INIT", C_LBLUE);
		//printf("size:%zu, buff_len:%d, str:%s\n", size, buff_len, str);
		i = -1;
		write(1, sbuff->buffer, sbuff->used_size);
		ret += sbuff->used_size;
		init_buffer_static(sbuff);
		while (++i < n)
		{
				//printf("n=%zu\ti=%u\n", n, i);
			//sleep(2);
			//buff_len = sbuff->buff_size - sbuff->remaining_size;
			//printf("buff_len:%d\tstr[%d](%p):'%c'\n", buff_len, i, str + i, *(str + i));
			while (!filln_buffer_static(sbuff, (void*)c, 1))
			{
				write(1, sbuff->buffer, sbuff->used_size);
				ret += sbuff->used_size;
				init_buffer_static(sbuff);
			}
			//i++;
		}
	}
	return (ret);
}

int do_filler_wstr(t_buffer_static *sbuff, wchar_t *wstr, size_t n)
{
	unsigned char c[5];
	int len;
	int ret;
	unsigned int i;
	unsigned int j;


	//printf("len:%zu", n);
	if (!sbuff || !wstr)
		return (0);
	if (!n)
		return (-1);
	ret = 0;
	len = 0;
	i = 0;
	j = 0;
	while (j < n)
	{
		//printf("par la\n");
		if (!init_wchar(c, wstr[i], &len))
		{
			//printf("return(%d)\n", ret);
			return (ret);
		}
		//write(1, c, len);
		//printf("do_filler_wstr len:%d\n", len);
		ret += do_filler(sbuff, c, len);
		//printf("do_filler_wstr ret:%d, size:%zu\n", ret, sbuff->used_size);
		j += len;
		++i;
	}
	return (ret);
}