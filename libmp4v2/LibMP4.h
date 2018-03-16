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
 * LibMP4 => MP4存盘封装类
 ******************************************************/

#pragma once

#include "mp4v2.h"

typedef struct RTMPFrame {
	string		m_strData;
	bool		m_bKeyFrame;
	uint32_t	m_nTimeStamp;
	uint32_t	m_nRenderOffset;
}RTMPFrame;

typedef	deque<RTMPFrame>	KH_DeqFrame;
class LibMP4
{
public:
	LibMP4(void);
	~LibMP4(void);
public:
	DWORD GetWriteSize()  { return m_dwWriteSize; }
	DWORD GetWriteSec()   { return m_dwWriteSec; }
	bool IsVideoCreated() { return ((m_videoID == MP4_INVALID_TRACK_ID) ? false : true); }
	bool IsAudioCreated() { return ((m_audioID == MP4_INVALID_TRACK_ID) ? false : true); }

	bool CreateAudioTrack(const char* lpUTF8Name, int nAudioSampleRate, string & strAES);
	bool CreateVideoTrack(const char* lpUTF8Name, int nVideoTimeScale, int width, int height, string & strSPS, string & strPPS);

	bool WriteSample(bool bIsVideo, BYTE * lpFrame, int nSize, uint32_t inTimeStamp, uint32_t inRenderOffset, bool bIsKeyFrame);

	bool Close();
private:
	DWORD GetDurationSecond();
private:
	MP4FileHandle	m_hFileHandle;		// 文件句柄
	MP4TrackId		m_videoID;			// 视频ID
	MP4TrackId		m_audioID;			// 音频ID
	RTMPFrame		m_VLastFrame;		// 上一帧视频，音频是固定的，不用记录上一帧数据
	KH_DeqFrame		m_deqAudio;			// 音频缓存数据帧
	DWORD			m_dwWriteSize;		// 写入文件长度...
	DWORD			m_dwWriteSec;		// 已经写入的秒数...
	DWORD			m_dwFirstStamp;		// 开始写盘的第一帧时间戳...
	bool			m_bFirstFrame;		// 第一帧必须写视频的关键帧,之前的音频丢掉
	int				m_nVideoTimeScale;	// 目前是固定的数值，由上层来控制并设置
};

