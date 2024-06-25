#include <iostream>
#include "./src/AutoGrad.hpp"
using namespace std;
using real = AD::CAdjoint;
auto tape = AD::CTape();

void test1()
{
    /* y = x1*exp(x2) +x3 */
    tape.reset();
    real x1(2), x2(3), x3(4);
    real y = x1 * exp(x2) + x3;
    tape.evalute(y);
    cout << "x1:" << x1 << endl
         << "x2:" << x2 << endl
         << "x3:" << x3 << endl
         << "y:" << y << endl
         << "dy/dx1:" << tape.getGradient(x1) << endl
         << "dy/dx2:" << tape.getGradient(x2) << endl
         << "dy/dx3:" << tape.getGradient(x3) << endl;
}

void test2()
{
    cout << "test2" << endl;
    tape.reset();
    real x1, x2, y;
    x1.Set(1);
    x2 = x1;
    y = x2 * x2;
    tape.evalute(y);
    cout << x1 << x2 << y << endl;
    cout << tape.getGradient(x2) << endl;
}

void test3()
{
    cout << endl
         << "test3:" << endl;
    cout << "y1 = x1^2 + sqrt(x2)" << endl;
    cout << "y2 = x1/x2 - x2*x2" << endl;
    cout << endl
         << "dy1/dx1 = 2*x1" << endl;
    cout << "dy1/dx2 = -0.5/sqrt(x2)" << endl;
    cout << endl
         << "dy2/dx1=1.0/x2" << endl;
    cout << "dy2/dx2=-x1/x2^2 - 2*x2" << endl;
    real x1, x2, y1, y2;
    tape.reset();
    x1.Set(2);
    x2.Set(3);
    y1 = pow(x1, 2.0) + sqrt(x2);
    // y2 = x1 / x2 - x2 * x2;
    cout << "x1:" << x1 << endl
         << "x2:" << x2 << endl
         << "y1:" << y1 << endl;
        //  << "y2:" << y2 << endl;
    auto dy1dx1=[](real& x1, real &x2){
        return 2*x1.val();
    };
    auto dy1dx2=[](real& x1, real &x2){
        return 0.5/sqrt(x2.val());
    };
    auto dy2dx1=[](real& x1, real &x2){
        return 1.0/x2.val();
    };
    auto dy2dx2=[](real& x1, real &x2){
        return -x1.val()/(x2.val()*x2.val()) - 2*x2.val();
    };
    auto y1_ =[](real &x1, real &x2){
        return x1.val()*x1.val() + sqrt(x2.val());
    };

    auto y2_ = [](real &x1, real &x2){
        return x1.val() / x2.val() - x2.val()*x2.val();
    };
    cout << "AD y1: " << y1 << "exact y1: " << y1_(x1, x2)<<endl;
    // cout << "AD y2: " << y2 << "exact y2: " << y2_(x1, x2)<<endl;
    tape.evalute(y1);
    cout << "AD dy1/dx1: " << tape.getGradient(x1) << "    exact dy1/dx1: " << dy1dx1(x1, x2) <<endl;
    cout << "AD dy1/dx2: " << tape.getGradient(x2) << "    exact dy1/dx2: " << dy1dx2(x1, x2) <<endl;
    // tape.evalute(y2);
    // cout << "AD dy2/dx1: " << tape.getGradient(x1) << "    exact dy2/dx1: " << dy2dx1(x1, x2) <<endl;
    // cout << "AD dy2/dx2: " << tape.getGradient(x2) << "    exact dy2/dx2: " << dy2dx2(x1, x2) <<endl;
}

int main(void)
{
    cout << "AD" << endl;
    test1();
    test2();
    test3();
    return 0;
}