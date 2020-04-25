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

auto to_lower_copy(
    std::string_view data) -> std::string
{
    std::string copy { data };
    to_lower(copy);
    return copy;
}

auto to_upper(
    std::string& data) -> void
{
    std::transform(data.begin(), data.end(), data.begin(), ::toupper);
}

auto to_upper_copy(
    std::string_view data) -> std::string
{
    std::string copy { data };
    to_upper(copy);
    return copy;
}

auto trim_left(
    std::string& data) -> void
{
    if (!data.empty()) {
        auto found = std::find_if_not(
            data.begin(),
            data.end(),
            [](unsigned char ch) -> bool { return std::isspace(ch); });

        // If the entire string is std::isspace just clear it.
        if (found == data.end()) {
            data.clear();
        } else {
            data.erase(data.begin(), found);
        }
    }
}

auto trim_left(
    std::string& data,
    std::string_view to_remove) -> void
{
    if (!data.empty() && !to_remove.empty()) {
        std::size_t total_remove_size = 0;
        std::string_view sv { data.data(), data.length() };
        while (starts_with(sv, to_remove)) {
            sv.remove_prefix(to_remove.size());
            total_remove_size += to_remove.size();
        }

        if (total_remove_size > 0) {
            data.erase(0, total_remove_size);
        }
    }
}

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
                while (starts_with(sv, remove)) {
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

auto trim_left_view(
    std::string_view data) -> std::string_view
{
    if (!data.empty()) {
        std::size_t index = 0;
        while (index < data.length()) {
            if (!std::isspace(static_cast<unsigned char>(data[index]))) {
                break;
            } else {
                ++index;
            }
        }
        data.remove_prefix(index);
    }

    return data;
}

auto trim_left_view(
    std::string_view data,
    std::string_view to_remove) -> std::string_view
{
    if (!data.empty() && !to_remove.empty()) {
        while (starts_with(data, to_remove)) {
            data.remove_prefix(to_remove.size());
        }
    }

    return data;
}

auto trim_left_view(
    std::string_view data,
    const std::vector<std::string_view>& to_remove) -> std::string_view
{
    if (!data.empty() && !to_remove.empty()) {
        while (true) {
            bool had_removal { false };

            for (const auto& remove : to_remove) {
                while (starts_with(data, remove)) {
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

auto trim_right(
    std::string& data) -> void
{
    if (!data.empty()) {
        auto found = std::find_if_not(
            data.rbegin(),
            data.rend(),
            [](unsigned char ch) -> bool { return std::isspace(ch); });

        if (found == data.rend()) {
            data.clear();
        } else {
            data.erase(found.base(), data.end());
        }
    }
}

auto trim_right(
    std::string& data,
    std::string_view to_remove) -> void
{
    if (!to_remove.empty()) {
        std::size_t total_remove_size = 0;
        std::string_view sv { data.data(), data.length() };
        while (ends_with(sv, to_remove)) {
            sv.remove_suffix(to_remove.size());
            total_remove_size += to_remove.size();
        }
        if (total_remove_size > 0) {
            data.erase(data.size() - total_remove_size);
        }
    }
}

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
                while (ends_with(sv, remove)) {
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

auto trim_right_view(
    std::string_view data) -> std::string_view
{
    if (!data.empty()) {
        int64_t index = static_cast<int64_t>(data.length() - 1);
        while (index >= 0) {
            if (!std::isspace(static_cast<unsigned char>(data[static_cast<std::size_t>(index)]))) {
                break;
            } else {
                --index;
            }
        }

        data = data.substr(0, static_cast<std::size_t>(index + 1));
    }

    return data;
}

auto trim_right_view(
    std::string_view data,
    std::string_view to_remove) -> std::string_view
{
    if (!data.empty() && !to_remove.empty()) {
        while (ends_with(data, to_remove)) {
            data.remove_suffix(to_remove.size());
        }
    }

    return data;
}

auto trim_right_view(
    std::string_view data,
    const std::vector<std::string_view>& to_remove) -> std::string_view
{
    if (!data.empty() && !to_remove.empty()) {
        while (true) {
            bool had_removal { false };

            for (const auto& remove : to_remove) {
                while (ends_with(data, remove)) {
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

auto trim(
    std::string& data,
    const std::vector<std::string_view>& to_remove) -> void
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
    return trim_right_view(trim_left_view(data, to_remove), to_remove);
}

auto trim_view(
    std::string_view data,
    const std::vector<std::string_view>& to_remove) -> std::string_view
{
    return trim_right_view(trim_left_view(data, to_remove), to_remove);
}

auto replace(
    std::string& data,
    std::string_view from,
    std::string_view to,
    Case case_type,
    std::optional<std::size_t> count) -> std::size_t
{
    (void)case_type; // TODO not supported yet

    auto max = std::numeric_limits<std::size_t>::max();

    if (count.has_value()) {
        if (count.value() == 0) {
            return 0;
        } else {
            max = count.value();
        }
    }

    std::size_t replaced { 0 };

    std::size_t start_pos { 0 };
    while ((start_pos = data.find(from.data(), start_pos, from.length())) != std::string::npos) {
        data.replace(start_pos, from.length(), to.data(), to.length());
        start_pos += to.length();
        ++replaced;

        if (replaced >= max) {
            return replaced;
        }
    }

    return replaced;
}

auto replace_copy(
    std::string_view data,
    std::string_view from,
    std::string_view to,
    Case case_type,
    std::optional<std::size_t> count) -> std::pair<std::string, std::size_t>
{
    std::string copy { data };
    std::size_t num = replace(copy, from, to, case_type, count);
    return { std::move(copy), num };
}

auto is_int(
    std::string_view data) -> bool
{
    // TODO These probably need stricter requirements to differentiate between
    // an integer and a float.
    if (data.find('.') != std::string_view::npos) {
        return false;
    }

    return to_number<int64_t>(data).has_value();
}

auto is_float(
    std::string_view data) -> bool
{
    if (data.find('.') == std::string_view::npos) {
        return false;
    }

    return to_number<double>(std::string { data }).has_value();
}

auto is_number(
    std::string_view data) -> bool
{
    return is_int(data) || is_float(std::string { data });
}

auto strerror(
    int errsv) -> std::string
{
    // strerror_r appears to ignore passed in buffer args, manually copy
    // the data from the returned error_ptr.  The XSI complain version of this
    // function would probably just work...
    // TODO: might need some #defines to make this more portable for non-GNU.
    constexpr std::size_t LEN = 1024;
    char buffer[LEN];
    char* error_ptr = strerror_r(errsv, buffer, LEN);

    return std::string { error_ptr, std::strlen(error_ptr) };
}

} // namespace chain::str
