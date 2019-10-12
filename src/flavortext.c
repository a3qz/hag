#include "floor.h"
#include "flavortext.h"

char* flavortext_from_floor(void) {
    static int visited[FLOOR_COUNT] = {0};
    static char* floor_texts[FLOOR_COUNT] = {
        "You find yourself on the first floor of a dangerous dungeon.",
        "You make your way down to the second floor with a sense of relief.",
        "You pass the first two floors with blood running down your face looking towards the monsters roaming in front of you... you draw your weapon and make your way forward",
        "You come up to the fourth floor and see that everything is pitch black with only a single torch hanging on the wall. You grab the torch and venture in the darkness.",
        "You find yourself on the fifth floor... with a sense of determination you proudly press onward",
		"The air gets thinner as you make your way down, you look to your left and see a scratched out number... you make out what it says... 6...",
        "You find it harder to breath as you come down the steps not knowing what lies ahead on the seventh floor",
        "Struggling to breath, you crawl down the steps and hear growls coming from deep in the dungeon... ",
        "Huffing and puffing you feel a sense of accomplishment as you feel like you can make it through... you vaguely recall how many steps you have walked through and realize you are on floor nine...",
		"Shivers run down your back as you come down the stairs and realize that this is the last floor... what awaits you at the end?"
    };
    if (!visited[floor_get()]) {
        visited[floor_get()] = 1;
        return floor_texts[floor_get()];
    } else {
        return "This floor seems familiar.";
    }
}
