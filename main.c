#include <SDL2/SDL.h>

const unsigned BLACK = 0x00000000;
const unsigned WHITE = 0xFFFFFF00;

const unsigned COLORS[] = {
    0x00000000, 0x08080800, 0x11111100, 0x19191900,
    0x22222200, 0x2A2A2A00, 0x33333300, 0x3B3B3B00,
    0x44444400, 0x4C4C4C00, 0x55555500, 0x5D5D5D00,
    0x66666600, 0x6e6e6e00, 0x77777700, 0x7F7F7F00,
    0x88888800, 0x90909000, 0x99999900, 0xA1A1A100,
    0xAAAAAA00, 0xb2B2B200, 0xBBBBBB00, 0xC3C3C300,
    0xCCCCCC00, 0xD4D4D400, 0xDDDDDD00, 0xE5E5E500,
    0xEEEEEE00, 0xF6F6F600, 0xFFFFFF00
};

unsigned int get_color( double y, double x )
{
    double iter_x = 0.0, iter_y = 0.0;

    // Black magic algorithm from wikipedia
    int i;
    for ( i = 0; (iter_x * iter_x + iter_y * iter_y < 4 ) && i < 64; i++ ) {
        double xtemp = iter_x*iter_x - iter_y*iter_y + x;
        iter_y = 2 * iter_x * iter_y + y;
        iter_x = xtemp;
    }

    return COLORS[ i % ( sizeof( COLORS ) / sizeof( unsigned ) ) ];
}

int main( int argc, char **argv )
{
    SDL_Init( SDL_INIT_VIDEO );

    SDL_Window *mainwin = SDL_CreateWindow(
            "Mandelbrot Visualiztion",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
            );


    SDL_Renderer *mainren = SDL_CreateRenderer(
            mainwin,
            -1,
            SDL_RENDERER_ACCELERATED
            );



    SDL_Event mainevent;

    int curr_winwidth, curr_winheight;

    SDL_GetWindowSize( mainwin, &curr_winwidth, &curr_winheight );
    SDL_Surface *mainsurf = SDL_CreateRGBSurface(
            0,
            curr_winwidth,
            curr_winheight,
            32,
            0xFF000000,
            0x00FF0000,
            0x0000FF00,
            0
            );

    double left = -2.0;
    double right = 1.0;
    double top = 1.0;
    double bottom = -1.0 ;
    char should_render = 0;
    for ( ;; ) {
        double x_shiftwidth = ( left - right ) / 4.0;
        double y_shiftwidth = ( top - bottom ) / 4.0;

        double x_center = ( left + right ) / 2.0;
        double y_center = ( top + bottom ) / 2.0;
        while ( SDL_PollEvent( &mainevent ) ) {
            switch ( mainevent.type ) {
            case SDL_QUIT:
                return 0;
                break;
            case SDL_KEYDOWN:
                should_render = 1;
                switch ( mainevent.key.keysym.sym ) {
                case SDLK_e:
                    left += fabs( left - x_center ) / 2;
                    right -= fabs( right - x_center ) / 2;
                    top -= fabs( top - y_center ) / 2;
                    bottom += fabs( bottom - y_center ) / 2;
                    break;
                case SDLK_q:
                    left -= fabs( left - x_center ) * 2;
                    right += fabs( right - x_center ) * 2;
                    top += fabs( top - y_center ) * 2;
                    bottom -= fabs( bottom - y_center ) * 2;
                    break;
                case SDLK_d:
                case SDLK_l:
                case SDLK_RIGHT:
                    right -= x_shiftwidth;
                    left -= x_shiftwidth;
                    break;
                case SDLK_a:
                case SDLK_h:
                case SDLK_LEFT:
                    right += x_shiftwidth;
                    left += x_shiftwidth;
                    break;
                case SDLK_s:
                case SDLK_j:
                case SDLK_DOWN:
                    top -= y_shiftwidth;
                    bottom -= y_shiftwidth;
                    break;
                case SDLK_w:
                case SDLK_k:
                case SDLK_UP:
                    top += y_shiftwidth;
                    bottom += y_shiftwidth;
                    break;
                }
                break;
            }
        }

        int new_winwidth, new_winheight;
        SDL_GetWindowSize( mainwin, &new_winwidth, &new_winheight );

        if (    new_winwidth  != curr_winwidth
             || new_winheight != curr_winheight ) {
            curr_winwidth =  new_winwidth;
            curr_winheight = new_winheight;

            SDL_FreeSurface( mainsurf );
            mainsurf = SDL_CreateRGBSurface(
                    0,
                    curr_winwidth,
                    curr_winheight,
                    32,
                    0xFF000000,
                    0x00FF0000,
                    0x0000FF00,
                    0
                    );

            should_render = 1;
        }

        if ( should_render ) {

            double dx = ( right - left ) / ( double ) curr_winwidth;
            double dy = ( top - bottom ) / ( double ) curr_winheight; 

            SDL_LockSurface( mainsurf );

            for ( unsigned y = 0; y < curr_winheight; y++ ) {
                for ( unsigned x = 0; x < curr_winwidth; x++ ) {
                    unsigned color = get_color(
                            top - ( ( double ) y * dy ),
                            left + ( ( double ) x * dx )
                            );

                    unsigned *pixel = 
                        (unsigned *) mainsurf->pixels
                        + ( ( y * mainsurf->pitch ) / 4 )
                        + ( ( x * sizeof( unsigned ) ) / 4 ) ;
                    *pixel = color;
                }
            }

            SDL_UnlockSurface( mainsurf );

            SDL_Texture *maintexture = SDL_CreateTextureFromSurface(
                    mainren,
                    mainsurf
                    );

            SDL_RenderCopy(
                    mainren,
                    maintexture,
                    NULL,
                    NULL
                    );

            SDL_RenderPresent( mainren );

            should_render = 0;
        }
        SDL_Delay( 17 );
    }

    SDL_FreeSurface( mainsurf );
    SDL_DestroyRenderer( mainren );
    SDL_DestroyWindow( mainwin );
    
    return 0;
}
