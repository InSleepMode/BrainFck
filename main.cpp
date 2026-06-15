#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

struct Rule {
    std::vector<char> command;
    std::vector<int> brackets;
};

int main(int argc, char* argv[]) {

    std::ifstream inFileProg(argv[1]);
    if (!inFileProg) {
        std::cerr << "Could not open ProgFile" << std::endl;
        return 1;
    }

    std::ifstream inFileInput(argv[2]);
    if (!inFileInput) {
        std::cerr << "Could not open InputFile" << std::endl;
        return 1;
    }

    Rule rule;
    char ch;

    while (inFileProg.get(ch)) {

        if (ch == '>' || ch == '<' || ch == '+' || ch == '-' || ch == '.'
            || ch == ',' || ch == ']' || ch == '[') {
            rule.command.push_back(ch);
        }
    }

    rule.brackets.resize(rule.command.size());

    std::stack<int> bracket_stack;
    for (int i = 0; i < rule.command.size(); ++i) {
        if (rule.command[i] == '[') {
            bracket_stack.push(i);
        }
        else if (rule.command[i] == ']') {
            int opened = bracket_stack.top();
            bracket_stack.pop();

            rule.brackets[opened] = i;
            rule.brackets[i] = opened;
        }
    }

    long long lenta_ptr = 0;
    long long command_ptr = 0;

    std::vector<unsigned char> Lenta(30000, 0);
    while (command_ptr < rule.command.size()) {
        switch (rule.command[command_ptr]) {
        case '>':
            if (lenta_ptr < 29999) {
                ++lenta_ptr;
            }
            else {
                std::cout << "ERROR";
                return 1;
            }
            break;
        case '<':
            if (lenta_ptr > 0) {
                --lenta_ptr;

            }
            else {
                std::cout << "ERROR";
                return 1;
            }
            break;
        case '+':
            Lenta[lenta_ptr] += 1;
            break;

        case '-':
            Lenta[lenta_ptr] -= 1;
            break;

        case '.':
            std::cout << Lenta[lenta_ptr];
            break;

        case ',':
            if (inFileInput.get(ch)) {
                Lenta[lenta_ptr] = (unsigned char)ch;
            }
            break;

        case '[':
            if (Lenta[lenta_ptr] == 0) {
                command_ptr = rule.brackets[command_ptr];
            }
            break;
        case ']':
            if (Lenta[lenta_ptr] != 0) {
                command_ptr = rule.brackets[command_ptr];
            }
            break;
        }

        ++command_ptr;
    }

return 0;
}
