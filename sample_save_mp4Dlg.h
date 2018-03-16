/******************************************************
 * ��һ�Ƽ����ṩ��¼�����Ƽ�ص�ȫƽ̨�޲�����������
 * ֧�ְ���ֱ������㲼�أ��ֲ�ʽ�����洢����̬���ݣ�
 * ֧��΢��ɨ���¼��ȫƽ̨�ʺ�ͳһ������΢��С����
 * ֧�ֶ����������룺����ͷIPC��rtmp��rtsp��MP4�ļ���
 * ֧��ȫʵʱ��ȫ��̬��ȫ��ҳ������ҳǰ��̨����IE8��
 * ֧�ֶ��ն��޲������Ӧ���ţ�flvjs/hls/rtmp�Զ����䣻
 ******************************************************
 * �ٷ���վ => https://myhaoyi.com
 * �������� => http://blog.csdn.net/haoyitech
 * ��Դ���� => https://github.com/HaoYiTech/
 * �Ƽ��Ⱥ => 483663026��QQȺ��
 * ��¼��Ⱥ => 630379661��QQȺ��
 ******************************************************
 * VS2010�Զ����ɵĶԻ�����ͷ�ļ�
 ******************************************************/

#pragma once

#include "LibMP4.h"
#include "HyperLink.h"

class Csample_save_mp4Dlg : public CDialogEx
{
public:
	Csample_save_mp4Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	enum { IDD = IDD_SAMPLE_SAVE_MP4_DIALOG };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
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
