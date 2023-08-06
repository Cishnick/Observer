# Observer
Набор классов, предоставляющий вариацию паттерна наблюдатель, но с подпиской через лямбда выражения.
В заголовочном файле observer.h объявлен mixin класс `Observable`, пример использования в main.cpp:

```
class TestObservable : public Observable<TestObservable>
{
public:
    int value_{};
};
```
Для того чтобы изменить экземпляр класса сообщая эти изменения подписанным клиентам, необходимо вызвать
функцию `uodate()`:

```
observable.update()->value_ = 15;
```
Если изменений нужно несколько:
```
{
    const auto &obs = observable.update();
    obs->value_ = 20;
    obs->value_ = 25;
}
```
Сообщение изменений произойдет при вызове деструктора объекта, возвращаемого из `update()`. 
При подписке на изменения необходимо указать экземпляр класса ObserverController, и функтор,
который будет вызываться при изменении наблюдаемого экземпляра класса:
```
ObserverController observer2;
observable.register_observer(&observer2,
                             [](const auto &observable)
                             { std::cout << "New value from observer2:" << observable.value_ << std::endl; });
```
`ObserverController` необходим для контроля времени жизни подпписки. При уничтожении экземпляра
`ObserverController` произойдет отписка лямбды от события.