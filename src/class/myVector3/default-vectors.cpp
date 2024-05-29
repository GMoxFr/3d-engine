
#include "myVector3.hpp"

const myVector3 myVector3::CAMERA(WINDOW_WIDTH / 2, -(WINDOW_WIDTH * 1), WINDOW_HEIGHT / 2);
// const myVector3 myVector3::CAMERA(0, 0, 1024);

const myVector3 myVector3::ZERO(0, 0, 0);

const myVector3 myVector3::UP(0, 0, 1);
const myVector3 myVector3::DOWN(0, 0, -1);
const myVector3 myVector3::LEFT(-1, 0, 0);
const myVector3 myVector3::RIGHT(1, 0, 0);
const myVector3 myVector3::FORWARD(0, 1, 0);
const myVector3 myVector3::BACKWARD(0, -1, 0);

const myVector3 myVector3::BOTTOM_LEFT(0, 0, 0);
const myVector3 myVector3::BOTTOM_RIGHT(WINDOW_WIDTH - 1, 0, 0);
const myVector3 myVector3::TOP_LEFT(0, 0, WINDOW_HEIGHT - 1);
const myVector3 myVector3::TOP_RIGHT(WINDOW_WIDTH - 1, 0, WINDOW_HEIGHT - 1);