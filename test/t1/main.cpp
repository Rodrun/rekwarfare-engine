// Tic-Tac-Toe test game using the Rekwarfare Engine
#include <iostream>
#include <iomanip>

#include "Rekwarfare.hpp"

using namespace rekwarfare;

#define WIDTH 800
#define HEIGHT 640
#define SEC_WIDTH WIDTH/3
#define SEC_HEIGHT HEIGHT/3
#define O_SPACING 35

typedef struct {
    int x;
    int y;
    int player_selection; // Store player # if clicked on it
} Section;

bool checkWithinSection(Section s, double, double);
void drawX(Section);
void drawO(Section);
bool sectionOn(Section, int);
bool sectionOn(Section);

int main() {
    // Initialize with RW-engine
    initializeSDL(INIT_EVERYTHING, IMG_PNG, MIX_MP3);
    Window window("t1", WINDOWPOS_UNDEF, WINDOWPOS_UNDEF, WIDTH, HEIGHT);
    initializeOpenGL(2, 1, window());
    setEvent(&window.e);

    Font* font = loadFont("test/resource/AIRSTREA.TTF", 24);
    if (font == nullptr) {
        std::cout << "Failed to load font!\n";
    }

    typedef struct {
        int number;
        //int points;
    } Player;

    enum GameState { PLAYING, END };
    GameState state = PLAYING;

    // Load board
    Section sections[9] = { };
    for (int i = 0; i < 9; i++) {
        sections[i].player_selection = -1;
        sections[i].x = (i % 3) * SEC_WIDTH;
        sections[i].y = (i / 3) * SEC_HEIGHT;
    }

    Player p1 = { 1 };
    Player p2 = { 2 };
    Player players[2] = { p1, p2 };
    int currentPlayer = 0;
    int winningPlayer = -1;
    bool win = false;

    while (window.isRunning()) {
        while (window.getEventPollingState() != 0) {
            window.pollWindowEvents();
            if (state == PLAYING) {
                if (mouseButtonPressed()) {
                    // Check each section for mouse input within borders
                    for (int i = 0; i < 9; i++) {
                        if (checkWithinSection(sections[i], getMouseX(),
                            getMouseY()) && sections[i].player_selection == -1) {
                            sections[i].player_selection =
                                players[currentPlayer].number;
                            // Change to next player
                            if (currentPlayer == 0) {
                                currentPlayer = 1;
                            } else {
                                currentPlayer = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }

        if (state == PLAYING) {
            // Check if player has won the match
            for (int x = 0; x < 2; x++) {
                int i = players[x].number;
                // 0 horizontal, vertical, diagonal
                if (sectionOn(sections[0], i)) {
                    if (sectionOn(sections[1], i) && sectionOn(sections[2], i))
                        win = true;
                    if (sectionOn(sections[3], i) && sectionOn(sections[6], i))
                        win = true;
                    if (sectionOn(sections[4], i) && sectionOn(sections[8], i))
                        win = true;
                }
                // 1 vertical
                if (sectionOn(sections[1], i)) {
                    if (sectionOn(sections[4], i) && sectionOn(sections[7], i))
                        win = true;
                }
                // 2 vertical, diagonal
                if (sectionOn(sections[2], i)) {
                    if (sectionOn(sections[5], i) && sectionOn(sections[8], i))
                        win = true;
                    if (sectionOn(sections[4], i) && sectionOn(sections[6], i))
                        win = true;
                }
                // 3 horizontal
                if (sectionOn(sections[3], i) && sectionOn(sections[4], i) &&
                    sectionOn(sections[5], i))
                    win = true;
                // 6 horizontal
                if (sectionOn(sections[6], i) && sectionOn(sections[7], i) &&
                    sectionOn(sections[8], i))
                    win = true;

                if (win) {
                    winningPlayer = players[x].number;
                    state = END;
                    break;
                } else {
                    bool full = true;
                    for (auto s : sections) {
                        if (!sectionOn(s))
                            full = false;
                    }
                    if (full) {
                        winningPlayer = -1;
                        state = END;
                        break;
                    }
                }
            }
        } else if (state == END) {
            // Assign point & declare winner
            if (winningPlayer != -1) {
                std::cout << "Player " << players[winningPlayer - 1].number <<
                    " has won!\n";
            } else {
                std::cout << "Cat! Nobody wins!\n";
            }
            // Reset sections
            for (int i = 0; i < 9; i++) {
                sections[i].player_selection = -1;
            }

            currentPlayer = 0;
            winningPlayer = -1;
            win = false;
            state = PLAYING;
        }

        window.clear();
        pushMatrix();

        // draw board
        Color c = { 1, 1, 1, 1 };
        drawLine(SEC_WIDTH, 0, SEC_WIDTH, HEIGHT, 0, c);
        drawLine(SEC_WIDTH * 2, 0, SEC_WIDTH * 2, HEIGHT, 0, c);
        drawLine(0, SEC_HEIGHT, WIDTH, SEC_HEIGHT, 0, c);
        drawLine(0, SEC_HEIGHT * 2, WIDTH, SEC_HEIGHT * 2, 0, c);
        // draw marks
        for (int i = 0; i < 9; i++) {
            if (sections[i].player_selection == p1.number)
                drawX(sections[i]);
            else if (sections[i].player_selection == p2.number)
                drawO(sections[i]);
        }

        popMatrix();
        window.update();
    }

    deleteFont(font);
    destroySDL();
    return 0;
}

void drawX(Section s) {
    Color c = { 1, 1, 1, 1 };
    drawLine(s.x, s.y, s.x + SEC_WIDTH, s.y + SEC_HEIGHT, 0, c);
    drawLine(s.x + SEC_WIDTH, s.y, s.x, s.y + SEC_HEIGHT, 0, c);
}

void drawO(Section s) {
    Color c = { 1, 1, 1, 1 };
    // No ellipse support, yet.
    drawRectangle(s.x + O_SPACING, s.y + O_SPACING, SEC_WIDTH - (2 * O_SPACING),
        SEC_HEIGHT - (2 * O_SPACING), 0, c);
}

bool checkWithinSection(Section s, double x, double y) {
    if (x < s.x + SEC_WIDTH && x > s.x && y < s.y + SEC_HEIGHT && y > s.y)
        return true;
    return false;
}

bool sectionOn(Section s, int pn) {
    if (s.player_selection == pn)
        return true;
    return false;
}

bool sectionOn(Section s) {
    return (s.player_selection != -1);
}

/*
Copyright (c) 2016 Juan Mendez

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgement in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/
