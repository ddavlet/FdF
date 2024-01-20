/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:24:05 by ddavlety          #+#    #+#             */
/*   Updated: 2023/11/20 14:00:48 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	tmp = lst;
	while (tmp)
	{
		ft_lstadd_back(&new_lst, ft_lstnew(f(tmp->content)));
		if (!ft_lstlast(new_lst))
			ft_lstclear(&new_lst, del);
		tmp = tmp->next;
	}
	return (new_lst);
}
