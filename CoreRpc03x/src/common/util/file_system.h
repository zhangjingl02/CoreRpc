#ifndef INCLUDED_CACTI_UTIL_FILESYSTEM_H
#define INCLUDED_CACTI_UTIL_FILESYSTEM_H

#include <string>
#include <vector>

#ifndef MAX_PATH
	#define	MAX_PATH	4096
#endif
#ifndef WIN32
	#define	_O_RDWR		O_RDWR
	#define	_O_RDONLY	O_RDONLY
	#define	_O_WRONLY	O_WRONLY
#endif

namespace util
{
	class FileSystem
	{
	public:
		static bool copyfile(const char* src, const char* dst);
		static std::string tempFile();
		static int fileSize(const char* file);
		static time_t fileUpdateTime(const char *file);
		static int  mkdir(const char* dir, int mode = 0777);
		static bool isFileExist(const char* filepath);
		static bool isFileCanR(const char* filepath);
		static bool isFileCanW(const char* filepath);
		static bool isFileCanRW(const char* filepath);
		static std::string getModulePath();
		static bool createMulDir(const std::string& dir);
	};
}

#endif // INCLUDED_CACTI_UTIL_FILESYSTEM_H

/*
 * ����˵���飺
 * 1����ʼ��������һ�������ļ����г�ʼ��
 *	[APC]
 *		local1=h:
 *		export1=file:	# empty means no change
 *		import1=file:	# empty means no change
 *
 *		local2=d:
 *		export2=			# empty means no change
 *		import2=/media/cdrom	# empty means no change
 *		#...
 *
 * 2����Ҫ���͵�����service��·������ʹ��AbstractPath.exportת���������·��
 * 3��������service�õ���·����������AbstractPath.import��ԭ����·��
 * 4��֧�ֽ���һģ����޸ģ�����tssg(windows)ʹ�ñ����ƣ�dmu(linux)��ʹ�ã����������£�
 *		[APC] 
 *			local1=h:
 *			export1=/mnt/h
 *			import1=/mnt/h
 *		������tssg����һ��·����h:\ttscache\abc.vox (����local1\ttscache\abc.vox)����dmu��ʱ��·����ת����
 *		��/mnt/h/ttscache/abc.vox (����local1 --> export1)��
 *		dmu�������·��֪ͨtssgɾ���ļ���/mnt/h/ttscache/abc.vox����ʱ��
 *		tssg��·����ԭΪ��h:\ttscache/abc.vox (����import1 --> local1)��
 * 5��·���еġ�\��ȫ��ͳһʹ�á�/��
 * 6������ͨ�ŵķ���A(windows)�� B��windows����C��linux�����ļ���������windows�ļ���ӳ�䵽H�̣���linux��mount��/mnt/h��
 *    Aͬʱ��Ҫ��һ��·�����͸�B��C����
 *  A��������
 *	[APC]
 *		local[1]=h:
 *		export]=file:
 *		import1=file:
 *	B��������
 *	[APC]
 *		local1=h:
 *		export1=file:
 *		import1=file:
 *	C��������
 *	[APC]
 *		local1=/mnt/H
 *		export1=file:
 *		import1=file:
 * 7����ȫ��ģ�鶼ʹ�ñ�����֮��ֻ��Ҫ�������ã�һ��windows��һ��linux���ɣ�ͳһ��Startup��ʼ����
 * 8������֧�ֶ�����ù���ͬʱ���ڣ������Ⱥ�˳��ƥ��ɹ���ѡ������ã����֧��100��������Ŀ
 * 9��export �㷨
		if thePath contains theLocal then
			replace theLocal with theExport
		loop until no entities
	  import �㷨
		if theRemovePath contains theImport then
			replace theImport with theLocal
		loop until no entities
 */
