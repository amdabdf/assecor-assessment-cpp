#include <cassert>
#include <vector>
#include "customer.h"
#include "customer_archive.h"

using customerlib::CustomerArchive;
using customerlib::Backend;

int main() {
    CustomerArchive ar{Backend::InMemory};

    // Add two valid customers (auto-increment id)
    customer::Customer a{0, "Hans", "Mueller", "12345", "Berlin",  customer::Color::Blue};
    customer::Customer b{0, "Anna", "Schmidt", "54321", "Hamburg", customer::Color::Red};
    customer::Customer bad{0, "", "", "", "", customer::Color::Blue}; // incomplete

    const int id1 = ar.add(a);
    const int id2 = ar.add(b);
    const int id_bad = ar.add(bad);

    // Prevent unused-variable warnings when asserts are compiled out (NDEBUG)
    (void)id2;
    (void)id_bad;

    assert(id1 > 0);
    assert(id2 > 0);
    assert(id1 != id2);
    assert(id_bad == -1);

    // get_by_id
    auto x = ar.get_by_id(id1);
    assert(x.has_value());
    assert(x->first_name == "Hans");

    auto y = ar.get_by_id(99999);
    assert(!y.has_value());

    // get_all
    auto all = ar.get_all();
    assert(all.size() == 2);

    return 0;
}