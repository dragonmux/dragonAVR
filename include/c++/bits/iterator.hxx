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

	namespace impl
	{
		template<typename iterator_t, typename container_t> struct normal_iterator
		{
		protected:
			iterator_t current;

			using traits_t = std::iterator_traits<iterator_t>;

		public:
			using iterator_type = iterator_t;
			using iterator_category = typename traits_t::iterator_category;
			using value_type = typename traits_t::value_type;
			using difference_type = typename traits_t::difference_type;
			using reference = typename traits_t::reference;
			using pointer = typename traits_t::pointer;

			constexpr normal_iterator() noexcept : current{iterator_t{}} { }
			explicit constexpr normal_iterator(const iterator_t &iter) noexcept : current{iter} { }

			template<typename iter_t> constexpr normal_iterator(const normal_iterator<iter_t,
				std::enable_if_t<std::is_same_v<iter_t, typename container_t::pointer>, container_t>> &iter) noexcept :
					current{iter.base()} { }

			constexpr reference operator *() const noexcept { return *current; }
			constexpr pointer operator ->() const noexcept { return current; }
			constexpr normal_iterator operator ++(int) noexcept { return normal_iterator{current++}; }
			constexpr normal_iterator operator --(int) noexcept { return normal_iterator{current--}; }
			constexpr reference operator [](const difference_type n) const noexcept { return current[n]; }
			constexpr normal_iterator operator +(const difference_type n) const noexcept
				{ return normal_iterator{current + n}; }
			constexpr normal_iterator operator -(const difference_type n) const noexcept
				{ return normal_iterator{current - n}; }
			constexpr const iterator_t &base() const noexcept { return current; }

			constexpr normal_iterator &operator ++() noexcept
			{
				++current;
				return *this;
			}

			constexpr normal_iterator &operator --() noexcept
			{
				--current;
				return *this;
			}

			constexpr normal_iterator &operator +=(const difference_type n) const noexcept
			{
				current += n;
				return *this;
			}

			constexpr normal_iterator &operator -=(const difference_type n) const noexcept
			{
				current -= n;
				return *this;
			}
		};
	} // impl
} // namespace std

#endif /*BITS_ITERATOR_HXX*/
