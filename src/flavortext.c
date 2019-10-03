#include "floor.h"

char* flavortext_from_floor() {
    static int visited[FLOOR_COUNT] = {0};
    static char* floor_texts[FLOOR_COUNT] = {
        "You find yourself on the first floor of a dangerous dungeon.",
        "You find yourself on the second floor.",
        "You find yourself on the third floor.",
        "You find yourself on the fourth floor.",
        "You find yourself on the fifth floor.",
        "You find yourself on the sixth floor.",
        "You find yourself on the seventh floor.",
        "You find yourself on the eigth floor.",
        "You find yourself on the ninth floor.",
        "You find yourself on the last floor."
    };
    if (!visited[floor_get()]) {
        visited[floor_get()] = 1;
        return floor_texts[floor_get()];
    } else {
        return "This floor seems familiar.";
    }
}
