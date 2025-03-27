#pragma once

#include <cstddef>
#include <string_view>
#include <tuple>
#include <type_traits>

struct any_cast{
    constexpr any_cast(size_t);
    
    template<typename T>
    constexpr operator T() const;
};


template <typename reflect_t>
concept is_reflectable = requires(reflect_t r) {
    std::is_reference_v<reflect_t>;
    std::is_aggregate_v<reflect_t>;
};



template <is_reflectable reflect_t, size_t N, size_t... Is>
struct test_constructior_args_count{
    static constexpr bool value = test_constructior_args_count<reflect_t, N-1, N-1, Is...>::value;
};

template <is_reflectable reflect_t, size_t... Is>
struct test_constructior_args_count<reflect_t, 0, Is...>{
    static constexpr bool value = requires { reflect_t{any_cast{Is}...}; };
};

template <is_reflectable reflect_t, size_t N, size_t... Is>
static constexpr bool test_constructior_args_count_v = test_constructior_args_count<reflect_t, N, Is...>::value;


template <is_reflectable reflect_t, size_t N = 0>
constexpr size_t member_count(){
    if constexpr(test_constructior_args_count_v<reflect_t, N> && !test_constructior_args_count_v<reflect_t, N+1>){
        return N;
    } else {
        return member_count<reflect_t, N+1>();
    }
}


template <typename object_t>
constexpr static auto collect_members(object_t&& object) {
    constexpr size_t m_count = member_count<std::remove_reference_t<object_t>>();
    // clang-format off
    if constexpr (m_count == 0) {
        return std::tuple{};
    } else if constexpr (m_count == 1) {
        auto&& [e1] = object;
        return std::tuple{ &e1 };
    } else if constexpr (m_count == 2) {
        auto&& [e1, e2] = object;
        return std::tuple{ &e1, &e2 };
    } else if constexpr (m_count == 3) {
        auto&& [e1, e2, e3] = object;
        return std::tuple{ &e1, &e2, &e3 };
    } else if constexpr (m_count == 4) {
        auto&& [e1, e2, e3, e4] = object;
        return std::tuple{ &e1, &e2, &e3, &e4 };
    } else if constexpr (m_count == 5) {
        auto&& [e1, e2, e3, e4, e5] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5 };
    } else if constexpr (m_count == 6) {
        auto&& [e1, e2, e3, e4, e5, e6] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6 };
    } else if constexpr (m_count == 7) {
        auto&& [e1, e2, e3, e4, e5, e6, e7] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7 };
    } else if constexpr (m_count == 8) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8 };
    } else if constexpr (m_count == 9) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9 };
    } else if constexpr (m_count == 10) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10 };
    } else if constexpr (m_count == 11) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11 };
    } else if constexpr (m_count == 12) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12 };
    } else if constexpr (m_count == 13) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13 };
    } else if constexpr (m_count == 14) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14 };
    } else if constexpr (m_count == 15) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15 };
    } else if constexpr (m_count == 16) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16 };
    } else if constexpr (m_count == 17) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17 };
    } else if constexpr (m_count == 18) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18 };
    } else if constexpr (m_count == 19) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19 };
    } else if constexpr (m_count == 20) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20 };
    } else if constexpr (m_count == 21) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20, &e21 };
    } else if constexpr (m_count == 22) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20, &e21, &e22 };
    } else if constexpr (m_count == 23) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20, &e21, &e22, &e23 };
    } else if constexpr (m_count == 24) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20, &e21, &e22, &e23, &e24 };
    } else if constexpr (m_count == 25) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20, &e21, &e22, &e23, &e24, &e25 };
    } else if constexpr (m_count == 26) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20, &e21, &e22, &e23, &e24, &e25, &e26 };
    } else if constexpr (m_count == 27) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20, &e21, &e22, &e23, &e24, &e25, &e26, &e27 };
    } else if constexpr (m_count == 28) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20, &e21, &e22, &e23, &e24, &e25, &e26, &e27, &e28 };
    } else if constexpr (m_count == 29) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20, &e21, &e22, &e23, &e24, &e25, &e26, &e27, &e28, &e29 };
    } else if constexpr (m_count == 30) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20, &e21, &e22, &e23, &e24, &e25, &e26, &e27, &e28, &e29, &e30 };
    } else if constexpr (m_count == 31) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20, &e21, &e22, &e23, &e24, &e25, &e26, &e27, &e28, &e29, &e30, &e31 };
    } else if constexpr (m_count == 32) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20, &e21, &e22, &e23, &e24, &e25, &e26, &e27, &e28, &e29, &e30, &e31, &e32 };
    } else if constexpr (m_count == 33) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20, &e21, &e22, &e23, &e24, &e25, &e26, &e27, &e28, &e29, &e30, &e31, &e32, &e33 };
    } else if constexpr (m_count == 34) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20, &e21, &e22, &e23, &e24, &e25, &e26, &e27, &e28, &e29, &e30, &e31, &e32, &e33, &e34 };
    } else if constexpr (m_count == 35) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20, &e21, &e22, &e23, &e24, &e25, &e26, &e27, &e28, &e29, &e30, &e31, &e32, &e33, &e34, &e35 };
    } else if constexpr (m_count == 36) {
        auto&& [e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36] = object;
        return std::tuple{ &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17, &e18, &e19, &e20, &e21, &e22, &e23, &e24, &e25, &e26, &e27, &e28, &e29, &e30, &e31, &e32, &e33, &e34, &e35, &e36 };
    } else {
        // For counts greater than 36, trigger a compile-time error
        static_assert(m_count <= 36, "Not supported member count");
    }
    // clang-format on
}


template<std::size_t Index = 0, typename callback_t, typename... T>
void iterate_tuple(const std::tuple<T...>& t, callback_t&& callback) {
    if constexpr (Index < sizeof...(T)) {
        callback(std::get<Index>(t));
        iterate_tuple<Index + 1, callback_t, T...>(t, std::forward<callback_t>(callback));
    }
}

template <typename object_t, typename callback_t>
void forech_member(object_t&& object, callback_t&& callback) {
    iterate_tuple(collect_members(std::forward<object_t>(object)), std::forward<callback_t>(callback));
}





template <typename T>
consteval std::string_view _type_name() {
#if defined(__clang__) || defined(__GNUC__)
    return __PRETTY_FUNCTION__;  // Clang / GCC
#elif defined(_MSC_VER)
    return __FUNCSIG__;  // MSVC
#else
    return "Unsupported compiler";
#endif
}
template <typename T>
consteval std::string_view extract_type_name() {
    std::string_view name = _type_name<T>();
#if defined(__clang__)
    constexpr std::string_view prefix = "constexpr std::string_view type_name() [T = ";
    constexpr std::string_view suffix = "]";
#elif defined(__GNUC__)
    constexpr std::string_view prefix = "constexpr std::string_view type_name() [with T =  ";
    constexpr std::string_view suffix = "; std::string_view = std::basic_string_view<char>]";
#elif defined(_MSC_VER)
    constexpr std::string_view prefix = "std::string_view __cdecl type_name<";
    constexpr std::string_view suffix = ">(void)";
#else
    return "Unsupported compiler";
#endif
    name.remove_prefix(prefix.size());
    name.remove_suffix(suffix.size());
    return name;
}
template <typename T>
consteval std::string_view type_name() {
    return extract_type_name<T>();
}

#define TYPE_NAME(T) (type_name<decltype(T)>())