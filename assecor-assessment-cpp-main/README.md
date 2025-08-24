# C++ Entwicklertest

## Szenario

Deine Firma hat in den letzten 30 Jahren einige verschiedene Programme in C und C++ entwickelt. Um den Entwicklungskosten gering zu halten und den Datenaustausch zwischen den Programmen zu ermöglichen, wurden von Beginn an Bibliotheken benutzt. Einige dieser alten Bibliotheken sollen nun modernisiert und erweitert werden. C-Programme werden in C++ Code überführt.

## Aufgaben

1. Die Datei [customer.h](customer.h) enthält eine C-Datenstruktur, in der Kundendaten gespeichert werden können. Im Unternehmen nutzen verschiedene Applikationen diesen Header. Seit kurzem allerdings keine Programme mehr in C.
Führe ein Refactoring des Headers customer.h in modernes C++ durch. Ziel ist es das neue Programme und Bibliotheken auf einen modernes Kundendaten-Objekt zurückgreifen können. Stelle dabei aber auch sicher, dass der Header zu schon bestehenden Programmen kompatibel bleibt.


3. Schreibe eine Bibliothek, die Kundendaten speichern kann. Die Bibliothek soll aus zwei Klassen bestehen:

	1. Ein Kunden-Archiv, das folgende Funktionen hat:
		1. Kunden hinzufügen
		2. Alle Kunden ausgeben
		3. Kundendaten zu einer ID ausgeben
	2. Ein Kundendatenformatierer, der folgendes kann:
		1. Gibt die Kundendaten zu einer gegebenen ID als schön formatierten Ausgabetext aus.


4. Schreibe eine Konsolenapplikation mit folgenden Funktionen:
	1. Hinzufügen eines Kunden zum Archiv
	2. Ausgeben der Kundendaten zu einer ID
	3. Ausgeben der Liste aller gespeicherten Kundendaten
	
## Akzeptanzkriterien

- Der Header [customer.h](customer.h) ist zu modernem C++ refactored. 
- Alte Programme, die den Header [customer.h](customer.h) einbinden, müssen nicht geändert werden.
- Die Bibliothek muss die neue Datenstruktur aus der Datei [customer.h](customer.h) benutzen. 
- Die Kunden sollen vorerst in-memory gespeichert werden. (Keine Datenbank benötigt)
- Es gibt Pläne die Bibliothek zu erweitern, so dass sie die Kundendaten auch woanders speichern kann, wie zum Beispiel in einer Datei, einer Datenbank oder in einem Cloud-Speicher. Schreibe die Bibliothek so, dass diese Änderungen in der Zukunft hinzugefügt werden könnten ohne den bestehenden Code ändern zu müssen.
- Der Kundendatenformatierer ruft die Kundendaten selbständig aus dem Kunden-Archiv. (Unabhängig von der Speichermethode des Archivs)
- Die Kundendaten sollen für den Ausgabetext in folgendem Format formatiert sein:
	- Wenn der Kunde gefunden wurde:
		- `<Nachname>, <Vorname>, <Postleitzahl> <Stadt>, <Lieblingsfarbe>`
		- Beispiel: "Müller, Hans, 677742 Lauterecken, Blau"
	- Wenn kein Kunde gefunden wurde:
		- "(kein Kunde)"
- Mit der Konsolenapplikation können beliebig viele Kunden angelegt und aus dem Archiv abgerufen werden.
- Die Konsolenapplikation stellt sicher, dass nur vollständig erfasste Kundendaten im Archiv gespeichert werden.
		
## Definition of Done
- Die Akzeptanzkriterien sind erfüllt.
- Es existieren Unit-Tests, die Funktionalität des Codes so testen, dass dieser problemlos refactored oder erweitert werden könnte.
	- Unit-Tests sollten mocked dependencies benutzen.
- Es existieren Integrationstests.
- Alle Tests wurden lokal ausgeführt und bestanden.
- Der Compiler gibt keine Warnings aus.
- Das Programm kompiliert und lässt sich starten.
