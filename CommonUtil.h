#pragma once

#include <vector>

namespace sjx
{
    /****** 字符串相关 ******/
    // 统计字符串的字符个数，中文算1个，英文算1个，数字算1个
    size_t CountCString(CString cs);
    // 判断字符串是否在字符串数组中，否返回-1，是返回index（基于0）
    int IsInCStringArray(CString cs, const CStringArray& csa,bool caseSense=true);
    // 将csaFrom中的字符串添加到csaTo数组中，bCheckDuplicate表示在添加的时候是否查重，如果已存在，则不添加
    void AddToCStringArray(BOOL bCheckDuplicate, const CStringArray& csaFrom, CStringArray& csaTo);
    // 把字符串放到剪贴板中
    BOOL CopyCStringToClipboard(CString data);
    // buffer是不是已UTF-8编码，带不带BOM都行
    bool IsUTF8(const void* pBuffer, long size);
    // Unicode转UTF-8
    void UnicodeToUTF8(CStringW uni, std::vector<char>& utf8);
    // 分割CString
    void SplitCString(CString str, CString split, CStringArray& strGet);
	// 合并CStringArr
	void AddToCString(CStringArray& strFrom,CString& strGet, CString split);
    // 在记事本中显示字符串
    void ShowTextInNotepad(CString csText);

    /****** 文件相关 ******/
    // 计算文件的MD5值
    BOOL GenFileMD5(CString filepath, CString& md5);
    // 比较两个文件的MD5值是否相同。返回值 0-相同，-1-file1生成MD5失败 -2-file2生成MD5失败 -3-MD5不同
    int CompareFileByMD5(CString file1, CString file2);
    // 检测MD5值的正确性
    BOOL IsValidMD5(CString csMD5);
    // 比较两个文件的时间。返回值 0-相同，-1-file1生成时间失败 -2-file2生成MD5失败 -3 -file1比file2早 -4 file1比file2晚
    int CompareFileByModTime(CString file1, CString file2);
    // 比较文件的修改时间和给定的时间。返回值 0-相同 -1-file生成时间失败 -2-file要早 -3-file要晚
    int CompareFileModTimeWithGivenTime(CString file, SYSTEMTIME time);
    // 移除文件的只读属性
    void RemoveFileReadOnlyAttr(CString filepath);
    // 删除文件，删除之前，会尝试移除文件的只读属性
    BOOL DelFile(CString filepath);
    // 删除文件夹，删除之前，会尝试移除所有子文件的只读属性
    BOOL DelFolder(CString folderPath);
	// 重命名文件或文件夹
	BOOL RenameFileOrFolder(CString oldPath, CString newPath);
    // 资源管理器打开并定位到某个文件
    BOOL ExplorerFile(CString filepath);
    // 在VS命令行提示符窗口执行bat文件
    BOOL ExecBatFileInVS2010CmdPrompt(CString filepath);
    // 获取文件的时间戳
    BOOL GetFileLastWriteTimeStamp(CString filepath, CString& timeStamp);
    // 复制文件，如果目标目录缺乏文件夹，则新建
    BOOL CopyFileWithCreateFolder(CString csSrcFilePath, CString csDestFilePath, BOOL flag);
    BOOL CopyFileWithCreateFolder(CString csSrcFilePath, CString csDestFolder, CString csDestRelativeFilePath, BOOL flag);
    // 判断文件夹是否存在
    BOOL IsFolderExist(CString csFolderPath);
    BOOL IsFileExist(CString csFilePath);
    CString GetFileExt(CString csFilePathOrName);
    CString DelFileExt(CString csFilePathOrName);
    CString GetFileOrFolderNameFromPath(CString csFilePath);
    // 获得一个目录下的文件，可以指定过滤器，以及是否搜索子目录
    void GetFilesInFolder(CString csFolderPath, CStringArray& csaFiles, CString csPattern = _T("*.*"), BOOL bIncludeSubFolder = FALSE);
    // 弹出对话框选择文件
    enum SEL_FILE_MODE { FILE_OPEN, FILE_SAVEAS };
    BOOL SelFile(CStringArray& csaFilePaths,
        SEL_FILE_MODE mode = FILE_OPEN,
        LPCTSTR lpszDefExt = NULL,
        LPCTSTR lpszFileName = NULL,
        DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        LPCTSTR lpszFilter = NULL);
    // 选择文件夹
    BOOL SelFolder(CString& csFolderPath, CString InitialDir = _T(""), CString csTitle = _T("选择文件夹"), HWND hParent = NULL);
    // 确保路径字符串以\\结尾
    void EnsurePathEndWithSlash(CString& path);
    // 确保路径字符串不以\\结尾
    void EnsurePathEndWithoutSlash(CString& path);
    // 获取exe所在目录
    CString GetModuleFolder();
    // 获得某个目录下所有某个后缀的文件名,1Path 2 Filename
    enum FILE_VALUE { FILEPATH, FILENAME };
    void GetAllExtFiles(CString csPath, CString csExt, FILE_VALUE value, CStringArray& csaFiles);
	// 由一个文件的路径获得其所在目录的路径
	CString GetFolderPathFromFilePath(CString filePath);

