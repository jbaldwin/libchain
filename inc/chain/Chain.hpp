#pragma once

#include <algorithm>
#include <charconv>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <numeric>

namespace chain::str {

extern const std::stringstream g_unused_stringstream;

enum class Case {
    /**
     * Compare case sensitive.  This is the default across all functions.
     */
    SENSITIVE,

    /**
     * Compare case insensitive.
     */
    INSENSITIVE
};

/**
 * Comapres two unsigned characeters for equality.
 * @tparam CaseType Is the comparison case sensitive or insensitive?
 * @param left Left unsigned char to compare.
 * @param right Right unsigned char to compare.
 * @return True if left is the same as right with case sensitivity.
 */
template<Case CaseType = Case::SENSITIVE>
inline auto equal_uchar(
    unsigned char left,
    unsigned char right) -> bool
{
    if constexpr (CaseType == Case::SENSITIVE) {
        return left == right;
    } else {
        return std::tolower(left) == std::tolower(right);
    }
}

/**
 * Compares two string views with the given sensitivity for equality.
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param left Left string view to compare.
 * @param right Right string view to compare.
 * @return True if left is the same as right.
 */
template<Case CaseType = Case::SENSITIVE>
auto equal(
    std::string_view left,
    std::string_view right) -> bool
{
    if (left.length() == right.length()) {
        if constexpr (CaseType == Case::SENSITIVE) {
            return left == right;
        } else {
            return std::equal(
                left.begin(), left.end(),
                right.begin(), right.end(),
                equal_uchar<Case::INSENSITIVE>);
        }
    }

    return false;
}

/**
 * Finds needle in the haystack from pos with the given case type.
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param haystack The string to search in for `needle`.
 * @param needle The string to find in `haystack`.
 * @param pos The starting position within `haystack`, defaults to the beginning.
 */
template<Case CaseType = Case::SENSITIVE>
auto find(
    std::string_view haystack,
    std::string_view needle,
    std::size_t pos = 0) -> std::string_view::size_type
{
    if constexpr (CaseType == Case::SENSITIVE) {
        return haystack.find(needle, pos);
    }
    else {
        auto it = std::search(
            haystack.begin() + pos,
            haystack.end(),
            needle.begin(),
            needle.end(),
            equal_uchar<Case::INSENSITIVE>);

        if(it != haystack.end()) {
            return it - haystack.begin();
        }
        else {
            return std::string_view::npos;
        }
    }
}

/**
 * Reverise finds needle in the haystack from pos with the given case type.
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param haystack The string to search in for `needle`.
 * @param needle The string to find in `haystack`.
 * @param pos The starting position within `haystack`, defaults to the end.
 */
template<Case CaseType = Case::SENSITIVE>
auto rfind(
    std::string_view haystack,
    std::string_view needle,
    std::size_t pos = std::string_view::npos) -> std::string_view::size_type
{
    if constexpr (CaseType == Case::SENSITIVE) {
        return haystack.rfind(needle, pos);
    }
    else {
        auto start = (pos == std::string_view::npos)
            ? haystack.rbegin()
            : haystack.rbegin() + (haystack.size() - pos);

        auto it = std::search(
            start,
            haystack.rend(),
            needle.rbegin(),
            needle.rend(),
            equal_uchar<Case::INSENSITIVE>);

        if(it != haystack.rend()) {
            return haystack.size() - (it - haystack.rbegin() + needle.size());
        }
        else {
            return std::string_view::npos;
        }
    }
}

/**
 * @tparam CaseType Is the comparison case sensitive or insensitive?
 * @param data The data to split by `delim`.
 * @param delim The delimeter to split `data` by.
 * @param out The string parts from the split.  This can be pre-allocated
 *            for the expected number of items to split.
 */
template<Case CaseType = Case::SENSITIVE>
auto split(
    std::string_view data,
    std::string_view delim,
    std::vector<std::string_view>& out) -> void
{
    std::size_t length;
    std::size_t start = 0;

    while (true) {
        std::size_t next = find<CaseType>(data, delim, start);
        if (next == std::string_view::npos) {
            // The length of this split is the full string length - start.
            // This is also true if there were no delimiters found at all.
            length = data.length() - start;
            out.emplace_back(data.data() + start, length);
            break;
        }

        // The length of this split is from start to next.
        length = next - start;
        out.emplace_back(data.data() + start, length);

        // Update our iteration to skip the 'next' delimiter found.
        start = next + delim.length();
    }
}

/**
 * @tparam CaseType Is the comparison case sensitive or insensitive?
 * @param data The data to split by `delim`.
 * @param delim The delimeter to split `data` by.
 * @param out The string parts from the split.  This can be pre-allocated
 *            for the expected number of items to split.
 */
template<Case CaseType = Case::SENSITIVE>
auto split(
    std::string_view data,
    char delim,
    std::vector<std::string_view>& out) -> void
{
    return split<CaseType>(data, std::string_view { &delim, 1 }, out);
}

/**
 * @tparam CaseType Is the comparison case sensitive or insensitive?
 * @param data The data to split by `delim`.
 * @param delim The delimeter to split `data` by.
 * @return The string parts from the split.
 */
template<Case CaseType = Case::SENSITIVE>
auto split(
    std::string_view data,
    std::string_view delim) -> std::vector<std::string_view>
{
    std::vector<std::string_view> out {};
    split<CaseType>(data, delim, out);
    return out;
}

/**
 * @tparam CaseType Is the comparison case sensitive or insensitive?
 * @param data The data to split by `delim`.
 * @param delim The delimeter to split `data` by.
 * @return The string parts from the split.
 */
template<Case CaseType = Case::SENSITIVE>
auto split(
    std::string_view data,
    char delim) -> std::vector<std::string_view>
{
    return split<CaseType>(data, std::string_view { &delim, 1 });
}


/**
 * @tparam CaseType Is the comparison case sensitive or insensitive?
 * @tparam T The output type that the `MapFunctor` maps into.
 * @tparam MapFunctor The function type to apply against each split item.
 * @param data The data to split by `delim`.
 * @param delim The delimeter to split `data` by.
 * @param map The map functor too apply to each split item.
 * @param out The string parts from the split.  This can be pre-allocated
 *            for the expected number of items to split.
 */
template <
    typename T,
    Case CaseType = Case::SENSITIVE,
    typename MapFunctor = std::function<T(std::string_view)>
>
auto split_map(
    std::string_view data,
    std::string_view delim,
    const MapFunctor& map,
    std::vector<T>& out) -> void
{
    std::size_t length;
    std::size_t start = 0;

    while (true) {
        std::size_t next = find<CaseType>(data, delim, start);
        if (next == std::string_view::npos) {
            // The length of this split is the full string length - start.
            // This is also true if there were no delimiters found at all.
            length = data.length() - start;
            out.emplace_back(map(std::string_view { data.data() + start, length }));
            break;
        }

        // The length of this split is from start to next.
        length = next - start;
        out.emplace_back(map(std::string_view { data.data() + start, length }));

        // Update our iteration to skip the 'next' delimiter found.
        start = next + delim.length();
    }
}

/**
 * @tparam CaseType Is the comparison case sensitive or insensitive?
 * @tparam T The output type that the `MapFunctor` maps into.
 * @tparam MapFunctor The function type to apply against each split item.
 * @param data The data to split by `delim`.
 * @param delim The delimeter to split `data` by.
 * @param map The map functor too apply to each split item.
 * @param out The string parts from the split.  This can be pre-allocated
 *            for the expected number of items to split.
 */
template <
    typename T,
    Case CaseType = Case::SENSITIVE,
    typename MapFunctor = std::function<T(std::string_view)>
>
auto split_map(
    std::string_view data,
    char delim,
    const MapFunctor& map,
    std::vector<T>& out) -> void
{
    split_map<T, CaseType, MapFunctor>(data, std::string_view { &delim, 1 }, map, out);
}

/**
 * @tparam CaseType Is the comparison case sensitive or insensitive?
 * @tparam T The output type that the `MapFunctor` maps into.
 * @tparam MapFunctor The function type to apply against each split item.
 * @param data The data to split by `delim`.
 * @param delim The delimeter to split `data` by.
 * @param map The map functor too apply to each split item.
 * @return The string parts from the split.
 */
template <
    typename T,
    Case CaseType = Case::SENSITIVE,
    typename MapFunctor = std::function<T(std::string_view)>
>
auto split_map(
    std::string_view data,
    std::string_view delim,
    const MapFunctor& map) -> std::vector<T>
{
    std::vector<T> out {};
    split_map<T, CaseType, MapFunctor>(data, delim, map, out);
    return out;
}

/**
 * @tparam CaseType Is the comparison case sensitive or insensitive?
 * @tparam T The output type that the `MapFunctor` maps into.
 * @tparam MapFunctor The function type to apply against each split item.
 * @param data The data to split by `delim`.
 * @param delim The delimeter to split `data` by.
 * @param map The map functor too apply to each split item.
 * @return The string parts from the split.
 */
template <
    typename T = std::string_view,
    Case CaseType = Case::SENSITIVE,
    typename MapFunctor = std::function<T(std::string_view)>
>
auto split_map(
    std::string_view data,
    char delim,
    const MapFunctor& map) -> std::vector<T>
{
    std::vector<T> out {};
    split_map<T, CaseType, MapFunctor>(data, std::string_view { &delim, 1 }, map, out);
    return out;
}

/**
 * Joins a set of values together into a single string.  The values being joined
 * together must have an ostream operator<< function declared to convert to strings.
 * @tparam RangeType A container of values that can be converted into strings via operator<<.
 * @param parts The set of values to join together with `delim`.
 * @param delim The delimter to place between each joined part.
 * @return `parts` joined by `delim`.
 */
template <typename RangeType>
auto join(
    const RangeType& parts,
    std::string_view delim) -> std::string
{
    thread_local std::stringstream ss {};

    ss.clear();
    ss.str("");
    ss.copyfmt(g_unused_stringstream);

    bool first { true };
    for (const auto& part : parts) {
        if (first) {
            first = false;
        } else {
            ss << delim;
        }

        ss << part;
    }

    return ss.str();
}

/**
 * Joins a set of values together into a single string.  The values being joined
 * together must have an ostream operator<< function declared to convert to strings.
 * @tparam RangeType A container of values that can be converted into strings via operator<<.
 * @param parts The set of values to join together with `delim`.
 * @param delim The delimter to place between each joined part.
 * @return `parts` joined by `delim`.
 */
template <typename RangeType>
auto join(
    const RangeType& parts,
    char delim) -> std::string
{
    return join(parts, std::string_view { &delim, 1 });
}

/**
 * Maps and joins a set of values together into a single string.  The values being joined
 * together must have an ostream operator<< function declared to convert to strings.
 * @tparam RangeType A container of values that can be converted into strings via operator<<.
 * @tparam MapFunctor A function to map each individual `parts` part before joining.
 * @param parts The set of values to join together with `delim`.
 * @param delim The delimter to place between each joined part.
 * @return Mapped `parts` joined by `delim`.
 */
template <typename RangeType, typename MapFunctor>
auto map_join(
    const RangeType& parts,
    std::string_view delim,
    const MapFunctor& map) -> std::string
{
    thread_local std::stringstream ss {};

    ss.clear();
    ss.str("");
    ss.copyfmt(g_unused_stringstream);

    bool first { true };
    for (const auto& part : parts) {
        if (first) {
            first = false;
        } else {
            ss << delim;
        }

        ss << map(part);
    }

    return ss.str();
}

/**
 * Maps and joins a set of values together into a string.
 * @tparam RangeType A container of values that can be converted into strings via operator<<.
 * @tparam MapFunctor A function to map each individual `parts` part before joining.
 * @param parts The set of values to join together with `delim`.
 * @param delim The delimter to place between each joined part.
 * @return Mapped `parts` joined by `delim`.
 */
template <typename RangeType, typename MapFunctor>
auto map_join(
    const RangeType& parts,
    char delim,
    const MapFunctor& map) -> std::string
{
    return map_join(parts, std::string_view { &delim, 1 }, map);
}

/**
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param data The data to see if it starts with `begin`.
 * @param begin Value to check if `data` starts with.
 * @return True if `data` starts with `begin`.  Equal length strings will match.
 */
template<Case CaseType = Case::SENSITIVE>
auto starts_with(
    std::string_view data,
    std::string_view begin) -> bool
{
    if(data.length() >= begin.length()) {
        return std::equal(begin.begin(), begin.end(), data.begin(), equal_uchar<CaseType>);
    }
    return false;
}

/**
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param data The data to see if it ends with `begin`.
 * @param begin Value to check if `data` ends with.
 * @return True if `data` ends with `begin`.  Equal length strings will match.
 */
template<Case CaseType = Case::SENSITIVE>
auto ends_with(
    std::string_view data,
    std::string_view end) -> bool
{
    if(data.length() >= end.length()) {
        return std::equal(end.rbegin(), end.rend(), data.rbegin(), equal_uchar<CaseType>);
    }
    return false;
}

/**
 * @param data The data to transform to lower case.  Uses std::tolower().
 */
auto to_lower(
    std::string& data) -> void;

/**
 * @param data The data to transform to lower case.  uses std::tolower().
 * @return A copy of `daa` transformed to lowercase.
 */
auto to_lower_copy(
    std::string_view data) -> std::string;

/**
 * @param data The data to transform to upper case.  Uses std::toupper().
 */
auto to_upper(
    std::string& data) -> void;

/**
 * @param data The data to transform to upper case.  Uses std::toupper().
 * @return A copy of `data` transformed to uppercase.
 */
auto to_upper_copy(
    std::string_view data) -> std::string;

/**
 * @param data Trims the left side with std::isspace().
 */
auto trim_left(
    std::string& data) -> void;

/**
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param data Trims the left side of this data with `to_remove`.
 * @param to_remove The value on the left side to remove from `data`.
 */
template<Case CaseType = Case::SENSITIVE>
auto trim_left(
    std::string& data,
    std::string_view to_remove) -> void
{
    if (!data.empty() && !to_remove.empty()) {
        std::size_t total_remove_size = 0;
        std::string_view sv { data.data(), data.length() };
        while (starts_with<CaseType>(sv, to_remove)) {
            sv.remove_prefix(to_remove.size());
            total_remove_size += to_remove.size();
        }

        if (total_remove_size > 0) {
            data.erase(0, total_remove_size);
        }
    }
}

/**
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param data Trims the left side of this data with `to_remove`.
 * @param to_remove The values on the left side to remove from `data`.
 */
template<Case CaseType = Case::SENSITIVE>
auto trim_left(
    std::string& data,
    const std::vector<std::string_view>& to_remove) -> void
{
    if (!data.empty() && !to_remove.empty()) {
        std::size_t total_remove_size = 0;
        std::string_view sv { data.data(), data.length() };

        while (true) {
            bool had_removal { false };

            for (const auto& remove : to_remove) {
                while (starts_with<CaseType>(sv, remove)) {
                    sv.remove_prefix(remove.size());
                    total_remove_size += remove.size();
                    had_removal = true;
                }
            }

            if (!had_removal) {
                break;
            }
        }

        if (total_remove_size > 0) {
            data.erase(0, total_remove_size);
        }
    }
}

/**
 * @param data Trims the left side of this data with `to_remove`.
 * @return A string view of `data` with the left side of `to_remove` removed.
 */
auto trim_left_view(
    std::string_view data) -> std::string_view;

/**
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param data Trims the left side of this data with `to_remove`.
 * @param to_remove The value on the left side to remove from `data`.
 * @return A string view of `data` with the left side of `to_remove` removed.
 */
template<Case CaseType = Case::SENSITIVE>
auto trim_left_view(
    std::string_view data,
    std::string_view to_remove) -> std::string_view
{
    if (!data.empty() && !to_remove.empty()) {
        while (starts_with<CaseType>(data, to_remove)) {
            data.remove_prefix(to_remove.size());
        }
    }

    return data;
}

/**
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param data Trims the left side of this data with `to_remove`.
 * @param to_remove The values on the left side to remove from `data`.
 * @return A string view of `data` with the left side of `to_remove` removed.
 */
template<Case CaseType = Case::SENSITIVE>
auto trim_left_view(
    std::string_view data,
    const std::vector<std::string_view>& to_remove) -> std::string_view
{
    if (!data.empty() && !to_remove.empty()) {
        while (true) {
            bool had_removal { false };

            for (const auto& remove : to_remove) {
                while (starts_with<CaseType>(data, remove)) {
                    data.remove_prefix(remove.size());
                    had_removal = true;
                }
            }

            if (!had_removal) {
                break;
            }
        }
    }

    return data;
}

/**
 * @param data Trims the right side with std::isspace().
 */
auto trim_right(
    std::string& data) -> void;

/**
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param data Trims the right side of this data with `to_remove`.
 * @param to_remove The value on the right side to remove from `data`.
 */
template<Case CaseType = Case::SENSITIVE>
auto trim_right(
    std::string& data,
    std::string_view to_remove) -> void
{
    if (!to_remove.empty()) {
        std::size_t total_remove_size = 0;
        std::string_view sv { data.data(), data.length() };
        while (ends_with<CaseType>(sv, to_remove)) {
            sv.remove_suffix(to_remove.size());
            total_remove_size += to_remove.size();
        }
        if (total_remove_size > 0) {
            data.erase(data.size() - total_remove_size);
        }
    }
}

/**
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param data Trims the right side of this data with `to_remove`.
 * @param to_remove The values on the right side to remove from `data`.
 */
template<Case CaseType = Case::SENSITIVE>
auto trim_right(
    std::string& data,
    const std::vector<std::string_view>& to_remove) -> void
{
    if (!data.empty() && !to_remove.empty()) {
        std::size_t total_remove_size = 0;
        std::string_view sv { data.data(), data.length() };

        while (true) {
            bool had_removal { false };

            for (const auto& remove : to_remove) {
                while (ends_with<CaseType>(sv, remove)) {
                    sv.remove_suffix(remove.size());
                    total_remove_size += remove.size();
                    had_removal = true;
                }
            }

            if (!had_removal) {
                break;
            }
        }

        if (total_remove_size > 0) {
            data.erase(data.size() - total_remove_size);
        }
    }
}

/**
 * @param data Trims the right side of this data with `to_remove`.
 * @return A string view of `data` with the right side of `to_remove` removed.
 */
auto trim_right_view(
    std::string_view data) -> std::string_view;

/**
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param data Trims the right side of this data with `to_remove`.
 * @param to_remove The value on the right side to remove from `data`.
 * @return A string view of `data` with the right side of `to_remove` removed.
 */
template<Case CaseType = Case::SENSITIVE>
auto trim_right_view(
    std::string_view data,
    std::string_view to_remove) -> std::string_view
{
    if (!data.empty() && !to_remove.empty()) {
        while (ends_with<CaseType>(data, to_remove)) {
            data.remove_suffix(to_remove.size());
        }
    }

    return data;
}

/**
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param data Trims the right side of this data with `to_remove`.
 * @param to_remove The values on the right side to remove from `data`.
 * @return A string view of `data` with the right side of `to_remove` removed.
 */
template<Case CaseType = Case::SENSITIVE>
auto trim_right_view(
    std::string_view data,
    const std::vector<std::string_view>& to_remove) -> std::string_view
{
    if (!data.empty() && !to_remove.empty()) {
        while (true) {
            bool had_removal { false };

            for (const auto& remove : to_remove) {
                while (ends_with<CaseType>(data, remove)) {
                    data.remove_suffix(remove.size());
                    had_removal = true;
                }
            }

            if (!had_removal) {
                break;
            }
        }
    }

    return data;
}

/**
 * @return Trims the left and right sides of `data` with std::isspace().
 */
auto trim(
    std::string& data) -> void;

/**
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param data Trims the left and right sides of this data with `to_remove`.
 * @param to_remove The value on the left and right side to remove from `data`.
 */
template<Case CaseType = Case::SENSITIVE>
auto trim(
    std::string& data,
    std::string_view to_remove) -> void
{
    trim_left<CaseType>(data, to_remove);
    trim_right<CaseType>(data, to_remove);
}

/**
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param data Trims the left and right sides of this data with `to_remove`.
 * @param to_remove The values on the left and right side to remove from `data`.
 */
template<Case CaseType = Case::SENSITIVE>
auto trim(
    std::string& data,
    const std::vector<std::string_view>& to_remove) -> void
{
    trim_left<CaseType>(data, to_remove);
    trim_right<CaseType>(data, to_remove);
}

/**
 * @param data Trims the left and right sides of `data` with std::isspace().
 * @return A string view of `data` with the left and right side of `to_remove` removed.
 */
auto trim_view(
    std::string_view data) -> std::string_view;

/**
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param data Trims the left and right side of this data with `to_remove`.
 * @param to_remove The value on the left and right side to remove from `data`.
 * @return A string view of `data` with the left and right side of `to_remove` removed.
 */
template<Case CaseType = Case::SENSITIVE>
auto trim_view(
    std::string_view data,
    std::string_view to_remove) -> std::string_view
{
    return trim_right_view<CaseType>(trim_left_view<CaseType>(data, to_remove), to_remove);
}

/**
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param data Trims the left and right side of this data with `to_remove`.
 * @param to_remove The values on the left and right side to remove from `data`.
 * @return A string view of `data` with the left and right side of `to_remove` values removed.
 */
template<Case CaseType = Case::SENSITIVE>
auto trim_view(
    std::string_view data,
    const std::vector<std::string_view>& to_remove) -> std::string_view
{
    return trim_right_view<CaseType>(trim_left_view<CaseType>(data, to_remove), to_remove);
}

/**
 * Replaces up to `count` instances of `from` to `to` within `data`.
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param data The data to replace instances of `from` with `to`.
 * @param from The value to replace.
 * @param to The value to replace with.
 * @param count The maximum number of occurrences to replace, if std::nullopt all occurences are replaced.
 * @return The number of `from` occurrences replaced with `to`.
 */
template<Case CaseType = Case::SENSITIVE>
auto replace(
    std::string& data,
    std::string_view from,
    std::string_view to,
    std::optional<std::size_t> count = std::nullopt) -> std::size_t
{
    std::size_t replaced { 0 };

    if (!data.empty()) {
        auto max = count.value_or(std::numeric_limits<std::size_t>::max());
        if(max == 0) {
            return replaced; // 0 replacements asked for...!
        }

        std::size_t pos { 0 };
        while((pos = find<CaseType>(data, from, pos)) != std::string_view::npos) {
            data.replace(pos, from.length(), to.data(), to.length());
            pos += to.length();
            ++replaced;

            if (replaced >= max) {
                break; // while()
            }
        }
    }

    return replaced;
}

/**
 * Replaces up to `count` instances of `from` to `to` within `data`.
 * @tparam CaseType Use case insensitive or senstive equality checks.
 * @param data The data to replace instances of `from` with `to`.
 * @param from The value to replace.
 * @param to The value to replace with.
 * @param count The maximum number of occurrences to replace, if std::nullopt all occurences are replaced.
 * @return `data` with replacements copy and the number of `from` occurrences replaced with `to`.
 */
template<Case CaseType = Case::SENSITIVE>
auto replace_copy(
    std::string data,
    std::string_view from,
    std::string_view to,
    std::optional<std::size_t> count = std::nullopt) -> std::pair<std::string, std::size_t>
{
    std::size_t num = replace<CaseType>(data, from, to, count);
    return { std::move(data), num };
}

/**
 * @param data Determines if `data` is an integer.
 * @return True if `data` starts with an integer value.
 */
auto is_int(
    std::string_view data) -> bool;

/**
 * @note This currently requires taking a copy of `data` to meet the floating point
 *       to_number limitations.
 *
 * @param data Determines if `data` is floating point.
 * @return True if `data` starts with an integer value.
 */
auto is_float(
    std::string_view data) -> bool;

/**
 * @note This currently requires taking a copy of `data` if the integer check fails
 *       to meet the floating point to_number limitations.
 *
 * @param data Determines if `data` is an number.
 * @return True if `data` starts with an integer value.
 */
auto is_number(
    std::string_view data) -> bool;

/**
 * Converts an integer string_view to a number with no copies.
 * @tparam T The output number type.
 * @param data The data to convert to a number.
 * @param base The data's base.
 * @return The number if converted.
 */
template <
    typename Integer,
    std::enable_if_t<std::is_integral_v<Integer>, int> = 0>
auto to_number(
    std::string_view data,
    uint64_t base = 10) -> std::optional<Integer>
{
    // https://en.cppreference.com/w/cpp/utility/from_chars

    if constexpr (std::is_unsigned<Integer>::value) {
        if (data.size() > 0 && data.front() == '-') {
            return std::nullopt;
        }
    }

    // remove "+" for signed and unsigned types, it isn't recognized by `std::from_chars()`
    if (data.size() > 0 && data.front() == '+') {
        data.remove_prefix(1);
    }

    Integer output {};
    auto result = std::from_chars(data.data(), data.data() + data.length(), output, base);

    if (result.ec == std::errc::invalid_argument) {
        return std::nullopt;
    }
    return output;
}

template <
    typename FloatingPoint,
    std::enable_if_t<std::is_floating_point_v<FloatingPoint>, int> = 0>
auto to_number(
    const std::string& data) -> std::optional<FloatingPoint>
{
    FloatingPoint output {};

    std::size_t pos { 0 };

    try {
        if constexpr (sizeof(FloatingPoint) == sizeof(float)) {
            output = std::stof(data, &pos);
        } else if constexpr (sizeof(FloatingPoint) == sizeof(double)) {
            output = std::stod(data, &pos);
        } else if constexpr (sizeof(FloatingPoint) == sizeof(long double)) {
            output = std::stold(data, &pos);
        } else {
            return std::nullopt;
        }
    } catch (...) {
        return std::nullopt;
    }

    return output;
}

/**
 * @param errsv The errno value to get its string representation.
 * @return Human readable representation of `errsv`.
 */
auto strerror(
    int errsv) -> std::string;

} // namespace chain::str
