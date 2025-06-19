#include "raylib.h"
#include <algorithm>

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Dino Runner");
    SetTargetFPS(60);
    InitAudioDevice(); // Initialize audio device

    // Load custom textures
    Texture2D background = LoadTexture("resources/background.png");
    Texture2D player = LoadTexture("resources/player.png");
    Texture2D cactus = LoadTexture("resources/cactus.png");
    Texture2D cloud = LoadTexture("resources/cloud.png");

    // Load custom font
    Font customFont = LoadFont("resources/Daydream.ttf");

    // Scrolling variables
    float cloudX1 = 0.0f;
    float cloudX2 = (float)cloud.width;
    const float cloudSpeed = 1.0f;

    // Player variables
    int surfaceHeight = screenHeight - 182; // 720 - 182 = 538
    float playerY = surfaceHeight - player.height; // Position player base at surfaceHeight
    float velocityY = 0.0f;
    bool isJumping = false;
    const float gravity = 0.5f;
    const float jumpForce = -15.0f;
    Rectangle playerRect = { 0, playerY, 122.0f, (float)player.height }; // Hitbox width set to 122

    // Cactus variables
    float cactusX = screenWidth;
    float cactusSpeed = 10.0f; // Initial speed
    Rectangle cactusRect = { cactusX, surfaceHeight - cactus.height, 90.0f, (float)cactus.height }; // Hitbox width set to 90

    // Game state and score
    bool gameOver = false;
    int score = 0;
    int cactiPassed = 0; // Counter for passed cacti
    float lastCactusX = screenWidth; // Track the last position to detect passing
    int highestScore = 0; // Variable to track highest score

    // Load audio
    Music bgm = LoadMusicStream("resources/bgm.mp3"); // Background music
    Sound jumpSound = LoadSound("resources/jump.wav"); // Jump sound effect
    Sound collisionSound = LoadSound("resources/collision.mp3"); // Collision sound effect
    PlayMusicStream(bgm); // Start playing BGM

    // Volume control
    float musicVolume = 0.5f; // Initial music volume (0.0f to 1.0f)
    float soundEffectVolume = 0.7f; // Initial sound effect volume (0.0f to 1.0f)
    SetMusicVolume(bgm, musicVolume);

    while (!WindowShouldClose()) {
        // Update
        if (!gameOver) {
            // Player movement
            if (IsKeyPressed(KEY_SPACE) && !isJumping) {
                velocityY = jumpForce;
                isJumping = true;
                PlaySound(jumpSound); // Play jump sound
            }
            velocityY += gravity;
            playerY += velocityY;
            if (playerY > (surfaceHeight - player.height)) {
                playerY = surfaceHeight - player.height;
                velocityY = 0.0f;
                isJumping = false;
            }
            playerRect.y = playerY;

            // Cactus movement
            float previousCactusX = cactusX;
            cactusX -= cactusSpeed;
            if (cactusX < -cactus.width) {
                cactusX = screenWidth;
            }
            cactusRect.x = cactusX;

            // Detect if player passed the cactus
            if (previousCactusX > playerRect.x + playerRect.width && cactusX <= playerRect.x + playerRect.width) {
                score += 10; // Increment score by 10 when passing
                cactiPassed++; // Increment cacti passed counter
                if (cactiPassed >= 10) {
                    cactusSpeed += 5.0f; // Increase speed by 5.0f after 10 cacti
                    cactiPassed = 0; // Reset counter for next increment
                }
            }

            // Update highest score
            if (score > highestScore) {
                highestScore = score;
            }

            // Scroll cloud
            cloudX1 -= cloudSpeed;
            cloudX2 -= cloudSpeed;
            if (cloudX1 <= -cloud.width) cloudX1 = cloud.width + cloudX2;
            if (cloudX2 <= -cloud.width) cloudX2 = cloud.width + cloudX1;

            // Collision detection
            if (CheckCollisionRecs(playerRect, cactusRect)) {
                gameOver = true;
                PlaySound(collisionSound); // Play collision sound
            }

            // Volume control with keys
            if (IsKeyPressed(KEY_UP)) {
                musicVolume = fmin(musicVolume + 0.1f, 1.0f); // Increase music volume, cap at 1.0f
                SetMusicVolume(bgm, musicVolume);
            }
            if (IsKeyPressed(KEY_DOWN)) {
                musicVolume = fmax(musicVolume - 0.1f, 0.0f); // Decrease music volume, cap at 0.0f
                SetMusicVolume(bgm, musicVolume);
            }

            // Update BGM
            UpdateMusicStream(bgm);
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw scrolling background
        float backgroundX = 0.0f;
        DrawTexture(background, (int)backgroundX, 0, WHITE);
        DrawTexture(background, (int)(backgroundX + background.width), 0, WHITE);

        // Draw cloud
        DrawTexture(cloud, (int)cloudX1, 50, WHITE); // Position cloud near top
        DrawTexture(cloud, (int)cloudX2, 50, WHITE);

        // Draw player
        DrawTexture(player, 0, (int)playerY, WHITE);

        // Draw cactus
        DrawTexture(cactus, (int)cactusX, surfaceHeight - cactus.height, WHITE);

        // Draw score with custom font
        DrawTextEx(customFont, TextFormat("Score: %d", score), (Vector2 { 10.0f, 10.0f }), (float)customFont.baseSize, 0.0f, BLACK);

        // Draw highest score in top right corner
        char highestScoreText[50];
        sprintf_s(highestScoreText, sizeof(highestScoreText), "High Score: %d", highestScore); // Use sprintf_s with buffer size
        DrawTextEx(customFont, highestScoreText, (Vector2 { screenWidth - MeasureText(highestScoreText, (int)customFont.baseSize) - 150.0f, 10.0f }), (float)customFont.baseSize, 0.0f, BLACK);

        // Draw game over
        if (gameOver) {
            DrawTextEx(customFont, "Game Over! Press R to Restart", (Vector2 { screenWidth / 4, screenHeight / 2 }), customFont.baseSize, 0, RED);
            if (IsKeyPressed(KEY_R)) {
                gameOver = false;
                playerY = surfaceHeight - player.height;
                cactusX = screenWidth;
                score = 0; // Reset score on restart
                cactusSpeed = 10.0f; // Reset speed to initial value
                cactiPassed = 0; // Reset cacti passed counter
                lastCactusX = screenWidth;
                cloudX1 = 0.0f;
                cloudX2 = (float)cloud.width;
                StopMusicStream(bgm); // Stop BGM on game over
                PlayMusicStream(bgm); // Restart BGM on reset
            }
        }

        EndDrawing();
    }

    // Unload textures, font, and audio
    UnloadTexture(background);
    UnloadTexture(player);
    UnloadTexture(cactus);
    UnloadTexture(cloud);
    UnloadFont(customFont);
    UnloadMusicStream(bgm);
    UnloadSound(jumpSound);
    UnloadSound(collisionSound);
    CloseAudioDevice(); // Close audio device
    CloseWindow();
    return 0;
}