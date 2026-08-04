#include <iostream>
#include <raylib.h>

using namespace std;

void Movement_Ball(int &x, int &y, int &speed_x, int &speed_y, int width, int height, 
                   int &p_x, int &p_y, int p_w, int p_h, 
                   int &p_2x, int &p_2y, int p_2w, int p_2h,
                   int screen_w, int screen_h, Sound effect, int &score1, int &score2, Sound score_effect) {
    x += speed_x;
    y += speed_y;

    if (x <= 0) {
        score2 += 1;
        speed_x *= -1;
        PlaySound(score_effect);
        x = screen_w / 2 - width / 2;
        y = screen_h / 2 - height / 2;
    } 
    else if (x + width >= screen_w) {
        score1 += 1;
        speed_x *= -1;
        PlaySound(score_effect);
        x = screen_w / 2 - width / 2;
        y = screen_h / 2 - height / 2;
    }

    if (y <= 0 || y + height >= screen_h) {
        speed_y *= -1;
        PlaySound(effect);
    }

    if (x < p_x + p_w && p_x < x + width && y < p_y + p_h && p_y < y + height) {
        speed_x *= -1;
        PlaySound(effect);
    }


    if (x < p_2x + p_2w && p_2x < x + width && y < p_2y + p_2h && p_2y < y + height) {
        speed_x *= -1;
        PlaySound(effect);
    }

}

void InCornerPaddle(int &y, int height, int screen_height) { 
    if (y < 0) {
        y = 0; 
    } 
    else if (y + height > 800) {
        y = 800 - height;
    } 
}

void Paddle_ai(int &ball_x, int &ball_y, int &paddle_y, int &random_num) {
    if (ball_x >= 600) {
        paddle_y = ball_y - random_num;
    }
    else if (ball_x <= 600) {
        random_num = GetRandomValue(-71, 71);
    }
}

int main() {
    InitWindow(1200, 800, "Ping Pong");
    InitAudioDevice();
    SetTargetFPS(60);
    
    int ball_x = 600;
    int ball_y = 400;
    int ball_width = 22;
    int ball_height = 22;
    int ball_speed_x = 7;
    int ball_speed_y = 7;
    Sound ball_hit = LoadSound("Sounds/ball_bounce.wav");
    Sound score_sound = LoadSound("Sounds/score_sound.wav");
    
    int paddle_x = 10;
    int paddle_y = GetScreenHeight() / 2 - 70;
    int paddle_x_2 = GetScreenWidth() - 35;
    int paddle_y_2 = GetScreenHeight() / 2 - 70;
    int paddle_width = 25;
    int paddle_height = 140;
    int paddle_width_2 = 25;
    int paddle_height_2 = 140;
    int paddle_speed = 8;
    int randomNumber = GetRandomValue(0, 70); 
    
    int score1 = 0;
    int score2 = 0;
    
    while (WindowShouldClose() == false) {
        if (IsKeyDown(KEY_W)) {
            paddle_y -= paddle_speed;
        }
        if (IsKeyDown(KEY_S)) {
            paddle_y += paddle_speed;
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawRectangle(ball_x, ball_y, ball_width, ball_height, WHITE);
        DrawRectangle(paddle_x, paddle_y, paddle_width, paddle_height, WHITE);
        DrawRectangle(paddle_x_2, paddle_y_2, paddle_width, paddle_height, WHITE);
        DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, 800, WHITE);
        
        DrawText(TextFormat("%i", score1), 300, 50, 60, WHITE);
        DrawText(TextFormat("%i", score2), 900, 50, 60, WHITE);
        
        Movement_Ball(ball_x, ball_y, ball_speed_x, ball_speed_y, ball_width, ball_height, 
                      paddle_x, paddle_y, paddle_width, paddle_height, 
                      paddle_x_2, paddle_y_2, paddle_width_2, paddle_height_2, 
                      GetScreenWidth(), GetScreenHeight(), ball_hit, score1, score2, score_sound);
        Paddle_ai(ball_x, ball_y, paddle_y_2, randomNumber);
        InCornerPaddle(paddle_y, paddle_height ,GetScreenHeight());
        InCornerPaddle(paddle_y_2, paddle_height_2 ,GetScreenHeight());
        EndDrawing();
    }
    
    UnloadSound(ball_hit);
    UnloadSound(score_sound);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}