#pragma once

#include "obj.h"
#include "WeatherManager.h"

#include <QDialog>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QTableWidget>

class WeatherApp : public QDialog, public Ui::Weather {
Q_OBJECT

public:
    explicit WeatherApp(QWidget *parent = nullptr);
    ~WeatherApp() override;

    void ShowInfo() const;

private slots:
    void on_pushFront_clicked();
    void on_pushBack_clicked();

private:
    void setupAnimation();
    void setupFonts(QObject* object);

    void createTable();
    QFrame* getFrame(QWidget* parent = nullptr);

    QParallelAnimationGroup* browsing_right_;
    QParallelAnimationGroup* browsing_left_;
    QParallelAnimationGroup* fade_;

    QFont* font;

    std::vector<WeatherManager*> cities;
    std::vector<WeatherManager*>::const_iterator iter_cities;

    std::vector<QFrame*> days;

    QString format_info_str = "<html><head/><body>"
                              "<p style=\"line-height: 20px\">%1<br/>%2<br/>%3<br/>%4<br/>%5</p>"
                              "</body></html>";

    const uint16_t max_days = 7;
};
