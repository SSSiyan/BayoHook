#include <cstdint>
#include <cstddef>

namespace utils
{
    // FNV-1a 32bit hashing algorithm.
    constexpr std::uint32_t fnv1a_32(char const* s, std::size_t count)
    {
        return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u;
    }
}    // namespace utils

constexpr std::uint32_t operator"" _hash(char const* s, std::size_t count)
{
    return utils::fnv1a_32(s, count);
}