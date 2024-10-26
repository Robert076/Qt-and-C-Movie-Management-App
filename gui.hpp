#pragma once
#include "services.hpp"
#include <QApplication>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QTableWidget>
#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include <QTimer>


class GUI : public QWidget
{
private:
    Services& services;
    QListWidget* tutorialsListWidget;
    QLineEdit* titleEdit;
    QLineEdit* presenterEdit;
    QLineEdit* durationEdit;
    QLineEdit* linkEdit;
    QLineEdit* likesEdit;
    QLineEdit* updateOldTitleEdit;

    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;

    QListWidget* watchlistWidget;
    QLabel* alertLabel;

    QLineEdit* presenterFilterEdit;
    QPushButton* filterButton;
    QPushButton* watchlistButton;
    QPushButton* openFileButton;
    QWidget* chartTab;
    QChart* chart;
    QChartView* chartView;
    QVBoxLayout* chartLayout;
    QPieSeries* chartSeries;
    QList<QColor> colors = {Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan, Qt::magenta, Qt::gray, Qt::darkRed, Qt::darkGreen, Qt::darkBlue, Qt::darkYellow, Qt::darkCyan, Qt::darkMagenta};
    string type;

    void buildGUI();
    void populateTutorials();
    void populateWatchlist();
    void populateChart();
    void showAlertMessage(const QString& message);
public:
    GUI(Services& services);
public slots:
    void addTutorial();
    void removeTutorial();
    void updateTutorial();
    void filterTutorials();
    void seeWatchlist();
    void openFile();
    void openChart();
};