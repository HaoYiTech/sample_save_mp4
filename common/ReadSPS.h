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
 * 专门用于SPS的辅助解析工具类...
 ******************************************************/

#ifndef _Read_SPS_h__
#define _Read_SPS_h__

//typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;

//for H264

typedef struct tag_bs_s
{
	uint8_t *p_start;
	uint8_t *p;
	uint8_t *p_end;

	int     i_left;			// i_count number of available bits
	int     i_bits_encoded; // RD only
} bs_t;


class CSPSReader
{
public:
	CSPSReader();
	~CSPSReader();

public:
	int			Do_Read_SPS( bs_t *s, int *width, int *height);

private:
	int			_bs_eof( bs_t *s );
	uint32_t	_bs_read( bs_t *s, int i_count );
	void		_bs_skip( bs_t *s, int i_count );
	int			_bs_read_ue( bs_t *s );
	int			_bs_read_se( bs_t *s );
	uint32_t    _bs_read1( bs_t *s );
	void		_scaling_list(bs_t *s,int scalingList,int sizeOfScalingList,int useDefaultScalingMatrixFlag ) ;
};

#endif  //_Read_SPS_h__