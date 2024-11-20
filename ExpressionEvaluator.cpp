#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>
using namespace std;

// Function to evaluate a postfix expression
int evaluatePostfix(const string& expression) {
    stack<int> s;
    stringstream ss(expression);
    string token;

    // Loop to read each token from the expression
    while (ss >> token) {
        // Check if the token is a number
        if (isdigit(token[0])) {
            // Convert the token to an integer and push onto the stack
            s.push(token[0] - '0');
        } else {
            // Check for sufficient elements in the stack before popping
            if (s.size() < 2) {
                throw invalid_argument("Invalid expression: insufficient operands");
            }

            // Pop two values from the stack
            int operand2 = s.top(); s.pop();
            int operand1 = s.top(); s.pop();

            // Perform the operation based on the token (operator)
            int result;
            switch (token[0]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        throw invalid_argument("Division by zero error");
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    throw invalid_argument("Invalid expression: unsupported operator");
            }

            // Push the result back onto the stack
            s.push(result);
        }
    }

    // Check if the final stack has exactly one element (the result)
    if (s.size() != 1) {
        throw invalid_argument("Invalid expression: too many operands");
    }

    return s.top();  // Return the result
}

int main() {
    string expression;
    cout << "Welcome to the Postfix Expression Evaluator!" << endl;
    cout << "Please enter a valid postfix expression using single-digit integers and operators (+, -, *, /)." << endl;
    cout << "Example: '3 4 + 2 * 7 /' or '5 1 2 + 4 * + 3 -'" << endl;
    cout << "Enter a postfix expression: ";
    getline(cin, expression);

    try {
        int result = evaluatePostfix(expression);
        cout << "Result: " << result << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}