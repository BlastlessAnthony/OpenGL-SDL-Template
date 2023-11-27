#include "SDL.h"
#include <Config.h>
#include <GLES2/gl2.h>
#include <SDL_opengl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void draw_rect( int x, int y, int width, int height );

int main( void ) {
	if ( 0 != SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER ) ) {
		( void )fprintf( stderr, "SDL failed to initialize.\nError: %s\n", SDL_GetError( ) );
		return EXIT_FAILURE;
	}

	SDL_Window *window = SDL_CreateWindow( "SDL OpenGL Template", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL );
	if ( NULL == window ) {
		( void )fprintf( stderr, "SDL failed to create a window.\nError: %s\n", SDL_GetError( ) );
		return EXIT_FAILURE;
	}

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 0 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

#ifdef __APPLE__
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG, SDL_TRUE );

#endif //__APPLE__

	SDL_GLContext *context = SDL_GL_CreateContext( window );
	if ( NULL == context ) {
		( void )fprintf( stderr, "SDL failed to create a context.\nError: %s\n", SDL_GetError( ) );
		return EXIT_FAILURE;
	}

	glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	glOrtho( 0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0, -1.0, 1.0 );
	glMatrixMode( GL_MODELVIEW );

	bool should_close = false;
	while ( !should_close ) {
		SDL_Event event;
		while ( SDL_PollEvent( &event ) ) {
			if ( event.type == SDL_EVENT_QUIT ) {
				should_close = true;
			}
		}
		glClearColor( 1.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glLoadIdentity( );

		glColor4b( 24, 128, 96, 255 );
		draw_rect( ( WINDOW_WIDTH / 2 ) - 64, ( WINDOW_HEIGHT / 2 ) - 64, 128, 128 );
		SDL_GL_SwapWindow( window );
	}

	SDL_GL_DeleteContext( context );
	SDL_DestroyWindow( window );
	SDL_Quit( );
}

void draw_rect( int x, int y, int width, int height ) {
	glBegin( GL_TRIANGLES );
	glVertex2i( x, y );                  // Top-left
	glVertex2i( x + width, y );          // Top-right
	glVertex2i( x, y + height );         // Bottom-left
	glVertex2i( x, y + height );         // Bottom-left
	glVertex2i( x + width, y );          // Top-right
	glVertex2i( x + width, y + height ); // Bottom-right
	glEnd( );
}