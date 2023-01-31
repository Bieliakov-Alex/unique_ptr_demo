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

	//Address comparation
	std::cout << "Address of c " << c << "\n";
	std::cout << "Address of unique_a " << &unique_a << "\n";

	A* d = c;

	f(c);
	//f(unique_a);

	//b = unique_a;

	//f(unique_a);


	//how to compare unique_ptr to nullptr
	if (unique_a) {
		std::cout << "unique_a is not empty\n";
	}
	else{
		std::cout << "unique_a is empty\n";
	}

	//how to destroy unique_ptr
	unique_a.reset();

	if (unique_a) {
		std::cout << "unique_a is not empty\n";
	}
	else {
		std::cout << "unique_a is empty\n";
	}

	unique_a.reset();


	//how to get pure pointer from unique_pointer
	//(Try to avoid this)
	auto pure_ptr = unique_a_with_param.release();

	if (unique_a_with_param) {
		std::cout << "unique_a_with_param is not empty\n";
	}
	else {
		std::cout << "unique_a_with_param is empty\n";
	}

	std::cout << "Delete pure_ptr:\n";
	delete pure_ptr;

	std::unique_ptr<int> test_ptr = nullptr;

	if (!test_ptr) {
		std::cout << "test_ptr is empty\n";
		test_ptr = std::make_unique<int>();
	}
	else {
		std::cout << "test_ptr is not empty\n";
	}

	//bad approach, don't do this
	/*std::cout << "Delete pure_ptr:\n";
	if (unique_a_with_param != nullptr) {
		delete& unique_a_with_param;
	}*/	

	std::cout << "Delete other objects:\n";

	delete a;
	delete a_with_param;
	return 0;
}