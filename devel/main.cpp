#include <X11/X.h>
#include <X11/Xlib.h>
#include <cstdio>
#include <stdexcept>

#define KEY_ESCAPE   9
#define KEY_SPACE   65
#define KEY_UP      25
#define KEY_DOWN    39
#define KEY_LEFT    38
#define KEY_RIGHT   40

#define COLOR 0x54508c

namespace mygame {

class GameDisplay {
public:
    GameDisplay();
    ~GameDisplay();

    Display *getDisplay();

    void drawRect(unsigned long col, int x, int y, int width, int height);
    void redraw();

private:
    Display *display;
    int screen;
    Window window;
};

GameDisplay::GameDisplay()
{
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        throw std::runtime_error("Unable to open the display\n");
    }

    screen = DefaultScreen(display);

    window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, 1000, 1000, 1, BlackPixel(display, screen), WhitePixel(display, screen));

    XSelectInput(display, window, KeyPressMask | ExposureMask);
    XMapWindow(display, window);
}

GameDisplay::~GameDisplay()
{
    XCloseDisplay(display);
}

void GameDisplay::drawRect(unsigned long col, int x, int y, int width, int height)
{
    XSetForeground(display, DefaultGC(display, screen), col);
    XFillRectangle(display, window, DefaultGC(display, screen), x, y, width, height);
}

void GameDisplay::redraw()
{
    XClearWindow(display, window);

    Window root_wind;
    int x, y;
    unsigned int width, height, border_width, depth;
    XGetGeometry(display, window, &root_wind, &x, &y, &width, &height, &border_width, &depth);


    XEvent ev;
    ev.xexpose.type = Expose;
    ev.xexpose.display = display;
    ev.xexpose.window = window;
    ev.xexpose.x = x;
    ev.xexpose.y = y;
    ev.xexpose.width = width;
    ev.xexpose.height = height;
    ev.xexpose.count = 0;

    XSendEvent(display, window, false, ExposureMask, &ev);
}

Display *GameDisplay::getDisplay()
{
    return display;
}

class Game{
public:
    Game();

    void run();

private:
    GameDisplay gamedisplay;
    XEvent event;
    bool is_running = true;

    bool getEvent();
    void handleEvent();
    int x = 50;
    int y = 50;
};

Game::Game()
{

}

void Game::run()
{
    while (is_running)
    {
        if(getEvent())
            handleEvent();
    }
}

bool Game::getEvent()
{
    if(XPending(gamedisplay.getDisplay()))
    {
        XNextEvent(gamedisplay.getDisplay(), &event);
        printf("EVENT: %d\n", event.type);
        return true;
    }

    return false;
}

void Game::handleEvent()
{
    if(event.type == Expose)
    {
        gamedisplay.drawRect(COLOR, x, y, 25, 25);
    }


    if(event.type == KeyPress)
    {
        printf("KeyPress Event: %d\n", event.xkey.keycode);

        switch (event.xkey.keycode)
        {
            case KEY_UP:     printf("KEY_UP\n");    y -= 5; gamedisplay.redraw(); break;
            case KEY_DOWN:   printf("KEY_DOWN\n");  y += 5; gamedisplay.redraw(); break;
            case KEY_LEFT:   printf("KEY_LEFT\n");  x -= 5; gamedisplay.redraw(); break;
            case KEY_RIGHT:  printf("KEY_RIGHT\n"); x += 5; gamedisplay.redraw(); break;

            case KEY_SPACE:  printf("KEY_SPACE\n"); break;

            case KEY_ESCAPE: printf("KEY_ESCAPE\n"); is_running = false; break;
        }
    }
}

}

int main(void)
{
    mygame::Game g;

    g.run();

    printf("EXITING\n");

    return 0;
}
