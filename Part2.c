#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <math.h>
void yes() { write(1, "Yes\n", 5); }
void no() { write(1, "No\n", 4); }
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        write(1, "ERROR: Wrong usage.\nCorrect usage: ./a.out newfile oldfile directory\n", 70);
        exit(1);
    }
    struct stat buffer;
    if (stat(argv[3], &buffer) == 0 && S_ISDIR(buffer.st_mode)) yes();  else no();
    write(1, "Whether file contents are reversed in newfile: ", 48);
    int oldfile = open(argv[1], O_RDONLY | __O_LARGEFILE);
    int newfile = open(argv[2], O_RDONLY | __O_LARGEFILE);
    if (oldfile < 0 || newfile < 0)
        write(1, "Files do not exist\n", 20);
    else
    {
        off_t old_fileLength = lseek(oldfile, 0, SEEK_END);
        off_t new_fileLength = lseek(newfile, 0, SEEK_END);
        if (old_fileLength != new_fileLength) no();	else
        {
            int reversed = 1;
            int chunk = (old_fileLength / 1000 == 0) ? 1 : pow(2, (int)(log((double)(old_fileLength / 1000)) / log(2.0)));
            int start = ((old_fileLength - 1) / chunk) * chunk;
            int cur_chunk = old_fileLength - start;
            char *new_c, *old_c;
            old_c = (char *)malloc(chunk);
            new_c = (char *)malloc(chunk);
            lseek(newfile, 0, SEEK_SET);
            while (start >= 0)
            {
                lseek(oldfile, start, SEEK_SET);
                read(oldfile, old_c, cur_chunk);
                read(newfile, new_c, cur_chunk);
                for (int begin = 0, end = cur_chunk - 1; begin < cur_chunk && end>=0; begin++, end--)
                    if (new_c[begin] != old_c[end])
                    {
                        reversed = 0;
                        break;
                    }
                if (reversed == 0)
                    break;
                start = lseek(oldfile, 0, SEEK_CUR) - chunk - cur_chunk;
                cur_chunk = chunk;
            }
            if (reversed == 1) yes();   else no();
        }
    }
    close(oldfile);
    close(newfile);
    write(1, "newfile is created: ", 21);
    if (stat(argv[2], &buffer) != 0) no();
    else
    {
        yes();
        write(1, "User has read permissions on newfile: ", 39);
        if (buffer.st_mode & S_IRUSR) yes();    else no();
        write(1, "User has write permission on newfile: ", 39);
        if (buffer.st_mode & S_IWUSR) yes();    else no();
        write(1, "User has execute permission on newfile: ", 41);
        if (buffer.st_mode & S_IXUSR) yes();	else no();
        write(1, "Group has read permissions on newfile: ", 39);
        if (buffer.st_mode & S_IRGRP) yes();	else no();
        write(1, "Group has write permission on newfile: ", 39);
        if (buffer.st_mode & S_IWGRP) yes();	else no();
        write(1, "Group has execute permission on newfile: ", 41);
        if (buffer.st_mode & S_IXGRP) yes();	else no();
        write(1, "Others has read permissions on newfile: ", 39);
        if (buffer.st_mode & S_IROTH) yes();	else no();
        write(1, "Others has write permission on newfile: ", 39);
        if (buffer.st_mode & S_IWOTH) yes();	else no();
        write(1, "Others has execute permission on newfile: ", 43);
        if (buffer.st_mode & S_IXOTH) yes();	else no();
    }
    write(1, "oldfile is created: ", 21);
    if (stat(argv[1], &buffer) != 0) no();
    else
    {
        yes();
        write(1, "User has read permissions on oldfile: ", 39);
        if (buffer.st_mode & S_IRUSR) yes();	else no();
        write(1, "User has write permission on oldfile: ", 39);
        if (buffer.st_mode & S_IWUSR) yes();	else no();
        write(1, "User has execute permission on oldfile: ", 41);
        if (buffer.st_mode & S_IXUSR) yes();	else no();
        write(1, "Group has read permissions on oldfile: ", 39);
        if (buffer.st_mode & S_IRGRP) yes();	else no();
        write(1, "Group has write permission on oldfile: ", 39);
        if (buffer.st_mode & S_IWGRP) yes();	else no();
        write(1, "Group has execute permission on oldfile: ", 41);
        if (buffer.st_mode & S_IXGRP) yes();	else no();
        write(1, "Others has read permissions on oldfile: ", 39);
        if (buffer.st_mode & S_IROTH) yes();	else no();
        write(1, "Others has write permission on oldfile: ", 39);
        if (buffer.st_mode & S_IWOTH) yes();	else no();
        write(1, "Others has execute permission on oldfile: ", 43);
        if (buffer.st_mode & S_IXOTH) yes();	else no();
    }
    write(1, "Directory is created: ", 23);
    if (stat(argv[3], &buffer) != 0 || !S_ISDIR(buffer.st_mode))
        no();
    else
    {
        yes();
        write(1, "User has read permissions on directory: ", 41);
        if (buffer.st_mode & S_IRUSR) yes();	else no();
        write(1, "User has write permission on directory: ", 41);
        if (buffer.st_mode & S_IWUSR) yes();	else no();
        write(1, "User has execute permission on directory: ", 43);
        if (buffer.st_mode & S_IXUSR) yes();	else no();
        write(1, "Group has read permissions on directory: ", 41);
        if (buffer.st_mode & S_IRGRP) yes();	else no();
        write(1, "Group has write permission on directory: ", 41);
        if (buffer.st_mode & S_IWGRP) yes();	else no();
        write(1, "Group has execute permission on directory: ", 43);
        if (buffer.st_mode & S_IXGRP) yes();	else no();
        write(1, "Others has read permissions on directory: ", 41);
        if (buffer.st_mode & S_IROTH) yes();	else no();
        write(1, "Others has write permission on directory: ", 41);
        if (buffer.st_mode & S_IWOTH) yes();	else no();
        write(1, "Others has execute permission on directory: ", 45);
        if (buffer.st_mode & S_IXOTH) yes();	else no();
    }
    return 0;
}