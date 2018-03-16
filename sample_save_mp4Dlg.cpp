/******************************************************
 * 浩一科技，提供云录播、云监控的全平台无插件解决方案。
 * 支持按需直播，多点布控，分布式海量存储，动态扩容；
 * 支持微信扫码登录，全平台帐号统一，关联微信小程序；
 * 支持多种数据输入：摄像头IPC、rtmp、rtsp、MP4文件；
 * 支持全实时、全动态、全网页管理，网页前后台兼容IE8；
 * 支持多终端无插件自适应播放，flvjs/hls/rtmp自动适配；
 ******************************************************
 * 官方网站 => https://myhaoyi.com
 * 技术博客 => http://blog.csdn.net/haoyitech
 * 开源代码 => https://github.com/HaoYiTech/
 * 云监控群 => 483663026（QQ群）
 * 云录播群 => 630379661（QQ群）
 ******************************************************
 * VS2010自动生成的对话框类实现代码
 ******************************************************/

#include "stdafx.h"
#include "sample_save_mp4.h"
#include "sample_save_mp4Dlg.h"
#include "afxdialogex.h"

#include "UtilTool.h"
#include "ReadSPS.h"

#define VIDEO_TIME_SCALE		90000		// 视频时间刻度，刻度越大好像越精确???

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

Csample_save_mp4Dlg::Csample_save_mp4Dlg(CWnd* pParent /*=NULL*/)
  : CDialogEx(Csample_save_mp4Dlg::IDD, pParent)
{
	m_lpRecMP4 = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Csample_save_mp4Dlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_HOME_WEBSITE, m_ctrlHome);
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Csample_save_mp4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &Csample_save_mp4Dlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()

// Csample_save_mp4Dlg 消息处理程序
BOOL Csample_save_mp4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 设置访问连接地址...
	m_ctrlHome.SetUnderline(TRUE);
	m_ctrlHome.SetURL("https://myhaoyi.com");
	m_ctrlHome.SetWindowText("联系我们 => https://myhaoyi.com");
	m_ctrlHome.SetLinkCursor(CUtilTool::GetSysHandCursor());
	m_ctrlHome.SetAutoSize();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Csample_save_mp4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Csample_save_mp4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR Csample_save_mp4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void myMP4LogCallback( MP4LogLevel loglevel, const char* fmt, va_list ap)
{
	// 组合传递过来的格式...
	CString	strDebug;
	strDebug.FormatV(fmt, ap);
	if( (strDebug.ReverseFind('\r') < 0) && (strDebug.ReverseFind('\n') < 0) ) {
		strDebug.Append("\r\n");
	}
	// 进行格式转换，并打印出来...
	string strANSI = CUtilTool::UTF8_ANSI(strDebug);
	TRACE(strANSI.c_str());
}

// 解析mp4文件并另存...
void Csample_save_mp4Dlg::OnBnClickedButtonSave()
{
	// 设置MP4调试级别 => 最高最详细级别...
	//MP4LogLevel theLevel = MP4LogGetLevel();
	//MP4LogSetLevel(MP4_LOG_VERBOSE4);
	//MP4SetLogCallback(myMP4LogCallback);
	// 打开MP4文件...
	CString strMP4File, strRecName;
	string  strExePath = CUtilTool::GetExePath((HINSTANCE)NULL);
	MP4FileHandle hMP4Handle = MP4_INVALID_FILE_HANDLE;
	strMP4File.Format("%s\\sample.mp4", strExePath.c_str());
	strRecName.Format("%s\\record.mp4", strExePath.c_str());
	m_strUTF8Rec = CUtilTool::ANSI_UTF8(strRecName);
	string strUTF8 = CUtilTool::ANSI_UTF8(strMP4File);
	hMP4Handle = MP4Read( strUTF8.c_str() );

	// 打印MP4文件全路径...
	TRACE("=== %s ===\n", strUTF8.c_str());

	do {
		// 创建LibMP4录像对象...
		m_lpRecMP4 = new LibMP4();
		ASSERT( m_lpRecMP4 != NULL );
		// 如果打开文件失败，直接跳出...
		if( hMP4Handle == MP4_INVALID_FILE_HANDLE ) {
			TRACE("=== 打开MP4文件失败 ===\n");
			break;
		}
		// 解析MP4文件里面的音视频格式头...
		if( !this->doMP4ParseAV(hMP4Handle) ) {
			TRACE("=== 解析MP4格式头失败 ===\n");
			break;
		}
		// 打印最终的录制信息...
		if( m_lpRecMP4 != NULL ) {
			// 这里需要记录已录制文件大小和已录制秒数...
			DWORD dwWriteSize = m_lpRecMP4->GetWriteSize();
			DWORD dwWriteSec = m_lpRecMP4->GetWriteSec();
			TRACE("=== 已录制文件长度：%lu 字节 ===\n", dwWriteSize);
			TRACE("=== 已录制文件时长：%lu 秒 ===\n", dwWriteSec);
		}
	} while( false );
	// 释放MP4句柄...
	if( hMP4Handle != MP4_INVALID_FILE_HANDLE ) {
		MP4Close(hMP4Handle);
		hMP4Handle = MP4_INVALID_FILE_HANDLE;
		TRACE("=== 关闭MP4文件成功 ===\n");
	}
	// 释放LibMP4对象...
	if( m_lpRecMP4 != NULL ) {
		delete m_lpRecMP4;
		m_lpRecMP4 = NULL;
	}
}

