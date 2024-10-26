#include "filerepository.hpp"
#ifndef SERVICES_HPP
#define SERVICES_HPP

#pragma once

using namespace std;

class Services
{
private:
	FileRepository repository;
public:
	Services();
	~Services() {};
	int addTutorial(const string& title, const string& presenter, const string& duration, const string& link, const int& likes);
	bool removeTutorial(const string& title);
	bool updateTutorial(const string& oldTitle, const string& newTitle, const string& newPresenter, const string& newDuration, const string& newLink, const int& newLikes);
	vector<Tutorial> getTutorials() const;
	void setupStartList();
	vector<Tutorial> getTutorialsByPresenter(const string& presenter);
	void openTutorialInBrowser(const string& link);
	bool addToWatchlist(Tutorial tutorial, string type);
	vector<Tutorial> getWatchlist();
	bool removeFromWatchlist(const string& title);
};

class Validator
{
public:
	Validator() {};
	~Validator() {};
	bool validateLink(const string& link);
	bool validateDuration(const string& duration);
	bool validateLikes(const int& likes);
	bool validateTitle(const string& title);
	bool validatePresenter(const string& presenter);
};


#endif