#pragma once

#include <charconv>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace chain::str {

extern const std::stringstream g_unused_stringstream;

enum class Case {
    /**
     * Compare case sensitive.
     */
    SENSITIVE,

    /**
     * Compare case insensitive.
     */
    INSENSITIVE
};

/**
 * @param data The data to split by `delim`.
 * @param delim The delimeter to split `data` by.
 * @return The string parts from the split.
 */
auto split(
    std::string_view data,
    char delim) -> std::vector<std::string_view>;

/**
 * @param data The data to split by `delim`.
 * @param delim The delimeter to split `data` by.
 * @return The string parts from the split.
 */
auto split(
    std::string_view data,
    std::string_view delim) -> std::vector<std::string_view>;

/**
 * @param data The data to split by `delim`.
 * @param delim The delimeter to split `data` by.
 * @param out The string parts from the split.  This can be pre-allocated
 *            for the expected number of items to split.
 */
auto split(
    std::string_view data,
    char delim,
    std::vector<std::string_view>& out) -> void;

/**
 * @param data The data to split by `delim`.
 * @param delim The delimeter to split `data` by.
 * @param out The string parts from the split.  This can be pre-allocated
 *            for the expected number of items to split.
 */
auto split(
    std::string_view data,
    std::string_view delim,
    std::vector<std::string_view>& out) -> void;

