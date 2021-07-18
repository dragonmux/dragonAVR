// SPDX-License-Identifier: BSD-3-Clause
#ifndef BITS_RANGE_ACCESS_HXX
#define BITS_RANGE_ACCESS_HXX

#include <cstddef>
#include <initializer_list>
#include <iterator>

namespace std
{
	template<typename container_t>
		constexpr inline auto begin(container_t &cont) -> decltype(cont.begin()) { return cont.begin(); }

	template<typename container_t>
		constexpr inline auto begin(const container_t &cont) -> decltype(cont.begin()) { return cont.begin(); }

	template<typename container_t>
		constexpr inline auto end(container_t &cont) -> decltype(cont.end()) { return cont.end(); }

	template<typename container_t>
		constexpr inline auto end(const container_t &cont) -> decltype(cont.end()) { return cont.end(); }

	template<typename T, size_t N> constexpr inline T *begin(T (&arr)[N]) { return arr; }
	template<typename T, size_t N> constexpr inline T *end(T (&arr)[N]) { return arr + N; }

	template<typename T> struct valarray;
	template<typename T> T *begin(valarray<T> &);
	template<typename T> const T *begin(const valarray<T> &);
	template<typename T> T *end(valarray<T> &);
	template<typename T> const T *end(const valarray<T> &);

	template<typename container_t> constexpr inline auto cbegin(const container_t &cont)
		noexcept(noexcept(std::begin(cont))) -> decltype(begin(cont)) { return begin(cont); }

	template<typename container_t> constexpr inline auto cend(const container_t &cont)
		noexcept(noexcept(std::end(cont))) -> decltype(end(cont)) { return end(cont); }

	template<typename container_t>
		constexpr inline auto rbegin(container_t &cont) -> decltype(cont.rbegin()) { return cont.rbegin(); }

	template<typename container_t>
		constexpr inline auto rbegin(const container_t &cont) -> decltype(cont.rbegin()) { return cont.rbegin(); }

	template<typename container_t>
		constexpr inline auto rend(container_t &cont) -> decltype(cont.rend()) { return cont.rend(); }

	template<typename container_t>
		constexpr inline auto rend(const container_t &cont) -> decltype(cont.rend()) { return cont.rend(); }

	template<typename T, size_t N> constexpr inline reverse_iterator<T *> rbegin(T (&arr)[N])
		{ return reverse_iterator<T *>{arr + N}; }
	template<typename T, size_t N> constexpr inline reverse_iterator<T *> rend(T (&arr)[N])
		{ return reverse_iterator<T *>{arr}; }

	template<typename T, size_t N> constexpr inline reverse_iterator<T *> rbegin(initializer_list<T> list)
		{ return reverse_iterator<const T *>{list.end()}; }
	template<typename T, size_t N> constexpr inline reverse_iterator<T *> rend(initializer_list<T> list)
		{ return reverse_iterator<const T *>{list.begin()}; }

	template<typename container_t> constexpr inline auto crbegin(const container_t &cont)
		noexcept(noexcept(std::rbegin(cont))) -> decltype(rbegin(cont)) { return rbegin(cont); }

	template<typename container_t> constexpr inline auto crend(const container_t &cont)
		noexcept(noexcept(std::rend(cont))) -> decltype(rend(cont)) { return rend(cont); }

	template<typename container_t> constexpr auto size(const container_t &cont) noexcept(noexcept(cont.size())) ->
		decltype(cont.size()) { return cont.size(); }

	template<typename T, size_t N> constexpr size_t size(const T (&)[N]) noexcept { return N; }

	template<typename container_t>
		[[nodiscard]] constexpr auto empty(const container_t &cont)
			noexcept(noexcept(cont.empty())) -> decltype(cont.empty()) { return cont.empty(); }

	template<typename T, size_t N> [[nodiscard]] constexpr bool empty(const T (&)[N]) noexcept { return false; }

	template<typename container_t> constexpr auto data(container_t &cont)
		noexcept(noexcept(cont.data())) -> decltype(cont.data())  { return cont.data(); }

	template<typename T, size_t N> constexpr T *data(T (&array)[N]) noexcept { return array; }

	template<typename T> constexpr const T *data(initializer_list<T> list) noexcept { return list.begin(); }

	template<typename container_t> constexpr auto ssize(const container_t &cont) noexcept(noexcept(cont.size()))
		-> common_type_t<ptrdiff_t, make_signed_t<decltype(cont.size())>>
	{
		using type = make_signed_t<decltype(cont.size())>;
		return static_cast<common_type_t<ptrdiff_t, type>>(cont.size());
	}

	template<typename T, ptrdiff_t N> constexpr ptrdiff_t ssize(const T (&)[N]) noexcept { return N; }
} // namespace std

#endif /*BITS_RANGE_ACCESS_HXX*/