    /***** 系统相关 *****/
    // 判断Windows系统是不是Vista及以后版本
    BOOL IsOSVistaOrGreater();
    // 运行exe
    void RunExeAndWait(CString csExePath);
    // 调用命令提示符执行命令，并获得输出
    BOOL ExecCmd(CString cmd, CString& csRet);
    CString ExecCmd2(CString cmd);
    // 获得当前Error的字符串
    CString GetErrorString();

    /***** 扩展ini文件 *****/
    // 打开文件，为读写扩展ini 0读1写
    CStdioFile* OpenExIniFile(CString csPath, int readOrWrite);
    // 读某个字段的结果
    void ReadExIniSection(CStdioFile* pFile, CString csSecName, CString& csSecValue);
    // 写某个字段的结果
    void WriteExIniSection(CStdioFile* pFile, CString csSecName, CString csSecValue);


    /***** 注册表相关 *****/
    // 读取注册表某个字符串键值
    BOOL GetRegString(HKEY hKeyArg, CString keyNameArg, CString valNameArg, ULONG len, CString& csRegValue);
    // 写注册表某个字符串键值，应该需要管理员权限
    BOOL SetRegString(HKEY hKeyArg, CString keyNameArg, CString csKey, CString csKeyVal);

    /***** 控件相关 *****/
    // 展开树上一个节点的所有子节点，指定TVI_ROOT的话，那就是展开整个树
    // 该函数不能在OnInitialDialog的时候用，否则可能程序会启动不了
    void ExpandTree(CTreeCtrl& tree, HTREEITEM hItem);
    // 设置某个CComboBox的下拉框宽度匹配下拉选项中最长的那个，拷贝自MSDN CComboBox::SetDroppedWidth
    void AutoSetComboBoxDropDownWidth(CComboBox* m_pComboBox);
}

#pragma region 计算MD5用
/*
* Authod: Marius Bancila (http://mariusbancila.ro)
* License: Code Project Open License
* Disclaimer: The software is provided "as-is". No claim of suitability, guarantee, or any warranty whatsoever is provided.
* Published: 19.09.2012
*/


#include <Windows.h>
#include <WinCrypt.h>
#pragma comment(lib, "Advapi32.lib")

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

namespace crypto
{
    typedef std::vector<unsigned char> hash_t;

    class string_utils
    {
    public:
        static std::string hextostr(std::vector<unsigned char> const & hexval, bool uppercase = false)
        {
            std::stringstream sstr;

            if (!hexval.empty())
            {
                sstr.setf(std::ios_base::hex, std::ios::basefield);
                if (uppercase)
                    sstr.setf(std::ios_base::uppercase);
                sstr.fill('0');
                for (size_t i = 0; i < hexval.size(); i++)
                {
                    sstr << std::setw(2) << (unsigned int)(unsigned char)(hexval[i]);
                }
            }

            return sstr.str();
        }
    };

    struct errorinfo_t
    {
        DWORD errorCode;
        std::string errorMessage;

        errorinfo_t(DWORD code = 0, std::string const &message = "") :
            errorCode(code), errorMessage(message)
        {}
    };

    template <ALG_ID algorithm>
    class cryptohash_t
    {
    public:

        cryptohash_t(void) : m_hCryptProv(NULL), m_hHash(NULL)
        {
        }

        ~cryptohash_t(void)
        {
            if (m_hHash != NULL)
            {
                ::CryptDestroyHash(m_hHash);
            }

            if (m_hCryptProv != NULL)
            {
                ::CryptReleaseContext(m_hCryptProv, 0);
            }
        }

        bool begin()
        {
            m_lasterror = errorinfo_t();

            if (m_hCryptProv != NULL && m_hHash != NULL)
            {
                m_lasterror = errorinfo_t(0, "Cryptographic provider already acquired!");
                return false;
            }

            m_digest.clear();

            if (!::CryptAcquireContext(
                &m_hCryptProv,
                NULL,
                NULL,
                PROV_RSA_FULL,
                CRYPT_VERIFYCONTEXT | CRYPT_MACHINE_KEYSET))
            {
                m_lasterror = errorinfo_t(GetLastError(), "Failed to acquire cryptographic context.");
                return false;
            }

            if (!::CryptCreateHash(
                m_hCryptProv,
                algorithm,
                0,
                0,
                &m_hHash))
            {
                m_lasterror = errorinfo_t(GetLastError(), "Failed to acquire cryptographic context.");

                ::CryptReleaseContext(m_hCryptProv, 0);
                m_hCryptProv = NULL;
                return false;
            }

            return true;
        }

