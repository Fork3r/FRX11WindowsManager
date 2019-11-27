//
// Created by rsalogub on 27.11.19.
//

#ifndef FR_X11_Windows_WINDOW_H
#define FR_X11_Windows_WINDOW_H

#include <string>

namespace X11Internals
{

#include<GL/glx.h>
#include<X11/X.h>
#include<X11/Xlib.h>

}

namespace FRX11Windows
{
    class Window
    {
    public:
        Window(int width, int height, const std::string &windowTitle = "");
    private:
        int att[5] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
        X11Internals::Display *display_;
        X11Internals::Window root_;
        X11Internals::XVisualInfo *vi_;
        X11Internals::Colormap cmap_;
        X11Internals::XSetWindowAttributes swa_;
        X11Internals::Window win_;
        X11Internals::GLXContext glc_;
        X11Internals::XWindowAttributes gwa_;
        X11Internals::XEvent xev_;
    };
}

#endif //FR_X11_Windows_WINDOW_H
