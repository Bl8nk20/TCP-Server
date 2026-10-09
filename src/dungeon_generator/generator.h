/*
 * Basisklasse / Interface für ein Dungeon Generator
 * Features, die der Generator beinhalten soll:
 *  * Verschiedene "Dungeon Types" unterstützen (Höhle, Grabmal, Turm, etc)
 *  * Unterstützung von Optionalen Parametern (Größe, Layers, Typ, Output?) 
 *  * Multi-Layered Dungeons unterstützen (soll automatisch auf der nächsten ebene den vorherigen Ausgang == nächster Eingang setzen)
 *  * Implementation von zwei verschiedenen Generatoren
 *      * Cellular Automata      : für "organisch" bzw. natürlich entstandene Konstrukte / Dungeons
 *      * Binary Space Partition : für "künstlich" bzw. gebaute Dungeons / Grabmäler
 *  
 * Implementierungsschritte:
 *  0. Gedanken / Pläne für Klassen. Interfaces & Abstraktionen machen
 *  1. Passende Design Patterns suchen
 *  2. Vorbereitungen für beide Algorithmen treffen (ggf. weitere sub-Libraries erstellen) 
 *  3. Cellular Automata Algorithmus implementieren
 *  4. ggf. anpassungen in bestandscode und Wrapper für Ausgabemöglichkeiten schreiben
 *  5. Binary Space Partition (BSP) implementieren
 *  6. Räume als Generische Structs vorbereiten
 *  7. Multi-Layer-Dungeons implementieren, indem BSP angepasst/erweitert wird.
 *
 * Gedanken:
 *  * Struct für (Beliebige-)Übergabeparameter
 *  * Struct für Dungeon-Type -> Davon abhängig machen, welcher Generator aufgerufen wird.
 *  * 
 * Inhalt TypeStruct:
 *  Enum für Verschiedene Typen (Höhle
 */

