#include "SDL2/SDL.h"
#include<stdio.h>
#include<assert.h>

#define MAX_BUTTONS 100


struct Mybutton{
    SDL_Rect button;
    const char *text;
};

struct Mybutton buttons[MAX_BUTTONS];
static int n;

//Creating a button in coordinates x,y with size w,h and with text
struct Mybutton createButton(int x, int y, int w, int h, const char *text){
    assert(n < MAX_BUTTONS);
    SDL_Rect rect;
    struct Mybutton btn;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    btn.button = rect;
    btn.text = text;
    buttons[n] = btn;
    return buttons[n++];
}

//Get the button which in range x,y
int getWhichButton(int x, int y){
    for(int i=0; i<n; i++){
        if(x >= buttons[i].button.x && x <= buttons[i].button.x+buttons[i].button.w && y >= buttons[i].button.y
        && y <= buttons[i].button.y+buttons[i].button.h)
            return i;
    }
    return -1;
}

//Show all buttons
void showButtons(SDL_Renderer *renderer){
    for(int i=0;i<n;i++){
        SDL_RenderFillRect(renderer,&buttons[i].button);
    }
}

//Just a function to automatize the clicking
void buttonClick(int index){
    printf("Click button text: %s\n",buttons[index].text);
}

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    
    /*SDL window and renderer*/
    SDL_Window *window = SDL_CreateWindow("The Main Window",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_SHOWN | SDL_WINDOWEVENT_MAXIMIZED);
    SDL_ShowWindow(window);
    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_TEXTUREACCESS_TARGET);

    /* Create buttons here

    createButton(10,20,30,40,"Test");
    createButton(50,60,10,10,"Hello world!");
    createButton(80,60,10,10,"Test3");
    createButton(100,200,19,9,"Test4");
    */
    while (1)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch (event.type)
            {
            case SDL_QUIT:
                goto out;
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                {
                    int x,y;
                    SDL_GetMouseState(&x,&y);
                    int buttonindex = getWhichButton(x,y);
                    if(buttonindex >= 0)
                        buttonClick(buttonindex);
                }
                    break;
                
                default:
                    break;
                }
            }
            break;
            default:
                break;
            }
        }
        /* Draw things */
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,0,0,255,SDL_ALPHA_OPAQUE);
        showButtons(renderer);
        SDL_RenderPresent(renderer);
    }

out:
    SDL_DestroyWindow(window);
    return 0;
}


