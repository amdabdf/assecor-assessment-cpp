#ifndef CUSTOMER_FORMATTER_H
#define CUSTOMER_FORMATTER_H

#include "customer.h"
#include "customer_archive.h"
#include <string>

namespace customerlib {

// Formats customer data by querying the archive (archive hides the storage backend).
class CustomerFormatter {
public:
    explicit CustomerFormatter(const CustomerArchive& archive) : archive_(archive) {}

    // Formats according to the spec or returns "(kein Kunde)"
    std::string format_by_id(int id) const {
        auto c = archive_.get_by_id(id);
        if (!c) return "(kein Kunde)";
        const auto& x = *c;
        return x.last_name + ", " + x.first_name + ", " + x.zip_code + " " + x.city + ", " +
               customer::to_string(x.favorite_color);
    }

private:
    const CustomerArchive& archive_;
};

} // namespace customerlib

#endif // CUSTOMER_FORMATTER_H