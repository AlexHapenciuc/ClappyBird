#ifndef FUNCTII_H_INCLUDED
#define FUNCTII_H_INCLUDED

void IesireJoc(SDL_Window *, SDL_Renderer *, SDL_Texture *, SDL_Texture *, SDL_Texture *, SDL_Texture *, SDL_Texture *, SDL_Texture *);
void InitializareElemente(SDL_Rect *p, SDL_Rect *o1a, SDL_Rect *o1b, SDL_Rect *o2a, SDL_Rect *o2b);
void RemakeObstacol(SDL_Rect *o1, SDL_Rect *o2);
bool GameplayStart_Stop();
void RenderUpdate(SDL_Renderer *r, SDL_Texture *b, SDL_Texture *p, SDL_Texture *o1a, SDL_Texture *o1b,
                  SDL_Texture *o2a, SDL_Texture *o2b, SDL_Rect *p_r, SDL_Rect *o1a_r, SDL_Rect *o1b_r,
                  SDL_Rect *o2a_r, SDL_Rect *o2b_r);
void Gameplay(JUCATOR j, SDL_Renderer *r, SDL_Texture *b, SDL_Texture *p, SDL_Texture *o1a, SDL_Texture *o1b, SDL_Texture *o2a, SDL_Texture *o2b);
SDL_Rect PozitiePersonajInceput();

int InitializareJoc(JUCATOR j);


void IesireJoc(SDL_Window *w, SDL_Renderer *r, SDL_Texture *b, SDL_Texture *p, SDL_Texture *o1, SDL_Texture *o2, SDL_Texture *o3, SDL_Texture *o4)
{
    SDL_DestroyTexture(b);
    SDL_DestroyTexture(p);
    SDL_DestroyTexture(o1);
    SDL_DestroyTexture(o2);
    SDL_DestroyTexture(o3);
    SDL_DestroyTexture(o4);
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();
}

void InitializareElemente(SDL_Rect *p, SDL_Rect *o1a, SDL_Rect *o1b, SDL_Rect *o2a, SDL_Rect *o2b)
{
    //personajul
    p->x = CLAPPY_WINDOW_WIDTH/3 - CLAPPYB_w/3;
    p->y = CLAPPY_WINDOW_HEIGHT/2 - CLAPPYB_h/3;
    p->w = CLAPPYB_w;
    p->h = CLAPPYB_h;
    //primul obstacol de sus
    o1a->x = 1000;
    o1a->y = 0;
    o1a->w = OBSTACOL_w;
    o1a->h = 2*OBSTACOL_h/3;
    //primul obstacol de jos
    o1b->x = 1000;
    o1b->y = CLAPPY_WINDOW_HEIGHT - GROUND_h - OBSTACOL_h/3;
    o1b->w = OBSTACOL_w;
    o1b->h = OBSTACOL_h/3;
    //al doilea obstacol de sus
    o2a->x = 1000 + OBSTACOL_GAP + OBSTACOL_w;
    o2a->y = 0;
    o2a->w = OBSTACOL_w;
    o2a->h = OBSTACOL_h/2;
    //al doilea obstacol de jos
    o2b->x = 1000 + OBSTACOL_GAP + OBSTACOL_w;
    o2b->y = CLAPPY_WINDOW_HEIGHT - GROUND_h - OBSTACOL_h/2;
    o2b->w = OBSTACOL_w;
    o2b->h = OBSTACOL_h/2;
}

void RemakeObstacol(SDL_Rect *o1, SDL_Rect *o2)
{
    int h;
    h = rand()%350;
    if(h < 50)
        h = 50;


    o1->x = CLAPPY_WINDOW_WIDTH;
    o1->y = 0;
    o1->h = h;

    o2->x = CLAPPY_WINDOW_WIDTH;
    o2->y = CLAPPY_WINDOW_HEIGHT - GROUND_h - 400 + h;
    o2->h = 400 - h; // 400 = WINDOW_HEIGHT - OBSTACOLE_GAP - OBSTACOLE_MIN_HEIGHT
}

bool GameplayStart_Stop()
{
    SDL_Event event;
    while(true)
        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                return false;
            else if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) ||
                    (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))
                return true;
    return false;//still error
}

