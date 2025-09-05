#include <iostream>
#include <app.hpp>

int main(int argc, char **argv) {
    PowerMenuApp app;
    int status = app.run(argc, argv);

    return status;
}