#include "debug_log.h"

void DebugLog::RecordLog()
{
	//if (IsDebuggerPresent()) {
	//	return;
	//}
	qInstallMessageHandler(Log);  //��װ��Ϣ������
}

void DebugLog::Log(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	QDir projectDir(QDir::currentPath());   //��ǰ����Ŀ¼��
	const QString logDir = "log";
	if (!projectDir.exists(logDir)) {
		projectDir.mkdir(logDir);
	}
	projectDir.cd(logDir);      //�л�����־Ŀ¼��
	QString logPath = projectDir.filePath(QDate::currentDate().toString("yyyy-MM-dd") + ".txt");

	QFile logFile(logPath);     //������־�ļ�
	if (!logFile.open(QFile::Append | QFile::WriteOnly)) {
		qInstallMessageHandler(0);  //�ָ���Ϣ�������
		qDebug("ERROR OPEN LOG FILE");
		return;
	}

	QString tp = nullptr;
	switch (type) {
	case QtDebugMsg:
		tp = "Debug";
		break;
	case QtInfoMsg:
		tp = "Info";
		break;
	case QtWarningMsg:
		tp = "Warning";
		break;
	case QtCriticalMsg:
		tp = "Critical";
		break;
	case QtFatalMsg:
		tp = "Fatal";
		break;
	default:
		break;
	}

	QString logLine = QString("%1%2    %3:%4:%5:%6    %7%8\r").arg("Time::").arg(QTime::currentTime().toString("hh:mm:ss"))
		.arg(tp).arg(context.file).arg(context.line).arg(context.function).arg("Log::").arg(msg);
	logFile.write(logLine.toUtf8());
	OutputDebugStringA(msg.toLocal8Bit());
}