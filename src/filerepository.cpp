#include "../filerepository.hpp"
#include <fstream>
FileRepository::FileRepository()
{
	/*
	 * Constructor for the FileRepository class
	 */
	this->tutorials = vector<Tutorial>();
	this->watchlist = vector<Tutorial>();

	ifstream intutorials("tutorials.txt");
	string title, presenter, duration, link;
	int likes;
	while (intutorials >> title >> presenter >> duration >> link >> likes)
	{
		Tutorial tutorial{title, presenter, duration, link, likes};
		this->tutorials.push_back(tutorial);
	}
	ifstream inwatchlist("watchlist.txt");
	while (inwatchlist >> title >> presenter >> duration >> link >> likes)
	{
		Tutorial tutorial{title, presenter, duration, link, likes};
		this->watchlist.push_back(tutorial);
	}
}

FileRepository::~FileRepository()
{
	/*
	 * Nothing to do here, the stl vecstor's destructor will automatically be called
	 */
}

bool FileRepository::addTutorial(Tutorial tutorial)
{
	/*
	 * Method that adds a tutorial to the repository.
	 * Input: tutorial - Tutorial object
	 * Output: the tutorial is added to the repository
	 */
	for (auto it = this->tutorials.begin(); it != this->tutorials.end(); it++)
		if (it->getTitle() == tutorial.getTitle())
			return false;

	this->tutorials.push_back(tutorial);
	ofstream outtutorial("tutorials.txt");
	for (auto tutorial : this->tutorials)
		outtutorial << tutorial.getTitle() << " " << tutorial.getPresenter() << " " << tutorial.getDuration() << " " << tutorial.getLink() << " " << tutorial.getLikes() << endl;
	return true;
}

bool FileRepository::removeTutorial(const string &title)
{
	/*
	 * Method that removes a tutorial from the repository.
	 * Input: title - string of the title we want to remove
	 * Output: the tutorial is removed from the repository
	 */
	for (auto it = this->tutorials.begin(); it != this->tutorials.end(); it++)
	{
		if (it->getTitle() == title)
		{
			this->tutorials.erase(it);
			ofstream outtutorial("tutorials.txt");
			for (auto tutorial : this->tutorials)
				outtutorial << tutorial.getTitle() << " " << tutorial.getPresenter() << " " << tutorial.getDuration() << " " << tutorial.getLink() << " " << tutorial.getLikes() << endl;
			this->tutorials = this->getTutorials();
			return true;
		}
	}
	return false;
}

vector<Tutorial> FileRepository::getTutorials() const
{
	/*
	 * Method that returns the tutorials from the repository.
	 * Input: -
	 * Output: an stl vector of Tutorial objects.
	 */
	vector<Tutorial> tutorials;
	ifstream intutorials("tutorials.txt");
	string title, presenter, duration, link;
	int likes;
	while (intutorials >> title >> presenter >> duration >> link >> likes)
	{
		Tutorial tutorial{title, presenter, duration, link, likes};
		tutorials.push_back(tutorial);
	}
	return tutorials;
}

vector<Tutorial> FileRepository::getWatchlist() const
{
	/*
	 * Method that returns the watchlist from the repository.
	 * Input: -
	 * Output: the watchlist from the repository
	 */
	vector<Tutorial> watchlist;
	ifstream inwatchlist("watchlist.txt");
	string title, presenter, duration, link;
	int likes;
	while (inwatchlist >> title >> presenter >> duration >> link >> likes)
	{
		Tutorial tutorial{title, presenter, duration, link, likes};
		watchlist.push_back(tutorial);
	}
	return watchlist;
}

bool FileRepository::updateTutorial(const string &title, const string &newTitle, const string &newPresenter, const string &newDuration, const string &newLink, const int &newLikes)
{
	/*
	 * Method that updates a tutorial from the repository.
	 * Input: title - string of the title we want to update
	 * 	     newTitle - string of the updated title
	 * 		 newPresenter - string of the updated presenter
	 * 		 newDuration - string of the updated duration
	 *		 newLink - string of the updated link
	 * 		 newLikes - integer of the updated likes
	 * Output: the tutorial is updated in the repository
	 */
	Tutorial updatedTutorial(newTitle, newPresenter, newDuration, newLink, newLikes);
	for (auto it = this->tutorials.begin(); it != this->tutorials.end(); it++)
		if (it->getTitle() == newTitle && it->getLikes() == newLikes)
			return false;

	for (auto it = this->tutorials.begin(); it != this->tutorials.end(); it++)
	{
		if (it->getTitle() == title)
		{
			*it = updatedTutorial;
			ofstream outtutorial("tutorials.txt");
			for (auto tutorial : this->tutorials)
				outtutorial << tutorial.getTitle() << " " << tutorial.getPresenter() << " " << tutorial.getDuration() << " " << tutorial.getLink() << " " << tutorial.getLikes() << endl;
			this->tutorials = this->getTutorials();
			return true;
		}
	}
	return false;
}

