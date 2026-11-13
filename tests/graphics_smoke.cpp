// Hidden-window startup and rendering check. Run from the project root.
#include "raylib.h"
#include "display.h"
#include "map.h"
#include "player.h"
int main() {
    SetConfigFlags(FLAG_WINDOW_HIDDEN);
    InitWindow(800, 720, "Protocol Echo rendering check");
    if (!IsWindowReady()) return 1;
    {
        Map map;
        Player player(0,0,0,0);
        Display display;
        display.addMessage("Rendering check");
        for (int i=0; i<3; ++i) {
            BeginDrawing();
            ClearBackground(BLACK);
            display.render(map,player);
            EndDrawing();
        }
    }
    CloseWindow();
    return 0;
}
