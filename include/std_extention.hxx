/**
 * @file std_extention.hxx
 * @author Felixaszx (felixaszx@outlook.com)
 * @brief Core defines and help tempaltes for xtd
 * @version 0.1
 * @date 2025-07-12
 *
 * @copyright MIT License Copyright (c) 2025
 *
 */

#ifndef STD_EXTENTION_HXX
#define STD_EXTENTION_HXX

#include <cstdint>
#include <climits>
#include <concepts>
#include <numeric>
#include <atomic>
#include <type_traits>

#define STD_EXT_HPP_NAMESPACE         std_ext
#define STD_EXT_HPP_NAMESPACE_CAPITAL STD_EXT

namespace STD_EXT_HPP_NAMESPACE::i_ // internal namespace
{
    template <typename L>
    struct limit_v_t
    {
        template <typename M>
        inline static const M as = L::template as<M>;
    };

    template <typename M, typename L>
    inline constexpr bool //
    operator<(const M& x, const limit_v_t<L>& y)
    {
        (void)y;
        return x < limit_v_t<L>::template as<M>;
    }

    template <typename M, typename L>
    inline constexpr bool //
    operator<=(const M& x, const limit_v_t<L>& y)
    {
        (void)y;
        return x <= limit_v_t<L>::template as<M>;
    }

    template <typename M, typename L>
    inline constexpr bool //
    operator>(const M& x, const limit_v_t<L>& y)
    {
        (void)y;
        return x > limit_v_t<L>::template as<M>;
    }

    template <typename M, typename L>
    inline constexpr bool //
    operator>=(const M& x, const limit_v_t<L>& y)
    {
        (void)y;
        return x >= limit_v_t<L>::template as<M>;
    }

    template <typename M, typename L>
    inline constexpr bool //
    operator==(const M& x, const limit_v_t<L>& y)
    {
        (void)y;
        return x == limit_v_t<L>::template as<M>;
    }

    template <bool S = false>
    struct max_v_t : public limit_v_t<max_v_t<S>>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            if constexpr (S)
            {
                return -std::numeric_limits<M>::max();
            }
            else
            {
                return std::numeric_limits<M>::max();
            }
        }

        inline consteval const max_v_t<!S> //
        operator-() const
        {
            return max_v_t<!S>();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::max();
    };

    template <bool S = false>
    struct min_v_t : public limit_v_t<min_v_t<S>>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            if constexpr (S)
            {
                return -std::numeric_limits<M>::min();
            }
            else
            {
                return std::numeric_limits<M>::min();
            }
        }

        inline consteval const min_v_t<!S> //
        operator-() const
        {
            return min_v_t<!S>();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::min();
    };

    template <bool S = false>
    struct inf_v_t : public limit_v_t<inf_v_t<S>>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            if constexpr (S)
            {
                return -std::numeric_limits<M>::infinity();
            }
            else
            {
                return std::numeric_limits<M>::infinity();
            }
        }

        inline consteval const inf_v_t<!S> //
        operator-() const
        {
            return inf_v_t<!S>();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::infinity();
    };

    template <bool S = false>
    struct epsilon_v_t : public limit_v_t<epsilon_v_t<S>>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            if constexpr (S)
            {
                return -std::numeric_limits<M>::epsilon();
            }
            else
            {
                return std::numeric_limits<M>::epsilon();
            }
        }

        inline consteval const epsilon_v_t<!S> //
        operator-() const
        {
            return epsilon_v_t<!S>();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::epsilon();
    };

    template <bool S = false>
    struct lowest_v_t : public limit_v_t<lowest_v_t<S>>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            if constexpr (S)
            {
                return -std::numeric_limits<M>::lowest();
            }
            else
            {
                return std::numeric_limits<M>::lowest();
            }
        }

        inline consteval const lowest_v_t<!S> //
        operator-() const
        {
            return lowest_v_t<!S>();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::lowest();
    };

    struct quiet_NaN_v_t : public limit_v_t<quiet_NaN_v_t>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            return std::numeric_limits<M>::quiet_NaN();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::quiet_NaN();
    };

    struct sig_NaN_v_t : public limit_v_t<sig_NaN_v_t>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            return std::numeric_limits<M>::signaling_NaN();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::signaling_NaN();
    };

    template <bool S = false>
    struct round_error_v_t : public limit_v_t<round_error_v_t<S>>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            if constexpr (S)
            {
                return -std::numeric_limits<M>::round_error();
            }
            else
            {
                return std::numeric_limits<M>::round_error();
            }
        }

        inline consteval const round_error_v_t<!S> //
        operator-() const
        {
            return round_error_v_t<!S>();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::round_error();
    };

    template <bool S = false>
    struct denorm_min_v_t : public limit_v_t<denorm_min_v_t<S>>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            if constexpr (S)
            {
                return -std::numeric_limits<M>::denorm_min();
            }
            else
            {
                return std::numeric_limits<M>::denorm_min();
            }
        }

        inline consteval const denorm_min_v_t<!S> //
        operator-() const
        {
            return denorm_min_v_t<!S>();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::denorm_min();
    };
}; // namespace STD_EXT_HPP_NAMESPACE::i_

