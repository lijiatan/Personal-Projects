// ansi_functions.h

#ifndef ANSI_FUNCTIONS_H
#define ANSI_FUNCTIONS_H

#include <iostream>
#include <sstream>

template <typename T>
std::string red_color(const T &data) {
    std::ostringstream oss;
    oss << data;  // Convert any type to a string
    return "\033[31m" + oss.str() + "\033[0m";  // Return the colored string
}

template <typename T>
std::string black_color(const T &data) {
    std::ostringstream oss;
    oss << data;  // Convert any type to a string
    return "\033[30m" + oss.str() + "\033[0m";  // Return the colored string
}

template <typename T>
std::string green_color(const T &data) {
    std::ostringstream oss;
    oss << data;  // Convert any type to a string
    return "\033[32m" + oss.str() + "\033[0m";  // Return the colored string
}

template <typename T>
std::string yellow_color(const T &data) {
    std::ostringstream oss;
    oss << data;  // Convert any type to a string
    return "\033[33m" + oss.str() + "\033[0m";  // Return the colored string
}

template <typename T>
std::string blue_color(const T &data) {
    std::ostringstream oss;
    oss << data;  // Convert any type to a string
    return "\033[34m" + oss.str() + "\033[0m";  // Return the colored string
}

template <typename T>
std::string magenta_color(const T &data) {
    std::ostringstream oss;
    oss << data;  // Convert any type to a string
    return "\033[35m" + oss.str() + "\033[0m";  // Return the colored string
}

template <typename T>
std::string cyan_color(const T &data) {
    std::ostringstream oss;
    oss << data;  // Convert any type to a string
    return "\033[36m" + oss.str() + "\033[0m";  // Return the colored string
}

// Template function to handle ANSI codes with text
template <typename T>
std::string apply_ansi_code(const T &data, const std::string &code) {
    std::ostringstream oss;
    oss << data;
    return "\033[" + code + "m" + oss.str() + "\033[0m";  // Reset at the end
}

// Function for bold text
template <typename T>
std::string bold(const T &data) {
    return apply_ansi_code(data, "1");
}

// Function for dim/faint text
template <typename T>
std::string faint(const T &data) {
    return apply_ansi_code(data, "2");
}

// Function for italic text
template <typename T>
std::string italic(const T &data) {
    return apply_ansi_code(data, "3");
}

// Function for underlined text
template <typename T>
std::string underline(const T &data) {
    return apply_ansi_code(data, "4");
}

// Function for blinking text
template <typename T>
std::string blink(const T &data) {
    return apply_ansi_code(data, "5");
}

// Function for inverse/reverse video
template <typename T>
std::string inverse(const T &data) {
    return apply_ansi_code(data, "7");
}

// Function for hidden/invisible text
template <typename T>
std::string hidden(const T &data) {
    return apply_ansi_code(data, "8");
}

// Function for strikethrough text
template <typename T>
std::string strikethrough(const T &data) {
    return apply_ansi_code(data, "9");
}

#endif // ANSI_FUNCTIONS_H
