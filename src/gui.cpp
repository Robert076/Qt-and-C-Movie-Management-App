#include "../gui.hpp"

GUI::GUI(Services &services) : services(services)
{
    buildGUI();
    populateTutorials();
    populateWatchlist();
    alertLabel = new QLabel(this);
    alertLabel->setStyleSheet("background-color: #FFD700; color: black; border: 1px solid black; padding: 4px;");
    alertLabel->setAlignment(Qt::AlignCenter);
    alertLabel->setFixedSize(200, 50);
    alertLabel->hide(); // Initially hide the ale
}

void GUI::buildGUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout{this}; // main layout for gui
    QTabWidget *mainTabWidget = new QTabWidget{};

    // Admin tab
    QWidget *adminTab = new QWidget{};

    // Admin tab layout
    QHBoxLayout *adminLayout = new QHBoxLayout{adminTab};

    QVBoxLayout *leftLayout = new QVBoxLayout{};
    QVBoxLayout *formLayout = new QVBoxLayout{};
    QVBoxLayout *buttonsLayout = new QVBoxLayout{};
    buttonsLayout->setAlignment(Qt::AlignCenter);

    QString lineEditStyleSheet = "QLineEdit {"
                                 "border-radius: 3px;"
                                 "padding: 2px 5px;"       // Add some padding for aesthetics
                                 "font-family: 'Poppins';" // Set font family
                                 "font-size: 17px;"        // Set font size
                                 "}";

    QLabel *titleLabel = new QLabel{"Name"};
    titleEdit = new QLineEdit{};
    titleEdit->setStyleSheet(lineEditStyleSheet);
    QLabel *presenterLabel = new QLabel{"Presenter"};
    presenterEdit = new QLineEdit();
    presenterEdit->setStyleSheet(lineEditStyleSheet);
    QLabel *durationLabel = new QLabel{"Duration"};
    durationEdit = new QLineEdit{};
    durationEdit->setStyleSheet(lineEditStyleSheet);
    QLabel *linkLabel = new QLabel{"Link"};
    linkEdit = new QLineEdit{"https://"};
    linkEdit->setStyleSheet(lineEditStyleSheet);
    QLabel *likesLabel = new QLabel{"Likes"};
    likesEdit = new QLineEdit{};
    likesEdit->setStyleSheet(lineEditStyleSheet);
    QLabel *oldTitleLabel = new QLabel{"Old Title (only fill this when updating a tutorial)"};
    updateOldTitleEdit = new QLineEdit{};
    updateOldTitleEdit->setStyleSheet(lineEditStyleSheet);

    titleEdit->setAlignment(Qt::AlignCenter);
    presenterEdit->setAlignment(Qt::AlignCenter);
    durationEdit->setAlignment(Qt::AlignCenter);
    linkEdit->setAlignment(Qt::AlignCenter);
    likesEdit->setAlignment(Qt::AlignCenter);
    updateOldTitleEdit->setAlignment(Qt::AlignCenter);

    formLayout->addWidget(titleLabel);
    formLayout->addWidget(titleEdit);
    formLayout->addWidget(presenterLabel);
    formLayout->addWidget(presenterEdit);
    formLayout->addWidget(durationLabel);
    formLayout->addWidget(durationEdit);
    formLayout->addWidget(linkLabel);
    formLayout->addWidget(linkEdit);
    formLayout->addWidget(likesLabel);
    formLayout->addWidget(likesEdit);
    formLayout->addWidget(oldTitleLabel);
    formLayout->addWidget(updateOldTitleEdit);

    addButton = new QPushButton{"Add"};
    addButton->setFont(QFont("Poppins", 16));
    QString addButtonStyleSheet =
        "QPushButton {"
        "background-color: #6ebc5e;" // Soft green color
        "border-radius: 3px;"        // Rounded corners
        "padding-top: 6px;"          // Padding top
        "padding-bottom: 6px;"       // Padding bottom
        "}"
        "QPushButton:hover {"
        "background-color: #88d18a;" // Lighter shade on hover
        "}";
    addButton->setStyleSheet(addButtonStyleSheet);
    // Connect addButton clicked signal to addTutorial slot
    connect(addButton, &QPushButton::clicked, this, &GUI::addTutorial);

    deleteButton = new QPushButton{"Delete"};
    deleteButton->setFont(QFont("Poppins", 16));
    QString removeButtonStyleSheet =
        "QPushButton {"
        "background-color: #D93200;" // Soft green color
        "border-radius: 3px;"        // Rounded corners
        "padding-top: 6px;"          // Padding top
        "padding-bottom: 6px;"       // Padding bottom
        "}"
        "QPushButton:hover {"
        "background-color: #FF7F50;" // Lighter shade on hover
        "}";
    deleteButton->setStyleSheet(removeButtonStyleSheet);
    // Connect deleteButton clicked signal to removeTutorial slot
    connect(deleteButton, &QPushButton::clicked, this, &GUI::removeTutorial);

    updateButton = new QPushButton{"Update"};
    updateButton->setFont(QFont("Poppins", 16));
    QString updateButtonSheet =
        "QPushButton {"
        "background-color: #4C8BF5;" // Soft green color
        "border-radius: 3px;"        // Rounded corners
        "padding-top: 6px;"          // Padding top
        "padding-bottom: 6px;"       // Padding bottom
        "}"
        "QPushButton:hover {"
        "background-color: #7AAFFF;" // Lighter shade on hover
        "}";
    updateButton->setStyleSheet(updateButtonSheet);
    // Connect updateButton clicked signal to updateTutorial slot
    connect(updateButton, &QPushButton::clicked, this, &GUI::updateTutorial);


    addButton->setMinimumWidth(400);
    addButton->setMaximumWidth(400);
    deleteButton->setMinimumWidth(400);
    deleteButton->setMaximumWidth(400);
    updateButton->setMinimumWidth(400);
    updateButton->setMaximumWidth(400);

    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(deleteButton);
    buttonsLayout->addWidget(updateButton);

    leftLayout->addLayout(formLayout);
    leftLayout->addLayout(buttonsLayout);

    adminLayout->addLayout(leftLayout);
    QVBoxLayout *rightLayout = new QVBoxLayout{};
    QLabel *adminLeftLabel = new QLabel{"Tutorials List"};
    QFont font{"Courier New", 15, 5};
    adminLeftLabel->setFont(font);
    tutorialsListWidget = new QListWidget{};
    rightLayout->addWidget(tutorialsListWidget);
    adminLayout->addLayout(rightLayout);

    mainTabWidget->addTab(adminTab, "Admin");

    // User tab layout
    QWidget *userTab = new QWidget{};
    QHBoxLayout *userLayout = new QHBoxLayout{userTab};
    watchlistWidget = new QListWidget{};
    userLayout->addWidget(watchlistWidget);

    presenterFilterEdit = new QLineEdit{};
    presenterFilterEdit->setPlaceholderText("Filter by presenter");
    presenterFilterEdit->setStyleSheet(lineEditStyleSheet);

    filterButton = new QPushButton{"Filter"};
    filterButton->setFont(QFont("Poppins", 16));
    QString filterButtonStyleSheet =
        "QPushButton {"
        "background-color: #4C8BF5;" // Soft green color
        "border-radius: 3px;"        // Rounded corners
        "padding-top: 6px;"          // Padding top
        "padding-bottom: 6px;"       // Padding bottom
        "}";
    filterButton->setStyleSheet(filterButtonStyleSheet);

    watchlistButton = new QPushButton{"See watchlist"};
    watchlistButton->setFont(QFont("Poppins", 16));
    QString watchlistButtonStyleSheet =
        "QPushButton {"
        "background-color: #4c8bf5;"
        "border-radius: 3px;"  // Rounded corners
        "padding-top: 6px;"    // Padding top
        "padding-bottom: 6px;" // Padding bottom
        "}";
    watchlistButton->setStyleSheet(watchlistButtonStyleSheet);
    connect(watchlistButton, &QPushButton::clicked, this, &GUI::seeWatchlist);

    openFileButton = new QPushButton{"Open file"};
    watchlistButton->setFont(QFont("Poppins", 16));
    QString openFileButtonStyleSheet =
        "QPushButton {"
        "background-color: #4c8bf5;"
        "border-radius: 3px;"  // Rounded corners
        "padding-top: 6px;"    // Padding top
        "padding-bottom: 6px;" // Padding bottom
        "}";
    openFileButton->setStyleSheet(openFileButtonStyleSheet);
    connect(openFileButton, &QPushButton::clicked, this, &GUI::openFile);

    chartTab = new QWidget{};
    chartLayout = new QVBoxLayout{chartTab};
    chartSeries = new QPieSeries{};
    populateChart();
    chart = new QChart{};
    chart->addSeries(chartSeries);
    chart->legend()->hide();
    chartView = new QChartView{chart};
    chartView->setRenderHint(QPainter::Antialiasing);
    chartLayout->addWidget(chartView);

    userLayout->addWidget(presenterFilterEdit);
    userLayout->addWidget(filterButton);
    userLayout->addWidget(watchlistButton);
    userLayout->addWidget(openFileButton);
    mainTabWidget->addTab(userTab, "User");
    mainTabWidget->addTab(chartTab, "Chart");

    mainLayout->addWidget(mainTabWidget);


    resize(1750, 500);

    // Connect filterButton clicked signal to filterTutorials slot
    connect(filterButton, &QPushButton::clicked, this, &GUI::filterTutorials);

    QMessageBox fileType;

    fileType.setText("File type");
    fileType.setIcon(QMessageBox::Information);

    QAbstractButton *html = fileType.addButton("html", QMessageBox::ActionRole);
    QAbstractButton *csv = fileType.addButton("csv", QMessageBox::ActionRole);

    fileType.exec();

    if (fileType.clickedButton() == html)
    {
        this->type = "h";
    }
    else
    {
        this->type = "c";
    }
}

