#include "../repository.hpp"

Repository::Repository()
{
	/*
	* Constructor for the repository class.
	* Initializes the dynamic array of tutorials.
	*/
	this->tutorials = vector<Tutorial>();
	this->watchlist = vector<Tutorial>();
}

Repository::~Repository()
{
	/*
	* Destructor for the repository class.
	* Nothing to do here, this will automatically call the destructor of the dynamic array.
	*/
}

bool Repository::addTutorial(Tutorial tutorial)
{
	/*
	* Method that adds a tutorial to the repository.
	* Input: tutorial - Tutorial object
	* Output: the tutorial is added to the repository
	*/
	for(auto tut : this->tutorials)
		if (tut.getTitle() == tutorial.getTitle())
			return false;

	this->tutorials.push_back(tutorial);
	return true;
}

bool Repository::removeTutorial(const string& title)
{
	/*
	* Method that removes a tutorial from the repository.
	* Input: title - string of the title we want to remove
	* Output: the tutorial is removed from the repository
	*/
	for(auto& tut : this->tutorials)
		if (tut.getTitle() == title)
		{
			this->tutorials.erase(remove(this->tutorials.begin(), this->tutorials.end(), tut), this->tutorials.end());
			return true;
		}
	return false;
}

bool Repository::updateTutorial(const string& oldTitle, const string& newTitle, const string& newPresenter, const string& newDuration, const string& newLink, const int& newLikes)
{
	/*
	* Method that updates a tutorial from the repository.
	* Input: oldTitle - string of the title we want to update
	* 	     newTitle - string of the updated title
	* 		 newPresenter - string of the updated presenter
	* 		 newDuration - string of the updated duration
	*		 newLink - string of the updated link
	* 		 newLikes - integer of the updated likes
	* Output: the tutorial is updated in the repository
	*/


	Tutorial updatedTutorial(newTitle, newPresenter, newDuration, newLink, newLikes);
	for(auto tut : this->tutorials)
		if (tut.getTitle() == newTitle && tut.getLikes() == newLikes)
			return false;

	for (auto& tut : this->tutorials)
	{
		if (tut.getTitle() == oldTitle)
		{
			tut = updatedTutorial;
			return true;
		}
	}
	return false;
}

vector<Tutorial> Repository::getTutorials() const
{
	/*
	* Method that returns the tutorials from the repository.
	* Input: -
	* Output: the tutorials from the repository
	*/
	return this->tutorials;
}

int Repository::getSize()
{
	/*
	* Method that returns the size of the repository.
	* Input: -
	* Output: the size of the repository
	*/
	return this->tutorials.size();
}

vector<Tutorial> Repository::getTutorialsByPresenter(const string& presenter)
{
	/*
	* Method that returns the tutorials from the repository by a certain presenter.
	* Input: presenter - string of the presenter we want to search for
	* Output: the tutorials from the repository by a certain presenter
	*/
	vector<Tutorial> tutorialsByPresenter = vector<Tutorial>();
	for(auto tut : this->tutorials)
		if (tut.getPresenter() == presenter)
			tutorialsByPresenter.push_back(tut);
	return tutorialsByPresenter;
}

vector<Tutorial> Repository::getWatchlist() const
{
	/*
	* Method that returns the watchlist from the repository.
	* Input: -
	* Output: the watchlist from the repository
	*/
	return this->watchlist;
}

bool Repository::addToWatchlist(Tutorial tutorial)
{
	/*
	* Method that adds a tutorial to the watchlist.
	* Input: tutorial - Tutorial object
	* Output: the tutorial is added to the watchlist
	*/
	for(auto tut : this->watchlist)
		if (tut.getTitle() == tutorial.getTitle())
			return false;
	this->watchlist.push_back(tutorial);
	return true;
}

bool Repository::removeFromWatchlist(const string& title)
{
	/*
	* Method that removes a tutorial from the watchlist.
	* Input: title - string of the title we want to remove
	* Output: the tutorial is removed from the watchlist
	*/
	for(auto& tut : this->watchlist)
		if (tut.getTitle() == title)
		{
			this->watchlist.erase(remove(this->watchlist.begin(), this->watchlist.end(), tut), this->watchlist.end());
			return true;
		}
	return false;
}