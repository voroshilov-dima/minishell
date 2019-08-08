#include "minishell.h"

t_dictionary	*dictionary_new(char *key, char *value)
{
	t_dictionary *dict;

	if ((dict = (t_dictionary *)malloc(sizeof(t_dictionary))))
	{
		dict->key = ft_strdup(key);
		dict->value = ft_strdup(value);
		dict->next = NULL;
		return (dict);
	}
	else
		return (NULL);
}