        bool update(unsigned char* const buffer, size_t size)
        {
            m_lasterror = errorinfo_t();

            if (m_hCryptProv == NULL || m_hHash == NULL)
            {
                m_lasterror = errorinfo_t(0, "Cryptographic provider not acquired!");
                return false;
            }

            if (!::CryptHashData(
                m_hHash,
                buffer,
                size,
                0))
            {
                m_lasterror = errorinfo_t(GetLastError(), "Updating hash failed!");
                return false;
            }

            return true;
        }

        bool finalize()
        {
            m_lasterror = errorinfo_t();

            if (m_hCryptProv == NULL || m_hHash == NULL)
            {
                m_lasterror = errorinfo_t(0, "Cryptographic provider not acquired!");
                return false;
            }

            bool success = false;
            DWORD dwHashLen = 0;
            DWORD dwHashLenSize = sizeof(dwHashLen);
            if (::CryptGetHashParam(
                m_hHash,
                HP_HASHSIZE,
                (BYTE*)&dwHashLen,
                &dwHashLenSize,
                0))
            {
                m_digest.resize(dwHashLen, 0);

                if (dwHashLen > 0)
                {
                    if (::CryptGetHashParam(
                        m_hHash,
                        HP_HASHVAL,
                        &m_digest[0],
                        &dwHashLen,
                        0))
                    {
                        success = true;
                    }
                    else
                    {
                        m_lasterror = errorinfo_t(GetLastError(), "Failed retrieving hash value!");
                    }
                }
            }
            else
            {
                m_lasterror = errorinfo_t(GetLastError(), "Failed computing hash length!");
            }

            if (m_hHash != NULL)
            {
                ::CryptDestroyHash(m_hHash);
                m_hHash = NULL;
            }

            if (m_hCryptProv != NULL)
            {
                ::CryptReleaseContext(m_hCryptProv, 0);
                m_hCryptProv = NULL;
            }

            return success;
        }

        hash_t digest() const { return m_digest; }
        std::string hexdigest(bool uppercase = false) const { return string_utils::hextostr(m_digest, uppercase); }
        errorinfo_t lasterror() const { return m_lasterror; }

    private:
        errorinfo_t m_lasterror;
        HCRYPTPROV m_hCryptProv;
        HCRYPTHASH m_hHash;
        hash_t m_digest;
    };

    template <ALG_ID algorithm>
    class cryptohash_helper_t
    {
        errorinfo_t m_lasterror;
    public:
        hash_t digesttext(std::string const& text)
        {
            cryptohash_t<algorithm> mdx;

            if (mdx.begin())
            {
                if (mdx.update((unsigned char*)(text.c_str()), text.length()))
                {
                    mdx.finalize();
                }
            }

            m_lasterror = mdx.lasterror();

            return mdx.digest();
        }

        std::string hexdigesttext(std::string const& text, bool uppercase = false)
        {
            return string_utils::hextostr(digesttext(text), uppercase);
        }

        hash_t digestfile(std::string const& filename)
        {
            cryptohash_t<algorithm> mdx;

            std::ifstream file;
            file.open(filename.c_str(), std::ios::binary | std::ios::in);
            if (file.is_open())
            {
                file.seekg(0, std::ios::end);
                size_t filesize = (size_t)file.tellg();
                file.seekg(0, std::ios::beg);

                if (filesize > 0)
                {
                    if (mdx.begin())
                    {
                        size_t total = 0;
                        unsigned char chunk[8 * 1024];
                        do
                        {
                            size_t left = (filesize - total) > sizeof(chunk) ? sizeof(chunk) : (filesize - total);
                            file.read(reinterpret_cast<char*>(chunk), left);

                            size_t totalread = (size_t)file.gcount();
                            total += totalread;

                            if (totalread > 0)
                            {
                                if (!mdx.update(chunk, totalread))
                                    break;
                            }
                        } while (total < filesize);

                        if (total == filesize)
                        {
                            mdx.finalize();
                        }
                    }

                    m_lasterror = mdx.lasterror();
                }

                file.close();
            }
            else
            {
                m_lasterror = errorinfo_t(0, filename + " could not be opened");
            }

            return mdx.digest();
        }

        std::string hexdigestfile(std::string const& filename, bool uppercase = false)
        {
            return string_utils::hextostr(digestfile(filename), uppercase);
        }

        errorinfo_t lasterror() const { return m_lasterror; }
    };

    typedef cryptohash_t<CALG_MD2> md2_t;
    typedef cryptohash_t<CALG_MD4> md4_t;
    typedef cryptohash_t<CALG_MD5> md5_t;
    typedef cryptohash_t<CALG_SHA1> sha1_t;

    typedef cryptohash_helper_t<CALG_MD2> md2_helper_t;
    typedef cryptohash_helper_t<CALG_MD4> md4_helper_t;
    typedef cryptohash_helper_t<CALG_MD5> md5_helper_t;
    typedef cryptohash_helper_t<CALG_SHA1> sha1_helper_t;
}


#pragma endregion 计算MD5用