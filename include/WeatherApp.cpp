#include "WeatherApp.h"
#include "obj.h"

#include <iostream>
#include <QGraphicsOpacityEffect>
#include <QFontDatabase>
#include <QMovie>
#include <QHeaderView>
#include <QThread>

using namespace std;


WeatherApp::WeatherApp(QWidget *parent)
        : QDialog(parent)
{
    setupUi(this);
    setupAnimation();

    int fontId = QFontDatabase::addApplicationFont("../resources/fonts/minecraft.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    font = new QFont(fontFamily);
    setupFonts(this);

    WeatherManager::SetMaxDays(max_days);

    std::ifstream f("../resources/config.json");
    nlohmann::json data = nlohmann::json::parse(f);

    std::vector<std::string> day_parts = data["day_parts"].get<std::vector<std::string>>();
    std::vector<std::string> weekday_names = data["weekday_names"].get<std::vector<std::string>>();
    std::vector<std::string> month_names = data["month_names"].get<std::vector<std::string>>();
    Day::SetMessages(day_parts, weekday_names, month_names);

    WeatherInfo::SetWeatherNames(data["weather_names"].get<std::vector<std::string>>());

    for (int i = 0; i < max_days; ++i) {
        createTable();
    }

    std::vector<std::string> cities_ = data["cities"].get<std::vector<std::string>>();
    cities.reserve(cities_.size());

    for (auto& city : cities_) {
        auto* cur = new WeatherManager(city);
        cur->Request();

        if (cur->status() == RequestStatus::NetworkError) {
            this->close();
        } else if (cur->status() == RequestStatus::Success) {
            cities.push_back(cur);
        } else {
            delete cur;
        }
    }

    iter_cities = cities.cbegin();
    cur_city->setText((*iter_cities)->city().c_str());

    ShowInfo();
}

void WeatherApp::ShowInfo() const {
    std::vector<std::string> info = (*iter_cities)->now().GetString(ColorMode::HTML);
    QString str = QString(format_info_str).arg(info[0].c_str()).arg(info[1].c_str())
            .arg(info[2].c_str()).arg(info[3].c_str()).arg(info[4].c_str());

    cur_info->setText(str);

    auto iter_days = (*iter_cities)->GetDayList().cbegin();

    for (QFrame* day : main_frame->findChildren<QFrame*>("day")) {
        day->findChild<QLabel*>("date")->setText(iter_days->GetStrDate().c_str());
        auto cur_info = iter_days->GetParts().cbegin();

        for (QFrame* day_part : day->findChildren<QFrame*>("day_part")) {
            info = (*cur_info)->GetString(ColorMode::HTML);
            str = QString(format_info_str).arg(info[0].c_str()).arg(info[1].c_str())
                    .arg(info[2].c_str()).arg(info[3].c_str()).arg(info[4].c_str());

            day_part->findChild<QLabel*>("info")->setText(str);
            ++cur_info;
        }

        ++iter_days;
    }
}

WeatherApp::~WeatherApp() = default;

void WeatherApp::on_pushBack_clicked() {
    if (browsing_right_->state() == QParallelAnimationGroup::Running ||
        browsing_left_->state() == QParallelAnimationGroup::Running  ||
        fade_->state() == QParallelAnimationGroup::Running) {
        return;
    }

    if (++iter_cities == cities.cend()) {
        iter_cities = cities.cbegin();
    }
    left_city->setText((*iter_cities)->city().c_str());

    browsing_right_->start();
    fade_->start();
}

void WeatherApp::on_pushFront_clicked() {
    if (browsing_right_->state() == QParallelAnimationGroup::Running ||
        browsing_left_->state() == QParallelAnimationGroup::Running  ||
        fade_->state() == QParallelAnimationGroup::Running) {
        return;
    }

    if (iter_cities == cities.cbegin()) {
        iter_cities = cities.cend();
    }
    --iter_cities;

    right_city->setText((*iter_cities)->city().c_str());
    browsing_left_->start();
    fade_->start();
}

void WeatherApp::setupAnimation() {
    browsing_left_ = new QParallelAnimationGroup(this);

    auto* effect_right = new QGraphicsOpacityEffect(right_city);
    effect_right->setOpacity(0.0);
    right_city->setGraphicsEffect(effect_right);

    auto* right_opacity = new QPropertyAnimation(effect_right, "opacity");
    right_opacity->setDuration(700);
    right_opacity->setStartValue(0.0);
    right_opacity->setEndValue(1.0);
    browsing_left_->addAnimation(right_opacity);

    auto* right_pos = new QPropertyAnimation(right_city, "pos");
    right_pos->setDuration(700);
    right_pos->setStartValue(QPoint(right_city->pos().x(), right_city->pos().y()));
    right_pos->setEndValue(QPoint(cur_city->pos().x(), cur_city->pos().y()));
    browsing_left_->addAnimation(right_pos);


    auto* effect_center = new QGraphicsOpacityEffect(cur_city);
    effect_center->setOpacity(1.0);
    cur_city->setGraphicsEffect(effect_center);

    auto* center_opacity = new QPropertyAnimation(effect_center, "opacity");
    center_opacity->setDuration(700);
    center_opacity->setStartValue(1.0);
    center_opacity->setEndValue(0.0);
    browsing_left_->addAnimation(center_opacity);

    auto* center_pos = new QPropertyAnimation(cur_city, "pos");
    center_pos->setDuration(700);
    center_pos->setStartValue(QPoint(cur_city->pos().x(), cur_city->pos().y()));
    center_pos->setEndValue(QPoint(left_city->pos().x(), left_city->pos().y()));
    browsing_left_->addAnimation(center_pos);

    connect(browsing_left_, &QParallelAnimationGroup::finished, [=, this]() {
        cur_city->setText((*iter_cities)->city().c_str());

        cur_city->move(center_pos->startValue().toPoint().x(), center_pos->startValue().toPoint().y());
        right_city->move(right_pos->startValue().toPoint().x(), right_pos->startValue().toPoint().y());

        effect_right->setOpacity(0.0);
        effect_center->setOpacity(1.0);
    });


    browsing_right_ = new QParallelAnimationGroup(this);

    auto* effect_left = new QGraphicsOpacityEffect(left_city);
    effect_left->setOpacity(0.0);
    left_city->setGraphicsEffect(effect_left);

    auto* left_opacity = new QPropertyAnimation(effect_left, "opacity");
    left_opacity->setDuration(700);
    left_opacity->setStartValue(0.0);
    left_opacity->setEndValue(1.0);
    browsing_right_->addAnimation(left_opacity);

    auto* left_pos = new QPropertyAnimation(left_city, "pos");
    left_pos->setDuration(700);
    left_pos->setStartValue(QPoint(left_city->pos().x(), left_city->pos().y()));
    left_pos->setEndValue(QPoint(cur_city->pos().x(), cur_city->pos().y()));
    browsing_right_->addAnimation(left_pos);

    center_opacity = new QPropertyAnimation(effect_center, "opacity");
    center_opacity->setDuration(700);
    center_opacity->setStartValue(1.0);
    center_opacity->setEndValue(0.0);
    browsing_right_->addAnimation(center_opacity);

    center_pos = new QPropertyAnimation(cur_city, "pos");
    center_pos->setDuration(700);
    center_pos->setStartValue(QPoint(cur_city->pos().x(), cur_city->pos().y()));
    center_pos->setEndValue(QPoint(right_city->pos().x(), right_city->pos().y()));
    browsing_right_->addAnimation(center_pos);

    connect(browsing_right_, &QParallelAnimationGroup::finished, [=, this]() {
        cur_city->setText((*iter_cities)->city().c_str());

        cur_city->move(center_pos->startValue().toPoint().x(), center_pos->startValue().toPoint().y());
        left_city->move(left_pos->startValue().toPoint().x(), left_pos->startValue().toPoint().y());

        effect_left->setOpacity(0.0);
        effect_center->setOpacity(1.0);
    });

    fade_ = new QParallelAnimationGroup(this);

    auto* effect_main = new QGraphicsOpacityEffect();
    effect_main->setOpacity(1.0);
    scrollAreaWidgetContents->setGraphicsEffect(effect_main);

    auto* main_opacity_out = new QPropertyAnimation(effect_main, "opacity");
    main_opacity_out->setDuration(350);
    main_opacity_out->setStartValue(1.0);
    main_opacity_out->setEndValue(0.0);
    fade_->addAnimation(main_opacity_out);

    auto* main_opacity_in = new QPropertyAnimation(effect_main, "opacity");
    main_opacity_in->setDuration(350);
    main_opacity_in->setStartValue(0.0);
    main_opacity_in->setEndValue(1.0);

    connect(main_opacity_out, &QParallelAnimationGroup::finished, [=, this]() {
        ShowInfo();
        main_opacity_in->start();
    });
}

void WeatherApp::setupFonts(QObject* object) {
    QList<QLabel*> labelList = object->findChildren<QLabel*>();

    for (QLabel* label : labelList) {
        font->setPointSize(label->font().pointSize());
        label->setFont(*font);
    }
}

void WeatherApp::createTable() {
    auto* last_child = dynamic_cast<QWidget*>(main_frame->children().back());

    auto* day_frame = new QFrame(main_frame);
    day_frame->setObjectName("day");
    day_frame->setFixedSize(main_frame->width() - 15, 190);

    auto* day_label = new QLabel(day_frame);
    day_label->setObjectName("date");
    day_label->setGeometry(QRect(0, 0, day_frame->width(), 20));
    day_label->setAlignment(Qt::AlignCenter);

    font->setPointSize(16);
    day_label->setFont(*font);

    auto* tableWidget = new QTableWidget(1, 4, day_frame);
    tableWidget->move(0, 25);

    QStringList horizontalHeaders;
    horizontalHeaders << Day::time_parts[0].c_str() << Day::time_parts[1].c_str()
                      << Day::time_parts[2].c_str() << Day::time_parts[3].c_str();

    tableWidget->setHorizontalHeaderLabels(horizontalHeaders);

    tableWidget->setFixedSize(main_frame->width() - 15, 165);

    tableWidget->horizontalHeader()->setDefaultSectionSize(main_frame->width() / 4 - 5);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tableWidget->horizontalHeader()->setStyleSheet(QString("QHeaderView::section { font-family: %1; font-size: %2pt; font-weight: %3; }")
                                  .arg(font->family())
                                  .arg(font->pointSize())
                                  .arg(font->weight()));

    day_frame->move(0, last_child->y() + last_child->height() + 30);
    main_frame->setFixedHeight(last_child->y() + last_child->height() + day_frame->height() + 30);

    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectColumns);
    tableWidget->setTextElideMode(Qt::ElideMiddle);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->verticalHeader()->setStretchLastSection(true);

    tableWidget->setCellWidget(0, 0, getFrame(day_frame));
    tableWidget->setCellWidget(0, 1, getFrame(day_frame));
    tableWidget->setCellWidget(0, 2, getFrame(day_frame));
    tableWidget->setCellWidget(0, 3, getFrame(day_frame));

    tableWidget->setStyleSheet("QTableWidget {"
                               "    border: 1px solid gray;"
                               "}"
                               "QHeaderView::section {"
                               "    padding: 3px 0 3px 0;"
                               "    border: 1px solid gray;"
                               "}"
                               "QTableWidget::item {"
                               "    border: 2px solid gray;"
                               "}"
                               "QTableWidget::item:selected {"
                               "    background-color: gray;"
                               "}");
}

