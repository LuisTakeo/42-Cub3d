#include "lib/libft/libft.h"
#include <stdbool.h>
#include <stdlib.h>

#define FT_VECTOR_INITIAL_CAPACITY 16

typedef struct s_vector
{
	void			**values;
	unsigned long	size;
	unsigned long	capacity;
}					t_vector;

void	*ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
	void	*new;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (malloc(new_size));
	else if (new_size <= original_size)
		return (ptr);
	else
	{
		new = malloc(new_size);
		if (!new)
		{
			free(ptr);
			return (NULL);
		}
		ft_memcpy(new, ptr, original_size);
		free(ptr);
		return (new);
	}
}

void	ft_vector_init(t_vector *vector)
{
	free(vector->values);
	vector->values = NULL;
	vector->capacity = 0;
	vector->size = 0;
}

bool	ft_vector_empty(const t_vector *vector)
{
	if (vector == NULL)
		return (true);
	return (vector->size == 0);
}

bool	ft_vector_resize(t_vector *vector, unsigned long new_capacity)
{
	void	*new_values;

	if (!vector)
		return (false);
	if ((int)new_capacity < 0)
		return (false);
	if (new_capacity == 0)
	{
		ft_vector_init(vector);
		return (true);
	}
	if (new_capacity < vector->size)
		new_capacity = vector->size;
	new_values = ft_realloc(vector->values, vector->capacity * sizeof(void *),
			new_capacity * sizeof(long));
	if (new_values == NULL)
		return (false);
	vector->values = new_values;
	vector->capacity = new_capacity;
	if (new_capacity < vector->size)
		vector->size = new_capacity;
	return (true);
}

unsigned long	ft_vector_insert(t_vector *vector, unsigned long position,
		void *value)
{
	unsigned long	new_capacity;
	unsigned long	i;

	if (vector == NULL)
		return (0);
	if (position > vector->size)
		return (0);
	if (vector->size >= vector->capacity)
	{
		new_capacity = vector->capacity + (vector->capacity >> 1);
		if (!ft_vector_resize(vector, new_capacity))
			return (0);
	}
	i = vector->size;
	while (i > position)
	{
		vector->values[i] = vector->values[i - 1];
		--i;
	}
	vector->values[position] = value;
	vector->size++;
	return (position);
}

void	ft_vector_reserve(t_vector *vector, unsigned long new_capacity)
{
	if (vector == NULL)
		return ;
	if (new_capacity > vector->capacity)
	{
		if (!ft_vector_resize(vector, new_capacity))
			return ;
	}
}

t_vector	*ft_vector_create(void)
{
	t_vector	*new_vector;

	new_vector = malloc(sizeof * new_vector);
	if (new_vector == NULL)
		return (NULL);
	new_vector->size = 0;
	new_vector->capacity = FT_VECTOR_INITIAL_CAPACITY;
	new_vector->values = malloc(new_vector->capacity * sizeof(void *));
	if (new_vector->values == NULL)
	{
		free(new_vector);
		return (NULL);
	}
	return (new_vector);
}

void	ft_vector_push_back(t_vector *vector, void *value)
{
	unsigned long	new_capacity;

	if (vector == NULL)
		return ;
	if (vector->size >= vector->capacity)
	{
		new_capacity = vector->capacity + (vector->capacity >> 1);
		if (!ft_vector_resize(vector, new_capacity))
			return ;
	}
	vector->values[vector->size] = value;
	vector->size++;
}

void	ft_vector_free(t_vector *vector)
{
	if (vector == NULL)
		return ;
	free(vector->values);
	free(vector);
}

void	ft_vector_pop_back(t_vector *vector)
{
	if (vector == NULL)
		return ;
	if (ft_vector_empty(vector))
		return ;
	//caso queira realmente apagar
	// ft_vector_erase(vector, vector->size - 1);
	// apenas diminui a size do vector
	vector->size--;
}

void	ft_vector_pop_front(t_vector *vector)
{
	unsigned long	i;

	if (vector == NULL)
		return ;
	if (ft_vector_empty(vector))
		return ;
	i = 0;
	while (i < vector->size - 1)
	{
		vector->values[i] = vector->values[i + 1];
		++i;
	}
	vector->size--;
}

void	ft_vector_erase(t_vector *vector, unsigned long position)
{
	unsigned long	i;

	if (vector == NULL)
		return ;
	if (position >= vector->size)
		return ;
	i = position;
	while (i < vector->size - 1)
	{
		vector->values[i] = vector->values[i + 1];
		++i;
	}
	vector->size--;
}

