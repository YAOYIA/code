#include <stdio.h>
#include <stdarg.h>

/* vsnprintf 是C语言标准库中的函数，它的作用是格式化可变参数列表到字符串缓冲区，并且限制最大写入的字符数，防止缓存区溢出
 * int vsnprintf(char *str, size_t size, const char *format, va_list ap);
 * str:存放结果的字符数组（缓冲区）
 * size：缓存区大小
 * format：格式化字符串
 * ap：va_list类型的可变参数列表
*/


void my_printf(const char *format, ...) {
    char buf[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);
    puts(buf);
}

int main() {
    my_printf("Hello %s, you have %d messages", "Alice", 5);
    return 0;
}