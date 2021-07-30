// SPDX-License-Identifier: BSD-3-Clause
#ifndef BITS_ITERATOR_HXX
#define BITS_ITERATOR_HXX

#include <type_traits>

namespace std
{
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template<typename category_t, typename T, typename distance_t = ptrdiff_t,
		typename pointer_t = T *, typename reference_t = T &> struct iterator
	{
		// One of the @link iterator_tags tag types@endlink.
		using iterator_category = category_t;
		// The type "pointed to" by the iterator.
		using value_type = T;
		// Distance between iterators is represented as this type.
		using difference_type = distance_t;
		// This type represents a pointer-to-value_type.
		using pointer = pointer_t;
		// This type represents a reference-to-value_type.
		using reference = reference_t;
	};

	template<typename iterator_t> struct iterator_traits;

	namespace impl
	{
		template<typename iterator_t, typename = std::void_t<>> struct iterator_traits { };

		template<typename iterator_t> struct iterator_traits<iterator_t,
			void_t<typename iterator_t::iterator_category, typename iterator_t::value_type,
				typename iterator_t::difference_type, typename iterator_t::pointer, typename iterator_t::reference>>
		{
			using iterator_category = typename iterator_t::iterator_category;
			using value_type = typename iterator_t::value_type;
			using difference_type = typename iterator_t::difference_type;
			using pointer = typename iterator_t::pointer;
			using reference = typename iterator_t::reference;
		};
	} // namespace impl

	template<typename iterator_t> struct iterator_traits : public impl::iterator_traits<iterator_t> { };

	template<typename T> struct iterator_traits<T *>
	{
		using iterator_category = random_access_iterator_tag;
		using value_type = T;
		using difference_type  = ptrdiff_t;
		using pointer = T *;
		using reference = T &;
	};

	template<typename T> struct iterator_traits<const T *>
	{
		using iterator_category = random_access_iterator_tag;
		using value_type = T;
		using difference_type  = ptrdiff_t;
		using pointer = const T *;
		using reference = const T &;
	};
} // namespace std

#endif /*BITS_ITERATOR_HXX*/
