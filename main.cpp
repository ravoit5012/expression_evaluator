#include "evaluator.h"
#include <iostream>

int main() {
    Evaluator evaluator;

    // Test 1: x = (5 + 3)
    vector<string> code1 = {"x", "=", "(", "5", "+", "3", ")"};
    evaluator.parse(code1);
    evaluator.eval();

    // Test 2: y = (x * 2)
    vector<string> code2 = {"y", "=", "(", "x", "*", "2", ")"};
    evaluator.parse(code2);
    evaluator.eval();

    // Test 3: z = ((y - 4) / 2)
    vector<string> code3 = {"z", "=", "(", "(", "y", "-", "4", ")", "/", "2", ")"};
    evaluator.parse(code3);
    evaluator.eval();

    // Test 4: a = (((x + y) * (z - 3)) / 5)
    vector<string> code4 = {"a", "=", "(", "(", "(", "x", "+", "y", ")", "*", "(", "z", "-", "3", ")", ")", "/", "5", ")"};
    evaluator.parse(code4);
    evaluator.eval();

    // Test 5: b = ((-5 + 2) * (z + 1))
    vector<string> code5 = {"b", "=", "(", "(", "-5", "+", "2", ")", "*", "(", "z", "+", "1", ")", ")"};
    evaluator.parse(code5);
    evaluator.eval();

    // Test 6: c = ((((((1 + 2) * 3) - 4) / 5) + 6) * 7)
    vector<string> code6 = {"c", "=", "(", "(", "(", "(", "(", "(", "1", "+", "2", ")", "*", "3", ")", "-", "4", ")", "/", "5", ")", "+", "6", ")", "*", "7", ")"};
    evaluator.parse(code6);
    evaluator.eval();

    // Print all results
    vector<string> vars = {"x", "y", "z", "a", "b", "c"};
    for (const string& var : vars) {
        UnlimitedRational* r = evaluator.symtable->search(var);
        if (r)
            std::cout << var << " = " << r->get_frac_str() << std::endl;
        else
            std::cout << var << " = [undefined or error]" << std::endl;
    }

    return 0;
}