void GUI::populateTutorials()
{
    tutorialsListWidget->clear();
    auto tutorials = services.getTutorials();
    if (tutorials.empty())
    {
        QListWidgetItem *item = new QListWidgetItem{"No tutorials available."};
        item->setFont(QFont{"Poppins", 17});
        item->setTextAlignment(Qt::AlignCenter);
        tutorialsListWidget->addItem(item);
    }
    else
    {
        for (auto tutorial : tutorials)
        {
            QListWidgetItem *item = new QListWidgetItem{QString::fromStdString(tutorial.getTitle() + "   |   " + tutorial.getPresenter() + "   |   " + tutorial.getDuration() + "   |   " + tutorial.getLink() + "   |   " + to_string(tutorial.getLikes()))};
            QFont font{"Poppins", 17};
            item->setTextAlignment(Qt::AlignCenter);
            item->setFont(font);
            tutorialsListWidget->addItem(item);
        }
    }
}

void GUI::populateWatchlist()
{
    watchlistWidget->clear();
    auto watchlist = this->services.getWatchlist();

    if (watchlist.empty())
    {
        QListWidgetItem *item = new QListWidgetItem{"No tutorials available."};
        item->setFont(QFont{"Poppins", 17});
        item->setTextAlignment(Qt::AlignCenter);
        watchlistWidget->addItem(item);
    }
    else
    {
        for (auto tutorial : watchlist)
        {
            QListWidgetItem *item = new QListWidgetItem{QString::fromStdString(tutorial.getTitle() + "   |   " + tutorial.getPresenter() + "   |   " + tutorial.getDuration() + "   |   " + tutorial.getLink() + "   |   " + to_string(tutorial.getLikes()))};
            QFont font{"Poppins", 17};
            item->setTextAlignment(Qt::AlignCenter);
            item->setFont(font);
            watchlistWidget->addItem(item);
        }
    }
}

