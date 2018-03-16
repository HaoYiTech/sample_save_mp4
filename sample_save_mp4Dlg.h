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
 * VS2010自动生成的对话框类头文件
 ******************************************************/

#pragma once

#include "LibMP4.h"
#include "HyperLink.h"

class Csample_save_mp4Dlg : public CDialogEx
{
public:
	Csample_save_mp4Dlg(CWnd* pParent = NULL);	// 标准构造函数
	enum { IDD = IDD_SAMPLE_SAVE_MP4_DIALOG };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	bool	doMP4ParseAV(MP4FileHandle inFile);
	bool    doMP4ReadFrame(MP4FileHandle inFile, MP4TrackId inVideoID, MP4TrackId inAudioID);
	bool	doMP4ReadOneFrame(MP4FileHandle inFile, MP4TrackId tid, uint32_t sid, bool bIsVideo, uint32_t & outSendTime);
	bool	BuildVideoTrack(string & inSPS, string & inPPS);
	bool    BuildAudioTrack(int nAudioRate, string & inAES);
private:
	HICON			m_hIcon;
	CHyperLink		m_ctrlHome;
	LibMP4		*	m_lpRecMP4;
	string			m_strUTF8Rec;
};