template <typename T, typename MapFunctor>
auto split_map(
    std::string_view data,
    std::string_view delim,
    const MapFunctor& map,
    std::vector<T>& out) -> void
{
    std::size_t length;
    std::size_t start = 0;

    while (true) {
        std::size_t next = data.find(delim, start);
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

template <typename T, typename MapFunctor>
auto split_map(
    std::string_view data,
    char delim,
    const MapFunctor& map,
    std::vector<T>& out) -> void
{
    split_map(data, std::string_view { &delim, 1 }, map, out);
}

template <typename T, typename MapFunctor>
auto split_map(
    std::string_view data,
    std::string_view delim,
    const MapFunctor& map) -> std::vector<T>
{
    std::vector<T> out {};
    split_map(data, delim, map, out);
    return out;
}

template <typename T, typename MapFunctor>
auto split_map(
    std::string_view data,
    char delim,
    const MapFunctor& map) -> std::vector<T>
{
    std::vector<T> out {};
    split_map(data, std::string_view { &delim, 1 }, map, out);
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
 * Comapres two unsigned characeters with case sensitivity.
 * @param left Left unsigned char to compare.
 * @param right Right unsigned char to compare.
 * @return True if left is the same as right with case sensitivity.
 */
inline auto cmp_uchar(
    unsigned char left,
    unsigned char right) -> bool
{
    return left == right;
}

/**
 * Compares two unsigned characters with case insensitivity.
 * @param left Left unsigned char to compare.
 * @param right Right unsigned char to compare.
 * @return True if left is the same as right with case insensitivity.
 */
inline auto icmp_uchar(
    unsigned char left,
    unsigned char right) -> bool
{
    return std::tolower(left) == std::tolower(right);
}

/**
 * Compares two string views with the given sensitivity.
 * @param left Left string view to compare.
 * @param right Right string view to compare.
 * @param case_type Is the comparison case sensitive or insensitive?
 * @return True if left is the same as right.
 */
auto cmp(
    std::string_view left,
    std::string_view right,
    Case case_type = Case::SENSITIVE) -> bool;

/**
 * @param data The data to see if it starts with `begin`.
 * @param begin Value to check if `data` starts with.
 * @param case_type Is the comparison case sensitive or insensitive?
 * @return True if `data` starts with `begin`.  Equal length strings will match.
 */
auto starts_with(
    std::string_view data,
    std::string_view begin,
    Case case_type = Case::SENSITIVE) -> bool;

/**
 * @param data The data to see if it ends with `begin`.
 * @param begin Value to check if `data` ends with.
 * @param case_type Is the comparison case sensitive or insensitive?
 * @return True if `data` ends with `begin`.  Equal length strings will match.
 */
auto ends_with(
    std::string_view data,
    std::string_view end,
    Case case_type = Case::SENSITIVE) -> bool;

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
 * @param data Trims the left side of this data with `to_remove`.
 * @param to_remove The value on the left side to remove from `data`.
 */
auto trim_left(
    std::string& data,
    std::string_view to_remove) -> void;

/**
 * @param data Trims the left side of this data with `to_remove`.
 * @param to_remove The values on the left side to remove from `data`.
 */
auto trim_left(
    std::string& data,
    const std::vector<std::string_view>& to_remove) -> void;

/**
 * @param data Trims the left side of this data with `to_remove`.
 * @return A string view of `data` with the left side of `to_remove` removed.
 */
auto trim_left_view(
    std::string_view data) -> std::string_view;

/**
 * @param data Trims the left side of this data with `to_remove`.
 * @param to_remove The value on the left side to remove from `data`.
 * @return A string view of `data` with the left side of `to_remove` removed.
 */
auto trim_left_view(
    std::string_view data,
    std::string_view to_remove) -> std::string_view;

/**
 * @param data Trims the left side of this data with `to_remove`.
 * @param to_remove The values on the left side to remove from `data`.
 * @return A string view of `data` with the left side of `to_remove` removed.
 */
auto trim_left_view(
    std::string_view data,
    const std::vector<std::string_view>& to_remove) -> std::string_view;

/**
 * @param data Trims the right side with std::isspace().
 */
auto trim_right(
    std::string& data) -> void;

/**
 * @param data Trims the right side of this data with `to_remove`.
 * @param to_remove The value on the right side to remove from `data`.
 */
auto trim_right(
    std::string& data,
    std::string_view to_remove) -> void;

/**
 * @param data Trims the right side of this data with `to_remove`.
 * @param to_remove The values on the right side to remove from `data`.
 */
auto trim_right(
    std::string& data,
    const std::vector<std::string_view>& to_remove) -> void;

/**
 * @param data Trims the right side of this data with `to_remove`.
 * @return A string view of `data` with the right side of `to_remove` removed.
 */
auto trim_right_view(
    std::string_view data) -> std::string_view;

/**
 * @param data Trims the right side of this data with `to_remove`.
 * @param to_remove The value on the right side to remove from `data`.
 * @return A string view of `data` with the right side of `to_remove` removed.
 */
auto trim_right_view(
    std::string_view data,
    std::string_view to_remove) -> std::string_view;

/**
 * @param data Trims the right side of this data with `to_remove`.
 * @param to_remove The values on the right side to remove from `data`.
 * @return A string view of `data` with the right side of `to_remove` removed.
 */
auto trim_right_view(
    std::string_view data,
    const std::vector<std::string_view>& to_remove) -> std::string_view;

/**
 * @return Trims the left and right sides of `data` with std::isspace().
 */
auto trim(
    std::string& data) -> void;

/**
 * @param data Trims the left and right sides of this data with `to_remove`.
 * @param to_remove The value on the left and right side to remove from `data`.
 */
auto trim(
    std::string& data,
    std::string_view to_remove) -> void;

/**
 * @param data Trims the left and right sides of this data with `to_remove`.
 * @param to_remove The values on the left and right side to remove from `data`.
 */
auto trim(
    std::string& data,
    const std::vector<std::string_view>& to_remove) -> void;

/**
 * @param data Trims the left and right sides of `data` with std::isspace().
 * @return A string view of `data` with the left and right side of `to_remove` removed.
 */
auto trim_view(
    std::string_view data) -> std::string_view;

/**
 * @param data Trims the left and right side of this data with `to_remove`.
 * @param to_remove The value on the left and right side to remove from `data`.
 * @return A string view of `data` with the left and right side of `to_remove` removed.
 */
auto trim_view(
    std::string_view data,
    std::string_view to_remove) -> std::string_view;

/**
 * @param data Trims the left and right side of this data with `to_remove`.
 * @param to_remove The values on the left and right side to remove from `data`.
 * @return A string view of `data` with the left and right side of `to_remove` values removed.
 */
auto trim_view(
    std::string_view data,
    const std::vector<std::string_view>& to_remove) -> std::string_view;

/**
 * Replaces up to `count` instances of `from` to `to` within `data`.
 * @param data The data to replace instances of `from` with `to`.
 * @param from The value to replace.
 * @param to The value to replace with.
 * @param case_type Which case to do the replace in, sensitive or insensitive.
 * @param count The maximum number of occurrences to replace, if std::nullopt all occurences are replaced.
 * @return The number of `from` occurrences replaced with `to`.
 */
auto replace(
    std::string& data,
    std::string_view from,
    std::string_view to,
    Case case_type = Case::SENSITIVE,
    std::optional<std::size_t> count = std::nullopt) -> std::size_t;

/**
 * Replaces up to `count` instances of `from` to `to` within `data`.
 * @param data The data to replace instances of `from` with `to`.
 * @param from The value to replace.
 * @param to The value to replace with.
 * @param case_type Which case to do the replace in, sensitive or insensitive.
 * @param count The maximum number of occurrences to replace, if std::nullopt all occurences are replaced.
 * @return `data` with replacements copy and the number of `from` occurrences replaced with `to`.
 */
auto replace_copy(
    std::string_view data,
    std::string_view from,
    std::string_view to,
    Case case_type = Case::SENSITIVE,
    std::optional<std::size_t> count = std::nullopt) -> std::pair<std::string, std::size_t>;

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
