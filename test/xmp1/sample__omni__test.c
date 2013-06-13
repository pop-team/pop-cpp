/*
 * Original Source  : test.c
 * Language         : C
 * Compiled Time    : 2012-11-27 13:46:46
 * Compiler Info    : XcodeML/C-FrontEnd
 * Compiler Version : 1
 */
# 1 "test.c"
typedef unsigned long size_t;
typedef unsigned char __u_char;
typedef unsigned short __u_short;
typedef unsigned int __u_int;
typedef unsigned long __u_long;
typedef char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long __int64_t;
typedef unsigned long __uint64_t;
typedef long __quad_t;
typedef unsigned long __u_quad_t;
typedef unsigned long __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long __ino_t;
typedef unsigned long __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long __nlink_t;
typedef long __off_t;
typedef long __off64_t;
typedef int __pid_t;
struct anon_type_1___fsid_t {
int __val[2];
};
typedef struct anon_type_1___fsid_t __fsid_t;
typedef long __clock_t;
typedef unsigned long __rlim_t;
typedef unsigned long __rlim64_t;
typedef unsigned int __id_t;
typedef long __time_t;
typedef unsigned int __useconds_t;
typedef long __suseconds_t;
typedef int __daddr_t;
typedef long __swblk_t;
typedef int __key_t;
typedef int __clockid_t;
typedef void * __timer_t;
typedef long __blksize_t;
typedef long __blkcnt_t;
typedef long __blkcnt64_t;
typedef unsigned long __fsblkcnt_t;
typedef unsigned long __fsblkcnt64_t;
typedef unsigned long __fsfilcnt_t;
typedef unsigned long __fsfilcnt64_t;
typedef long __ssize_t;
typedef long __loff_t;
typedef long * __qaddr_t;
typedef char * __caddr_t;
typedef long __intptr_t;
typedef unsigned int __socklen_t;
union anon_type_3___value {
unsigned int __wch;
char __wchb[4];
};
typedef struct anon_type_2___mbstate_t __mbstate_t;
typedef int __attribute__((mode(__HI__))) _G_int16_t;
typedef int __attribute__((mode(__SI__))) _G_int32_t;
typedef unsigned int __attribute__((mode(__HI__))) _G_uint16_t;
typedef unsigned int __attribute__((mode(__SI__))) _G_uint32_t;
typedef __builtin_va_list __gnuc_va_list;
struct _IO_jump_t {
};
typedef void _IO_lock_t;
enum __codecvt_result {
__codecvt_ok = 0,
__codecvt_partial = 1,
__codecvt_error = 2,
__codecvt_noconv = 3
};
struct _IO_FILE_plus {
};
typedef long __io_read_fn(void * __cookie, char * __buf, unsigned long __nbytes);
typedef long __io_write_fn(void * __cookie, char const * __buf, unsigned long __n);
typedef int __io_seek_fn(void * __cookie, long * __pos, int __w);
typedef int __io_close_fn(void * __cookie);
typedef __builtin_va_list va_list;
typedef long off_t;
typedef long ssize_t;
struct _IO_marker;
struct _IO_FILE;
typedef struct _IO_FILE FILE;
typedef struct _IO_FILE __FILE;
struct anon_type_2___mbstate_t {
int __count;
union anon_type_3___value __value;
};
struct anon_type_4__G_fpos_t {
long __pos;
struct anon_type_2___mbstate_t __state;
};
typedef struct anon_type_4__G_fpos_t _G_fpos_t;
struct anon_type_5__G_fpos64_t {
long __pos;
struct anon_type_2___mbstate_t __state;
};
typedef struct anon_type_5__G_fpos64_t _G_fpos64_t;
struct _IO_marker {
struct _IO_marker * _next;
struct _IO_FILE * _sbuf;
int _pos;
};
struct _IO_FILE {
int _flags;
char * _IO_read_ptr;
char * _IO_read_end;
char * _IO_read_base;
char * _IO_write_base;
char * _IO_write_ptr;
char * _IO_write_end;
char * _IO_buf_base;
char * _IO_buf_end;
char * _IO_save_base;
char * _IO_backup_base;
char * _IO_save_end;
struct _IO_marker * _markers;
struct _IO_FILE * _chain;
int _fileno;
int _flags2;
long _old_offset;
unsigned short _cur_column;
char _vtable_offset;
char _shortbuf[1];
void * _lock;
long _offset;
void * __pad1;
void * __pad2;
void * __pad3;
void * __pad4;
unsigned long __pad5;
int _mode;
char _unused2[(((15) * (sizeof(int))) - ((4) * (sizeof(void * )))) - (sizeof(unsigned long))];
};
typedef struct _IO_FILE _IO_FILE;
typedef struct anon_type_4__G_fpos_t fpos_t;
# include "xmp_func_decl.h"
# include "xmp_index_macro.h"
# include "xmp_comm_macro.h"
static void * _XMP_DESC_p;
static int _XMP_NODES_SIZE_p;
static int _XMP_NODES_RANK_p_0;
static void * _XMP_DESC_t;
int * _XMP_ADDR_a;
static void * _XMP_DESC_a;
static unsigned long long _XMP_GTOL_acc_a_0;
static int _XMP_GTOL_temp0_a_0;
static void __attribute__((constructor)) _XMP_constructor(int argc, char * * argv);
static void __attribute__((destructor)) _XMP_destructor();
# 348 "/usr/include/libio.h"
extern struct _IO_FILE_plus _IO_2_1_stdin_;
# 349 "/usr/include/libio.h"
extern struct _IO_FILE_plus _IO_2_1_stdout_;
# 350 "/usr/include/libio.h"
extern struct _IO_FILE_plus _IO_2_1_stderr_;
extern int __underflow(struct _IO_FILE * );
extern int __uflow(struct _IO_FILE * );
extern int __overflow(struct _IO_FILE * , int);
extern int _IO_getc(struct _IO_FILE * __fp);
extern int _IO_putc(int __c, struct _IO_FILE * __fp);
extern __attribute__((nothrow)) int _IO_feof(struct _IO_FILE * __fp);
extern __attribute__((nothrow)) int _IO_ferror(struct _IO_FILE * __fp);
extern int _IO_peekc_locked(struct _IO_FILE * __fp);
extern __attribute__((nothrow)) void _IO_flockfile(struct _IO_FILE * );
extern __attribute__((nothrow)) void _IO_funlockfile(struct _IO_FILE * );
extern __attribute__((nothrow)) int _IO_ftrylockfile(struct _IO_FILE * );
extern int _IO_vfscanf(struct _IO_FILE * restrict, char const * restrict, __builtin_va_list, int * restrict);
extern int _IO_vfprintf(struct _IO_FILE * restrict, char const * restrict, __builtin_va_list);
extern long _IO_padn(struct _IO_FILE * , int, long);
extern unsigned long _IO_sgetn(struct _IO_FILE * , void * , unsigned long);
extern long _IO_seekoff(struct _IO_FILE * , long, int, int);
extern long _IO_seekpos(struct _IO_FILE * , long, int);
extern __attribute__((nothrow)) void _IO_free_backup_area(struct _IO_FILE * );
# 169 "/usr/include/stdio.h"
extern struct _IO_FILE * stdin;
# 170 "/usr/include/stdio.h"
extern struct _IO_FILE * stdout;
# 171 "/usr/include/stdio.h"
extern struct _IO_FILE * stderr;
extern __attribute__((nothrow)) int remove(char const * __filename);
extern __attribute__((nothrow)) int rename(char const * __old, char const * __new);
extern __attribute__((nothrow)) int renameat(int __oldfd, char const * __old, int __newfd, char const * __new);
extern struct _IO_FILE * tmpfile(void);
extern __attribute__((nothrow)) char * tmpnam(char * __s);
extern __attribute__((nothrow)) char * tmpnam_r(char * __s);
extern __attribute__((nothrow, malloc)) char * tempnam(char const * __dir, char const * __pfx);
extern int fclose(struct _IO_FILE * __stream);
extern int fflush(struct _IO_FILE * __stream);
extern int fflush_unlocked(struct _IO_FILE * __stream);
extern struct _IO_FILE * fopen(char const * restrict __filename, char const * restrict __modes);
extern struct _IO_FILE * freopen(char const * restrict __filename, char const * restrict __modes, struct _IO_FILE * restrict __stream);
extern __attribute__((nothrow)) struct _IO_FILE * fdopen(int __fd, char const * __modes);
extern __attribute__((nothrow)) struct _IO_FILE * fmemopen(void * __s, unsigned long __len, char const * __modes);
extern __attribute__((nothrow)) struct _IO_FILE * open_memstream(char * * __bufloc, unsigned long * __sizeloc);
extern __attribute__((nothrow)) void setbuf(struct _IO_FILE * restrict __stream, char * restrict __buf);
extern __attribute__((nothrow)) int setvbuf(struct _IO_FILE * restrict __stream, char * restrict __buf, int __modes, unsigned long __n);
extern __attribute__((nothrow)) void setbuffer(struct _IO_FILE * restrict __stream, char * restrict __buf, unsigned long __size);
extern __attribute__((nothrow)) void setlinebuf(struct _IO_FILE * __stream);
extern int fprintf(struct _IO_FILE * restrict __stream, char const * restrict __format, ...);
extern int printf(char const * restrict __format, ...);
extern __attribute__((nothrow)) int sprintf(char * restrict __s, char const * restrict __format, ...);
extern int vfprintf(struct _IO_FILE * restrict __s, char const * restrict __format, __builtin_va_list __arg);
extern int vprintf(char const * restrict __format, __builtin_va_list __arg);
extern __attribute__((nothrow)) int vsprintf(char * restrict __s, char const * restrict __format, __builtin_va_list __arg);
extern __attribute__((nothrow, format(__printf__, 3, 4))) int snprintf(char * restrict __s, unsigned long __maxlen, char const * restrict __format, ...);
extern __attribute__((nothrow, format(__printf__, 3, 0))) int vsnprintf(char * restrict __s, unsigned long __maxlen, char const * restrict __format, __builtin_va_list __arg);
extern __attribute__((format(__printf__, 2, 0))) int vdprintf(int __fd, char const * restrict __fmt, __builtin_va_list __arg);
extern __attribute__((format(__printf__, 2, 3))) int dprintf(int __fd, char const * restrict __fmt, ...);
extern int fscanf(struct _IO_FILE * restrict __stream, char const * restrict __format, ...);
extern int scanf(char const * restrict __format, ...);
extern __attribute__((nothrow)) int sscanf(char const * restrict __s, char const * restrict __format, ...);
extern int fscanf(struct _IO_FILE * restrict __stream, char const * restrict __format, ...);
extern int scanf(char const * restrict __format, ...);
extern __attribute__((nothrow)) int sscanf(char const * restrict __s, char const * restrict __format, ...);
extern __attribute__((format(__scanf__, 2, 0), format(__scanf__, 2, 0))) int vfscanf(struct _IO_FILE * restrict __s, char const * restrict __format, __builtin_va_list __arg);
extern __attribute__((format(__scanf__, 1, 0), format(__scanf__, 1, 0))) int vscanf(char const * restrict __format, __builtin_va_list __arg);
extern __attribute__((format(__scanf__, 2, 0), nothrow, format(__scanf__, 2, 0))) int vsscanf(char const * restrict __s, char const * restrict __format, __builtin_va_list __arg);
extern __attribute__((format(__scanf__, 2, 0), format(__scanf__, 2, 0))) int vfscanf(struct _IO_FILE * restrict __s, char const * restrict __format, __builtin_va_list __arg);
extern __attribute__((format(__scanf__, 1, 0), format(__scanf__, 1, 0))) int vscanf(char const * restrict __format, __builtin_va_list __arg);
extern __attribute__((format(__scanf__, 2, 0), nothrow, format(__scanf__, 2, 0))) int vsscanf(char const * restrict __s, char const * restrict __format, __builtin_va_list __arg);
extern int fgetc(struct _IO_FILE * __stream);
extern int getc(struct _IO_FILE * __stream);
extern int getchar(void);
extern int getc_unlocked(struct _IO_FILE * __stream);
extern int getchar_unlocked(void);
extern int fgetc_unlocked(struct _IO_FILE * __stream);
extern int fputc(int __c, struct _IO_FILE * __stream);
extern int putc(int __c, struct _IO_FILE * __stream);
extern int putchar(int __c);
extern int fputc_unlocked(int __c, struct _IO_FILE * __stream);
extern int putc_unlocked(int __c, struct _IO_FILE * __stream);
extern int putchar_unlocked(int __c);
extern int getw(struct _IO_FILE * __stream);
extern int putw(int __w, struct _IO_FILE * __stream);
extern char * fgets(char * restrict __s, int __n, struct _IO_FILE * restrict __stream);
extern char * gets(char * __s);
extern long __getdelim(char * * restrict __lineptr, unsigned long * restrict __n, int __delimiter, struct _IO_FILE * restrict __stream);
extern long getdelim(char * * restrict __lineptr, unsigned long * restrict __n, int __delimiter, struct _IO_FILE * restrict __stream);
extern long getline(char * * restrict __lineptr, unsigned long * restrict __n, struct _IO_FILE * restrict __stream);
extern int fputs(char const * restrict __s, struct _IO_FILE * restrict __stream);
extern int puts(char const * __s);
extern int ungetc(int __c, struct _IO_FILE * __stream);
extern unsigned long fread(void * restrict __ptr, unsigned long __size, unsigned long __n, struct _IO_FILE * restrict __stream);
extern unsigned long fwrite(void const * restrict __ptr, unsigned long __size, unsigned long __n, struct _IO_FILE * restrict __s);
extern unsigned long fread_unlocked(void * restrict __ptr, unsigned long __size, unsigned long __n, struct _IO_FILE * restrict __stream);
extern unsigned long fwrite_unlocked(void const * restrict __ptr, unsigned long __size, unsigned long __n, struct _IO_FILE * restrict __stream);
extern int fseek(struct _IO_FILE * __stream, long __off, int __whence);
extern long ftell(struct _IO_FILE * __stream);
extern void rewind(struct _IO_FILE * __stream);
extern int fseeko(struct _IO_FILE * __stream, long __off, int __whence);
extern long ftello(struct _IO_FILE * __stream);
extern int fgetpos(struct _IO_FILE * restrict __stream, struct anon_type_4__G_fpos_t * restrict __pos);
extern int fsetpos(struct _IO_FILE * __stream, struct anon_type_4__G_fpos_t const * __pos);
extern __attribute__((nothrow)) void clearerr(struct _IO_FILE * __stream);
extern __attribute__((nothrow)) int feof(struct _IO_FILE * __stream);
extern __attribute__((nothrow)) int ferror(struct _IO_FILE * __stream);
extern __attribute__((nothrow)) void clearerr_unlocked(struct _IO_FILE * __stream);
extern __attribute__((nothrow)) int feof_unlocked(struct _IO_FILE * __stream);
extern __attribute__((nothrow)) int ferror_unlocked(struct _IO_FILE * __stream);
extern void perror(char const * __s);
# 27 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h"
extern int sys_nerr;
# 28 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h"
extern char const * const sys_errlist[];
extern __attribute__((nothrow)) int fileno(struct _IO_FILE * __stream);
extern __attribute__((nothrow)) int fileno_unlocked(struct _IO_FILE * __stream);
extern struct _IO_FILE * popen(char const * __command, char const * __modes);
extern int pclose(struct _IO_FILE * __stream);
extern __attribute__((nothrow)) char * ctermid(char * __s);
extern __attribute__((nothrow)) void flockfile(struct _IO_FILE * __stream);
extern __attribute__((nothrow)) int ftrylockfile(struct _IO_FILE * __stream);
extern __attribute__((nothrow)) void funlockfile(struct _IO_FILE * __stream);
# 3 "test.c"
# /* ignored Xcode.XMP_PRAGMA */
# 4 "test.c"
# /* ignored Xcode.XMP_PRAGMA */
# 5 "test.c"
# /* ignored Xcode.XMP_PRAGMA */
# /* array 'a' is removed by XcalableMP align directive */
# 7 "test.c"
# /* ignored Xcode.XMP_PRAGMA */
int main(void)
{
{
# 10 "test.c"
int i;
{
int _XMP_loop_init_i;
int _XMP_loop_cond_i;
int _XMP_loop_step_i;
_XMP_sched_loop_template_BLOCK(0, 10, 1, &(_XMP_loop_init_i), &(_XMP_loop_cond_i), &(_XMP_loop_step_i), _XMP_DESC_t, 0);
# 13 "test.c"
for(i = _XMP_loop_init_i; i < _XMP_loop_cond_i; i += _XMP_loop_step_i) {
# 14 "test.c"
(*(_XMP_M_GET_ADDR_E_1(_XMP_ADDR_a, i))) = (_XMP_M_LTOG_TEMPLATE_BLOCK(i, 0, 10, _XMP_NODES_SIZE_p, _XMP_NODES_RANK_p_0));
}
}
{
int _XMP_loop_init_i;
int _XMP_loop_cond_i;
int _XMP_loop_step_i;
_XMP_sched_loop_template_BLOCK(0, 10, 1, &(_XMP_loop_init_i), &(_XMP_loop_cond_i), &(_XMP_loop_step_i), _XMP_DESC_t, 0);
# 17 "test.c"
for(i = _XMP_loop_init_i; i < _XMP_loop_cond_i; i += _XMP_loop_step_i) {
# 18 "test.c"
printf("%d %d\n", xmp_node_num(), *(_XMP_M_GET_ADDR_E_1(_XMP_ADDR_a, i)));
}
}
# 20 "test.c"
return 0;
}
}
static void __attribute__((constructor)) _XMP_constructor(int argc, char * * argv)
{
_XMP_init(argc, argv);
_XMP_init_nodes_DYNAMIC_GLOBAL(&(_XMP_DESC_p), 1, (int * )(&(_XMP_NODES_SIZE_p)), (int * )(&(_XMP_NODES_RANK_p_0)));
_XMP_init_template_FIXED(&(_XMP_DESC_t), 1, (long long)(0), (long long)(9));
_XMP_init_template_chunk(_XMP_DESC_t, _XMP_DESC_p);
_XMP_dist_template_BLOCK(_XMP_DESC_t, 0, 0);
_XMP_init_array_desc(&(_XMP_DESC_a), _XMP_DESC_t, 1, 507, sizeof(int), (int)(0x00000000all));
_XMP_align_array_BLOCK(_XMP_DESC_a, 0, 0, 0, &(_XMP_GTOL_temp0_a_0));
_XMP_init_array_comm(_XMP_DESC_a, 0);
_XMP_init_array_nodes(_XMP_DESC_a);
_XMP_alloc_array((void * * )(&(_XMP_ADDR_a)), _XMP_DESC_a, (unsigned long long * )(&(_XMP_GTOL_acc_a_0)));
}
static void __attribute__((destructor)) _XMP_destructor()
{
_XMP_finalize();
}