void GUI::addTutorial()
{
    // Retrieve input from QLineEdit boxes
    string title = titleEdit->text().toStdString();
    string presenter = presenterEdit->text().toStdString();
    string duration = durationEdit->text().toStdString();
    string link = linkEdit->text().toStdString();
    int likes = likesEdit->text().toInt();

    // Call addTutorial function in services
    int result = this->services.addTutorial(title, presenter, duration, link, likes);

    if (result == 1)
    {
        titleEdit->clear();
        presenterEdit->clear();
        durationEdit->clear();
        linkEdit->clear();
        likesEdit->clear();
        linkEdit->setText("https://");
        QMessageBox messageBox;
        messageBox.information(0, "Success!", "Tutorial added successfully!");
        messageBox.setFixedSize(500, 200);
    }
    else
    {
        QMessageBox messageBox;
        messageBox.information(0, "Failed!", "Tutorial could not be added!");
        messageBox.setFixedSize(500, 200);
    }

    // Re-populate tutorials after addition
    populateTutorials();
    populateChart();
}
void GUI::showAlertMessage(const QString &message)
{
    alertLabel->setText(message);
    alertLabel->show();

    // Hide the alert message after 2 seconds
    QTimer::singleShot(2000, alertLabel, &QWidget::hide);
}

void GUI::removeTutorial()
{
    // Retrieve input from QLineEdit boxes
    string title = titleEdit->text().toStdString();

    // Call removeTutorial function in services
    int result = this->services.removeTutorial(title);

    if (result == 1)
    {
        titleEdit->clear();
        presenterEdit->clear();
        durationEdit->clear();
        linkEdit->clear();
        likesEdit->clear();
        linkEdit->setText("https://");
        showAlertMessage("Tutorial removed successfully!");
    }
    else
    {
        showAlertMessage("Failed to remove tutorial.");
    }

    // Re-populate tutorials after removal
    populateTutorials();
    populateChart();
}

