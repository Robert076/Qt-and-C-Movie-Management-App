#include "../domain.hpp"
#include <iostream>
using namespace std;
Tutorial::Tutorial(string title, string presenter, string duration, string link, int likes)
{
	/*
	* Constructor for the Tutorial class
	* Input: title - string, the title of the tutorial
	* 		 presenter - string, the presenter of the tutorial
	* 		 duration - string, the duration of the tutorial
	* 		 link - string, the link of the tutorial
	* 	     likes - int, the number of likes of the tutorial
	* Output: an object of type Tutorial
	*/
	this->title = title;
	this->presenter = presenter;
	this->duration = duration;
	this->link = link;
	this->likes = likes;
}

string Tutorial::getTitle()
{
	/*
	* Method that gets the title of a tutorial
	* Input: -
	* Output: string, the title of the tutorial
	*/
	return this->title;
}

string Tutorial::getPresenter()
{
	/*
	* Method that gets the presenter of a tutorial
	* Input: -
	* Output: string, the presenter of the tutorial
	*/
	return this->presenter;
}

string Tutorial::getDuration()
{
	/*
	* Method that gets the duration of a tutorial
	* Input: -
	* Output: string, the duration of the tutorial
	*/
	return this->duration;
}

string Tutorial::getLink()
{
	/*
	* Method that gets the link of a tutorial
	* Input: -
	* Output: string, the link of the tutorial
	*/
	return this->link;
}

int Tutorial::getLikes()
{
	/*
	* Method that gets the number of likes of a tutorial
	* Input: -
	* Output: int, the number of likes of the tutorial
	*/
	return this->likes;
}

bool Tutorial::operator==(const Tutorial& other)
{
	/*
	* Overloading the == operator for the Tutorial class
	* Input: other - Tutorial, the tutorial to be compared with
	* Output: bool, true if the tutorials are equal, false otherwise
	*/
	return this->title == other.title && this->presenter == other.presenter && this->link == other.link && this->duration == other.duration && this->likes == other.likes;
}

void Tutorial::setTitle(string title)
{
	/*
	* Method that sets the title of a tutorial
	* Input: title - string, the new title of the tutorial
	* Output: -
	*/
	this->title = title;
}

void Tutorial::setPresenter(string presenter)
{
	/*
	* Method that sets the presenter of a tutorial
	* Input: presenter - string, the new presenter of the tutorial
	* Output: -
	*/
	this->presenter = presenter;
}

void Tutorial::setDuration(string duration)
{
	/*
	* Method that sets the duration of a tutorial
	* Input: duration - string, the new duration of the tutorial
	* Output: -
	*/
	this->duration = duration;
}

void Tutorial::setLink(string link)
{
	/*
	* Method that sets the link of a tutorial
	* Input: link - string, the new link of the tutorial
	* Output: -
	*/
	this->link = link;
}

void Tutorial::setLikes(int likes)
{
	/*
	* Method that sets the number of likes of a tutorial
	* Input: likes - int, the new number of likes of the tutorial
	* Output: -
	*/
	this->likes = likes;
}

istream& operator>>(istream& in, Tutorial& tutorial)
{
	/*
	* Overloading the >> operator for the Tutorial class
	* Input: in - istream, the input stream
	* 		 tutorial - Tutorial, the tutorial to be read
	* Output: istream&, the input stream
	*/
	string title, presenter, duration, link, likesString;
	int likes = 0;
	cout << "Title: ";
	cin >> title;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Presenter: ";
	cin >> presenter;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Duration: ";
	cin >> duration;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Link: ";
	cin >> link;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (true) {
        cout << "Likes: ";
        in >> likesString;
        // Check if every character in likesString is a digit
        bool validInput = true;
        for (char c : likesString) {
            if (!isdigit(c)) {
                validInput = false;
                break;
            }
        }

        if (validInput) {
            // Convert likesString to integer if it contains only digits
            likes = stoi(likesString);
            break;
        } else {
            cout << "Invalid input. Please enter a valid integer for likes." << endl;
        }
    }
	tutorial = Tutorial(title, presenter, duration, link, likes);
	return in;
}

ostream& operator<<(ostream& out, Tutorial tutorial)
{
	/*
	* Overloading the << operator for the Tutorial class
	* Input: out - ostream, the output stream
	* 		 tutorial - Tutorial, the tutorial to be printed
	* Output: ostream&, the output stream
	*/
	out << "Title: " << tutorial.getTitle() << "| Presenter: " << tutorial.getPresenter() << "| Duration: " << tutorial.getDuration() << "| Link: " << tutorial.getLink() << "| Likes: " << tutorial.getLikes() << "\n";
	return out;
}