namespace STD_EXT_HPP_NAMESPACE_CAPITAL
{
    using i8 = std::int8_t;
    using u8 = std::uint8_t;
    using i16 = std::int16_t;
    using u16 = std::uint16_t;
    using i32 = std::int32_t;
    using u32 = std::uint32_t;
    using i64 = std::int64_t;
    using u64 = std::uint64_t;
    using imax = std::intmax_t;
    using umax = std::uintmax_t;
    using usz = std::size_t;
    using ssz = std::ptrdiff_t;
    using ptrdiff = std::ptrdiff_t;

    using uchar = unsigned char;
    using char8 = char8_t;
    using char16 = char16_t;
    using char32 = char32_t;

    using f32 = float;
    using f64 = double;

    // atomic variants
    using atomic_bool = std::atomic<bool>;
    using atomic_i8 = std::atomic<i8>;
    using atomic_u8 = std::atomic<u8>;
    using atomic_i16 = std::atomic<i16>;
    using atomic_u16 = std::atomic<u16>;
    using atomic_i32 = std::atomic<i32>;
    using atomic_u32 = std::atomic<u32>;
    using atomic_i64 = std::atomic<i64>;
    using atomic_u64 = std::atomic<u64>;
    using atomic_imax = std::atomic<imax>;
    using atomic_umax = std::atomic<umax>;
    using atomic_usz = std::atomic<usz>;
    using atomic_ssz = std::atomic<ssz>;
    using atomic_ptrdiff = std::atomic<ptrdiff>;

    using atomic_char = std::atomic<char>;
    using atomic_uchar = std::atomic<uchar>;
    using atomic_char8 = std::atomic<char8>;
    using atomic_char16 = std::atomic<char16>;
    using atomic_char32 = std::atomic<char32>;

    inline static const std_ext::i_::quiet_NaN_v_t quiet_NaN = {};
    inline static const std_ext::i_::sig_NaN_v_t sig_NaN = {};
    inline static const std_ext::i_::quiet_NaN_v_t nan_v = {};

    inline static const std_ext::i_::min_v_t min_v = {};
    inline static const std_ext::i_::lowest_v_t lowest_v = {};
    inline static const std_ext::i_::max_v_t max_v = {};
    inline static const std_ext::i_::epsilon_v_t epsilon_v = {};
    inline static const std_ext::i_::round_error_v_t round_err_v = {};
    inline static const std_ext::i_::inf_v_t inf_v = {};
    inline static const std_ext::i_::denorm_min_v_t denorm_min_v = {};
}; // namespace STD_EXT_HPP_NAMESPACE_CAPITAL

namespace STD_EXT_HPP_NAMESPACE
{
    using namespace STD_EXT_HPP_NAMESPACE_CAPITAL;

    template <typename T>
    inline constexpr auto //
    aligned [[nodiscard]] (const T& size, std::size_t alignment) noexcept
        requires std::is_arithmetic_v<T>
    {
        return alignment * ((size - 1) / alignment) + alignment;
    }