void	*ft_vector_at(const t_vector *vector, unsigned long index)
{
	if (vector == NULL)
		return (0);
	if (index >= vector->size)
		return (0);
	return (vector->values[index]);
}

void	*ft_value(const t_vector *vector, unsigned long i, unsigned long j)
{
	t_vector	*inner_vector;

	if (vector == NULL)
		return (0);
	if (i >= vector->size)
		return (0);
	inner_vector = vector->values[i];
	if (inner_vector == NULL)
		return (0);
	if (j >= inner_vector->size)
		return (0);
	return (inner_vector->values[j]);
}

int	ft_value_int(const t_vector *vector, unsigned long i, unsigned long j)
{
	return (*(int *)ft_value(vector, i, j));
}

unsigned long	ft_vector_size(const t_vector *vector)
{
	if (vector == NULL)
		return (-1);
	return (vector->size);
}

void	**ft_vector_data(const t_vector *vector)
{
	if (vector == NULL)
		return (NULL);
	return (vector->values);
}

bool	ft_vector_emplace_back(t_vector *vector, void *value)
{
	unsigned long	new_capacity;

	if (vector == NULL)
		return (false);
	if (vector->size >= vector->capacity)
	{
		new_capacity = vector->capacity + (vector->capacity >> 1);
		if (!ft_vector_resize(vector, new_capacity))
			return (false);
	}
	vector->values[vector->size++] = value;
	return (true);
}

bool	ft_vector_resize_and_default(t_vector *vector,
		unsigned long new_capacity, void *default_value)
{
	void			**new_values;
	unsigned long	i;

	if (vector == NULL)
		return (false);
	if (new_capacity < vector->size)
		new_capacity = vector->size;
	new_values = ft_realloc(vector->values, vector->capacity * sizeof(void *),
			new_capacity * sizeof(void *));
	if (new_values == NULL)
		return (false);
	i = vector->capacity;
	while (i < new_capacity)
	{
		new_values[i] = default_value;
		i++;
	}
	vector->values = new_values;
	vector->capacity = new_capacity;
	if (new_capacity < vector->size)
		vector->size = new_capacity;
	return (true);
}

void	**ft_vector_rbegin(const t_vector *vector)
{
	if (vector == NULL || vector->size == 0)
		return (NULL);
	return (&(vector->values[vector->size - 1]));
}

void	ft_vector_operator_equals(t_vector *dest, const t_vector *src)
{
	unsigned long	i;

	if (dest == NULL || src == NULL)
		return ;
	ft_vector_resize(dest, src->size);
	i = 0;
	while (i < src->size)
	{
		dest->values[i] = src->values[i];
		i++;
	}
	dest->size = src->size;
}

void	*ft_vector_operator_index(const t_vector *vector, unsigned long index)
{
	if (vector == NULL || index >= vector->size)
		return (NULL);
	return (vector->values[index]);
}

void	**ft_vector_end(const t_vector *vector)
{
	if (vector == NULL || vector->size == 0)
		return (NULL);
	return (&(vector->values[vector->size]));
}

const void	**ft_vector_crend(const t_vector *vector)
{
	if (vector == NULL || vector->size == 0)
		return (NULL);
	return ((const void **)&(vector->values[-1]));
}

const void	**ft_vector_crbegin(const t_vector *vector)
{
	if (vector == NULL || vector->size == 0)
		return (NULL);
	return ((const void **)&(vector->values[vector->size - 1]));
}

const void	**ft_vector_cend(const t_vector *vector)
{
	if (vector == NULL || vector->size == 0)
		return (NULL);
	return ((const void **)&(vector->values[vector->size]));
}

const void	**ft_vector_cbegin(const t_vector *vector)
{
	if (vector == NULL || vector->size == 0)
		return (NULL);
	return ((const void **)&(vector->values[0]));
}

void	**ft_vector_begin(const t_vector *vector)
{
	if (vector == NULL || vector->size == 0)
		return (NULL);
	return (&(vector->values[0]));
}

void	**ft_vector_rend(const t_vector *vector)
{
	if (vector == NULL || vector->size == 0)
		return (NULL);
	return ((void **)&(vector->values[-1]));
}

