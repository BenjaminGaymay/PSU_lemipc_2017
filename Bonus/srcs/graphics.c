/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** graphics
*/

#include "lemipc.h"

SDL_Surface *g_window;

void init_window()
{
	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);
	SDL_WM_SetCaption("LemiPc", NULL);
	g_window = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL);
	TTF_Init();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70,(double)WIDTH/HEIGHT,1,1000);
	glEnable(GL_DEPTH_TEST);
	gluLookAt(10 , ARENA_SIZE, ARENA_SIZE / 2, 0, 0, 0, 0, 0, 1);
}

void delete_window()
{
	TTF_Quit();
	SDL_Quit();
}

void draw_arena()
{
	glBegin(GL_QUADS);

    	glColor3ub(50,50,50);
	glVertex3d((ARENA_SIZE + 2) / 2, -(ARENA_SIZE + 2) / 2, 0);
    	glVertex3d((ARENA_SIZE + 2) / 2, (ARENA_SIZE + 2) / 2, 0);
    	glVertex3d(-(ARENA_SIZE + 2) / 2, (ARENA_SIZE + 2) / 2, 0);
    	glVertex3d(-(ARENA_SIZE + 2) / 2, -(ARENA_SIZE + 2) / 2, 0);

    	glEnd();
}

void draw_cube(float x, float y, const float size, int *rgb)
{
	x = ARENA_SIZE / 2 - x - size;
	y = ARENA_SIZE / 2 - y - size;

	glTranslatef(-x, -y, size + 0.1);
	glBegin(GL_QUADS);

	glColor3ub(rgb[0], rgb[1], rgb[2]);

	// FRONT
	glVertex3f(-size,-size,size);
	glVertex3f(size,-size,size);
	glVertex3f(size,size,size);
	glVertex3f(-size,size,size);

	// BACK
	glVertex3f(-size,-size,-size);
	glVertex3f(-size,size,-size);
	glVertex3f(size,size,-size);
	glVertex3f(size,-size,-size);

	// LEFT
	glVertex3f(-size,-size,size);
	glVertex3f(-size,size,size);
	glVertex3f(-size,size,-size);
	glVertex3f(-size,-size,-size);

	// RIGHT
	glVertex3f(size,-size,-size);
	glVertex3f(size,size,-size);
	glVertex3f(size,size,size);
	glVertex3f(size,-size,size);

	// TOP
	glVertex3f(-size,size,size);
	glVertex3f(size,size,size);
	glVertex3f(size,size,-size);
	glVertex3f(-size,size,-size);

	// BOTTON
	glVertex3f(-size,-size,size);
	glVertex3f(-size,-size,-size);
	glVertex3f(size,-size,-size);
	glVertex3f(size,-size,size);

    	glEnd();
	glTranslatef(x, y, -(size + 0.1));
}


void draw_array(const char *array)
{
	for (int y = ARENA_SIZE - 1 ; y >= 0 ; y--) {
		for (int x = ARENA_SIZE ; x >= -1 ; x--) {
			switch(array[CHARPOS(x, y)]) {
				case '1':
					draw_cube(x, y, CUBE_SIZE, (int[3]){0, 255, 0}); break;
				case '2':
					draw_cube(x, y, CUBE_SIZE, (int[3]){255, 0, 255}); break;
				case '3':
					draw_cube(x, y, CUBE_SIZE, (int[3]){200, 200, 200}); break;
				case '4':
					draw_cube(x, y, CUBE_SIZE, (int[3]){0, 255, 255}); break;
				case '5':
					draw_cube(x, y, CUBE_SIZE, (int[3]){255, 225, 25}); break;
				case '6':
					draw_cube(x, y, CUBE_SIZE, (int[3]){145, 30, 180}); break;
				case '7':
					draw_cube(x, y, CUBE_SIZE, (int[3]){245, 130, 48}); break;
				case '8':
					draw_cube(x, y, CUBE_SIZE, (int[3]){255, 0, 0}); break;
				case '9':
					draw_cube(x, y, CUBE_SIZE, (int[3]){0, 0, 255}); break;
			}
		}
	}
}

int key(const int key)
{
	if (key == SDLK_ESCAPE)
		return (EXIT);
	return (SUCCESS);
}

int manage_event()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_KEYUP:
				return (key(event.key.keysym.sym));
			case SDL_QUIT:
				return (EXIT);
		}
	}
	return (SUCCESS);
}

void clear_window()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
}

void refresh_window()
{
	glFlush();
    	SDL_GL_SwapBuffers();
}



void print_text(float x, float y, SDL_Color color, const char *string)
{
    	GLuint tex;
    	TTF_Font *font = TTF_OpenFont("ressources/Lato.ttf", 300);
    	SDL_Surface *text = TTF_RenderText_Blended(font, string, color);

	gluLookAt(0, 1, -20, 0, 0, 30, 0.005, 0, 1);

    	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D,tex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, text->w, text->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, text->pixels);

	glEnable(GL_BLEND);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTranslatef(x, y, -10);

	glEnable(GL_TEXTURE_2D);
    	glBindTexture(GL_TEXTURE_2D, tex);
    	glBegin(GL_QUADS);
        	glTexCoord2f(0.0f, 0.0f); glVertex2f(-80.0f, -60.0f);
        	glTexCoord2f(1.0f, 0.0f); glVertex2f(80.0f, -60.0f);
        	glTexCoord2f(1.0f, 1.0f); glVertex2f(80.0f, 60.0f);
        	glTexCoord2f(0.0f, 1.0f); glVertex2f(-80.0f, 60.0f);
    	glEnd();
    	glDisable(GL_TEXTURE_2D);

  	TTF_CloseFont(font);
  	SDL_FreeSurface(text);
	glTranslatef(-x, -y, 10);
}