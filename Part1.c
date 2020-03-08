#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <sys/stat.h>
void disp_err(char *s)
{
    write(1, s, strlen(s));
    exit(1);
}
int main(int argc, char *argv[])
{
    if (argc != 2)
        disp_err("Invalid usage\n");
    int source_file = open(argv[1], O_RDONLY | __O_LARGEFILE);
    if (source_file < 0)
        disp_err("File error\n");
    off_t tot = lseek(source_file, 0, SEEK_END);
    mkdir("Assignment", 0700);
    char output_path[1000000] = {0};
    strcat(output_path, "Assignment/");
    strcat(output_path, argv[1]);
    int dest_file = open(output_path, O_CREAT | O_RDWR | __O_LARGEFILE | O_TRUNC, 0600);
    if (dest_file < 0)
        disp_err("File error\n");
    int chunk = (tot / 1000 == 0) ? 1 : pow(2, (int)(log(tot / 1000.0) / log(2.0)));
    char *c, *r;
    c = (char *)malloc(chunk);
    r = (char *)malloc(chunk);
    int start = ((tot - 1) / chunk) * chunk;
    int cur_chunk = tot - start;
    lseek(dest_file, 0, SEEK_SET);
    lseek(source_file, start, SEEK_SET);
    int readbytes = 0;
    while (start >= 0)
    {
        lseek(source_file, start, SEEK_SET);
        read(source_file, c, cur_chunk);
        for (int begin = 0, end = cur_chunk - 1; begin < cur_chunk; begin++, end--)
            r[begin] = c[end];
        write(dest_file, r, cur_chunk);
        readbytes += cur_chunk;
        char buf[50] = {0};
        sprintf(buf, "\r %.4f", (float)readbytes / tot * 100.0);
        write(1, buf, 14);
        start = lseek(source_file, 0, SEEK_CUR) - chunk - cur_chunk;
        cur_chunk = chunk;
    }
    write(1, "\r 100.000    ", 14);
    close(source_file);
    close(dest_file);
}
