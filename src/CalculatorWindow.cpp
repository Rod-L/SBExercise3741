#include "CalculatorWindow.h"

std::string CalculatorWindow::calculate(std::string& left, std::string& right, char op) {
    double numLeft, numRight;
    try {
        numLeft = std::stod(left);
        numRight = std::stod(right);
    } catch (...) {
        return "ERROR";
    }

    double result;
    switch (op) {
        case '-': result = numLeft - numRight; break;
        case '+': result = numLeft + numRight; break;
        case '*': result = numLeft * numRight; break;
        case '/': result = numLeft / numRight; break;
        default: return "ERROR";
    }

    auto str = std::to_string(result);

    if (str.find('.') != std::string::npos) {
        // remove unnecessary trailing symbols
        while (str.back() == '0') str.pop_back();
        if (str.back() == '.') str.pop_back();
    }

    return str;
}

QLineEdit* CalculatorWindow::current_input_field() const {
    return (input_position == LEFT_VALUE ? UI->leLeftValue : UI->leRightValue);
}

CalculatorWindow::CalculatorWindow(Ui_Calculator* inUI, QWidget* inParent): QMainWindow(inParent) {
    assert(inUI != nullptr);
    input_position = LEFT_VALUE;
    if (inUI) {
        inUI->setupUi(this);
        UI = inUI;
    }
}

//// operation handlers

void CalculatorWindow::addMullDivOp(char code) {
    auto left = UI->leLeftValue->text().toStdString();
    if (left.empty()) UI->leLeftValue->setText("0");
    input_position = RIGHT_VALUE;
    UI->leOperator->setText(QString(code));
}

void CalculatorWindow::subtractOp() {
    if (input_position == LEFT_VALUE && UI->leLeftValue->text().isEmpty()
            || input_position == RIGHT_VALUE && UI->leRightValue->text().isEmpty()) {
        current_input_field()->setText("-");
    } else {
        addMullDivOp('-');
    }
}

void CalculatorWindow::equalOp() {
    auto left = UI->leLeftValue->text().toStdString();
    auto right = UI->leRightValue->text().toStdString();
    auto current_operator = UI->leOperator->text().toStdString();
    UI->leResult->setText(QString::fromStdString(calculate(left, right, current_operator.front())));
}

void CalculatorWindow::dotOp() {
    auto field = current_input_field();
    const auto& current_text = field->text();

    // Allow only one dot in number
    if (current_text.toStdString().find('.') < std::string::npos) return;
    if (current_text.isEmpty()) {
        field->setText("0.");
    } else {
        field->setText(current_text + ".");
    }
}

void CalculatorWindow::removeOp() {
    auto field = current_input_field();
    const auto& current_text = field->text();
    auto length = current_text.length();

    if (length == 0) {
        if (input_position == RIGHT_VALUE) {
            UI->leOperator->clear();
            input_position = LEFT_VALUE;
        }
        return;
    }

    auto str = current_text.toStdString();
    str.resize(length - 1);
    field->setText(QString::fromStdString(str));
}

void CalculatorWindow::clearOp() {
    input_position = LEFT_VALUE;
    UI->leLeftValue->clear();
    UI->leRightValue->clear();
    UI->leOperator->clear();
    UI->leResult->clear();
}

//// slots

void CalculatorWindow::inputOperator() {
    auto source = qobject_cast<QPushButton*>(sender());
    assert(source != nullptr);

    auto code = source->text().toStdString()[0];

    switch (code) {
        case '-': subtractOp();       break;
        case '+':
        case '*':
        case '/': addMullDivOp(code); break;
        case '=': equalOp();          break;
        case '.': dotOp();            break;
        case '<': removeOp();         break;
        case 'C': clearOp();          break;
        default: return;
    }
};

void CalculatorWindow::inputNum() {
    auto source = qobject_cast<QPushButton*>(sender());
    assert(source != nullptr);

    auto field = current_input_field();
    const auto& current_text = field->text();
    if (current_text.length() > 8) return;

    field->setText(current_text + source->text());
};