#include "minishell.h"

t_dictionary	*string_to_dictionary(char *str)
{
	t_dictionary	*dict;
	int				len;
	int				equal_sign_pos;
	

	if ((dict = (t_dictionary *)malloc(sizeof(t_dictionary))))
	{
		equal_sign_pos = 0;
		while (str[equal_sign_pos] != '=')
			equal_sign_pos++;
		len = ft_strlen(str);
		dict->key = ft_strsub(str, 0, equal_sign_pos);
		dict->value = ft_strsub(str, equal_sign_pos + 1, len);
		dict->next = NULL;
		return (dict);
	}
	else
		return (NULL);
}

void			dictionary_append(t_dictionary *main, t_dictionary *new)
{
	while (main->next)
		main = main->next;
	main->next = new;
}