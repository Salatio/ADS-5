// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int Prior(chac c) {
    int ret = -1;
    if (c == 'C' )
        ret = 0;
    else if (c == ')' )
        ret = 1;
    else if (c == '+' || c == '-')
        ret = 2;
    else if (c == '*' || c == '/')
        ret = 3;
    else ret = -1;
    return ret;
}

std::string infx2pstfx(std::string inf) {
    std::string out = "";
    TStack<char> stack1;
    for (int i = 0; i < inf.length(); ++i) {
        if (stack1.isEmpty() && Prior(inf[i]) != -1)
            stack1.push(inf[i]);
        else
            switch(Prior(inf[i])) {
                case -1:
                    out += inf[i];
                    if (Prior(inf[i]) != -1)
                        out += " ";
                    if (i+1 == inf.length()) {
                        while (!stack1.isEmpty()) {
                            out += " ";
                            out += stack1.get();
                            stack1.pop();
                        }
                    }
                    break;
                case 0:
                    stack1.push(inf[i]);
                    break;
                case 1:{
                    while (!stack1.isEmpty()) {
                        if (Prior(stack1.get()) > 0) {
                            out += stack1.get();
                            out += " ";
                            stack1.pop();
                        }
                        else {
                            stack1.pop();
                            break;
                        }
                    }
                    if (i+1 == inf.length()) {
                        while (!stack1.isEmpty()) {
                            out += stack1.get();
                            out += " ";
                            stack1.pop();
                        }
                    }
                    break;
                }
                case 2:
                    if (Prior(stack1.get()) < Prior(inf[i]))
                        stack1.push(inf[i]);
                    else {
                        while (!stack1.isEmpty()) {
                            if (Prior(stack1.get()) == 0)
                                break;
                            else if (Prior(stack1.get()) >= Prior(inf[i])) {
                                out += stack1.get();
                                out += " ";
                                stack1.pop();
                            }
                        }
                        stack1.push(inf[i]);
                    }
                    break;
                case 3:
                    if (Prior(stack1.get()) < Prior(inf[i]))
                        stack1.push(inf[i]);
                    else {
                        while (!stack1.isEmpty()) {
                            if (Prior(stack1.get()) == 0)
                                break;
                            else if (Prior(stack1.get()) >= Prior(inf[i]) {
                                out += stack1.get();
                                out += " ";
                                stack1.pop();
                            }
                        }
                        stack1.push(inf[i]);
                    }
                    break;
            }
    }
    if (out[out.length()-1] == ' ') {
        std::string temp = out;
        out.assign(temp, 0, temp.length()-1);
    }
    return out;
}

int eval(std::string pref) {
    TStack1<int> stack1;
    int count = 0;
    for (int i = 0; i < post.length(); ++i) {
        if (post[i] != ' ') {
            if (Prior(post[i]) == -1) {
                std::string temp = "";
                temp += post[i];
                stack1.push(std::stoi(temp));
                temp = "";
            }
            else {
                int temp1 = stack1.get();
                stack1.pop();
                int temp2 = stack1.get();
                stack1.pop();
                if (post[i] == '+') {
                    count = temp2 + temp1;
                    stack1.push(count);
                }
                else if (post[i] == '-') {
                    count = temp2 - temp1;
                    stack1.push(count);
                }
                else if (post[i] == '*') {
                    count = temp2 * temp1;
                    stack1.push(count);
                }
                else if (post[i] == '/') {
                    count = temp2 / temp1;
                    stack1.push(count);
                }
            }
            if (i+1 == post.length()) {
                count = stack1.get();
                stack1.pop();
                return count;
            }
        }
    }
}
