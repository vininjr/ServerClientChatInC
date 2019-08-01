#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    int socket_desc,i, client_sock, read_size, c;
    struct sockaddr_in server, client;
    unsigned char client_message[2000];
    int length;
    unsigned char server_message[2000];
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket criado");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    if( bind(socket_desc,(struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
    listen(socket_desc, 3);
    puts("Aguardando por conexao...");
    c = sizeof(struct sockaddr_in);
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Conexão aceita");

    while(1)
    {
        if(recv(client_sock, client_message, 2000, 0) < 0){
            puts("recv failed");
            break;
        }
        printf("Mensagem do cliente: ");
        puts(client_message);

        printf("\nEntre com a resposta ao cliente: ");
        gets(server_message);

        if( send(client_sock, server_message, sizeof(server_message),0)  < 0)
        {
            puts("Send failed");
            return 1;
        }

    }

    if(read_size == 0)
    {
        puts("Cliente Disconectou");
        fflush(stdout);
    }

    return 0;
}
