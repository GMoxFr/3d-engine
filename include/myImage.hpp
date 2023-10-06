#ifndef __MY_IMAGE_HPP__
#define __MY_IMAGE_HPP__

#include "3dengine.hpp"

class myImage {
    private:
        // ATTRIBUTES
        int width;
        int height;
        myColor* pixels;
        double* yBuffer;

    public:
        // CONSTRUCTORS
        myImage();
        myImage(int width, int height);
        myImage(int width, int height, myColor c);
        ~myImage();

        // SETTERS AND GETTERS
        int getWidth() const { return width; }
        int getHeight() const { return height; }

        // METHODS
        myColor getPixelColor(int x, int y);
        myColor getPixelColor(myVector2 v);

        void setPixelColor(myPoint v, myColor c, double y);
        void setPixelColor(int x, int y, myColor c);
        void setPixelColor(myVector2 v, myColor c);
        void setPixelColor(myVector3 v, myColor c);
        
        void clear(myColor c);
};

#endif