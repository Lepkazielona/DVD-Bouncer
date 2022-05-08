#include <raylib.h>
#include<stdio.h>

static const Color colors[] = {
RAYWHITE,
YELLOW,
GOLD,
ORANGE,
PINK,
RED,
GREEN,
LIME,
GREEN,
SKYBLUE,
BLUE,
BEIGE
}; //12 colors

struct DVD
{
    int x;
    int y;
    int width;
    int height;
} dvd;


int main(void)
{
    int randValue;


    //init stuff
    int screenWidth = 800;
    int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "dvd bouncer");
    
    SetTargetFPS(60);

    //dvd image and collision box
    
    dvd.x = screenWidth/2;      // center dvd logo on the screen
    dvd.y = screenHeight/2;    // 
    dvd.width = 200;          // 
    dvd.height = 100;        //

    Image dvdImage = LoadImage("./dvdIcon.png");
    ImageResize(&dvdImage, dvd.width, dvd.height);
    ImageFormat(&dvdImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8); 
    Texture2D dvdTexture = LoadTextureFromImage(dvdImage); 
    
    bool colorReload = false;

    Image imgCopy = ImageCopy(dvdImage);


    Rectangle box = {dvd.x, dvd.y, dvd.width, dvd.height};

    float speedx = 4.0;
    float speedy = -4.0;
    bool showFPS = false;
    
    while (!WindowShouldClose())
    {

    // physics stuff

        if (box.y == 0) {
            box.y = 0;
            speedy *= -1.0;
            colorReload = true;
        } 
        if (box.y == screenHeight - box.height) {
            box.y = screenHeight - box.height;
            speedy *= -1.0;
            colorReload = true;
        }
        if (box.x == 0) {
            speedx *= -1.0;
            box.x = 0;
            colorReload = true;
        }
        if (box.x == screenWidth - box.width) {
            box.x = screenWidth - box.width;
            speedx *= -1.0;
            colorReload = true;
        }
        printf("x = %g y = %g\n", box.x,box.y); 
        box.x += speedx;
        box.y += speedy;

        if(IsKeyPressed(KEY_SPACE)){
            ToggleFullscreen();
            if (screenWidth == 800){
                SetWindowSize(1920,1080);
                screenWidth = 1920;
                screenHeight = 1080;
                box.x = screenWidth/2;
                box.y = screenHeight/2;
            } else {
                SetWindowSize(800,480);
                screenWidth = 800;
                screenHeight = 480;
                box.x = screenWidth/2;
                box.y = screenHeight/2;
            } 
        } 
        if(IsKeyPressed(KEY_LEFT_CONTROL)) showFPS = !showFPS;

        if(colorReload)
        {
            UnloadImage(imgCopy);
            imgCopy = ImageCopy(dvdImage);
            
            randValue = GetRandomValue(0, 11);
            ImageColorTint(&imgCopy, colors[randValue]);

            Color *pixels = LoadImageColors(imgCopy);     // Load pixel data from image (RGBA 32bit)
            UpdateTexture(dvdTexture, pixels);           // Update texture with new image data
            UnloadImageColors(pixels);                  // Unload pixels data from RAM

            colorReload = false;
        }    
        //Drawning
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(dvdTexture, box.x, box.y, WHITE);
            DrawText(" SPACE - Full screen \n L-CTRL - FPS counter", 5, screenHeight -55, 20, RAYWHITE);
            if(showFPS) DrawFPS(10,10);
        EndDrawing();

    }

    UnloadTexture(dvdTexture);
    UnloadImage(dvdImage);
    UnloadImage(imgCopy);

    CloseWindow();
    return 0;
}