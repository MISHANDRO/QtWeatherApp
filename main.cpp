#include "WeatherApp.h"

#include <iostream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    WeatherApp wa_;
    wa_.show();

    return QApplication::exec();
}