void RenderUpdate(SDL_Renderer *r, SDL_Texture *b, SDL_Texture *p, SDL_Texture *o1a, SDL_Texture *o1b,
                  SDL_Texture *o2a, SDL_Texture *o2b, SDL_Rect *p_r, SDL_Rect *o1a_r, SDL_Rect *o1b_r,
                  SDL_Rect *o2a_r, SDL_Rect *o2b_r)
{
    SDL_RenderClear(r);
    SDL_RenderCopy(r, b, NULL, NULL);
    SDL_RenderCopy(r, o1a, NULL, o1a_r);
    SDL_RenderCopy(r, o1b, NULL, o1b_r);
    SDL_RenderCopy(r, o2a, NULL, o2a_r);
    SDL_RenderCopy(r, o2b, NULL, o2b_r);
    SDL_RenderCopy(r, p, NULL, p_r);
    SDL_RenderPresent(r);
}

void Gameplay(JUCATOR j, SDL_Renderer *r, SDL_Texture *b, SDL_Texture *p, SDL_Texture *o1a, SDL_Texture *o1b, SDL_Texture *o2a, SDL_Texture *o2b)
{
    int birdHit = 0, fly = 20, scor = 0, reset = 1;
    float p_y;
    SDL_Event event;
    SDL_Rect p_r, o1a_r, o1b_r, o2a_r, o2b_r;

    SDL_Surface *surface1 = SDL_LoadBMP("Reincercati.bmp");
    SDL_Texture *reincercati = SDL_CreateTextureFromSurface(r, surface1);
    SDL_FreeSurface(surface1);
    SDL_Rect reincercati_r;
    SDL_QueryTexture(reincercati, NULL, NULL, &reincercati_r.w, &reincercati_r.h);
    reincercati_r.x = CLAPPY_WINDOW_WIDTH/2-reincercati_r.w/2;
    reincercati_r.y = CLAPPY_WINDOW_HEIGHT/2-reincercati_r.h/2;
    InitializareElemente(&p_r, &o1a_r, &o1b_r, &o2a_r, &o2b_r);
    RenderUpdate(r, b, p, o1a, o1b, o2a, o2b, &p_r, &o1a_r, &o1b_r, &o2a_r, &o2b_r);

    if(!GameplayStart_Stop())
        return;
    srand(time(0));
    p_y = p_r.y;
    while(true)
    {
        while(fly>0)
        {
            if(p_y>=0 && p_y<=CLAPPY_WINDOW_HEIGHT-GROUND_h-CLAPPYB_h)
            {
                p_y -= 1.8*(float)FORCE/FPS;
                p_r.y = p_y;
                o1a_r.x -= GAME_SPEED;
                o1b_r.x -= GAME_SPEED;
                o2a_r.x -= GAME_SPEED;
                o2b_r.x -= GAME_SPEED;
                RenderUpdate(r, b, p, o1a, o1b, o2a, o2b, &p_r, &o1a_r, &o1b_r, &o2a_r, &o2b_r);
            }
            else
            {
                birdHit = 1;
                fly = 0;
                o1a_r.x -= GAME_SPEED;
                o1b_r.x -= GAME_SPEED;
                o2a_r.x -= GAME_SPEED;
                o2b_r.x -= GAME_SPEED;
                RenderUpdate(r, b, p, o1a, o1b, o2a, o2b, &p_r, &o1a_r, &o1b_r, &o2a_r, &o2b_r);
            }
            while(SDL_PollEvent(&event))
                if(event.type == SDL_QUIT)
                    return;
                else if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) ||
                    (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))
                    if(fly > 3)
                        fly = 10;
            fly -= 1;
            SDL_Delay(SECUNDA/FPS);
        }

        if(p_y>=0 && p_y<=CLAPPY_WINDOW_HEIGHT-GROUND_h-CLAPPYB_h)
        {
            p_y += (float)FORCE/FPS;
            p_r.y = p_y;
        }
        else
            birdHit = 1;

        if(birdHit)
        {
            SDL_RenderCopy(r, reincercati, NULL, &reincercati_r);
            SDL_RenderPresent(r);
            break;
        }
        else
        {
            o1a_r.x -= GAME_SPEED;
            o1b_r.x -= GAME_SPEED;
            o2a_r.x -= GAME_SPEED;
            o2b_r.x -= GAME_SPEED;
        }

        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                return;
            else if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) ||
                    (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))
                fly = 10;

        if(RectsCollide(&p_r, &o1a_r))
            birdHit = 1;
        if(RectsCollide(&p_r, &o1b_r))
            birdHit = 1;
        if(RectsCollide(&p_r, &o2a_r))
            birdHit = 1;
        if(RectsCollide(&p_r, &o2b_r))
            birdHit = 1;

        if(o1a_r.x+o1a_r.w < 0)
        {
            RemakeObstacol(&o1a_r, &o1b_r);
            reset = 1;
        }

        else if(o2a_r.x+o2a_r.w < 0)
        {
            RemakeObstacol(&o2a_r, &o2b_r);
            reset = 1;
        }

        if(o1a_r.x+o1a_r.w < p_r.x || o2a_r.x+o2a_r.w < p_r.x)
            if(reset)
            {
                reset = 0;
                scor++;
            }

        RenderUpdate(r, b, p, o1a, o1b, o2a, o2b, &p_r, &o1a_r, &o1b_r, &o2a_r, &o2b_r);
        SDL_Delay(SECUNDA/FPS);
    }

    AdaugaScor(j, scor);


    if(GameplayStart_Stop())
    {
        PrinteazaScoruri(j);
        Gameplay(j, r, b, p, o1a, o1b, o2a, o2b);
    }
    else
    {
        PrinteazaScoruri(j);
        return;
    }
}

