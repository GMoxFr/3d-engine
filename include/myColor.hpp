#ifndef __MY_COLOR_HPP__
#define __MY_COLOR_HPP__

#include "3dengine.hpp"

class myColor {
    private:

    public:
        // ATTRIBUTES
        u_int8_t r;
        u_int8_t g;
        u_int8_t b;
        u_int8_t a;

        // SETTERS AND GETTERS
        public:
        u_int8_t getR() const { return r; }
        void setR(int value) { r = std::clamp(value, 0, 255); }

        u_int8_t getG() const { return g; }
        void setG(int value) { g = std::clamp(value, 0, 255); }

        u_int8_t getB() const { return b; }
        void setB(int value) { b = std::clamp(value, 0, 255); }

        u_int8_t getA() const { return a; }
        void setA(int value) { a = std::clamp(value, 0, 255); }

        // CONSTRUCTORS
        myColor();
        myColor(u_int8_t r, u_int8_t g, u_int8_t b);
        myColor(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a);
        myColor(int r, int g, int b);
        myColor(int r, int g, int b, int a);
        myColor(float r, float g, float b);
        myColor(float r, float g, float b, float a);
        myColor(double r, double g, double b);
        myColor(double r, double g, double b, double a);
        myColor(const myColor& c);
        myColor(const sf::Color& c);
        ~myColor();

        // OPERATORS
        myColor& operator=(const myColor& c);
        myColor& operator=(const sf::Color& c);

        myColor& operator+=(const myColor& c);
        friend myColor operator+(const myColor& lhs, const myColor& rhs);
        
        myColor& operator-=(const myColor& c);
        friend myColor operator-(const myColor& lhs, const myColor& rhs);

        myColor& operator*=(float factor);
        friend myColor operator*(const myColor& c, float factor);
        friend myColor operator*(float factor, const myColor& c);
        myColor& operator*=(const myColor& c);
        friend myColor operator*(const myColor& lhs, const myColor& rhs);


        myColor& operator/=(float factor);
        friend myColor operator/(const myColor& c, float factor);
        myColor& operator/=(const myColor& c);
        friend myColor operator/(const myColor& lhs, const myColor& rhs);

        friend bool operator==(const myColor& lhs, const myColor& rhs);
        friend bool operator!=(const myColor& lhs, const myColor& rhs);

        myColor operator-() const;

        friend std::ostream& operator<<(std::ostream& os, const myColor& c);

        // METHODS
        sf::Color toSFMLColor();
        void fromSFMLColor(const sf::Color& c);

        // DEFAULT COLORS
        static const myColor BLACK;
        static const myColor WHITE;
        static const myColor RED;
        static const myColor GREEN;
        static const myColor BLUE;
        static const myColor YELLOW;
        static const myColor MAGENTA;
        static const myColor CYAN;
        
        static const myColor PINK;
        static const myColor ORANGE;
        static const myColor PURPLE;
        static const myColor BROWN;
        static const myColor GOLD;
        static const myColor SILVER;
        static const myColor GRAY;
};

#endif