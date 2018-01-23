#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int N = 1024;
int finp, fout;
char buf[1024];

void check (int size, char * input, char * output) {

    if (size != 3) {
        perror("Invalid input value");
        finish ();
    }

    if (output == input) {
        perror("Invalid address");
        finish ();
    }

    finp = open (input, O_RDONLY);
    if (finp == -1) {
        perror("Error input address");
        finish ();
    }

    fout = open(output, O_RDWR | O_CREAT
            , S_IRUSR | S_IWUSR | S_IXUSR
            | S_IRGRP | S_IWGRP | S_IXGRP
            | S_IROTH | S_IWOTH | S_IXOTH);

    if (fout == -1) {
        perror("Error output address");
        finish ();
    }
}

void finish () {
    close(finp);
    close(fout);
    exit(0);
}

int main (int argc, char* argv[]) {

    check(argc, argv[1], argv[2]);

    int fd1, fd2;
    while (1) {
        fd1 = read (finp, &buf, N);
        if (fd1 == -1) {
            perror("Error with input file");
            finish ();
        }

        lseek(fd2, N, SEEK_CUR);

        fd2 = write (fout, &buf, fd1);
        if (fd2 == -1) {
            perror("Error with output file");
            finish ();
        }
    }

    finish ();
}
