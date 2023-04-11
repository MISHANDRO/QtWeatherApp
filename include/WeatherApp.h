#pragma once

#include "Ui_Wether.h"
#include "WeatherManager.h"

#include <QDialog>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QTableWidget>
#include <QFuture>

class WeatherApp : public QDialog, public Ui::Weather {
Q_OBJECT

public:
    explicit WeatherApp(QWidget *parent = nullptr);
    ~WeatherApp() override;

    void ShowInfo();

signals:
   void startLoading();
   void finishLoading();

   void startFadeIn();
   void errorSignal();

private slots:
    void on_pushFront_clicked();
    void on_pushBack_clicked();

private:
    [[nodiscard]] bool SwitchRunning() const;
    void SetImage(QLabel* image, uint16_t weather_code);


    void setupAnimation();
    void setupFonts(QObject* object);

    void CreateDayFrame();
    QFrame* getFrame(QWidget* parent = nullptr);

    QParallelAnimationGroup* browsing_right_;
    QParallelAnimationGroup* browsing_left_;
    QPropertyAnimation* switch_city_;
    bool replace_info_running_;

    QFont* font;

    std::vector<WeatherManager*> cities;
    std::vector<WeatherManager*>::const_iterator iter_cities;

    std::vector<QFrame*> days;

    QString format_info_str = "<html><head/><body>"
                              "<p style=\"line-height: 20px\">%1<br/>%2<br/>%3<br/>%4<br/>%5</p>"
                              "</body></html>";

    const uint16_t kMaxDays = 7;
    QString error_weather;
    QString error_city;
    QString error_network;
};
