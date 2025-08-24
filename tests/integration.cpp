#include <cassert>
#include <string>
#include "customer.h"
#include "customer_archive.h"
#include "customer_formatter.h"

using customerlib::CustomerArchive;
using customerlib::Backend;

int main() {
    // End-to-end: add → format_by_id
    CustomerArchive ar{Backend::InMemory};
    customerlib::CustomerFormatter fmt{ar};

    customer::Customer c{0, "Hans", "Mueller", "677742", "Lauterecken", customer::Color::Blue};
    const int id = ar.add(c);
    assert(id > 0);

    const std::string out = fmt.format_by_id(id);
    assert(out == "Mueller, Hans, 677742 Lauterecken, Blau");

    const std::string miss = fmt.format_by_id(999);
    assert(miss == "(kein Kunde)");

    return 0;
}