int InitializareJoc(JUCATOR j)
{
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);
    //fereastra
    SDL_Window *window;
    SDL_Texture *background, *personaj, *obstacol1sus, *obstacol1jos,*obstacol2sus, *obstacol2jos;
    window = SDL_CreateWindow(
                 CLAPPY_GAME_NAME,
                 SDL_WINDOWPOS_CENTERED,
                 SDL_WINDOWPOS_CENTERED,
                 CLAPPY_WINDOW_WIDTH,
                 CLAPPY_WINDOW_HEIGHT,
                 SDL_WINDOW_OPENGL
             );
    if(window == NULL)
    {
        printf("Eroare la crearea ferestrei: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_RaiseWindow(window); //Aduce fereastra in fata si o focuseaza pentru input
    //renderer
    SDL_Renderer *render = SDL_CreateRenderer(window, CLAPPY_GRAPHICS_DRIVER, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(render == NULL)
    {
        printf("Eroare la crearea renderer-ului: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 2;
    }
    //background, personaj si obstacole
    SDL_Surface *surface = SDL_LoadBMP("Background.bmp");//backgroundbackground = SDL_CreateTextureFromSurface(render, surface);
    if(surface == NULL)
    {
        printf("Eroare la incarcarea background-ului: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(render);
        SDL_Quit();
        return 3;
    }
    background = SDL_CreateTextureFromSurface(render, surface);
    if(background == NULL)
    {
        printf("Eroare la crearea background-ului: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(render);
        SDL_Quit();
        return 4;
    }
    surface = SDL_LoadBMP("Bird.bmp");//personaj
    if(surface == NULL)
    {
        printf("Eroare la incarcarea personajului: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(render);
        SDL_Quit();
        return 5;
    }
    personaj = SDL_CreateTextureFromSurface(render, surface);
    if(personaj == NULL)
    {
        printf("Eroare la crearea personajului: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(render);
        SDL_Quit();
        return 6;
    }
    surface = SDL_LoadBMP("Obstacol.bmp");//obstacol
    if(surface == NULL)
    {
        printf("Eroare la incarcarea obstacolului: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(render);
        SDL_Quit();
        return 7;
    }
    obstacol1sus = SDL_CreateTextureFromSurface(render, surface);
    if(obstacol1sus == NULL)
    {
        printf("Eroare la crearea personajului: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(render);
        SDL_Quit();
        return 8;
    }
    obstacol1jos = SDL_CreateTextureFromSurface(render, surface);
    if(obstacol1jos == NULL)
    {
        printf("Eroare la crearea personajului: %s\n", SDL_GetError());
        SDL_DestroyTexture(obstacol1sus);
        SDL_FreeSurface(surface);
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(render);
        SDL_Quit();
        return 9;
    }
    obstacol2sus = SDL_CreateTextureFromSurface(render, surface);
    if(obstacol2sus == NULL)
    {
        printf("Eroare la crearea personajului: %s\n", SDL_GetError());
        SDL_DestroyTexture(obstacol1jos);
        SDL_DestroyTexture(obstacol1sus);
        SDL_FreeSurface(surface);
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(render);
        SDL_Quit();
        return 9;
    }
    obstacol2jos = SDL_CreateTextureFromSurface(render, surface);
    if(obstacol2jos == NULL)
    {
        printf("Eroare la crearea personajului: %s\n", SDL_GetError());
        SDL_DestroyTexture(obstacol2sus);
        SDL_DestroyTexture(obstacol1jos);
        SDL_DestroyTexture(obstacol1sus);
        SDL_FreeSurface(surface);
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(render);
        SDL_Quit();
        return 9;
    }
    SDL_FreeSurface(surface);

    Gameplay(j, render, background, personaj, obstacol1sus, obstacol1jos, obstacol2sus, obstacol2jos);

    IesireJoc(window, render, background, personaj, obstacol1sus, obstacol1jos, obstacol2sus, obstacol2jos);
    return 0;
}


#endif // FUNCTII_H_INCLUDED
