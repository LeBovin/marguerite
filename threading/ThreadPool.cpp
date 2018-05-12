/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/04 by lebovin
*/

#include "../../inc/concurrency/ThreadPool.hpp"

ThreadPool::ThreadPool(size_t thread_count)
: m_isWorking(true)
{
	for (size_t counter = 0; counter < thread_count; counter++)
		m_threads.push_back(std::thread(&ThreadPool::wait, this));
}
void ThreadPool::wait()
{
	std::function<bool()> shouldStopWaiting = [this]()
	{
		return (!m_isWorking || !m_tasks.empty());
	};
	while (m_isWorking || !m_tasks.empty())
	{
		std::function<void()> task;
		std::unique_lock<std::mutex> locker(m_lock);
		m_newTaskAdded.wait(locker, shouldStopWaiting);
		if (!m_isWorking && m_tasks.empty())
			return ;
		task = m_tasks.front();
		m_tasks.pop();
		locker.unlock();
		task();
	}
}
ThreadPool::~ThreadPool()
{
	m_lock.lock();
	m_isWorking = false;
	m_lock.unlock();
	m_newTaskAdded.notify_all();
	for (auto &thread: m_threads)
		thread.join();
}
