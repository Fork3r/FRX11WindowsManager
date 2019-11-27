//
// Created by rsalogub on 27.11.19.
//

#include<stdio.h>
#include<stdlib.h>
#include "window.h"

namespace FRX11Windows
{
    using namespace X11Internals;
    Window::Window(int width, int height, const std::string &windowTitle)
    {
        display_ = XOpenDisplay(NULL);

        if(display_ == NULL) {
            printf("\n\tcannot connect to X server\n\n");
            exit(0);
        }

        root_ = DefaultRootWindow(display_);

        vi_ = glXChooseVisual(display_, 0, att);

        if(vi_ == NULL) {
            printf("\n\tno appropriate visual found\n\n");
            exit(0);
        }
        else {
            printf("\n\tvisual %p selected\n", (void *)vi_->visualid); /* %p creates hexadecimal output like in glxinfo */
        }


        cmap_ = XCreateColormap(display_, root_, vi_->visual, AllocNone);

        swa_.colormap = cmap_;
        swa_.event_mask = ExposureMask | KeyPressMask;

        win_ = XCreateWindow(display_, root_, 0, 0, width, height, 0, vi_->depth, InputOutput, vi_->visual, CWColormap | CWEventMask, &swa_);

        XMapWindow(display_, win_);
        if (!windowTitle.empty()) {
            XStoreName(display_, win_, windowTitle.c_str());
        }

        glc_ = glXCreateContext(display_, vi_, NULL, GL_TRUE);
        glXMakeCurrent(display_, win_, glc_);

        glEnable(GL_DEPTH_TEST);

        while(1) {
            XNextEvent(display_, &xev_);

            if(xev_.type == Expose) {
                XGetWindowAttributes(display_, win_, &gwa_);
                glViewport(0, 0, gwa_.width, gwa_.height);
                glXSwapBuffers(display_, win_);
            }

            else if(xev_.type == KeyPress) {
                glXMakeCurrent(display_, None, NULL);
                glXDestroyContext(display_, glc_);
                XDestroyWindow(display_, win_);
                XCloseDisplay(display_);
                exit(0);
            }
        }
    }
}