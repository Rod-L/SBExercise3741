#include <QApplication>
#include "CalculatorWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Ui_Calculator calculator{};
    CalculatorWindow window(&calculator);
    window.show();

    return QApplication::exec();
}
