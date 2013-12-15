/*
	Program: Naught.Net Dynamic Link Library (DLL)
	Author: Dylan Plecki <dylanplecki@gmail.com>
	License:
		Copyright (C) 2013 Dylan Plecki. All rights reserved.
		This work is licensed under the Microsoft Reference Source License (MS-RSL).
		Please reference the LICENSE.txt file included with this program for more information,
		Or visit <http://referencesource.microsoft.com/referencesourcelicense.aspx> for a copy.
*/

#include "stdafx.h"
#include "Queue.h"


template<class T>
size_t Queue<T>::size()
{
	std::lock_guard<std::mutex> lk(this->lock);
	return this->queue.size();
};

template<class T>
T Queue<T>::next()
{
	std::lock_guard<std::mutex> lk(this->lock);
	T nextVal = this->queue.front();
	this->queue.pop();
	return nextVal;
};

template<class T>
void Queue<T>::add(T& entity)
{
	std::lock_guard<std::mutex> lk(this->lock);
	this->queue.push(entity);
};