QFrame* WeatherApp::getFrame(QWidget* parent) {
    font->setPointSize(12);

    auto* day_part = new QFrame(parent);
    day_part->setObjectName("day_part");
    day_part->setFixedSize(main_frame->width() / 4 - 5, 145);

    day_part->setFrameShape(QFrame::StyledPanel);
    day_part->setFrameShadow(QFrame::Raised);

    auto* image = new QLabel(day_part);
    image->setObjectName("image");
    image->setGeometry(QRect(15, 20, 111, 71));
    image->setFrameShape(QFrame::NoFrame);
    image->setFrameShadow(QFrame::Plain);
    image->setPixmap(QPixmap(QString::fromUtf8("../resources/images/cloud.png")));
    image->setScaledContents(true);

    auto* info = new QLabel(day_part);
    info->setObjectName("info");
    info->setGeometry(QRect(90, 0, 221, 111));

    info->setFont(*font);
    info->setContextMenuPolicy(Qt::ActionsContextMenu);
    info->setLineWidth(1);
    info->setMidLineWidth(0);
    info->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    info->setWordWrap(false);
    info->setOpenExternalLinks(false);
    image->raise();

    image->setText(QString());
    info->setText(QCoreApplication::translate("Weather", "<html><head/><body>"
                                                               "<p style=\"line-height: 20px\">\320\247\320\270\321\201\321\202\320\276\320\265 \320\275\320\265\320\261\320\276<br/><span style=\" color:#00aa00;\">+9</span>(<span style=\" color:#0000ff;\">0</span>) \302\260C<br/>\342\206\222 <span style=\" color:#00aa00;\">3</span>-<span style=\" color:#00aa00;\">5</span> \320\274/\321\201<br/><span style=\" color:#ffff00;\">772</span> \320\274\320\274.\321\200\321\202.\321\201\321\202<br/>0.0 mm | 0% </p>"
                                                               "</body></html>", nullptr));

    day_part->setStyleSheet("background-color: none;"
                            "border: none");

    return day_part;
}
