#include "chain/Chain.hpp"

#include <algorithm>
#include <cstring>

namespace chain::str {

const std::stringstream g_unused_stringstream {};

auto split(
    std::string_view data,
    char delim) -> std::vector<std::string_view>
{
    return split(data, std::string_view { &delim, 1 });
}

auto split(
    std::string_view data,
    std::string_view delim) -> std::vector<std::string_view>
{
    std::vector<std::string_view> out {};
    split(data, delim, out);
    return out;
}

auto split(
    std::string_view data,
    char delim,
    std::vector<std::string_view>& out) -> void
{
    return split(data, std::string_view { &delim, 1 }, out);
}

auto split(
    std::string_view data,
    std::string_view delim,
    std::vector<std::string_view>& out) -> void
{
    std::size_t length;
    std::size_t start = 0;

    while (true) {
        std::size_t next = data.find(delim, start);
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

auto cmp(
    std::string_view left,
    std::string_view right,
    Case case_type) -> bool
{
    if (left.length() == right.length()) {
        if (case_type == Case::SENSITIVE) {
            return left == right;
        } else {
            return std::equal(
                left.begin(), left.end(),
                right.begin(), right.end(),
                icmp_uchar);
        }
    }

    return false;
}

auto starts_with(
    std::string_view data,
    std::string_view start,
    Case case_type) -> bool
{
    if (data.length() >= start.length()) {
        if (case_type == Case::SENSITIVE) {
            return std::equal(start.begin(), start.end(), data.begin(), [](auto& lhs, auto& rhs) {
                return lhs == rhs;
            });
        } else {
            return std::equal(start.begin(), start.end(), data.begin(), [](auto& lhs, auto& rhs) {
                return icmp_uchar(static_cast<unsigned char>(lhs), static_cast<unsigned char>(rhs));
            });
        }
    }

    return false;
}

auto ends_with(
    std::string_view data,
    std::string_view end,
    Case case_type) -> bool
{

    if (data.length() >= end.length()) {
        if (case_type == Case::SENSITIVE) {
            return std::equal(end.rbegin(), end.rend(), data.rbegin(), [](auto& lhs, auto& rhs) {
                return lhs == rhs;
            });
        } else {
            return std::equal(end.rbegin(), end.rend(), data.rbegin(), [](auto& lhs, auto& rhs) {
                return icmp_uchar(static_cast<unsigned char>(lhs), static_cast<unsigned char>(rhs));
            });
        }
    }

    return false;
}

auto to_lower(
    std::string& data) -> void
{
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);
}

auto to_upper(
    std::string& data) -> void
{
    std::transform(data.begin(), data.end(), data.begin(), ::toupper);
}

auto trim_left(
    std::string& s) -> void
{
    auto found = std::find_if_not(s.begin(), s.end(), [](int ch) -> bool { return std::isspace(ch); });
    /**
     * If nothing is found, e.g. the entire string is whitespace then
     * the erase will trim the entire string.
     */
    s.erase(s.begin(), found);
}

auto trim_left(
    std::string& s,
    std::string_view to_remove) -> void
{
    if (to_remove.empty()) {
        return;
    }
    std::size_t remove_size = 0;
    std::string_view sv { s };
    std::size_t to_remove_size = to_remove.size();
    while (starts_with(sv, to_remove)) {
        sv.remove_prefix(to_remove_size);
        remove_size += to_remove_size;
    }
    if (remove_size > 0) {
        s.erase(0, remove_size);
    }
}

auto trim_left_view(
    std::string_view s) -> std::string_view
{
    if (s.empty()) {
        return s;
    }

    std::size_t index = 0;
    while (index < s.length()) {
        if (!std::isspace(s[index])) {
            break;
        } else {
            ++index;
        }
    }
    return s.substr(index);
}

auto trim_right(
    std::string& s) -> void
{
    auto start = std::find_if_not(s.rbegin(), s.rend(), [](int ch) -> bool { return std::isspace(ch); }).base();
    s.erase(start, s.end());
}

auto trim_right(
    std::string& s,
    std::string_view to_remove) -> void
{
    if (to_remove.empty()) {
        return;
    }
    std::size_t remove_size = 0;
    std::string_view sv { s };
    std::size_t to_remove_size = to_remove.size();
    while (ends_with(sv, to_remove)) {
        sv.remove_suffix(to_remove_size);
        remove_size += to_remove_size;
    }
    if (remove_size > 0) {
        s.erase(s.size() - remove_size);
    }
}

auto trim_right_view(
    std::string_view s) -> std::string_view
{
    if (s.empty()) {
        return s;
    }

    int64_t index = static_cast<int64_t>(s.length() - 1);
    while (index >= 0) {
        if (!std::isspace(s[static_cast<std::size_t>(index)])) {
            break;
        } else {
            --index;
        }
    }
    return s.substr(0, static_cast<std::size_t>(index + 1));
}

auto trim(
    std::string& data) -> void
{
    trim_left(data);
    trim_right(data);
}

auto trim(
    std::string& data,
    std::string_view to_remove) -> void
{
    trim_left(data, to_remove);
    trim_right(data, to_remove);
}

auto trim_view(
    std::string_view s) -> std::string_view
{
    return trim_left_view(trim_right_view(s));
}

auto trim_view(
    std::string_view data,
    std::string_view to_remove) -> std::string_view
{
    return trim_left_view(trim_right_view(data, to_remove), to_remove);
}

auto replace(
    std::string& data,
    std::string_view from,
    std::string_view to,
    std::optional<std::size_t> count) -> std::size_t
{
    std::size_t replaced { 0 };

    std::size_t start_pos { 0 };
    while ((start_pos = data.find(from.data(), start_pos, from.length())) != std::string::npos) {
        data.replace(start_pos, from.length(), to.data(), to.length());
        start_pos += to.length();
        ++replaced;

        // If a maximum number was requested, stop at that number.
        if (count.has_value() && replaced >= count.value()) {
            return replaced;
        }
    }

    return replaced;
}

auto is_int(
    std::string_view data) -> bool
{
    return to_number<int64_t>(data).has_value();
}

auto strerror(
    std::string& buffer) -> void
{
    char* error_ptr = strerror_r(errno, buffer.data(), buffer.length());
    std::size_t len = std::strlen(error_ptr);
    buffer.resize(len);
}

auto strerror() -> std::string
{
    std::string buffer(1024, ' ');
    strerror(buffer);
    return buffer;
}

} // namespace chain::str
