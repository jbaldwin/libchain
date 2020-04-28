#include "chain/Chain.hpp"

#include <cstring>

namespace chain::str {

const std::stringstream g_unused_stringstream {};

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
            ::isspace);

        // If the entire string is std::isspace just clear it.
        if (found == data.end()) {
            data.clear();
        } else {
            data.erase(data.begin(), found);
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

auto trim(
    std::string& data) -> void
{
    trim_left(data);
    trim_right(data);
}

auto trim_view(
    std::string_view data) -> std::string_view
{
    return trim_left_view(trim_right_view(data));
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
