#include <iostream>
#include "ulimitedint.h"
#include "ulimitedrational.h"
using namespace std;

void testUnlimitedInt() {
    cout << "Testing UnlimitedInt Operations:\n";

    UnlimitedInt a("12345");
    UnlimitedInt b("6789");

    cout << "a = " << a.to_string() << "\n";
    cout << "b = " << b.to_string() << "\n";

    UnlimitedInt* sum = UnlimitedInt::add(&a, &b);
    UnlimitedInt* diff = UnlimitedInt::sub(&a, &b);
    UnlimitedInt* prod = UnlimitedInt::mul(&a, &b);
    UnlimitedInt* quo = UnlimitedInt::div(&a, &b);
    UnlimitedInt* rem = UnlimitedInt::mod(&a, &b);

    cout << "a + b = " << sum->to_string() << "\n";    // Expected: 19134
    cout << "a - b = " << diff->to_string() << "\n";   // Expected: 5556
    cout << "a * b = " << prod->to_string() << "\n";   // Expected: 83810205
    cout << "a / b = " << quo->to_string() << "\n";    // Expected: 1 (since 12345 / 6789 ≈ 1.818)
    cout << "a % b = " << rem->to_string() << "\n";    // Expected: 12345 - 1*6789 = 5556

    delete sum; delete diff; delete prod; delete quo; delete rem;
}

void testUnlimitedRational() {
    cout << "\nTesting UnlimitedRational Operations:\n";

    UnlimitedInt num1(1224), den1(36);
    UnlimitedInt num2(18), den2(48);

    UnlimitedRational* r1 = new UnlimitedRational(&num1, &den1);
    UnlimitedRational* r2 = new UnlimitedRational(&num2, &den2);

    cout << "r1 = " << r1->get_frac_str() << "\n";  // Expected: 34/1
    cout << "r2 = " << r2->get_frac_str() << "\n";  // Expected: 3/8

    UnlimitedRational* radd = UnlimitedRational::add(r1, r2);
    UnlimitedRational* rsub = UnlimitedRational::sub(r1, r2);
    UnlimitedRational* rmul = UnlimitedRational::mul(r1, r2);
    UnlimitedRational* rdiv = UnlimitedRational::div(r1, r2);

    cout << "r1 + r2 = " << radd->get_frac_str() << "\n"; // Expected: (34*8 + 3*1)/8 = 275/8
    cout << "r1 - r2 = " << rsub->get_frac_str() << "\n"; // Expected: (34*8 - 3*1)/8 = 269/8
    cout << "r1 * r2 = " << rmul->get_frac_str() << "\n"; // Expected: (34*3)/(8*1) = 102/8 = 51/4
    cout << "r1 / r2 = " << rdiv->get_frac_str() << "\n"; // Expected: (34*8)/(3*1) = 272/3

    delete r1; delete r2;
    delete radd; delete rsub; delete rmul; delete rdiv;
}

void testEdgeCases() {
    cout << "\nTesting Edge Cases:\n";

    UnlimitedInt n1("-1000"), d1("-250");
    UnlimitedRational* neg_rational = new UnlimitedRational(&n1, &d1);

    cout << "-1000/-250 = " << neg_rational->get_frac_str() << "\n";  // Expected: 4/1

    UnlimitedInt n2("1000"), d2("-250");
    UnlimitedRational* neg_rational2 = new UnlimitedRational(&n2, &d2);

    cout << "1000/-250 = " << neg_rational2->get_frac_str() << "\n";  // Expected: -4/1

    UnlimitedInt n3("-1000"), d3("250");
    UnlimitedRational* neg_rational3 = new UnlimitedRational(&n3, &d3);

    cout << "-1000/250 = " << neg_rational3->get_frac_str() << "\n";  // Expected: -4/1

    delete neg_rational;
    delete neg_rational2;
    delete neg_rational3;
}

int main() {
    testUnlimitedInt();
    testUnlimitedRational();
    testEdgeCases();
    return 0;
}
