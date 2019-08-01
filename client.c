#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[2000];
    long long int c[50];
    char  server_reply[2000];
    char hash[2000];
    long long int sign[2000];
    int length;
    long long i,j,s,l1;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Erro na criacao do socket");
    }
    puts("Socket criado");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Erro na conexao");
        return 1;
    }

    puts("Conectado\n");
    while(1)
    {
        printf("Entre com a mensagem para o servidor : ");
        gets(message);

        if( send(sock, message, sizeof(message),0)  < 0)
        {
            puts("Send failed");
            return 1;
        }

        if( recv(sock, server_reply, 2000, 0) < 0)
        {
            puts("recv failed");
            break;
        }

        puts("\nResposta do servidor: ");
        puts(server_reply);
    }

    close(sock);
    return 0;
}
