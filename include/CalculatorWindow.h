#pragma once
#include <QMainWindow>
#include "ui_calculator.h"
#include <iostream>

enum CurrentInputPosition {
    LEFT_VALUE,
    RIGHT_VALUE
};

class CalculatorWindow: public QMainWindow {
    Q_OBJECT

private:
    Ui_Calculator* UI;
    CurrentInputPosition input_position;

    void addMullDivOp(char code);
    void subtractOp();
    void equalOp();
    void dotOp();
    void removeOp();
    void clearOp();

public:
    static std::string calculate(std::string& left, std::string& right, char op);
    QLineEdit* current_input_field() const;
    explicit CalculatorWindow(Ui_Calculator* inUI, QWidget* inParent = nullptr);

public slots:
    void inputOperator();
    void inputNum();
};
