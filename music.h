
class CMusic:public CObject
{
public:
	CMusic();
	virtual ~CMusic();
public:
	BOOL Open(CString waveFileName);//调用一个波形文件并打开设备
	void Close();  //关闭设备
	void Stop();  //停止播放
	BOOL Play(CWnd *pwnd);//播放并向窗口发送MCI_NOTIFY消息，为了便于程序判断媒体播放结束
	//还让MCI发送一个MCI_NOTIFY命令
	void Pause();
	void Resume();
	DWORD GetLen();
	DWORD GetCuPos();
	BOOL SetPos();
protected:
	WORD m_wDeviceID;//接收MCI命令的设备标示符
	BOOL m_bOpened;//设备打开的标志
};