void GUI::updateTutorial()
{
    // Retrieve input from QLineEdit boxes
    string oldTitle = updateOldTitleEdit->text().toStdString();
    string title = titleEdit->text().toStdString();
    string presenter = presenterEdit->text().toStdString();
    string duration = durationEdit->text().toStdString();
    string link = linkEdit->text().toStdString();
    int likes = likesEdit->text().toInt();

    // Call updateTutorial function in services
    int result = this->services.updateTutorial(oldTitle, title, presenter, duration, link, likes);

    if (result == 1)
    {
        updateOldTitleEdit->clear();
        titleEdit->clear();
        presenterEdit->clear();
        durationEdit->clear();
        linkEdit->clear();
        likesEdit->clear();
        linkEdit->setText("https://");
        showAlertMessage("Tutorial updated successfully!");
    }
    else
    {
        showAlertMessage("Failed to update tutorial.");
    }

    // Re-populate tutorials after update
    populateTutorials();
    populateChart();
}

void GUI::filterTutorials()
{
    // Retrieve presenter filter from QLineEdit box
    string presenter = presenterFilterEdit->text().toStdString();
    vector<Tutorial> filteredTutorials = services.getTutorialsByPresenter(presenter);

    if (filteredTutorials.empty())
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "No tutorials available.");
        messageBox.setFixedSize(500, 200);
    }
    else
    {
        for (auto &tutorial : filteredTutorials)
        {
            QMessageBox messageBox;
            QString tutorialInfo = QString::fromStdString(
                tutorial.getTitle() + "\nPresenter: " +
                tutorial.getPresenter() + "\nDuration: " +
                tutorial.getDuration() + "\nLink: " +
                tutorial.getLink() + "\nLikes: " +
                std::to_string(tutorial.getLikes()));

            messageBox.setText(tutorialInfo);
            messageBox.setWindowTitle("Filtered Tutorial");
            messageBox.setIcon(QMessageBox::Information);

            QAbstractButton *skipButton = messageBox.addButton("Skip", QMessageBox::ActionRole);
            QAbstractButton *addButton = messageBox.addButton("Add to watchlist", QMessageBox::ActionRole);

            messageBox.exec();

            if (messageBox.clickedButton() == addButton)
            {
                services.addToWatchlist(tutorial, "h"); // Assuming there is an addToWatchlist method in the services
                populateWatchlist();
            }
            else if (messageBox.clickedButton() == skipButton)
            {
                // Do nothing, just skip to the next tutorial
            }
            populateWatchlist();
        }
        while (true)
        {
            QMessageBox messageBox2;
            messageBox2.setText("Do you want to see the list again?");
            messageBox2.setWindowTitle("See again");
            messageBox2.setIcon(QMessageBox::Information);

            QAbstractButton *yesButton = messageBox2.addButton("Yes", QMessageBox::ActionRole);
            QAbstractButton *noButton = messageBox2.addButton("No", QMessageBox::ActionRole);

            filteredTutorials = this->services.getTutorialsByPresenter(presenter);
            messageBox2.exec();
            if (messageBox2.clickedButton() == yesButton)
            {
                for (auto &tutorial : filteredTutorials)
                {
                    QMessageBox messageBox;
                    QString tutorialInfo = QString::fromStdString(
                        tutorial.getTitle() + "\nPresenter: " +
                        tutorial.getPresenter() + "\nDuration: " +
                        tutorial.getDuration() + "\nLink: " +
                        tutorial.getLink() + "\nLikes: " +
                        std::to_string(tutorial.getLikes()));

                    messageBox.setText(tutorialInfo);
                    messageBox.setWindowTitle("Filtered Tutorial");
                    messageBox.setIcon(QMessageBox::Information);

                    QAbstractButton *skipButton = messageBox.addButton("Skip", QMessageBox::ActionRole);
                    QAbstractButton *addButton = messageBox.addButton("Add to watchlist", QMessageBox::ActionRole);

                    messageBox.exec();

                    if (messageBox.clickedButton() == addButton)
                    {
                        services.addToWatchlist(tutorial, "h"); // Assuming there is an addToWatchlist method in the services
                        populateWatchlist();
                    }
                    else if (messageBox.clickedButton() == skipButton)
                    {
                        // Do nothing, just skip to the next tutorial
                    }
                    populateWatchlist();
                }
            }
            else
                break;
        }
    }
}

