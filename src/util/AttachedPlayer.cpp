#include "AttachedPlayer.h"

using namespace chatterino;

bool AttachedPlayer::getIfStreamActive()
{
    return !(mpvWindow == nullptr || mpvContainer == nullptr || !mpvContainer->isVisible());
}

void AttachedPlayer::updateStreamLinkProcess(const QString &channel, const QString &command)
{

    // Return doing nothing if the stream is already active and it is the same channel
    if(getIfStreamActive() && channel == lastShownChannel)
    {
        return;
    }

    // Create the attached window we will stream the video into
    // TODO: we should try to dock this to the application main window??
    // TODO: how to add a volumn control to this??
    if(!getIfStreamActive())
    {
        // create the window
        QWindow* mainWindow = chatterino::getApp()->windows->getMainWindow().windowHandle();
        mpvWindow = new QWindow;
        //mpvWindow = mainWindow;
        mpvContainerWID = mpvWindow->winId();
        mpvContainer = QWidget::createWindowContainer(mpvWindow);
        mpvContainer->setBackgroundRole(QPalette::Window);
        mpvContainer->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        // the size should default to near the same height as the main chat client
        float scale = 0.90;
        int height = (int)(scale*(float)mainWindow->size().height());
        int width = (int)(16.0/9.0*scale*(float)mainWindow->size().height());
        mpvContainer->setFixedSize(width,height);
        mpvContainer->show();
    }

    // Now we need to replace any window ids in the command
    // https://mpv.io/
    // https://github.com/mpv-player/mpv/blob/master/DOCS/man/options.rst
    QString commandEdited = command;
    commandEdited.replace("WID", QString::number(mpvContainerWID));

    // Now lets update our process
    if(streamlinkProcess != nullptr)
    {
        streamlinkProcess->terminate();
        streamlinkProcess->kill();
    }
    streamlinkProcess = new QProcess;
    streamlinkProcess->start(commandEdited);

    // Update the last channel we displayed
    lastShownChannel = channel;

}
