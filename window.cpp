//
// Created by rsalogub on 27.11.19.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "window.h"

namespace FRX11Windows
{
    X11Internals::Display* Display::display_ = nullptr;

    X11Internals::Display* Display::getDisplay()
    {
        if (!display_) {
            display_ = X11Internals::XOpenDisplay(nullptr);
        }

        if (display_ == nullptr) {
            printf("\n\tcannot connect to X server\n\n");
            exit(0);
        }
        return display_;
    }

    using namespace X11Internals;

    Window::Window(int width, int height, const std::string &windowTitle)
    {
        int screenId = DefaultScreen(Display::getDisplay());

        windowId_ = XCreateWindow(Display::getDisplay(), DefaultRootWindow(Display::getDisplay()), 0, 0, width,
                                height, 0, CopyFromParent, CopyFromParent,
                                CopyFromParent, 0, nullptr);

        std::cout << __func__ << " " << windowId_ << std::flush;

        if (!windowTitle.empty()) {
            XStoreName(Display::getDisplay(), windowId_, windowTitle.c_str());
        }

        // Show the window
        XSelectInput(Display::getDisplay(), windowId_, StructureNotifyMask | ButtonPressMask | KeyPressMask | KeyReleaseMask);
        XMapWindow(Display::getDisplay(), windowId_);
        while (true) {
            XEvent e;
            XNextEvent(Display::getDisplay(), &e);
            if (e.type == MapNotify)
                break;
        }
        while (true) {
            XEvent e;
            XNextEvent(Display::getDisplay(), &e);
            if (e.type == ButtonPress)
                break;
        }
    }

    Window::~Window()
    {
        std::cout << __func__ << " " << windowId_ << std::flush;
        XDestroyWindow(Display::getDisplay(), windowId_);
    }

    void Window::resize(unsigned int width, unsigned int height)
    {
        XResizeWindow(Display::getDisplay(), windowId_, width, height);
    }

    void EventHandler::processEvents()
    {
        XEvent event;
        while(XPending(Display::getDisplay())) {
            XNextEvent(Display::getDisplay(), &event);
            if (event.type == KeyPress) {
                std::cout << XkbKeycodeToKeysym(Display::getDisplay(), event.xkey.keycode, 0, 0) << "::" << XK_F1 << std::endl << std::flush;
            }
        }
    }
}