bool FileRepository::addToWatchlist(Tutorial tutorial, string type)
{
	/*
	 * Method that adds a tutorial to the watchlist.
	 * Input: tutorial - Tutorial object
	 * Output: the tutorial is added to the watchlist in the required format (csv or html)
	 */
	for (auto it = this->watchlist.begin(); it != this->watchlist.end(); it++)
		if (it->getTitle() == tutorial.getTitle())
			return false;

	this->watchlist.push_back(tutorial);
	ofstream outwatchlist("watchlist.txt");
	for (auto tutorial : this->watchlist)
		outwatchlist << tutorial.getTitle() << " " << tutorial.getPresenter() << " " << tutorial.getDuration() << " " << tutorial.getLink() << " " << tutorial.getLikes() << endl;
	if (type == "c")
	{
		ofstream outwatchlist("watchlist.csv");
		for (auto tutorial : this->watchlist)
			outwatchlist << tutorial.getTitle() << "," << tutorial.getPresenter() << "," << tutorial.getDuration() << "," << tutorial.getLink() << "," << tutorial.getLikes() << endl;
		this->watchlist = this->getWatchlist();
	}
	else if (type == "h")
	{
		ofstream outwatchlist("watchlist.html");
		outwatchlist << "<!DOCTYPE html>\n";
		outwatchlist << "<html>\n";
		outwatchlist << "<head>\n";
		outwatchlist << "<title>Watchlist</title>\n";
		outwatchlist << "</head>\n";
		outwatchlist << "<body>\n";
		outwatchlist << "<table border = '1'>\n";
		outwatchlist << "<tr>\n";
		outwatchlist << "<td>Title</td>\n";
		outwatchlist << "<td>Presenter</td>\n";
		outwatchlist << "<td>Duration</td>\n";
		outwatchlist << "<td>Link</td>\n";
		outwatchlist << "<td>Likes</td>\n";
		outwatchlist << "</tr>\n";
		for (auto tutorial : this->watchlist)
		{
			outwatchlist << "<tr>\n";
			outwatchlist << "<td>" << tutorial.getTitle() << "</td>\n";
			outwatchlist << "<td>" << tutorial.getPresenter() << "</td>\n";
			outwatchlist << "<td>" << tutorial.getDuration() << "</td>\n";
			outwatchlist << "<td>" << tutorial.getLink() << "</td>\n";
			outwatchlist << "<td>" << tutorial.getLikes() << "</td>\n";
			outwatchlist << "</tr>\n";
		}
		outwatchlist << "</table>\n";
		outwatchlist << "</body>\n";
		outwatchlist << "</html>";
	}
	return true;
}

vector<Tutorial> FileRepository::getTutorialsByPresenter(const string &presenter)
{
	/*
	 * Method that returns the tutorials from the repository by a given presenter.
	 * Input: presenter - string of the presenter we want to search for
	 * Output: an stl vector of Tutorial objects.
	 */
	vector<Tutorial> tutorialsByPresenter;
	if(presenter == "all")
		return this->getTutorials();
	this->tutorials = this->getTutorials();
	for (auto tutorial : this->tutorials)
		if (tutorial.getPresenter() == presenter)
			tutorialsByPresenter.push_back(tutorial);
	return tutorialsByPresenter;
}

bool FileRepository::removeFromWatchlist(const string &title)
{
	/*
	 * Method that removes a tutorial from the watchlist.
	 * Input: title - string of the title we want to remove
	 * Output: the tutorial is removed from the watchlist
	 */
	for (auto it = this->watchlist.begin(); it != this->watchlist.end(); it++)
	{
		if (it->getTitle() == title)
		{
			this->watchlist.erase(it);
			ofstream outwatchlist("watchlist.txt");
			ofstream outwatchlisthtml("watchlist.html");
			outwatchlisthtml << "<!DOCTYPE html>\n";
			outwatchlisthtml << "<html>\n";
			outwatchlisthtml << "<head>\n";
			outwatchlisthtml << "<title>Watchlist</title>\n";
			outwatchlisthtml << "</head>\n";
			outwatchlisthtml << "<body>\n";
			outwatchlisthtml << "<table border = '1'>\n";
			outwatchlisthtml << "<tr>\n";
			outwatchlisthtml << "<td>Title</td>\n";
			outwatchlisthtml << "<td>Presenter</td>\n";
			outwatchlisthtml << "<td>Duration</td>\n";
			outwatchlisthtml << "<td>Link</td>\n";
			outwatchlisthtml << "<td>Likes";
			ofstream outwatchlistcsv("watchlist.csv");
			for (auto tutorial : this->watchlist)
			{
				outwatchlist << tutorial.getTitle() << " " << tutorial.getPresenter() << " " << tutorial.getDuration() << " " << tutorial.getLink() << " " << tutorial.getLikes() << endl;
				outwatchlisthtml << "<tr>\n";
				outwatchlisthtml << "<td>" << tutorial.getTitle() << "</td>\n";
				outwatchlisthtml << "<td>" << tutorial.getPresenter() << "</td>\n";
				outwatchlisthtml << "<td>" << tutorial.getDuration() << "</td>\n";
				outwatchlisthtml << "<td>" << tutorial.getLink() << "</td>\n";
				outwatchlisthtml << "<td>" << tutorial.getLikes() << "</td>\n";
				outwatchlistcsv << tutorial.getTitle() << "," << tutorial.getPresenter() << "," << tutorial.getDuration() << "," << tutorial.getLink() << "," << tutorial.getLikes() << endl;
				outwatchlisthtml << "</tr>\n";
			}
			this->watchlist = this->getWatchlist();
			return true;
		}
	}

	return false;
}
