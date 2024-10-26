#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#pragma once

#ifndef DOMAIN_HPP
#define DOMAIN_HPP

using namespace std;


class Tutorial
{
private:
	string title, presenter, duration, link;
	int likes;
public:
	Tutorial() : title(""), presenter(""), duration(""), link(""), likes(0) {};
	Tutorial(string title, string presenter, string duration, string link, int likes);
	~Tutorial() {};
	string getTitle();
	string getPresenter();
	string getDuration();
	string getLink();
	int getLikes();
	bool operator==(const Tutorial& other);
	void setTitle(string title);
	void setPresenter(string presenter);
	void setDuration(string duration);
	void setLink(string link);
	void setLikes(int likes);
	friend istream& operator>>(istream& in, Tutorial& tutorial);
	friend ostream& operator<<(ostream& out, Tutorial tutorial);
};

#endif