# C++ Entwicklertest – Kundenarchiv

## Überblick
- **Header (`include/customer.h`)**: C-kompatibles Legacy-Struct unverändert + moderner C++-Layer (`customer::Customer`, `enum class Color`, Konvertierung).
- **Bibliothek**:
  - `CustomerArchive` – speichert Kunden (in-memory), API: `add`, `get_by_id`, `get_all`. Backend-Auswahl vorbereitet (`InMemory` / `File` / `Cloud`-Stubs).
  - `CustomerFormatter` – formatiert: `"<Nachname>, <Vorname>, <PLZ> <Stadt>, <Farbe>"` oder `"(kein Kunde)"`.
- **CLI (`app`)**: `add`, `get <id>`, `list`, `quit`. IDs werden automatisch vergeben.

## Wichtige Entscheidungen
- Rückwärtskompatibel: C-Teil bleibt erhalten; neue C++-Programme nutzen `customer::Customer`.
- Speicher-Unabhängigkeit: Archiv kapselt Speicher intern; API bleibt stabil (später Datei/Cloud ohne API-Änderung).
- **Warum C++17?** Wegen `std::optional` im Archiv (`get_by_id`) – benötigt C++17.
- Sprache: README Deutsch & Farbnamen im Code deutsch (Aufgabenbeispiel). Code-Kommentare Englisch.

## Projektstruktur
```
include/  customer.h, customer_archive.h, customer_formatter.h
src/      customer_archive.cpp
app/      main.cpp
tests/    unit_archive.cpp, unit_formatter.cpp, integration.cpp
CMakeLists.txt
```

## Build & Tests (Windows, Ninja + GCC/MinGW, Debug)
Voraussetzungen: CMake, Ninja, MinGW-w64 (GCC) im PATH.

```powershell
cmake -S . -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
ctest --test-dir build --output-on-failure
.\build\app.exe
```

## Benutzung (CLI)
- `add` → Kundendaten interaktiv eingeben; Archiv vergibt ID.
- `get <id>` → formatierten Datensatz ausgeben oder "(kein Kunde)".
- `list` → alle Datensätze, je Zeile im geforderten Format.
- Start mit (Stub-)Backends möglich:
  - `app.exe` (In-Memory, Default)

## Tests
- Unit: `unit_archive` (Archivfunktionen), `unit_formatter` (Formatierung).
- Integration: `integration` (Archiv + Formatter zusammen).
- Ausführen: `ctest --test-dir build --output-on-failure`.

## Akzeptanzkriterien & DoD (Abdeckung)
- Moderner C++-Header mit C-Kompatibilität – **erfüllt**
- Bibliothek nutzt `customer::Customer` – **erfüllt**
- In-Memory-Speicher, später austauschbar (API stabil) – **erfüllt**
- Formatter holt selbst Daten aus Archiv – **erfüllt**
- Format exakt wie gefordert; „kein Kunde“ abgedeckt – **erfüllt**
- CLI: beliebig viele Kunden, nur vollständige Einträge gespeichert – **erfüllt**
- Unit- & Integrationstests vorhanden; lokal ausführbar; keine Warnings im Produktcode; Programm baut & startet – **erfüllt**
