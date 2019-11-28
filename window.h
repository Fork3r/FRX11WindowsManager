//
// Created by rsalogub on 27.11.19.
//

#ifndef FR_X11_Windows_WINDOW_H
#define FR_X11_Windows_WINDOW_H

#include <string>

namespace X11Internals
{
#include<X11/XKBlib.h>
#include<X11/keysym.h>
#include<X11/keysymdef.h>

}

namespace FRX11Windows
{
    class Display
    {
    public:
        static X11Internals::Display* getDisplay();
    private:
        static X11Internals::Display* display_;
    };

    class EventHandler
    {
    public:
        static void processEvents();

        // TODO:
        // subscribing on events
    };

    class Window
    {
    public:
        Window(int width, int height, const std::string &windowTitle = "");
        ~Window();

        void resize(unsigned int width, unsigned int height);
    private:
        X11Internals::Window windowId_;
    };
}

#endif //FR_X11_Windows_WINDOW_H