int	ft_vector_find(t_vector *vector, void *item, int (*cmp)(void *, void *))
{
	unsigned long	i;

	if (vector == NULL || item == NULL || cmp == NULL)
		return (-1);
	i = 0;
	while (i < vector->size)
	{
		if (cmp(vector->values[i], item) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_vector_swap(t_vector *vector1, t_vector *vector2)
{
	void			**temp_values;
	unsigned long	temp_size;
	unsigned long	temp_capacity;

	if (vector1 == NULL || vector2 == NULL)
		return ;
	temp_values = vector1->values;
	temp_size = vector1->size;
	temp_capacity = vector1->capacity;
	vector1->values = vector2->values;
	vector1->size = vector2->size;
	vector1->capacity = vector2->capacity;
	vector2->values = temp_values;
	vector2->size = temp_size;
	vector2->capacity = temp_capacity;
}

// essa funcao substitui um valor na pos pelo valor que voce quiser
void	ft_vector_set(t_vector *vector, int pos, void *value)
{
	if (pos >= 0 && pos < vector->size)
		vector->values[pos] = value;
}

// cria um subvector a partir de outro vetor,
// recebendo o inicio daonde vc quer e o tamanho do vetor que voce vai criar
t_vector	*ft_vector_subvector(t_vector *vector, int start, int length)
{
	t_vector	*subvector;
	int			i;

	subvector = ft_vector_create();
	if (start < 0 || start >= vector->size || length < 0 || start
		+ length > vector->size)
		return (subvector);
	i = start;
	while (i < start + length)
	{
		ft_vector_push_back(subvector, ft_vector_at(vector, i));
		i++;
	}
	return (subvector);
}

// passar os valores de um vetor para outro ja criado
void	ft_vector_assign(t_vector *dest, const t_vector *src)
{
	unsigned long	i;

	if (dest == NULL || src == NULL)
		return ;
	ft_vector_resize(dest, src->size);
	i = 0;
	while (i < src->size)
	{
		dest->values[i] = src->values[i];
		i++;
	}
	dest->size = src->size;
}

// cria um vetor novo clon do passado como argumento
t_vector	*ft_vector_clone(const t_vector *vector)
{
	t_vector		*new_vector;
	unsigned long	i;

	if (vector == NULL)
		return (NULL);
	new_vector = ft_vector_create();
	if (new_vector == NULL)
		return (NULL);
	if (!ft_vector_resize(new_vector, vector->capacity))
	{
		ft_vector_free(new_vector);
		return (NULL);
	}
	i = 0;
	while (i < vector->size)
	{
		new_vector->values[i] = vector->values[i];
		i++;
	}
	new_vector->size = vector->size;
	return (new_vector);
}

// retorna o ultimo valor do vetor
void	*ft_vector_back(const t_vector *vector)
{
	if (vector == NULL || vector->size == 0)
		return (NULL);
	return (vector->values[vector->size - 1]);
}

// retorna o primeiro valor do vetor
void	*ft_vector_front(const t_vector *vector)
{
	if (vector == NULL || vector->size == 0)
		return (NULL);
	return (vector->values[0]);
}

// da resize no vetor pra ficar com a capacidade perfeita do size
bool	ft_vector_shrink_to_fit(t_vector *vector)
{
	if (vector == NULL)
		return (false);
	return (ft_vector_resize(vector, vector->size));
}

// insere um valor na posicao que voce quer
// e apaga o valor original na posicao original
void	ft_vector_insert_and_erase(t_vector *vector, unsigned long insert_pos,
		unsigned long erase_pos, void *value)
{
	if (vector == NULL)
		return ;
	if (ft_vector_insert(vector, insert_pos, value) == -1)
		return ;
	if (erase_pos >= insert_pos)
		erase_pos++;
	ft_vector_erase(vector, erase_pos);
}

// push_back e apaga o valor e posicao antigos
void	ft_vector_push_back_and_erase(t_vector *dest, t_vector *src,
		unsigned long pos_to_erase)
{
	void			*value;
	unsigned long	new_capacity;

	// unsigned long	i;
	if (src == NULL || pos_to_erase >= src->size)
		return ;
	value = src->values[pos_to_erase];
	if (dest->size >= dest->capacity)
	{
		new_capacity = dest->capacity + (dest->capacity >> 1);
		if (!ft_vector_resize(dest, new_capacity))
			return ;
	}
	dest->values[dest->size] = value;
	dest->size++;
	// i = pos_to_erase;
	// while (i < src->size - 1)
	//{
	//	src->values[i] = src->values[i + 1];
	//	i++;
	//}
	// src->size--;
	ft_vector_erase(src, pos_to_erase);
}

void	ft_vector_push_front(t_vector *vector, void *value)
{
	unsigned long	new_capacity;
	unsigned long	i;

	if (vector == NULL)
		return ;
	if (vector->size >= vector->capacity)
	{
		new_capacity = vector->capacity + (vector->capacity >> 1);
		if (!ft_vector_resize(vector, new_capacity))
			return ;
	}
	i = vector->size;
	while (i > 0)
	{
		vector->values[i] = vector->values[i - 1];
		i--;
	}
	vector->values[0] = value;
	vector->size++;
}
