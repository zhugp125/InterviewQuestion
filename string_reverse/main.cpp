#include <iostream>
#include <string.h>

using namespace std;

/**
 * 字符串反序
 * 例如 This is a macbook  -> sihT si a koobcam
 * 时间复杂度 O(n)
*/
bool reverse(const char* input, char* output)
{
    if (nullptr == input || nullptr == output)
    {
        return false;
    }

    char sep = ' ';
    size_t index = 0;
    size_t size = strlen(input);
    for (size_t i = 0; i < size; ++i)
    {
        // 遇到空格或者字符串末尾，才会进行下一步的反转字符串
        if (input[i] != sep && i != size - 1)
        {
            continue;
        }

        // 遇到空格，从空格前一个字符开始反向遍历
        // 到字符串末尾，从当前位置开始反向遍历
        // 反向遍历的终止是到字符串开始或者遇到空格，这个for循环的下表j的类型不能是size_t
        for (int j = (i == size - 1) ? i : i - 1; (j >= 0) && input[j] != sep; --j)
        {
            output[index++] = input[j];
        }

        // 不是字符串末尾时，要在输出字符串末尾添加空格
        if (i != size - 1)
        {
            output[index++] = sep;
        }
    }
    return true;
}

/**
 * 字符串反转，在原字符串基础上反转
 * 时间复杂度 O(n)
*/
bool reverse(char* input)
{
    if (nullptr == input)
    {
        return false;
    }

    size_t size = strlen(input);
    size_t beg = 0;
    for (size_t i = 0; i < size; ++i)
    {
        if (input[i] != ' ' && i != size - 1)
        {
            continue;
        }

        size_t last = (i == size - 1) ? i : i - 1;
        while (beg < last)
        {
            char temp = input[beg];
            input[beg] = input[last];
            input[last] = temp;

            ++beg;
            --last;
        }
        beg = i + 1;
    }
    return true;
}

class String
{
public:
    String(char* str = nullptr)
    {
        if (nullptr == str)
        {
            m_data = new char[1];
            m_data[0] = '\0';
        }
        else
        {
            int len = strlen(str);
            m_data = new char[len + 1];
            strcpy(m_data, str);
        }
    }

    String(const String& str)
    {
        int len = strlen(str.m_data);
        m_data = new char[len + 1];
        strcpy(m_data, str.m_data);
    }

    friend bool operator ==(const String& lhs, const String& rhs)
    {
        return !strcmp(lhs.m_data, rhs.m_data);
    }

    friend bool operator !=(const String& lhs, const String& rhs)
    {
        return !(lhs == rhs);
    }

    // 异常安全
    String& operator =(const String& str)
    {
        if (*this != str)
        {
            String strTemp(str);
            std::swap(strTemp.m_data, m_data);
        }
        return *this;
    }

    ~String()
    {
        delete[] m_data;
    }

    size_t size() const
    {
        return strlen(m_data);
    }

    char* c_str() const
    {
        return m_data;
    }

private:
    char* m_data;
};

/*
 * string to int
 * 考虑输入为空，输入负号，小数点前输入除负号以外的非数字字符
 * 考虑int越界的问题
 * 时间复杂度 O(n)
*/
int stringToInt(const char* s, bool *ok = nullptr)
{
    (ok != nullptr) ? (*ok = false) : 0;
    if (nullptr == s)
    {
        return 0;
    }

    int symbol = 1;
    if (*s == '-')
    {
        symbol = -1;
        ++s;
    }

    long long nResult = 0;
    do
    {
        if (*s == '.')
        {
            break;
        }
        else if (*s < '0' || *s > '9')
        {
            return 0;
        }

        nResult = nResult * 10 + (*s - '0');
        ++s;
    }while (*s);

    if (nResult < INT_MIN || nResult > INT_MAX)
    {
        return 0;
    }

    (ok != nullptr) ? (*ok = true) : 0;
    return (int)nResult * symbol;
}

/*!
 * \brief isPalindromic 回文字符串判断
 * \param str 输入字符串
 * \return    是否回文
 * 时间复杂度 O(n)
 */
bool isPalindromic(const char* str)
{
    if (nullptr == str)
    {
        return false;
    }

    size_t len = strlen(str);
    for (int i = 0, j = len -1; i < j; ++i, --j)
    {
        if (str[i] != str[j])
            return false;
    }
    return true;
}

/*!
 * \brief replaceBlank  替换空格
 * \param str           输入字符数组
 * \param length        字符数组长度
 */
void replaceBlank(char str[], int length)
{
    if (nullptr == str)
    {
        return;
    }

    int orginalLength = 0;
    int blankCount = 0;
    char* p = str;
    while (*p)
    {
        ++orginalLength;
        if (*p == ' ')
            ++blankCount;
    }

    int newLength = orginalLength + blankCount * 2;
    if (newLength > length)
        return;

    int orginalIndex = orginalLength;
    int newIndex = newLength;
    while (orginalIndex > 0 && orginalIndex < newIndex)
    {
        if (str[orginalIndex] != ' ')
        {
            str[newIndex--] = str[orginalIndex];
        }
        else
        {
            str[newIndex--] = '0';
            str[newIndex--] = '2';
            str[newIndex--] = '%';
        }
        --orginalIndex;
    }
}

int main()
{
    const char* input = "This is a macbook";
    char output[18] = {0};
    reverse(input, output);
    cout << output << endl;

    {
        char input[] = "This is a macbook";
        reverse(input);
        cout << input << endl;
    }

    cout << boolalpha;
    bool ok;
    int ret = stringToInt("", &ok);
    cout << ok << " " << ret << endl;

    ret = stringToInt("1234", &ok);
    cout << ok << " " << ret << endl;

    ret = stringToInt("-12.34", &ok);
    cout << ok << " " << ret << endl;

    ret = stringToInt("12a34", &ok);
    cout << ok << " " << ret << endl;

    cout << noboolalpha;

    cout << "Hello World!" << endl;
    return 0;
}
