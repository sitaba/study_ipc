
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

//#define PRINT_DEBUG
#ifdef PRINT_DEBUG
#define	print_debug	printf
#else
void print_debug(char *format, ...){};
#endif

#define	PIPE_READ	0
#define	PIPE_WRITE	1

#define	CHILD	0
#define	PAREND	1


int main(int argc, char *argv[])
{
	int pid;
	int pipe_parent2child[2];
	FILE *ifp,  *ofp;
	clock_t begin, end;

	if ((ifp = fopen("random.txt", "r")) == NULL) {
		perror("error: fopen(\"random.txt\", \"r\")");
		exit(1);
	}
	if ((ofp = fopen("receive.txt", "w")) == NULL) {
		perror("error: fopen(\"receive.txt\", \"w\")");
		exit(1);
	}

	if (pipe(pipe_parent2child) == -1) {
		perror("error: pipe(pipe_parent2child)");
		exit(1);
	}


	pid = fork();
	switch( pid ) {
		case -1: //	error
			perror("error: fork()");
			exit(1);

		case 0:	//	child
			close( pipe_parent2child[PIPE_WRITE] );

			int receive;

			begin = clock();
			print_debug("child: start read pipe\n");
			read(pipe_parent2child[PIPE_READ], &receive, 4);
			print_debug("child: end read pipe\n");
			print_debug("child: received parameter '%c'\n", receive);
			while ((int)receive != 1000) {
				fprintf(ofp, "%c", receive);
				print_debug("child: start read pipe\n");
				read(pipe_parent2child[PIPE_READ], &receive, 4);
				print_debug("child: end read pipe\n");
				print_debug("child: received parameter '%d'\n", (int)receive);
			}
			end = clock();
			printf("child: end receiving\n");
			printf("child: receiving time: %f [sec]\n",
					(double)(end-begin)/CLOCKS_PER_SEC);

			fclose(ofp);
			close( pipe_parent2child[PIPE_READ] );
			exit(0);

		default: // parent
			close( pipe_parent2child[PIPE_READ] );

			int send;

			begin = clock();
			while ((send = fgetc(ifp)) != EOF) {
				print_debug("parent: start send pipe\n");
				write(pipe_parent2child[PIPE_WRITE], &send, 4);
				print_debug("parent: end send pipe\n");
				print_debug("parent: sended parameter '%d'\n", send);
				print_debug("\n");
				//sleep(1);
			}
			send = 1000;
			print_debug("parent: start send pipe\n");
			write(pipe_parent2child[PIPE_WRITE], &send, 4);
			print_debug("parent: end send pipe\n");
			print_debug("parent: sended parameter '%d'\n", send);
			end = clock();
			printf("parent: end sending\n");
			printf("parent: receiving time: %f [sec]\n",
					(double)(end-begin)/CLOCKS_PER_SEC);

			fclose(ifp);
			close( pipe_parent2child[PIPE_WRITE] );
			wait(NULL);
			break;
	}

	printf("All is done\n");

	return 0;
}