// 解析MP4里面的音视频数据帧...
bool Csample_save_mp4Dlg::doMP4ParseAV(MP4FileHandle inFile)
{
	if( inFile == MP4_INVALID_FILE_HANDLE )
		return false;
	ASSERT( inFile != MP4_INVALID_FILE_HANDLE );
	
	// 首先获取文件的每秒刻度数和总刻度数(不是毫秒数)...
	uint32_t dwFileScale = MP4GetTimeScale(inFile);
	MP4Duration theDuration = MP4GetDuration(inFile);
	TRACE("=== 文件每秒刻度数：%lu ===\n", dwFileScale);
	TRACE("=== 文件总刻度数：%lu ===\n", theDuration);
	// 总毫秒数 = 总刻度数*1000/每秒刻度数 => 先乘法可以降低误差...
	uint32_t		dwMP4Duration = theDuration*1000/dwFileScale;
	TRACE("=== 总毫秒数 = 文件总刻度数*1000/文件每秒刻度数 => %lu ===\n", dwMP4Duration);
	MP4TrackId		tidVideo = MP4_INVALID_TRACK_ID;	// 视频轨道编号
	MP4TrackId		tidAudio = MP4_INVALID_TRACK_ID;	// 音频轨道编号
	string			strSPS, strPPS, strAES;
	int				audio_rate_index = 0;
	int				audio_channel_num = 0;
	int				audio_type = 0;
	uint32_t		audio_time_scale = 0;
	uint32_t		video_time_scale = 0;
	// 获取需要的相关信息...
    uint32_t trackCount = MP4GetNumberOfTracks( inFile );
	TRACE("=== 发现轨道数：%lu ===\n", trackCount);
    for( uint32_t i = 0; i < trackCount; ++i ) {
		MP4TrackId  id = MP4FindTrackId( inFile, i );
		const char* type = MP4GetTrackType( inFile, id );
		if( MP4_IS_VIDEO_TRACK_TYPE( type ) ) {
			// 视频已经有效，检测下一个...
			if( tidVideo > 0 )
				continue;
			// 获取视频信息...
			tidVideo = id;
			TRACE("=== 视频轨道号：%d，标识：%s ===\n", tidVideo, type);
			char * lpVideoInfo = MP4Info(inFile, id);
			TRACE("视频信息：%s \n", lpVideoInfo);
			free(lpVideoInfo);
			// 获取视频时间间隔...
			video_time_scale = MP4GetTrackTimeScale(inFile, id);
			TRACE("=== 视频每秒刻度数：%lu ===\n", video_time_scale);
			const char * video_name = MP4GetTrackMediaDataName(inFile, id);
			TRACE("=== 视频编码：%s ===\n", video_name);
			// 获取视频的PPS/SPS信息...
			uint8_t  ** spsHeader = NULL;
			uint8_t  ** ppsHeader = NULL;
			uint32_t  * spsSize = NULL;
			uint32_t  * ppsSize = NULL;
			uint32_t    ix = 0;
			bool bResult = MP4GetTrackH264SeqPictHeaders(inFile, id, &spsHeader, &spsSize, &ppsHeader, &ppsSize);
			for(ix = 0; spsSize[ix] != 0; ++ix) {
				// SPS指针和长度...
				uint8_t * lpSPS = spsHeader[ix];
				uint32_t  nSize = spsSize[ix];
				// 只存储第一个SPS信息...
				if( strSPS.size() <= 0 && nSize > 0 ) {
					strSPS.assign((char*)lpSPS, nSize);
				}
				free(spsHeader[ix]);
				TRACE("=== 找到第 %d 个SPS格式头，长度：%lu ===\n", ix+1, nSize);
			}
			free(spsHeader);
			free(spsSize);
			for(ix = 0; ppsSize[ix] != 0; ++ix) {
				// PPS指针和长度...
				uint8_t * lpPPS = ppsHeader[ix];
				uint32_t  nSize = ppsSize[ix];
				// 只存储第一个PPS信息...
				if( strPPS.size() <= 0 && nSize > 0 ) {
					strPPS.assign((char*)lpPPS, nSize);
				}
				free(ppsHeader[ix]);
				TRACE("=== 找到第 %d 个PPS格式头，长度：%lu ===\n", ix+1, nSize);
			}
			free(ppsHeader);
			free(ppsSize);
		} else if( MP4_IS_AUDIO_TRACK_TYPE( type ) ) {
			// 音频已经有效，检测下一个...
			if( tidAudio > 0 )
				continue;
			// 获取音频信息...
			tidAudio = id;
			TRACE("=== 音频轨道号：%d，标识：%s ===\n", tidVideo, type);
			char * lpAudioInfo = MP4Info(inFile, id);
			TRACE("音频信息：%s \n", lpAudioInfo);
			free(lpAudioInfo);

			// 获取音频的类型/名称/采样率/声道信息...
			audio_type = MP4GetTrackAudioMpeg4Type(inFile, id);
			TRACE("=== 音频格式类型：%d ===\n", audio_type);
			audio_channel_num = MP4GetTrackAudioChannels(inFile, id);
			TRACE("=== 音频声道数：%d ===\n", audio_channel_num);
			const char * audio_name = MP4GetTrackMediaDataName(inFile, id);
			TRACE("=== 音频编码：%s ===\n", audio_name);
			audio_time_scale = MP4GetTrackTimeScale(inFile, id);
			TRACE("=== 音频每秒刻度数(采样率)：%lu ===\n", audio_time_scale);
			if (audio_time_scale == 48000)
				audio_rate_index = 0x03;
			else if (audio_time_scale == 44100)
				audio_rate_index = 0x04;
			else if (audio_time_scale == 32000)
				audio_rate_index = 0x05;
			else if (audio_time_scale == 24000)
				audio_rate_index = 0x06;
			else if (audio_time_scale == 22050)
				audio_rate_index = 0x07;
			else if (audio_time_scale == 16000)
				audio_rate_index = 0x08;
			else if (audio_time_scale == 12000)
				audio_rate_index = 0x09;
			else if (audio_time_scale == 11025)
				audio_rate_index = 0x0a;
			else if (audio_time_scale == 8000)
				audio_rate_index = 0x0b;
			TRACE("=== 音频采样率编号：%lu ===\n", audio_rate_index);
			// 获取音频扩展信息...
            uint8_t  * pAES = NULL;
            uint32_t   nSize = 0;
            bool haveEs = MP4GetTrackESConfiguration(inFile, id, &pAES, &nSize);
			// 存储音频扩展信息...
			if( strAES.size() <= 0 && nSize > 0 ) {
				strAES.assign((char*)pAES, nSize);
			}
			TRACE("=== 音频扩展信息长度：%lu ===\n", nSize);
			// 释放分配的缓存...
			if( pAES != NULL ) {
				free(pAES);
				pAES = NULL;
			}
		}
	}
	// 如果音频和视频都没有，返回失败...
	if((tidVideo == MP4_INVALID_TRACK_ID) && (tidAudio == MP4_INVALID_TRACK_ID)) {
		MsgLogGM(GM_File_Read_Err);
		return false;
	}
	// 根据解析到的音视频格式信息，创建音视频轨道...
	this->BuildVideoTrack(strSPS, strPPS);
	this->BuildAudioTrack(audio_time_scale, strAES);
	// 一切正常，循环抽取音视频数据帧...
	return this->doMP4ReadFrame(inFile, tidVideo, tidAudio);
}

