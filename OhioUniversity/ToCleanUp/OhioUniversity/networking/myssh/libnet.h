#ifdef __cplusplus
extern "C" {
#endif

int passiveTCP(char *service, int qlen);
int connectTCP(char *host, char *service);
unsigned short lport(int sockfd);
int passivesock(char *service, char *protocol, int qlen);
int connectsock(char *host, char *service, char *protocol);
void encrypt_data(char*);
void decrypt_data(char*);
void mysshHelp();
void mysshdHelp();


void SysError(char *format, ...);	/* System call failed, fatal */
void Error(char *format, ...);		/* fatal internal error */

#ifdef __cplusplus
}
#endif

