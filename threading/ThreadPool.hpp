/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/04 by lebovin
*/

#ifndef CPP_PLAZZA_THREADPOOL_HPP
#define CPP_PLAZZA_THREADPOOL_HPP

#include <cstddef>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <functional>
#include <future>

class ThreadPool
{
public:
	explicit ThreadPool(size_t thread_count);
	~ThreadPool();

	template<typename F, typename... Args>
	std::future<typename std::result_of<F(Args...)>::type>
	addTask(F &&func, Args &&...args)
	{
		if (!m_isWorking)
			throw std::runtime_error("Threadpool has been stopped.");

		using ret = typename std::result_of<F(Args...)>::type;
		auto shared_ptask = std::make_shared<std::packaged_task<ret()>>
		(std::bind(std::forward<F>(func), std::forward<Args>(args)...));
		auto result = shared_ptask->get_future();
		std::unique_lock<std::mutex> ulock(m_lock);
		m_tasks.emplace([shared_ptask]()
				{
					(*shared_ptask)();
				});
		ulock.unlock();
		m_newTaskAdded.notify_one();

		return (result);
	};
private:
	bool m_isWorking;
	std::mutex m_lock;
	std::condition_variable m_newTaskAdded;
	std::vector<std::thread> m_threads;
	std::queue<std::function<void()>> m_tasks;

	void wait();
};

#endif //CPP_PLAZZA_THREADPOOL_HPP