bool Csample_save_mp4Dlg::BuildVideoTrack(string & inSPS, string & inPPS)
{
	if( m_lpRecMP4 == NULL || inSPS.size() <= 0 || inPPS.size() <= 0 )
		return false;
	// 获取 width 和 height...
	int	nPicWidth = 0;
	int	nPicHeight = 0;
	if( inSPS.size() >  0 ) {
		CSPSReader _spsreader;
		bs_t    s = {0};
		s.p		  = (uint8_t *)inSPS.c_str();
		s.p_start = (uint8_t *)inSPS.c_str();
		s.p_end	  = (uint8_t *)inSPS.c_str() + inSPS.size();
		s.i_left  = 8; // 这个是固定的,对齐长度...
		_spsreader.Do_Read_SPS(&s, &nPicWidth, &nPicHeight);
	}
	// 正在创建视频轨道...
	TRACE("=== 正在创建视频录制轨道，视频高：%lu，视频宽：%lu ===\n", nPicWidth, nPicHeight);
	// 调用封装接口，直接创建视频轨道...
	return m_lpRecMP4->CreateVideoTrack(m_strUTF8Rec.c_str(), VIDEO_TIME_SCALE, nPicWidth, nPicHeight, inSPS, inPPS);
}

bool Csample_save_mp4Dlg::BuildAudioTrack(int nAudioRate, string & inAES)
{
	if( m_lpRecMP4 == NULL || nAudioRate <= 0 || inAES.size() <= 0 )
		return false;
	// 正在创建音频轨道...
	TRACE("=== 正在创建音频录制轨道，采样率：%lu ===\n", nAudioRate);
	// 调用封装接口，直接创建音频轨道...
	return m_lpRecMP4->CreateAudioTrack(m_strUTF8Rec.c_str(), nAudioRate, inAES);
}

