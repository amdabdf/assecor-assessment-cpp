#include <iostream>
#include <sstream>
#include <string>
#include "customer.h"
#include "customer_archive.h"
#include "customer_formatter.h"

using customerlib::CustomerArchive;
using customerlib::Backend;

static void print_help() {
    std::cout << "commands:\n"
              << "  add               - add a new customer (interactive)\n"
              << "  get <id>          - print one customer by id\n"
              << "  list              - print all customers\n"
              << "  help              - show this help\n"
              << "  quit              - exit\n";
}

static bool read_int(const std::string& s, int& out) {
    // Strict integer parsing: no trailing characters allowed
    std::istringstream is(s);
    return (is >> out) && is.peek() == std::char_traits<char>::eof();
}

int main(int argc, char** argv) {
    // Optional backend from args: "file:<path>", "cloud:<url>"; default is in-memory
    Backend be = Backend::InMemory;
    std::string source;

    if (argc >= 2) {
        std::string arg = argv[1];
        if (arg.rfind("file:", 0) == 0) {
            be = Backend::File;
            source = arg.substr(5);
        } else if (arg.rfind("cloud:", 0) == 0) {
            be = Backend::Cloud;
            source = arg.substr(6);
        }
    }

    CustomerArchive archive{be, source};
    customerlib::CustomerFormatter fmt{archive};

    std::cout << "Customer Console (type 'help')\n";
    print_help();

    std::string line;
    while (std::cout << "> " && std::getline(std::cin, line)) {
        if (line == "quit") break;
        if (line == "help" || line.empty()) { print_help(); continue; }

        std::istringstream iss(line);
        std::string cmd; iss >> cmd;

        if (cmd == "add") {
            // Collect fields interactively
            std::string first, last, zip, city, color_s;

            std::cout << "first: ";
            std::getline(std::cin, first);

            std::cout << "last: ";
            std::getline(std::cin, last);

            std::cout << "zip: ";
            std::getline(std::cin, zip);

            std::cout << "city: ";
            std::getline(std::cin, city);

            std::cout << "color (0=Unbekannt, 1=Blau, 2=Gruen, 3=Violett, 4=Rot, 5=Gelb, 6=Tuerkis, 7=Weiss): ";
            std::getline(std::cin, color_s);

            // Validate color input
            int color_i = 0;
            if (!read_int(color_s, color_i)) {
                std::cout << "invalid numeric input\n";
                continue;
            }

            // Archive assigns the id (pass 0 here)
            customer::Customer c{0, first, last, zip, city, customer::color_from_int(color_i)};

            // Ensure text fields are present
            if (first.empty() || last.empty() || zip.empty() || city.empty()) {
                std::cout << "incomplete data (all text fields required)\n";
                continue;
            }

            const int assigned = archive.add(std::move(c));
            if (assigned < 0) {
                std::cout << "could not add (backend not available or invalid)\n";
                continue;
            }
            std::cout << "added with id " << assigned << "\n";
        }
        else if (cmd == "get") {
            std::string id_s; iss >> id_s;
            int id = 0;
            if (!read_int(id_s, id)) { std::cout << "usage: get <id>\n"; continue; }
            std::cout << fmt.format_by_id(id) << "\n";
        }
        else if (cmd == "list") {
            for (const auto& c : archive.get_all()) {
                std::cout << fmt.format_by_id(c.id) << "\n";
            }
        }
        else {
            std::cout << "unknown command\n";
        }
    }
    return 0;
}