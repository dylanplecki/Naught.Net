#pragma once

template <typename T>
struct Queue
{
	std::mutex opLock;
	std::vector<T> contents;
};