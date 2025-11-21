#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <stdexcept>

class RPNCalculator {
private:
    std::stack<double> stack;

public:
    void push(double value) {
        stack.push(value);
    }

    double pop() {
        if (stack.empty()) {
            throw std::runtime_error("错误: 栈为空");
        }
        double value = stack.top();
        stack.pop();
        return value;
    }

    void calculate(const std::string& operation) {
        if (operation == "+") {
            double b = pop();
            double a = pop();
            push(a + b);
        } else if (operation == "-") {
            double b = pop();
            double a = pop();
            push(a - b);
        } else if (operation == "*") {
            double b = pop();
            double a = pop();
            push(a * b);
        } else if (operation == "/") {
            double b = pop();
            if (b == 0) {
                throw std::runtime_error("错误: 除零错误");
            }
            double a = pop();
            push(a / b);
        } else {
            // 尝试解析为数字
            try {
                double value = std::stod(operation);
                push(value);
            } catch (const std::exception&) {
                throw std::runtime_error("错误: 未知操作符 '" + operation + "'");
            }
        }
    }

    void clear() {
        while (!stack.empty()) {
            stack.pop();
        }
    }

    void displayStack() {
        std::stack<double> temp = stack;
        std::vector<double> elements;
        
        while (!temp.empty()) {
            elements.push_back(temp.top());
            temp.pop();
        }
        
        std::cout << "当前栈: ";
        for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    bool empty() const {
        return stack.empty();
    }

    size_t size() const {
        return stack.size();
    }
};

void processRPNExpression(const std::string& expression) {
    RPNCalculator calc;
    std::istringstream iss(expression);
    std::string token;
    
    try {
        while (iss >> token) {
            if (token == "q" || token == "quit") {
                return;
            }
            calc.calculate(token);
        }
        
        if (calc.size() == 1) {
            std::cout << "结果: " << calc.pop() << std::endl;
        } else if (calc.size() > 1) {
            std::cout << "警告: 栈中仍有多个值" << std::endl;
            calc.displayStack();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

int main() {
    std::cout << "C++ RPN 计算器" << std::endl;
    std::cout << "输入表达式 (例, '5 5 +'), 或 'q' 退出." << std::endl;
    
    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        
        if (input == "q" || input == "quit") {
            break;
        }
        
        if (!input.empty()) {
            processRPNExpression(input);
        }
    }
    
    return 0;
}
