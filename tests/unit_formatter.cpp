#include <cassert>
#include "customer.h"
#include "customer_archive.h"
#include "customer_formatter.h"

using customerlib::CustomerArchive;
using customerlib::Backend;
using customerlib::CustomerFormatter;

int main() {
    CustomerArchive ar{Backend::InMemory};
    CustomerFormatter fmt{ar};

    // Add one customer; archive assigns the id
    customer::Customer c{0, "Hans", "Mueller", "677742", "Lauterecken", customer::Color::Blue};
    int id = ar.add(c);
    assert(id > 0);

    // Existing
    auto s1 = fmt.format_by_id(id);
    assert(s1 == "Mueller, Hans, 677742 Lauterecken, Blau");

    // Missing
    auto s2 = fmt.format_by_id(999);
    assert(s2 == "(kein Kunde)");

    return 0;
}
