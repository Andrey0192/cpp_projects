#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <algorithm>
#include <string>
#include <fstream>

template <typename T>
class IObserver
{
public:
    virtual ~IObserver() = default;
    virtual void onEvent(const T& eventData) = 0;
};


template <typename T>
class Subject
{
public:
    Subject();
    ~Subject();

    void attach(std::shared_ptr<IObserver<T>> observer);
    void detach(std::shared_ptr<IObserver<T>> observer);
    void notify(const T& eventData);

private:
    // PIMPL
    struct SubjectImpl;
    std::unique_ptr<SubjectImpl> impl;
};


class CustomEvent
{
public:
    std::string id;
    int eventType;
    std::string payload;
};

template <>
struct Subject<int>::SubjectImpl
{
    std::vector<std::weak_ptr<IObserver<int>>> observers;

    void attach(const std::shared_ptr<IObserver<int>>& observer)
    {
        observers.push_back(observer);
    }

    void detach(const std::shared_ptr<IObserver<int>>& observer)
    {
        observers.erase(
                std::remove_if(observers.begin(), observers.end(),
                               [&](const std::weak_ptr<IObserver<int>>& wptr) {
                                   return wptr.lock() == observer;
                               }),
                observers.end());
    }

    void notify(const int& eventData)
    {
        for (auto& wptr : observers)
        {
            if (auto obs = wptr.lock())
            {
                obs->onEvent(eventData);
            }
        }
    }
};

template <>
Subject<int>::Subject() : impl(std::make_unique<SubjectImpl>())
{
}
template <>
Subject<int>::~Subject() = default;

template <>
void Subject<int>::attach(std::shared_ptr<IObserver<int>> observer)
{
    impl->attach(observer);
}
template <>
void Subject<int>::detach(std::shared_ptr<IObserver<int>> observer)
{
    impl->detach(observer);
}
template <>
void Subject<int>::notify(const int& eventData)
{
    impl->notify(eventData);
}


template <>
struct Subject<std::string>::SubjectImpl
{
    std::list<std::weak_ptr<IObserver<std::string>>> observers;

    void attach(const std::shared_ptr<IObserver<std::string>>& observer)
    {
        observers.push_back(observer);
    }

    void detach(const std::shared_ptr<IObserver<std::string>>& observer)
    {
        observers.remove_if([&](const std::weak_ptr<IObserver<std::string>>& wptr) {
            return wptr.lock() == observer;
        });
    }

    void notify(const std::string& eventData)
    {
        for (auto& wptr : observers)
        {
            if (auto obs = wptr.lock())
            {
                obs->onEvent(eventData);
            }
        }
    }
};

template <>
Subject<std::string>::Subject() : impl(std::make_unique<SubjectImpl>())
{
}
template <>
Subject<std::string>::~Subject() = default;

template <>
void Subject<std::string>::attach(std::shared_ptr<IObserver<std::string>> observer)
{
    impl->attach(observer);
}
template <>
void Subject<std::string>::detach(std::shared_ptr<IObserver<std::string>> observer)
{
    impl->detach(observer);
}
template <>
void Subject<std::string>::notify(const std::string& eventData)
{
    impl->notify(eventData);
}


template <>
struct Subject<CustomEvent>::SubjectImpl
{
    std::vector<std::weak_ptr<IObserver<CustomEvent>>> observers;

    void attach(const std::shared_ptr<IObserver<CustomEvent>>& observer)
    {
        observers.push_back(observer);
    }

    void detach(const std::shared_ptr<IObserver<CustomEvent>>& observer)
    {
        observers.erase(
                std::remove_if(observers.begin(), observers.end(),
                               [&](const std::weak_ptr<IObserver<CustomEvent>>& wptr) {
                                   return wptr.lock() == observer;
                               }),
                observers.end());
    }

    void notify(const CustomEvent& eventData)
    {
        for (auto& wptr : observers)
        {
            if (auto obs = wptr.lock())
            {
                obs->onEvent(eventData);
            }
        }
    }
};

template <>
Subject<CustomEvent>::Subject() : impl(std::make_unique<SubjectImpl>())
{
}
template <>
Subject<CustomEvent>::~Subject() = default;

template <>
void Subject<CustomEvent>::attach(std::shared_ptr<IObserver<CustomEvent>> observer)
{
    impl->attach(observer);
}
template <>
void Subject<CustomEvent>::detach(std::shared_ptr<IObserver<CustomEvent>> observer)
{
    impl->detach(observer);
}
template <>
void Subject<CustomEvent>::notify(const CustomEvent& eventData)
{
    impl->notify(eventData);
}



template <typename T>
class ConsoleObserver : public IObserver<T>
{
public:
    void onEvent(const T& eventData) override
    {
        std::cout << "[ConsoleObserver] Event data: " << eventData << std::endl;
    }
};


template <>
void ConsoleObserver<CustomEvent>::onEvent(const CustomEvent& eventData)
{
    std::cout << "[ConsoleObserver] CustomEvent received:"
              << " id = " << eventData.id
              << ", eventType = " << eventData.eventType
              << ", payload = " << eventData.payload
              << std::endl;
}

template <typename T>
class LoggingObserver : public IObserver<T>
{
public:
    explicit LoggingObserver(const std::string& filename)
            : m_filename(filename) {}

    void onEvent(const T& eventData) override
    {
        std::ofstream ofs(m_filename, std::ios::app);
        if (ofs.is_open())
        {
            ofs << "[LoggingObserver] Event data: " << eventData << "\n";
        }
    }

private:
    std::string m_filename;
};

template <>
void LoggingObserver<CustomEvent>::onEvent(const CustomEvent& eventData)
{
    std::ofstream ofs(m_filename, std::ios::app);
    if (ofs.is_open())
    {
        ofs << "[LoggingObserver] CustomEvent received:"
            << " id=" << eventData.id
            << ", eventType=" << eventData.eventType
            << ", payload=" << eventData.payload
            << std::endl;
    }
}

int main()
{
    Subject<int> intSubject;

    auto intConsoleObs = std::make_shared<ConsoleObserver<int>>();
    auto intLoggingObs = std::make_shared<LoggingObserver<int>>("int_events.log");

    intSubject.attach(intConsoleObs);
    intSubject.attach(intLoggingObs);

    intSubject.notify(42);
    intSubject.notify(100);

    Subject<std::string> stringSubject;

    auto strConsoleObs = std::make_shared<ConsoleObserver<std::string>>();
    auto strLoggingObs = std::make_shared<LoggingObserver<std::string>>("string_events.log");

    stringSubject.attach(strConsoleObs);
    stringSubject.attach(strLoggingObs);

    stringSubject.notify("Hello, Observer Pattern!");
    stringSubject.notify("Another string event");

    Subject<CustomEvent> customSubject;

    auto customConsoleObs = std::make_shared<ConsoleObserver<CustomEvent>>();
    auto customLoggingObs = std::make_shared<LoggingObserver<CustomEvent>>("custom_events.log");

    customSubject.attach(customConsoleObs);
    customSubject.attach(customLoggingObs);

    CustomEvent evt1{"evt1", 101, "Payload #1"};
    CustomEvent evt2{"evt2", 202, "Payload #2"};

    customSubject.notify(evt1);
    customSubject.notify(evt2);

    std::cout << "check log files (int_events.log, string_events.log, custom_events.log) \n";
    return 0;
}
