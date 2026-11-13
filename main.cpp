#include "raylib.h"
#include "map.h"
#include "display.h"
#include "player.h"
#include "robot.h"
#include "dog.h"
#include "item.h"
#include <string>
#include <cctype>
#include "position.h"
#include "gameLog.h"
using namespace std;

enum class State
{
    PLAYING,
    MACHINE_PUZZLE,
    FINAL_PUZZLE,
    DEAD,
    WON
};

int main()
{
    InitWindow(800, 720, "Protocol: Echo");
    SetTargetFPS(60);

    Map map;
    Display display;
    GameLog log;

    Player player(0, 0, 0, 0);
    Robot robot(3, 3, 1, 1);
    Dog dog(1, 0, 2, 2);

    Stew stew(0, 0, 2, 2);
    Bone bone(0, 3, 1, 1);
    Screw screw(2, 1, 2, 2);
    Machine machine(1, 2, 2, 2);

    map.getTile(0, 0, 0, 0).setOccupant(&player);
    map.getTile(3, 3, 1, 1).setOccupant(&robot);
    map.getTile(1, 0, 2, 2).setOccupant(&dog);

    map.getTile(0, 0, 2, 2).setObject(&stew);
    map.getTile(0, 3, 1, 1).setObject(&bone);
    map.getTile(2, 1, 2, 2).setObject(&screw);
    map.getTile(1, 2, 2, 2).setObject(&machine);

    display.addMessage("You awaken in a silent, abandoned village.");
    display.addMessage("Robot: Objective: Stabilize environment.");

    log.logEvent("Game started. Player spawned.");
    log.logPlayerState(player);

    State state = State::PLAYING;
    string puzzleInput = "";
    string puzzleMessage = "";
    string endReason = "";
    bool endScreenReady = false;
    MachinePuzzle &machinePuzzle = machine.getPuzzle();

    while (!WindowShouldClose())
    {

        if (state == State::PLAYING)
        {
            char move = 0;
            if (IsKeyPressed(KEY_W))
                move = 'w';
            if (IsKeyPressed(KEY_A))
                move = 'a';
            if (IsKeyPressed(KEY_S))
                move = 's';
            if (IsKeyPressed(KEY_D))
                move = 'd';
            if (IsKeyPressed(KEY_Q))
                break;

            if (move != 0)
            {
                player.move(move, map, display);
                player.update(map);
                robot.update(map);
                dog.update(map);

                if (display.getLastMessage() == "MACHINE_PUZZLE_OPEN")
                {
                    display.clearLastMessage();
                    puzzleMessage = "";
                    state = State::MACHINE_PUZZLE;
                }
            }

            if (IsKeyPressed(KEY_E))
            {
                Position pPos(map.toGlobalRow(player.getBlockRow(), player.getRow()),
                              map.toGlobalCol(player.getBlockCol(), player.getCol()));
                Position rPos(map.toGlobalRow(robot.getBlockRow(), robot.getRow()),
                              map.toGlobalCol(robot.getBlockCol(), robot.getCol()));

                if (pPos.manhattanDistance(rPos) == 1 && robot.isHostile() && !robot.isDisabled() && player.hasScrewItem())
                {
                    display.addMessage("You jam the screw into the robot's core.");
                    robot.disable();
                    log.logEvent("Player used screw on robot. Final puzzle triggered.");
                    log.logPlayerState(player);
                    puzzleInput = "";
                    state = State::FINAL_PUZZLE;
                    endScreenReady = false;
                }
            }

            if (machinePuzzle.isSolved() && !robot.isHostile())
            {
                robot.setHostile();
                display.addMessage("Something shifts. The robot's eyes turn red.");
            }

            if (!player.isAlive())
            {
                log.logEvent("Player died from poison.");
                log.logResult("DEATH — " + endReason, player);
                endReason = "The poison consumed you. You collapse alone.";
                state = State::DEAD;
                endScreenReady = false;
            }
            if (robot.isDisabled() && robot.isFinalPuzzleSolved())
            {
                log.logEvent("Final puzzle solved. Player escaped.");
                log.logResult("WIN — " + endReason, player);
                endReason = "You decoded the signal. The robot shuts down. You are free.";
                state = State::WON;
                endScreenReady = false;
            }
        }

        else if (state == State::MACHINE_PUZZLE)
        {
            if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1))
            {
                bool ok = machinePuzzle.submitChoice(1);
                if (machinePuzzle.isSolved())
                {
                    map.openFinalZone();
                    log.logEvent("Machine puzzle solved. Final zone opened.");
                    log.logPlayerState(player);
                    display.addMessage("The machine hums. A path opens ahead.");
                    state = State::PLAYING;
                }
                else if (!ok)
                {
                    player.takeDamage(100);
                    endReason = "You pulled the lever too early. The explosion was instant.";
                    state = State::DEAD;
                    endScreenReady = false;
                }
                else
                {
                    puzzleMessage = "The dial turns...";
                }
            }
            if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2))
            {
                player.takeDamage(100);
                endReason = "The red button triggered a chain reaction. You never had a chance.";
                state = State::DEAD;
                endScreenReady = false;
            }
            if (IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_KP_3))
            {
                bool ok = machinePuzzle.submitChoice(3);
                if (ok)
                {
                    puzzleMessage = "The dial turns. Something shifts...";
                }
                else
                {
                    player.takeDamage(100);
                    endReason = "Something explodes beneath your feet.";
                    state = State::DEAD;
                    endScreenReady = false;
                }
            }
            if (IsKeyPressed(KEY_ESCAPE))
            {
                state = State::PLAYING;
            }
        }

        else if (state == State::FINAL_PUZZLE)
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if (key >= 32 && key <= 125 && (int)puzzleInput.size() < 10)
                {
                    puzzleInput += (char)key;
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !puzzleInput.empty())
            {
                puzzleInput.pop_back();
            }
            if (IsKeyPressed(KEY_ENTER))
            {
                bool correct = robot.getFinalPuzzle().checkAnswer(puzzleInput);
                if (correct)
                {
                    player.setPoisoned(false);
                    display.addMessage("Poison inhibitor released. ESCAPE NOW.");
                    endReason = "You decoded the signal. The robot shuts down. You are free.";
                    state = State::WON;
                    endScreenReady = false;
                }
                else
                {
                    player.takeDamage(100);
                    endReason = "Wrong answer. The robot overloads and destroys you.";
                    state = State::DEAD;
                    endScreenReady = false;
                }
                puzzleInput = "";
            }
        }

        BeginDrawing();
        ClearBackground({20, 30, 20, 255});

        if (state == State::PLAYING)
        {
            display.render(map, player);
        }
        else if (state == State::MACHINE_PUZZLE)
        {
            display.render(map, player);
            display.drawMachinePuzzle(machinePuzzle.getStep(), puzzleMessage);
        }
        else if (state == State::FINAL_PUZZLE)
        {
            display.render(map, player);
            display.drawFinalPuzzle(puzzleInput);
        }
        else if (state == State::DEAD)
        {
            display.showDeath(endReason);
            if (!endScreenReady)
            {
                endScreenReady = true;
            }
            else if (GetKeyPressed() != 0)
            {
                break;
            }
        }
        else if (state == State::WON)
        {
            display.showWin(endReason);
            if (!endScreenReady)
            {
                endScreenReady = true;
            }
            else if (GetKeyPressed() != 0)
            {
                break;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
