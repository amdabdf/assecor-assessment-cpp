#include "customer_archive.h"
#include <utility>   // std::move

namespace customerlib {

CustomerArchive::CustomerArchive(Backend backend, std::string source)
    : backend_{backend}, source_{std::move(source)} {}

int CustomerArchive::add(customer::Customer c) {
    switch (backend_) {
        case Backend::InMemory: return add_mem(std::move(c));
        case Backend::File:     return add_file(std::move(c));
        case Backend::Cloud:    return add_cloud(std::move(c));
    }
    return -1; // unreachable
}

std::optional<customer::Customer> CustomerArchive::get_by_id(int id) const {
    switch (backend_) {
        case Backend::InMemory: return get_by_id_mem(id);
        case Backend::File:     return get_by_id_file(id);
        case Backend::Cloud:    return get_by_id_cloud(id);
    }
    return std::nullopt; // unreachable
}

std::vector<customer::Customer> CustomerArchive::get_all() const {
    switch (backend_) {
        case Backend::InMemory: return get_all_mem();
        case Backend::File:     return get_all_file();
        case Backend::Cloud:    return get_all_cloud();
    }
    return {}; // unreachable
}

// ---- In-memory implementation ----

int CustomerArchive::add_mem(customer::Customer c) {
    // Archive assigns the id; require all text fields non-empty
    if (!is_text_complete(c)) return -1;
    const int id = next_id_++;
    c.id = id;
    store_.emplace(id, std::move(c));
    return id;
}

std::optional<customer::Customer> CustomerArchive::get_by_id_mem(int id) const {
    auto it = store_.find(id);
    if (it == store_.end()) return std::nullopt;
    return it->second;
}

std::vector<customer::Customer> CustomerArchive::get_all_mem() const {
    std::vector<customer::Customer> out;
    out.reserve(store_.size());
    for (const auto& kv : store_) out.push_back(kv.second);
    return out;
}

bool CustomerArchive::is_text_complete(const customer::Customer& c) {
    // Completeness rule: all text fields required (id is assigned here)
    return !c.first_name.empty()
        && !c.last_name.empty()
        && !c.zip_code.empty()
        && !c.city.empty();
}

// ---- File backend (Placeholder) ----

int CustomerArchive::add_file(customer::Customer c) {
    (void)c;
    // TODO: implement file persistence
    return -1; // not implemented yet
}

std::optional<customer::Customer> CustomerArchive::get_by_id_file(int id) const {
    (void)id;
    // TODO: implement
    return std::nullopt;
}

std::vector<customer::Customer> CustomerArchive::get_all_file() const {
    // TODO: implement
    return {};
}

// ---- Cloud backend (Placeholder) ----

int CustomerArchive::add_cloud(customer::Customer c) {
    (void)c;
    // TODO: implement cloud persistence using 'source_'
    return -1; // not implemented yet
}

std::optional<customer::Customer> CustomerArchive::get_by_id_cloud(int id) const {
    (void)id;
    // TODO: implement
    return std::nullopt;
}

std::vector<customer::Customer> CustomerArchive::get_all_cloud() const {
    // TODO: implement
    return {};
}

} // namespace customerlib
