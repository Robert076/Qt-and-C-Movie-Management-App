#include "domain.hpp"
#include "repository.hpp"

#ifndef FILEREPOSITORY_HPP
#define FILEREPOSITORY_HPP

class FileRepository : public Repository
{
public:
	FileRepository();
	~FileRepository();
	bool addTutorial(Tutorial tutorial);
	vector<Tutorial> getTutorials() const;
	bool removeTutorial(const string& title);
	bool updateTutorial(const string& oldTitle, const string& newTitle, const string& newPresenter, const string& newDuration, const string& newLink, const int& newLikes);
	vector<Tutorial> getTutorialsByPresenter(const string& presenter);
	vector<Tutorial> getWatchlist() const;
	bool addToWatchlist(Tutorial tutorial, string type);
	bool removeFromWatchlist(const string& title);
};

#endif