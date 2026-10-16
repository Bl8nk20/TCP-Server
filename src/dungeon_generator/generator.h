#ifndef DUNGEON_GENERATOR_H
#define DUNGEON_GENERATOR_H

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
 *  Enum für Verschiedene Typen (Höhle,
 */

#include "grid/grid.h"
typedef enum{
    CAVE,
    STRONGHOLD,
    NOTHING
}DungeonType;

typedef struct{
    size_t width;
    size_t height;
    bool is_multi_layered;
    size_t amt_Layers;
    unsigned int seed;
    int amt_Repetitions;
}DungeonParams;

typedef struct{
    DungeonType type;
    DungeonGrid* (*generate)(const DungeonParams *params);
    void (*free_grid)(DungeonGrid *grid);
}DungeonGenerator;

bool validate_inputs(const DungeonParams *params);
DungeonGenerator* dungeon_generator_create(DungeonType type);
void generate_dungeor_destroy(DungeonGenerator *generator);

#endif
