struct stat;
struct rtcdate;

// system calls
int fork(void);
int exit(int) __attribute__((noreturn));
int wait(int*);
int pipe(int*);
int write(int, const void*, int); 
int read(int, void*, int); 
int close(int);
int kill(int); 
int exec(char*, char**); // TODO: Execute permission
int open(const char*, int); // TODO: rwx
int mknod(const char*, short, short); //TODO: rwx
int unlink(const char*); //TODO: Write permission
int fstat(int fd, struct stat*);
int link(const char*, const char*); //TODO: Write permission
int mkdir(const char*); //TODO: Write permission
int chdir(const char*); //TODO: Read permission
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int ps(void);
int setuid(int);
int getuid(int);

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void fprintf(int, const char*, ...);
void printf(const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
int memcmp(const void *, const void *, uint);
void *memcpy(void *, const void *, uint);

//md5.c
typedef unsigned long int UINT4;
typedef struct {
  UINT4 i[2];
  UINT4 buf[4];
  unsigned char in[64];
  unsigned char digest[16];
} MD5_CTX;

void MD5Init ();
void MD5Update ();
void MD5Final ();
void MD5Get(char*, unsigned int, char*);
