#pragma once

#include <charconv>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
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

/**
 * @brief Joins a set of values together into a string.
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
 * @brief Joins a set of values together into a string.
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
    return join(parts, std::string_view { delim, 1 });
}

/**
 * @brief Joins a set of values together into a string.
 * @tparam RangeType A container of values that can be converted into strings via operator<<.
 * @tparam TransformFunctor A function to transform each individual `parts` part before joining.
 * @param parts The set of values to join together with `delim`.
 * @param delim The delimter to place between each joined part.
 * @return Transformed `parts` joined by `delim`.
 */
template <typename RangeType, typename TransformFunctor>
auto transform_join(
    const RangeType& parts,
    std::string_view delim,
    const TransformFunctor& transform) -> std::string
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
            ss << transform(part);
        }
    }

    return ss.str();
}

/**
 * @brief Joins a set of values together into a string.
 * @tparam RangeType A container of values that can be converted into strings via operator<<.
 * @tparam TransformFunctor A function to transform each individual `parts` part before joining.
 * @param parts The set of values to join together with `delim`.
 * @param delim The delimter to place between each joined part.
 * @return Transformed `parts` joined by `delim`.
 */
template <typename RangeType>
auto transform_join(
    const RangeType& parts,
    char delim) -> std::string
{
    return transform_join(parts, std::string_view { delim, 1 });
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
 * @return True if `data` starts with `begin`.
 */
auto starts_with(
    std::string_view data,
    std::string_view begin,
    Case case_type = Case::SENSITIVE) -> bool;

/**
 * @param data The data to see if it ends with `begin`.
 * @param begin Value to check if `data` ends with.
 * @param case_type Is the comparison case sensitive or insensitive?
 * @return True if `data` ends with `begin`.
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
 * @param data The data to transform to upper case.  Uses std::toupper().
 */
auto to_upper(
    std::string& data) -> void;

/**
 * @param data Trims the left side with std::isspace().
 */
auto trim_left(
    std::string& data) -> void;

/**
 * @param data Trims the left side of this data with `to_remove`.
 * @param to_remove The values on the left side to remove from `data`.
 */
auto trim_left(
    std::string& data,
    std::string_view to_remove) -> void;

/**
 * @param data Trims the left side of this data with `to_remove`.
 * @return A string view of `data` with the left side of `to_remove` removed.
 */
auto trim_left_view(
    std::string_view data) -> std::string_view;

/**
 * @param data Trims the left side of this data with `to_remove`.
 * @param to_remove The values on the left side to remove from `data`.
 * @return A string view of `data` with the left side of `to_remove` removed.
 */
auto trim_left_view(
    std::string_view data,
    std::string_view to_remove) -> std::string_view;

/**
 * @param data Trims the right side with std::isspace().
 */
auto trim_right(
    std::string& data) -> void;

/**
 * @param data Trims the right side of this data with `to_remove`.
 * @param to_remove The values on the right side to remove from `data`.
 */
auto trim_right(
    std::string& data,
    std::string_view to_remove) -> void;

/**
 * @param data Trims the right side of this data with `to_remove`.
 * @param to_remove The values on the right side to remove from `data`.
 * @return A string view of `data` with the right side of `to_remove` removed.
 */
auto trim_right_view(
    std::string_view data) -> std::string_view;

/**
 * @param data Trims the right side of this data with `to_remove`.
 * @param to_remove The values on the right side to remove from `data`.
 * @return A string view of `data` with the right side of `to_remove` removed.
 */
auto trim_right_view(
    std::string_view data,
    std::string_view to_remove) -> std::string_view;

/**
 * @return Trims the left and right sides of `data` with std::isspace().
 */
auto trim(
    std::string& data) -> void;

/**
 * @param data Trims the left and right sides of this data with `to_remove`.
 * @param to_remove The values on the left and right side to remove from `data`.
 */
auto trim(
    std::string& data,
    std::string_view to_remove) -> void;

/**
 * @param data Trims the left and right sides of `data` with std::isspace().
 * @return A string view of `data` with the left and right side of `to_remove` removed.
 */
auto trim_view(
    std::string_view data) -> std::string_view;

/**
 * @param data Trims the left and right side of this data with `to_remove`.
 * @param to_remove The values on the left and right side to remove from `data`.
 * @return A string view of `data` with the left and right side of `to_remove` removed.
 */
auto trim_view(
    std::string_view data,
    std::string_view to_remove) -> std::string_view;

/**
 * @brief Replaces up to `count` instances of `from` to `to` within `data`.
 * @param data The data to replace instances of `from` with `to`.
 * @param from The value to replace.
 * @param to The value to replace with.
 * @param count The maximum number of occurrences to replace, if std::nullopt all occurences are replaced.
 * @return The number of `from` occurrences replaced with `to`.
 */
auto replace(
    std::string& data,
    std::string_view from,
    std::string_view to,
    std::optional<std::size_t> count = std::nullopt) -> std::size_t;

/**
 * @param data Determines if `data` starts with an integer value.  Might have trailing non-integer characters.
 * @return True if `data` starts with an integer value.
 */
auto is_int(
    std::string_view data) -> bool;

/**
 * @brief cCnverts a string_view to a number with no copies.
 * Scientific notiation is supported if converting to a double.
 * @throws std::exception On failure.
 * @tparam T The output number type.
 * @param data The data to convert to a number.
 * @return The number if converted.
 */
template <typename T>
auto to_number(
    std::string_view data) -> std::optional<T>
{
    if constexpr (std::is_unsigned<T>::value) {
        if (data.size() > 0 && data.front() == '-') {
            return std::nullopt;
        }
    }

    T output {};
    auto result = std::from_chars(&data.front(), &data.back(), output);
    if (result.ec == std::errc::invalid_argument) {
        return std::nullopt;
    }
    return output;
}

/**
 * @param buffer Places the current errno value into `buffer`.
 *               Will resize the buffer if the errno message is
 *               < buffer.length().  Does not allocate more space.
 */
auto strerror(
    std::string& buffer) -> void;

/**
 * @return String of the current errno value, maximum length is 1024 characters.
 */
auto strerror() -> std::string;

} // namespace chain::str