void GUI::seeWatchlist()
{
    populateWatchlist();
    // display them one by one from the watchlist JUST LIKE IN THE FILTER METHOD
    // make a button with LIKE and one with DISLIKE if they press ANY OF THEM IT IS REMOVED NOTHING ELSE
    QMessageBox messageBox;
    vector<Tutorial> watchlist = this->services.getWatchlist();

    if (watchlist.empty())
    {
        messageBox.critical(0, "Error", "No tutorials available in the watchlist.");
        messageBox.setFixedSize(500, 200);
    }
    else
    {
        int cnt = 0;
        for (auto &tutorial : watchlist)
        {
            QString tutorialInfo = QString::fromStdString(
                tutorial.getTitle() + "\nPresenter: " +
                tutorial.getPresenter() + "\nDuration: " +
                tutorial.getDuration() + "\nLink: " +
                tutorial.getLink() + "\nLikes: " +
                std::to_string(tutorial.getLikes()));

            messageBox.setText(tutorialInfo);
            messageBox.setWindowTitle("Watchlist Tutorial");
            messageBox.setIcon(QMessageBox::Information);
            QAbstractButton *skipButton = messageBox.addButton("Skip", QMessageBox::ActionRole);
            QAbstractButton *dislikeButton = messageBox.addButton("Dislike and remove", QMessageBox::ActionRole);
            QAbstractButton *likeButton = messageBox.addButton("Like and remove", QMessageBox::ActionRole);

            messageBox.exec();

            if (messageBox.clickedButton() == likeButton)
            {
                services.removeFromWatchlist(tutorial.getTitle());
                this->services.updateTutorial(tutorial.getTitle(), tutorial.getTitle(), tutorial.getPresenter(), tutorial.getDuration(), tutorial.getLink(), tutorial.getLikes() + 1);
                populateWatchlist();
                populateTutorials();
            }
            else if (messageBox.clickedButton() == dislikeButton)
            {
                services.removeFromWatchlist(tutorial.getTitle());
                populateWatchlist();
            }
            else if (messageBox.clickedButton() == skipButton)
            {
                // Do nothing, just skip to the next tutorial
            }
            // delete the buttons
            messageBox.removeButton(likeButton);
            messageBox.removeButton(dislikeButton);
            messageBox.removeButton(skipButton);
        }
    }
}

void GUI::openFile()
{
    if (type == "h")
        system("open watchlist.html");
    else
        system("open watchlist.csv");
}


void GUI::openChart()
{
    // create new window
    QWidget *chartWindow = new QWidget{};
    QVBoxLayout *chartLayout = new QVBoxLayout{chartWindow};

    // make pillar chart
    map<string, int> chartData;
    vector<Tutorial> tutorials = services.getTutorials();
    for (auto tutorial : tutorials)
    {
        chartData[tutorial.getPresenter()] += tutorial.getLikes();
    }
    

}



void GUI::populateChart()
{
    chartSeries->clear();
    vector<Tutorial> sortedTutorials = services.getTutorials();
    for (int i = 0; i < sortedTutorials.size(); i++)
    {
        for (int j = i + 1; j < sortedTutorials.size(); j++)
        {
            if (sortedTutorials[i].getLikes() < sortedTutorials[j].getLikes())
            {
                Tutorial aux = sortedTutorials[i];
                sortedTutorials[i] = sortedTutorials[j];
                sortedTutorials[j] = aux;
            }
        }
    }
    for(auto tutorial : sortedTutorials)
    {
        chartSeries->append(QString::fromStdString(tutorial.getTitle()), tutorial.getLikes());
    }
    int colorIndex = 0;
    for(auto slice : chartSeries->slices())
    {
        slice->setExploded();
        slice->setLabel(slice->label() + " " + QString::number(slice->percentage() * 100, 'f', 1) + "%");
        slice->setLabelVisible();
        slice->setBrush(colors.at(colorIndex++ % colors.size()));
    }
}