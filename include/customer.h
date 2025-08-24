#ifndef __DEFINED_CUSTOMER_H
#define __DEFINED_CUSTOMER_H

// =========================
//    Legacy C API (compat)
// =========================

// Bonus: Added COLOR_UNDEFINED to cover cases with other colors
#define COLOR_UNDEFINED  0
#define COLOR_BLUE       1
#define COLOR_GREEN      2
#define COLOR_VIOLET     3
#define COLOR_RED        4
#define COLOR_YELLOW     5
#define COLOR_TURQUOISE  6
#define COLOR_WHITE      7

// Legacy struct. Do not change layout.
struct _CUSTOMER {
    int  id;
    char first_name[24];
    char last_name[32];
    char zip_code[8];
    char city[32];
    int  favorite_color; // uses COLOR_*
};

typedef struct _CUSTOMER CUSTOMER;

#ifdef __cplusplus
// =========================
//    Modern C++ API
// =========================

#include <string>
#include <cstddef>
#include <cstring>
#include <utility>

namespace customer {

// Strongly typed color matching legacy values
enum class Color : int {
    Undefined = COLOR_UNDEFINED,
    Blue      = COLOR_BLUE,
    Green     = COLOR_GREEN,
    Violet    = COLOR_VIOLET,
    Red       = COLOR_RED,
    Yellow    = COLOR_YELLOW,
    Turquoise = COLOR_TURQUOISE,
    White     = COLOR_WHITE
};

// Human-readable (German) color name
inline std::string to_string(Color c) {
    switch (c) {
        case Color::Blue:      return "Blau";
        case Color::Green:     return "Gruen";
        case Color::Violet:    return "Violett";
        case Color::Red:       return "Rot";
        case Color::Yellow:    return "Gelb";
        case Color::Turquoise: return "Tuerkis";
        case Color::White:     return "Weiss";
        default:               return "Unbekannt";
    }
}

// Map legacy int to enum
inline Color color_from_int(int v) {
    switch (v) {
        case COLOR_BLUE:      return Color::Blue;
        case COLOR_GREEN:     return Color::Green;
        case COLOR_VIOLET:    return Color::Violet;
        case COLOR_RED:       return Color::Red;
        case COLOR_YELLOW:    return Color::Yellow;
        case COLOR_TURQUOISE: return Color::Turquoise;
        case COLOR_WHITE:     return Color::White;
        default:              return Color::Undefined;
    }
}

// Modern customer type
struct Customer {
    int         id{};                              // id
    std::string first_name;                        // first name
    std::string last_name;                         // last name
    std::string zip_code;                          // postal code
    std::string city;                              // city
    Color       favorite_color{Color::Undefined};  // favorite color

    Customer() = default;

    // Convenience full constructor for C++ callers
    Customer(int id_,
             std::string first,
             std::string last,
             std::string zip,
             std::string city_,
             Color color)
        : id{id_},
          first_name{std::move(first)},
          last_name{std::move(last)},
          zip_code{std::move(zip)},
          city{std::move(city_)},
          favorite_color{color} {}

    // Build from legacy struct
    explicit Customer(const ::CUSTOMER& c)
        : id{c.id},
          first_name{from_c_array(c.first_name)},
          last_name{from_c_array(c.last_name)},
          zip_code{from_c_array(c.zip_code)},
          city{from_c_array(c.city)},
          favorite_color{color_from_int(c.favorite_color)} {}

    // Quick completeness check (id > 0, text fields non-empty; no color requirement)
    bool is_complete() const {
        return id > 0
            && !first_name.empty()
            && !last_name.empty()
            && !zip_code.empty()
            && !city.empty();
    }

    // Bonus: convert back to legacy struct (helps with interop/migration)
    ::CUSTOMER to_c() const {
        ::CUSTOMER c{};
        c.id = id;
        copy_bounded(c.first_name, first_name);
        copy_bounded(c.last_name,  last_name);
        copy_bounded(c.zip_code,   zip_code);
        copy_bounded(c.city,       city);
        c.favorite_color = static_cast<int>(favorite_color);
        return c;
    }

private:
    // Copy std::string into fixed char array (truncate, NUL-terminate)
    template <std::size_t N>
    static void copy_bounded(char (&dst)[N], const std::string& src) {
        static_assert(N > 0, "destination buffer must not be empty");
        const std::size_t limit = (N > 0) ? N - 1 : 0;
        const std::size_t n = (src.size() < limit) ? src.size() : limit;
        if (n > 0) {
            std::memcpy(dst, src.data(), n);
        }
        dst[n] = '\0';
    }

    // Read from fixed char array up to NUL (bounded)
    template <std::size_t N>
    static std::string from_c_array(const char (&a)[N]) {
        std::size_t len = 0;
        while (len < N && a[len] != '\0') { ++len; }
        return std::string(a, len);
    }
};

} // namespace customer

#endif // __cplusplus
#endif // __DEFINED_CUSTOMER_H