#pragma once
#include "domain.hpp"

#ifndef REPOSITORY_HPP
#define REPOSITORY_HPP

class Repository
{
protected:
	vector<Tutorial> tutorials;
	vector<Tutorial> watchlist;
public:
	Repository();
	~Repository();
	bool addTutorial(Tutorial tutorial);
	vector<Tutorial> getTutorials() const;
	int getSize();
	bool removeTutorial(const string& title);
	bool updateTutorial(const string& oldTitle, const string& newTitle, const string& newPresenter, const string& newDuration, const string& newLink, const int& newLikes);
	vector<Tutorial> getTutorialsByPresenter(const string& presenter);
	vector<Tutorial> getWatchlist() const;
	bool addToWatchlist(Tutorial tutorial);
	bool removeFromWatchlist(const string& title);
};

#endif