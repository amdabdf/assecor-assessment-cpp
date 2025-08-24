#ifndef CUSTOMER_ARCHIVE_H
#define CUSTOMER_ARCHIVE_H

#include "customer.h"
#include <unordered_map>
#include <vector>
#include <optional>
#include <string>

namespace customerlib {

// Storage backend selector, only InMemory is implemented for now
enum class Backend {
    InMemory,
    File,
    Cloud
};

// Customer archive with backend selection.
class CustomerArchive {
public:
    explicit CustomerArchive(Backend backend = Backend::InMemory, std::string source = {});

    // Adds a customer and returns the assigned id (auto-increment).
    // Returns -1 if input is incomplete or backend not available.
    int add(customer::Customer c);

    // Returns a customer by id if found
    std::optional<customer::Customer> get_by_id(int id) const;

    // Returns all customers
    std::vector<customer::Customer> get_all() const;

private:
    // ---- In-memory implementation ----
    int add_mem(customer::Customer c);
    std::optional<customer::Customer> get_by_id_mem(int id) const;
    std::vector<customer::Customer> get_all_mem() const;
    static bool is_text_complete(const customer::Customer& c);

    // ---- File backend (Placeholder) ----
    int add_file(customer::Customer c);
    std::optional<customer::Customer> get_by_id_file(int id) const;
    std::vector<customer::Customer> get_all_file() const;

    // ---- Cloud backend (Placeholder) ----
    int add_cloud(customer::Customer c);
    std::optional<customer::Customer> get_by_id_cloud(int id) const;
    std::vector<customer::Customer> get_all_cloud() const;

private:
    Backend backend_;
    std::string source_;

    // in-memory data
    std::unordered_map<int, customer::Customer> store_;
    int next_id_{1};
};

} // namespace customerlib

#endif // CUSTOMER_ARCHIVE_H
