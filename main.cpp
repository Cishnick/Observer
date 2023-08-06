#include <iostream>

#include "observable.h"

// --- test ----
class TestObservable : public Observable<TestObservable>
{
public:
	int value_{};
};

class TestObserver1 : public ObserverController
{
};

int main()
{
	TestObserver1 observer1;
	auto *observer12 = new TestObserver1();
	TestObservable observable;
	ObserverController observer2;

	observable.register_observer(&observer1,
	                             [](const auto &observable)
	                             { std::cout << "New value from observer1:" << observable.value_ << std::endl; });
	observable.register_observer(observer12,
	                             [](const auto &observable)
	                             { std::cout << "New value from observer12:" << observable.value_ << std::endl; });
	observable.register_observer(&observer2,
	                             [](const auto &observable)
	                             { std::cout << "New value from observer2:" << observable.value_ << std::endl; });

	observable.update()->value_ = 10;

	delete observer12;

	observable.update()->value_ = 15;

	{
		const auto &obs = observable.update();
		obs->value_ = 20;
		obs->value_ = 25;
	}

	return 0;
}