// 循环抽取音视频数据帧...
bool Csample_save_mp4Dlg::doMP4ReadFrame(MP4FileHandle inFile, MP4TrackId inVideoID, MP4TrackId inAudioID)
{
	BOOL		bAudioComplete = false;
	BOOL		bVideoComplete = false;
	uint32_t	dwOutVSendTime = 0;
	uint32_t	dwOutASendTime = 0;
	uint32_t	iVSampleInx = 1;
	uint32_t	iASampleInx = 1;
	while( true ) {
		// 读取一帧视频帧...
		if( !bVideoComplete && !this->doMP4ReadOneFrame(inFile, inVideoID, iVSampleInx++, true, dwOutVSendTime) ) {
			bVideoComplete = true;
			continue;
		}
		// 读取一帧音频帧...
		if( !bAudioComplete && !this->doMP4ReadOneFrame(inFile, inAudioID, iASampleInx++, false, dwOutASendTime) ) {
			bAudioComplete = true;
			continue;
		}
		// 如果音频和视频全部结束，退出循环...
		if( bVideoComplete && bAudioComplete ) {
			TRACE("=== MP4文件数据帧读取完毕 ===\n");
			TRACE("=== 已读取视频帧：%lu ===\n", iVSampleInx);
			TRACE("=== 已读取音频帧：%lu ===\n", iASampleInx);
			break;
		}
	}
	return true;
}

// 抽取一帧音频或视频数据帧...
bool Csample_save_mp4Dlg::doMP4ReadOneFrame(MP4FileHandle inFile, MP4TrackId tid, uint32_t sid, bool bIsVideo, uint32_t & outSendTime)
{
	uint8_t		*	pSampleData = NULL;		// 帧数据指针
	uint32_t		nSampleSize = 0;		// 帧数据长度
	MP4Timestamp	nStartTime = 0;			// 开始时间
	MP4Duration		nDuration = 0;			// 持续时间
	MP4Duration     nOffset = 0;			// 偏移时间
	bool			bIsKeyFrame = false;	// 是否关键帧
	uint32_t		timescale = 0;
	uint64_t		msectime = 0;

	// 读取轨道的采样率 和 当前帧的时间戳...
	timescale = MP4GetTrackTimeScale( inFile, tid );
	msectime = MP4GetSampleTime( inFile, tid, sid );

	// 读取一帧数据帧，失败，直接返回...
	if( false == MP4ReadSample(inFile, tid, sid, &pSampleData, &nSampleSize, &nStartTime, &nDuration, &nOffset, &bIsKeyFrame) )
		return false;

	// 计算当前读取数据帧的时间戳...
	// 计算发送时间 => PTS => 刻度时间转换成毫秒...
	msectime *= UINT64_C( 1000 );
	msectime /= timescale;
	// 计算开始时间 => DTS => 刻度时间转换成毫秒...
	nStartTime *= UINT64_C( 1000 );
	nStartTime /= timescale;
	// 计算偏差时间 => CTTS => 刻度时间转换成毫秒...
	nOffset *= UINT64_C( 1000 );
	nOffset /= timescale;

	// 返回发送时间(毫秒) => 已将刻度时间转换成了毫秒...
	outSendTime = (uint32_t)msectime;
	
	// 打印获取的音视频数据帧内容信息...
	TRACE("[%s] duration = %I64d, offset = %I64d, KeyFrame = %d, SendTime = %lu, StartTime = %I64d, Size = %lu\n", bIsVideo ? "Video" : "Audio", nDuration, nOffset, bIsKeyFrame, outSendTime, nStartTime, nSampleSize);

	// 直接对获取到音视频数据帧进行录像操作...
	if( m_lpRecMP4 != NULL ) {
		if( !m_lpRecMP4->WriteSample(bIsVideo, pSampleData, nSampleSize, outSendTime, nOffset, bIsKeyFrame) ) {
			TRACE("=== 录制MP4数据帧失败! ===\n");
		}
	}

	// 这里需要释放读取的缓冲区...
	MP4Free(pSampleData);
	pSampleData = NULL;

	return true;
}