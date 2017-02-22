/*
 * Emmanuel A. Castillo
 * 004268444
 * Operating Systems
 * Programming Assignment 1:
 * -----------------------------------------------------
 * Develop a program that will use system calls to copy
 * one file to another file.
 *
 */
#include <fcntl.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/stat.h> 
#define REQ_ARGS 3 // Required number of program arguments 
#define SRC_FILE_IDX 1 // Source file argument index 
#define DST_FILE_IDX 2 // Destination file argument index define 
#BUFF_SIZE 256
void error(const char *errorMsg) {
   perror(errorMsg);
   exit(EXIT_FAILURE);
}
int main(int argc, char *argv[]) {
   char *srcFile, *dstFile, fileBuffer[BUFF_SIZE];
   int srcFileDesc, dstFileDesc;
   size_t srcReadBytes, dstReadBytes, dstWriteBytes, srcCloseStatus, 
dstCloseStatus;
   // Verifies the correct number of arguments are provided
   if (argc != REQ_ARGS)
      error("Please provide a source and destination file path as 
arguments.\n");
   srcFile = argv[SRC_FILE_IDX];
   srcFileDesc = open(srcFile, O_RDONLY);
   printf("Src file desc: %u\n", srcFileDesc);
   if (srcFileDesc < 0)
      error(strcat("Error opening file: ", srcFile));
   dstFile = argv[DST_FILE_IDX];
   // Either overwrites and creates an output file with read and write 
access.
   dstFileDesc = open(dstFile, O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, 
S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
   printf("Dst file desc: %u\n", dstFileDesc);
   // Validates that the output file open (or create) successfully
   if (dstFileDesc < 0)
      error(strcat("Error opening file: ", dstFile));
   // Reads source file bytes and writes to destination file.
   while ((srcReadBytes = read(srcFileDesc, fileBuffer, BUFF_SIZE)) > 0)
   {
      // Verifies the read operation was successful
      if (srcReadBytes < 0)
         error(strcat("Error reading file: ", srcFile));
      printf("Src read bytes: %u\n", srcReadBytes);
      dstWriteBytes = write(dstFileDesc, fileBuffer, srcReadBytes);
      // Verifies the write operation was successful
      if (dstWriteBytes < 0)
         error(strcat("Error writing to file: ", dstFile));
      printf("Dst write bytes: %u\n", dstWriteBytes);
   }
   // Closes both source and destination file for proper use later.
   srcCloseStatus = close(srcFileDesc);
   printf("Src close status: %u\n", srcCloseStatus);
   dstCloseStatus = close(dstFileDesc);
   printf("Dst close status: %u\n", dstCloseStatus);
   // Verifies the close operations were successful
   if (srcCloseStatus != 0)
      error(strcat("Error closing file: ", srcFile));
   if (dstCloseStatus != 0)
      error(strcat("Error closing file: ", dstFile));
   return(EXIT_SUCCESS);
}
/* STRACE OUTPUT */
//execve("./filecpy", ["./filecpy", "read.txt", "write.txt"], [/* 39 
vars */]) = 0
//brk(0) = 0x85e6000
//mmap2(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 
-1, 0) = 0xb7
//fd4000
//access("/etc/ld.so.preload", R_OK) = -1 ENOENT(No such file or 
directory)
//open("/opt/rh/devtoolset-1.1/root/usr/lib/tls/i686/sse2/libc.so.6", 
O_RDONLY) =
//-1 ENOENT(No such file or directory)
//stat64("/opt/rh/devtoolset-1.1/root/usr/lib/tls/i686/sse2", 
0xbf90d20c) = -1 ENO
//ENT(No such file or directory)
//open("/opt/rh/devtoolset-1.1/root/usr/lib/tls/i686/libc.so.6", 
O_RDONLY) = -1 EN
//OENT(No such file or directory)
//stat64("/opt/rh/devtoolset-1.1/root/usr/lib/tls/i686", 0xbf90d20c) = 
-1 ENOENT(
//   No such file or directory)
//   open("/opt/rh/devtoolset-1.1/root/usr/lib/tls/sse2/libc.so.6", 
O_RDONLY) = -1 EN
//   OENT(No such file or directory)
//   stat64("/opt/rh/devtoolset-1.1/root/usr/lib/tls/sse2", 0xbf90d20c) 
= -1 ENOENT(
//      No such file or directory)
//   open("/opt/rh/devtoolset-1.1/root/usr/lib/tls/libc.so.6", O_RDONLY) 
= -1 ENOENT
//   (No such file or directory)
//   stat64("/opt/rh/devtoolset-1.1/root/usr/lib/tls", { st_mode = 
S_IFDIR | 0755, st_size
//      = 4096, ... }) = 0
//   open("/opt/rh/devtoolset-1.1/root/usr/lib/i686/sse2/libc.so.6", 
O_RDONLY) = -1 E
//   NOENT(No such file or directory)
//   stat64("/opt/rh/devtoolset-1.1/root/usr/lib/i686/sse2", 0xbf90d20c) 
= -1 ENOENT
//   (No such file or directory)
//   open("/opt/rh/devtoolset-1.1/root/usr/lib/i686/libc.so.6", 
O_RDONLY) = -1 ENOENT
//   (No such file or directory)
//   stat64("/opt/rh/devtoolset-1.1/root/usr/lib/i686", 0xbf90d20c) = -1 
ENOENT(No s
//      uch file or directory)
//   open("/opt/rh/devtoolset-1.1/root/usr/lib/sse2/libc.so.6", 
O_RDONLY) = -1 ENOENT
//   (No such file or directory)
//   stat64("/opt/rh/devtoolset-1.1/root/usr/lib/sse2", { st_mode = 
S_IFDIR | 0755, st_siz
//      e = 4096, ... }) = 0
//   open("/opt/rh/devtoolset-1.1/root/usr/lib/libc.so.6", O_RDONLY) = 
-1 ENOENT(No
//      such file or directory)
//   stat64("/opt/rh/devtoolset-1.1/root/usr/lib", { st_mode = S_IFDIR | 
0755, st_size = 409
//      6, ... }) = 0
//   open("/etc/ld.so.cache", O_RDONLY) = 3
//   fstat64(3, { st_mode = S_IFREG | 0644, st_size = 106412, ... }) = 0
//   mmap2(NULL, 106412, PROT_READ, MAP_PRIVATE, 3, 0) = 0xb7fba000
//   close(3) = 0
//   open("/lib/libc.so.6", O_RDONLY) = 3
//   read(3, "\177ELF\1\1\1\0\0\0\0\0\0\0\0\0\3\0\3\0\1\0\0\0 
\260[\0004\0\0\0"..., 5
//      12) = 512
//   fstat64(3, { st_mode = S_IFREG | 0755, st_size = 1706204, ... }) = 
0
//   mmap2(0x5a5000, 1422788, PROT_READ | PROT_EXEC, MAP_PRIVATE | 
MAP_DENYWRITE, 3, 0) =
//   0x5a5000
//   mmap2(0x6fb000, 12288, PROT_READ | PROT_WRITE, MAP_PRIVATE | 
MAP_FIXED | MAP_DENYWRITE
//      , 3, 0x156) = 0x6fb000
//   mmap2(0x6fe000, 9668, PROT_READ | PROT_WRITE, MAP_PRIVATE | 
MAP_FIXED | MAP_ANONYMOUS,
//      -1, 0) = 0x6fe000
//   close(3) = 0
//   mmap2(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | 
MAP_ANONYMOUS, -1, 0) = 0xb7
//   fb9000
//   set_thread_area({ entry_number:-1 -> 6, base_addr : 0xb7fb96c0, 
limit : 1048575, seg_
//      32bit : 1, contents : 0, read_exec_only : 0, limit_in_pages : 1, 
seg_not_present : 0, usea
//      ble : 1 }) = 0
//   mprotect(0x6fb000, 8192, PROT_READ) = 0
//   mprotect(0x5a1000, 4096, PROT_READ) = 0
//   munmap(0xb7fba000, 106412) = 0
//   open("read.txt", O_RDONLY) = 3
//   fstat64(1, { st_mode = S_IFCHR | 0620, st_rdev = makedev(136, 26), 
... }) = 0
//   mmap2(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | 
MAP_ANONYMOUS, -1, 0) = 0xb7
//   fd3000
//   write(1, "Src file desc: 3\n", 17Src file desc : 3
//   ) = 17
//   open("write.txt", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0666) = 
4
//   write(1, "Dst file desc: 4\n", 17Dst file desc : 4
//   ) = 17
//   read(3, "this is a test yto\nTEST YO\nTEST "..., 256) = 55
//   write(1, "Src read bytes: 55\n", 19Src read bytes : 55
//   ) = 19
//   write(4, "this is a test yto\nTEST YO\nTEST "..., 55) = 55
//   write(1, "Dst write bytes: 55\n", 20Dst write bytes : 55
//   ) = 20
//   read(3, "", 256) = 0
//   close(3) = 0
//   write(1, "Src close status: 0\n", 20Src close status : 0
//   ) = 20
//   close(4) = 0
//   write(1, "Dst close status: 0\n", 20Dst close status : 0
//   ) = 20
//   exit_group(0) = ?