    template <typename T>
    inline constexpr auto //
    align(T& size, std::size_t alignment) noexcept
        requires std::is_arithmetic_v<T>
    {
        size = aligned(size, alignment);
        return size;
    }

    // retuns number of elements in a given array
    template <typename T>
        requires std::is_bounded_array_v<T>
    inline constexpr auto //
    elmsof [[nodiscard]] (const T& arr) noexcept
    {
        return sizeof(T) / sizeof(arr[0]);
    }

    template <typename T>
    concept sizeof2_compatible = requires(T container) //
    {
        { container.size() } -> std::convertible_to<std::size_t>;
        { sizeof(typename std::remove_cvref_t<decltype(container)>::value_type) } -> std::convertible_to<std::size_t>;
    };
}; // namespace STD_EXT_HPP_NAMESPACE

namespace STD_EXT_HPP_NAMESPACE::literals
{
    inline consteval std::size_t //
    operator""_b(unsigned long long size)
    {
        return size;
    }

    inline consteval std::size_t //
    operator""_kb(unsigned long long size)
    {
        return 1024_b * size;
    }

    inline consteval std::size_t //
    operator""_mb(unsigned long long size)
    {
        return 1024_kb * size;
    }

    inline consteval std::size_t //
    operator""_gb(unsigned long long size)
    {
        return 1024_mb * size;
    }

    inline consteval std::int8_t //
    operator""_i8(unsigned long long i)
    {
        return static_cast<std::int8_t>(i);
    }

    inline consteval std::uint8_t //
    operator""_u8(unsigned long long i)
    {
        return static_cast<std::uint8_t>(i);
    }

    inline consteval std::int16_t //
    operator""_i16(unsigned long long i)
    {
        return static_cast<std::int16_t>(i);
    }

    inline consteval std::uint16_t //
    operator""_u16(unsigned long long i)
    {
        return static_cast<std::uint16_t>(i);
    }

    inline consteval std::int32_t //
    operator""_i32(unsigned long long i)
    {
        return static_cast<std::int32_t>(i);
    }

    inline consteval std::uint32_t //
    operator""_u32(unsigned long long i)
    {
        return static_cast<std::uint32_t>(i);
    }

    inline consteval std::int64_t //
    operator""_i64(unsigned long long i)
    {
        return static_cast<std::int64_t>(i);
    }

    inline consteval std::uint64_t //
    operator""_u64(unsigned long long i)
    {
        return static_cast<std::uint64_t>(i);
    }

    inline consteval std::intmax_t //
    operator""_imax(unsigned long long i)
    {
        return static_cast<std::intmax_t>(i);
    }

    inline consteval std::uintmax_t //
    operator""_umax(unsigned long long i)
    {
        return static_cast<std::uintmax_t>(i);
    }

    inline consteval std::size_t //
    operator""_usz(unsigned long long i)
    {
        return static_cast<std::size_t>(i);
    }

    inline consteval std::ptrdiff_t //
    operator""_ssz(unsigned long long i)
    {
        return static_cast<std::ptrdiff_t>(i);
    }

    inline consteval std::ptrdiff_t //
    operator""_ptrdiff(unsigned long long i)
    {
        return static_cast<std::ptrdiff_t>(i);
    }

}; // namespace STD_EXT_HPP_NAMESPACE::literals

#if !defined(STD_EXT_NO_NAMESPACE)
using namespace STD_EXT_HPP_NAMESPACE_CAPITAL;
using namespace STD_EXT_HPP_NAMESPACE;
using namespace STD_EXT_HPP_NAMESPACE::literals;

    #define castc(to, from) const_cast<to>(from)
    #define castd(to, from) dynamic_cast<to>(from)
    #define castr(to, from) reinterpret_cast<to>(from)
    #define casts(to, from) static_cast<to>(from)
    #define castf(to, from) (to)(from)
    #define restrict __restrict
#endif

#endif // STD_EXTENTION_HXX
