#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QPushButton>
#include <QPixmap>
#include <QPaintEvent>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPainter>
#include <QPaintEvent>


class ImageButton : public QPushButton
{
public:
    ImageButton() = default;
    ImageButton(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent *e) override;
public slots:
    void setUp();
    void setDown();
private:
    QPixmap currentButtonImage;
    QPixmap buttonDownImage;
    QPixmap buttonUpImage;
    std::unique_ptr<QMediaPlayer> player;
    std::unique_ptr<QAudioOutput> audioOutput;
    bool isDown;
};

ImageButton::ImageButton(QWidget *parent)
{
    setParent(parent);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonDownImage = QPixmap("C:\\Qt\\Projects\\HomeWork38_5_1\\button_down.png");
    buttonUpImage = QPixmap("C:\\Qt\\Projects\\HomeWork38_5_1\\button_up.png");
    currentButtonImage = buttonUpImage;
    setGeometry(currentButtonImage.rect());
    isDown = false;
    player = std::make_unique<QMediaPlayer>(parent);
    audioOutput = std::make_unique<QAudioOutput>();
    player->setAudioOutput(audioOutput.get());
    audioOutput->setVolume(50);
    player->setSource(QUrl::fromLocalFile("C:\\Qt\\Projects\\HomeWork38_5_1\\knopka.mp3"));
    connect(this, &QPushButton::clicked, this, &ImageButton::setDown);
    connect(player.get(), &QMediaPlayer::positionChanged, this, [this](qint64 pos)
    {
        //std::cout << pos << std::endl;
        if(pos >= 200) setUp();
    });
}

void ImageButton::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.drawPixmap(currentButtonImage.rect(),currentButtonImage);
}
QSize ImageButton::sizeHint() const
{
    return QSize(320,320);
}
QSize ImageButton::minimumSizeHint() const
{
    return sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent *e)
{
    setDown();
}

void ImageButton::setDown()
{
    player->stop();
    currentButtonImage = buttonDownImage;
    update();
    player->play();
}

void ImageButton::setUp()
{

    currentButtonImage = buttonUpImage;
    update();

}


#endif // IMAGEBUTTON_H
