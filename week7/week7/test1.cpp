#include <iostream> 
#include <stdexcept> 
class Test {
public:
    Test(char id) : id_(id) {}

    ~Test() {
        std::cout << "Destructor execution: "
            << id_ << std::endl;
    }
private: char id_;
};
int funcB() {
    Test r('B');
    throw std::runtime_error("Exception from funcB!\n");
    std::cout << "Executed in B" << std::endl;
    return 0;
}
int funcA() {
    Test r('A');
    funcB();
    std::cout << "Executed in A" << std::endl;
    return 0;
}
int main() {
    try {
        funcA();
    }
    catch (std::exception& e) {
        std::cout << "Exception : " << e.what();
    }
}
/* (실습 1-1) 분석결과 :
실행결과 :
Executed in B
Destructor execution: B
Executed in A
Destructor execution: A
결과분석 :
메인함수에서부터 실행이 된다. 메인함수의 try에는 함수 funcA가 호출된다.
함수 funcA에서는 객체A를 생성시키고 함수 funcB를 호출한다.
함수 funcB까지 호출되면 stack unwinding이 실행된다.
호출 순서와는 반대로 실행된다.
함수 funcB가 실행되고 문자열을 출력하고 함수가 종료되면 객체가 소멸되기 때문에 객체가 실행됬음을 알리는 문자열이 출력된다.
그 다음 함수 funcA와 객체 A에도 동일한 과정이 일어난다.
*/
/* (실습 1-2) 분석결과 :
실행결과 :
Destructor execution: B
Destructor execution: A
Exception : Exception from funcB!
결과분석 :
메인함수에서부터 실행이 된다. 메인함수의 try에는 함수 funcA가 호출된다.
함수 funcA에서는 객체A를 생성시키고 함수 funcB를 호출한다.
함수 funcB에서 객체B를 생성시키면 runtime error에 도달하게 된다.
exception을 만나게 되면 함수가 종료된다. exception을 만난 후의 문자열은 실행되지 않는다.
이때 객체B가 소멸되고 객체 A가 따라서 소멸한다.
메인함수에서의 catch부분이 실행된다. 함수B에서의 예외처리한 문장과 메인 함수에서의 문자열이 합쳐서 출력된다.
*/