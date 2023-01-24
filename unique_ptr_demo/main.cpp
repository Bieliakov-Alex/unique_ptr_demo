#include <iostream>

#include <memory>

class A {
public:
	A() { std::cout << "This is A constructor\n"; }
	A(int param) :x{ param } { std::cout << "This is A constructor with param\n"; }
	~A() { std::cout << "This is A destructor\n"; }
	int getX() { return x; }
	A(const A& param) = delete;

private:
	int x{ 0 };
};

void f(A* param) { std::cout << "Pure pointer\n"; }
void f(std::unique_ptr<A> param) { std::cout << "Smart pointer\n"; }

int main() {
	A* a = new A();
	A* a_with_param = new A(1);

	std::cout << a->getX() << " " << a_with_param->getX() << "\n";
	std::cout << (*a).getX() << " " << (*a_with_param).getX() << "\n";

	A* b = a;
	//A* c = new A(*b);
	f(b);

	std::unique_ptr<A> unique_a = std::make_unique<A>();
	std::unique_ptr<A> unique_a_with_param = std::make_unique<A>(1);

	std::cout << unique_a->getX() << " " << unique_a_with_param->getX() << "\n";
	std::cout << (*unique_a).getX() << " " << (*unique_a_with_param).getX() << "\n";

	auto c = unique_a.get();
	A* d = c;

	f(c);
	//f(unique_a);

	//b = unique_a;

	//f(unique_a);

	delete a;
	delete a_with_param;
	return 0;
}