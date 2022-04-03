// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack1;
    std::string output = "";

    for (int i = 0; i < inf.length(); i++) {
        if (priority(inf[i]) == 4) {
            output += inf[i];
            output += ' ';
        } else {
            if (priority(inf[i]) == 0) {
                stack1.push(inf[i]);
            } else if (priority(inf[i]) > priority(stack1.get())) {
                stack1.push(inf[i]);
            } else if (stack1.isEmpty()) {
                stack1.push(inf[i]);
            } else if (priority(inf[i]) == 1) {
                while (priority(stack1.get()) != 0) {
                    output += stack1.get();
                    output += ' ';
                    stack1.pop();
                }
                stack1.pop();
            } else if (priority(inf[i]) <= priority(stack1.get())) {
                while ((!(stack1.isEmpty())) && (priority(stack1.get()) > 1)) {
                    output += (stack1.get());
                    output += (' ');
                    stack1.pop();
                }
                stack1.push(inf[i]);
            }
        }
    }

    while (!(stack1.isEmpty())) {
        output += stack1.get();
        output += (' ');
        stack1.pop();
    }

    output.pop_back();
    return output;
}

int eval(std::string pref) {
    TStack<int, 100> stack2;
    for (int i = 0; i < pref.length(); i++) {
        std::string out2 = "";
        while ((priority(pref[i]) == 4) && (i < pref.length())) {
            out2 += pref[i];
            i++;
        }
        if ((priority(pref[i]) == 2) || (priority(pref[i]) == 3)) {
            int op1 = stack2.get(); stack2.pop();
            int op2 = stack2.get(); stack2.pop();
            if (pref[i] == '+') {
                stack2.push(op1 + op2);
            }
            if (pref[i] == '-') {
                stack2.push(op2 - op1);
            }
            if (pref[i] == '*') {
                stack2.push(op1 * op2);
            }
            if (pref[i] == '/') {
                stack2.push(op2 / op1);
            }
        }
        if (out2 != "") {
            stack2.push(std::stoi(out2));
        }
    }
    return stack2.get();
}
